#include <memory>
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "MemEngineConfig.h"
#include "MemorySystem.h"
#include "RFMMemEngine.h"
#include "MemoryEngine.h"

using namespace boost::interprocess;

namespace VR_Soft
{
//	const size_t CMD_TOTAL_LEN  = 1024 * 48;
	// 构造函数
	CMemoryEngine::CMemoryEngine(void)
		:m_nStartData(1024 * 6),
		m_nCount(0),
		m_nOffset(0)
	{
		m_nCount = ((CMemorySystem*)(IMemoryManager::GetInstancePtr(\
			)))->GetConfig()->GetMenCount();
		m_nOffset =  ((CMemorySystem*)(IMemoryManager::GetInstancePtr(\
			)))->GetConfig()->GetStartAddr();
		m_nStartData =  ((CMemorySystem*)(IMemoryManager::GetInstancePtr(\
			)))->GetConfig()->GetStructCount();

		// 设置数据偏移量
		m_nCurPos = m_nStartData + sizeof(size_t);

		m_pRFMMenEgn = new CRFMMemEngine;
		// 打开设备
		m_pRFMMenEgn->Open();

		m_pszTemp = new char[m_nCount];

		try
		{
			// 打开内存共享内存块空间
			m_pShardMemObj = new boost::interprocess::shared_memory_object (boost::interprocess::open_only,\
				"VRSim_EGSM", boost::interprocess::read_write);
			offset_t memSize = 0;
			m_pShardMemObj->get_size(memSize);
			if (memSize < m_nCount)
			{
				m_pShardMemObj->truncate(m_nCount);
			}

			// 创建映射区
			m_pMapRegion = new boost::interprocess::mapped_region(*m_pShardMemObj, boost::interprocess::read_write);
			m_szMemSart = static_cast<char*>(m_pMapRegion->get_address());
		}
		catch (...)
		{
			// 抛出异常 说明内存未被创建 则直接创建内存
			m_pShardMemObj = new boost::interprocess::shared_memory_object (boost::interprocess::create_only,\
				"VRSim_EGSM", boost::interprocess::read_write);

			m_pShardMemObj->truncate(m_nCount);

			// 创建映射区
			m_pMapRegion = new boost::interprocess::mapped_region(*m_pShardMemObj, boost::interprocess::read_write);
			m_szMemSart = static_cast<char*>(m_pMapRegion->get_address());	
		}

		// 获得
		int nSize = 0;
		//Write(&nSize, 38, sizeof(int));
		Read(&nSize, 38, sizeof(int));
		if (nSize <= 0)
		{
			int nDataSize = m_nStartData - 42;
			char* pszTempData = new char[nDataSize];
			memset(pszTempData, 0, nDataSize);
			m_pRFMMenEgn->Write(pszTempData, 42, nDataSize);
			nSize = 0;
			// 写入偏移量
			SetCurOffset(m_nCurPos);
		}

		++nSize;
		Write(&nSize, 38, sizeof(int));


		//memset(m_szMemSart, 0, m_nStartData);
		
		// 从内存中更新偏移量的值
		GetCurOffset();

	
	}

	// 析构函数
	CMemoryEngine::~CMemoryEngine(void)
	{
		// 初始化内存快的值
		//memset(m_szMemSart, 0, CMD_TOTAL_LEN);

		int nSize = 0;
		Read(&nSize, 38, sizeof(int));
		--nSize;
		Write(&nSize, 38, sizeof(int));
		// 移除内存共享机制
		boost::interprocess::shared_memory_object::remove("VRSim_EGSM");

		VRSOFT_DELETE_ARRAY(m_pszTemp);

		VRSOFT_DELETE(m_pMapRegion);
		VRSOFT_DELETE(m_pShardMemObj);
		VRSOFT_DELETE(m_pRFMMenEgn);
	}

	
	bool CMemoryEngine::Write(void* src, size_t offset, size_t count)
	{
		// 断言
		assert(src);
		assert(offset>=0);
		assert(count>0);

		// 写入内存中
		memcpy((void*)(m_szMemSart + offset), src, count);

		// 写到内存反射卡
		m_pRFMMenEgn->Write(src, m_nOffset + offset , count);

		return (true);
	}

	// 读出内存
	bool CMemoryEngine::Read(void* dst, size_t offset, size_t count) const
	{
		// 断言
		assert(dst);
		assert(offset>=0);
		assert(count>0);

		// 从板卡中读取
	/*	memset(m_pszTemp, 0, m_nCount);
		if (m_pRFMMenEgn->Read(m_pszTemp, m_nOffset, m_nCount))
		{
			memcpy(m_szMemSart, m_pszTemp, m_nCount);
		}*/

		// 全部从板卡中读取速度太慢 只能读出当前需要的内存空间 进行空间本地更新
		if (m_pRFMMenEgn->Read(dst, m_nOffset + offset, count))
		{
			// memcpy(m_szMemSart, m_pszTemp, m_nCount);

			// 更新本地一小块内存 
			// 写入内存中
			memcpy((void*)(m_szMemSart + offset), dst, count);

			
		}
		else
		{
			// 从内存反射卡中失败 直接读取本地缓存内存
			memcpy(dst, (void*)(m_szMemSart + offset), count);
		}

		return (true);
	}

	// 获得板卡指针对象
	CRFMMemEngine* CMemoryEngine::GetRFMMemEngine( void ) const
	{
		return (m_pRFMMenEgn);
	}

	// 获得偏移位置
	size_t CMemoryEngine::GetCurOffset( void ) const
	{
		// 从内存中读取
		Read((void*)&m_nCurPos, m_nStartData + 1, sizeof(size_t));
		return (m_nCurPos);
	}

	// 设置偏移位置
	void CMemoryEngine::SetCurOffset( const size_t offset )
	{
		// 写入内存中
		m_nCurPos = offset;
		Write((void*)&m_nCurPos, m_nStartData + 1, sizeof(size_t));
	}

	// 初始化引擎
	void CMemoryEngine::InitEngine( void )
	{
		int nSize = 0;
		Write(&nSize, 38, sizeof(int));

		int nDataSize = m_nStartData - 42;
		char* pszTempData = new char[nDataSize];
		memset(pszTempData, 0, nDataSize);
		m_pRFMMenEgn->Write(pszTempData, 42, nDataSize);
		nSize = 0;
		// 写入偏移量
		SetCurOffset(m_nCurPos);
	}

}