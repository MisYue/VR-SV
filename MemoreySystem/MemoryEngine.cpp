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
	// ���캯��
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

		// ��������ƫ����
		m_nCurPos = m_nStartData + sizeof(size_t);

		m_pRFMMenEgn = new CRFMMemEngine;
		// ���豸
		m_pRFMMenEgn->Open();

		m_pszTemp = new char[m_nCount];

		try
		{
			// ���ڴ湲���ڴ��ռ�
			m_pShardMemObj = new boost::interprocess::shared_memory_object (boost::interprocess::open_only,\
				"VRSim_EGSM", boost::interprocess::read_write);
			offset_t memSize = 0;
			m_pShardMemObj->get_size(memSize);
			if (memSize < m_nCount)
			{
				m_pShardMemObj->truncate(m_nCount);
			}

			// ����ӳ����
			m_pMapRegion = new boost::interprocess::mapped_region(*m_pShardMemObj, boost::interprocess::read_write);
			m_szMemSart = static_cast<char*>(m_pMapRegion->get_address());
		}
		catch (...)
		{
			// �׳��쳣 ˵���ڴ�δ������ ��ֱ�Ӵ����ڴ�
			m_pShardMemObj = new boost::interprocess::shared_memory_object (boost::interprocess::create_only,\
				"VRSim_EGSM", boost::interprocess::read_write);

			m_pShardMemObj->truncate(m_nCount);

			// ����ӳ����
			m_pMapRegion = new boost::interprocess::mapped_region(*m_pShardMemObj, boost::interprocess::read_write);
			m_szMemSart = static_cast<char*>(m_pMapRegion->get_address());	
		}

		// ���
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
			// д��ƫ����
			SetCurOffset(m_nCurPos);
		}

		++nSize;
		Write(&nSize, 38, sizeof(int));


		//memset(m_szMemSart, 0, m_nStartData);
		
		// ���ڴ��и���ƫ������ֵ
		GetCurOffset();

	
	}

	// ��������
	CMemoryEngine::~CMemoryEngine(void)
	{
		// ��ʼ���ڴ���ֵ
		//memset(m_szMemSart, 0, CMD_TOTAL_LEN);

		int nSize = 0;
		Read(&nSize, 38, sizeof(int));
		--nSize;
		Write(&nSize, 38, sizeof(int));
		// �Ƴ��ڴ湲�����
		boost::interprocess::shared_memory_object::remove("VRSim_EGSM");

		VRSOFT_DELETE_ARRAY(m_pszTemp);

		VRSOFT_DELETE(m_pMapRegion);
		VRSOFT_DELETE(m_pShardMemObj);
		VRSOFT_DELETE(m_pRFMMenEgn);
	}

	
	bool CMemoryEngine::Write(void* src, size_t offset, size_t count)
	{
		// ����
		assert(src);
		assert(offset>=0);
		assert(count>0);

		// д���ڴ���
		memcpy((void*)(m_szMemSart + offset), src, count);

		// д���ڴ淴�俨
		m_pRFMMenEgn->Write(src, m_nOffset + offset , count);

		return (true);
	}

	// �����ڴ�
	bool CMemoryEngine::Read(void* dst, size_t offset, size_t count) const
	{
		// ����
		assert(dst);
		assert(offset>=0);
		assert(count>0);

		// �Ӱ忨�ж�ȡ
	/*	memset(m_pszTemp, 0, m_nCount);
		if (m_pRFMMenEgn->Read(m_pszTemp, m_nOffset, m_nCount))
		{
			memcpy(m_szMemSart, m_pszTemp, m_nCount);
		}*/

		// ȫ���Ӱ忨�ж�ȡ�ٶ�̫�� ֻ�ܶ�����ǰ��Ҫ���ڴ�ռ� ���пռ䱾�ظ���
		if (m_pRFMMenEgn->Read(dst, m_nOffset + offset, count))
		{
			// memcpy(m_szMemSart, m_pszTemp, m_nCount);

			// ���±���һС���ڴ� 
			// д���ڴ���
			memcpy((void*)(m_szMemSart + offset), dst, count);

			
		}
		else
		{
			// ���ڴ淴�俨��ʧ�� ֱ�Ӷ�ȡ���ػ����ڴ�
			memcpy(dst, (void*)(m_szMemSart + offset), count);
		}

		return (true);
	}

	// ��ð忨ָ�����
	CRFMMemEngine* CMemoryEngine::GetRFMMemEngine( void ) const
	{
		return (m_pRFMMenEgn);
	}

	// ���ƫ��λ��
	size_t CMemoryEngine::GetCurOffset( void ) const
	{
		// ���ڴ��ж�ȡ
		Read((void*)&m_nCurPos, m_nStartData + 1, sizeof(size_t));
		return (m_nCurPos);
	}

	// ����ƫ��λ��
	void CMemoryEngine::SetCurOffset( const size_t offset )
	{
		// д���ڴ���
		m_nCurPos = offset;
		Write((void*)&m_nCurPos, m_nStartData + 1, sizeof(size_t));
	}

	// ��ʼ������
	void CMemoryEngine::InitEngine( void )
	{
		int nSize = 0;
		Write(&nSize, 38, sizeof(int));

		int nDataSize = m_nStartData - 42;
		char* pszTempData = new char[nDataSize];
		memset(pszTempData, 0, nDataSize);
		m_pRFMMenEgn->Write(pszTempData, 42, nDataSize);
		nSize = 0;
		// д��ƫ����
		SetCurOffset(m_nCurPos);
	}

}