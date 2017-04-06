#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"

#ifdef WIN32
#include <Windows.h>
#endif


#include "MemoryEngine.h"
#include "MemEngineConfig.h"
#include "MemorySystem.h"
#include "MemMap.h"

namespace VR_Soft
{
	//const int mdCount = 1024 * 6 - 38;
	CMemMap::CMemMap(CMemoryEngine* pMemEng)
		:m_pMemEng(pMemEng),
		m_nStartPos(43),	
		m_nCurCount(0),
		m_nFlag(42)
	{
		n_nCountPos = m_nStartPos + sizeof(size_t);
		m_nCurSizePos = n_nCountPos + sizeof(size_t);
		m_nDataPos = m_nCurSizePos + sizeof(size_t);

		// 从内存中读取偏移量
		size_t nSize = 0;
		m_pMemEng->Read((void*)&nSize, m_nStartPos, sizeof(size_t));

		if (0 == nSize)
		{
			// 第一次刚创建好的内存
			m_nCurPos = m_nStartPos + (sizeof(int) +( sizeof(size_t) << 1));
			// 写入内存中
			m_pMemEng->Write(&m_nCurPos, m_nStartPos, sizeof(size_t));
		}
		else
		{
			m_nCurPos = nSize;
		}
	}


	CMemMap::~CMemMap(void)
	{
	}

	// 获得内存偏移量
	MemModel CMemMap::GetOffset(const uint64_t ID, const VRString& strName ) const
	{
		// 更新映射表
		UpdateMemMap(ID);

		// 是否已经存在
		ListAttributeMem::const_iterator cstItor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() != cstItor)
		{
			const CMemObj& memObj = cstItor->second.GetMenObj(strName);
			return (MemModel(memObj.GetOffset(), memObj.GetCount()));
		}

		return (MemModel(-1, -1));
	}

	// 更新当前的映射表
	void CMemMap::UpdateMemMap(const uint64_t ID) const
	{
		UpdateAllMemMap(ID);

		return;

		// 后续升级 再进行处理修改ID的情况 本次对该情况不进行处理， time 2015-12-08
		// 查找是否含有当前的ID
		ListAttributeMem::iterator itor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() == itor)
		{
			return;
		}

		// 获得属性项
		CAttributeMem& attrMem = itor->second;

		// 获得大小
		char* pszData = new char[attrMem.GetSize()];
		memset(pszData, 0, (int)attrMem.GetSize());
		m_pMemEng->Read(pszData, attrMem.GetOffset(), attrMem.GetSize());
		attrMem.SetData(pszData);
		VRSOFT_DELETE_ARRAY(pszData);

		// 更新完毕 更改状态
	//	m_bUpdate = false;
	}

	// 更新当前隐射表到内存中
	void CMemMap::UpdateMemMapToMem(const uint64_t ID) const
	{
		VR_MUTEX_AUTO

		// 查找是否含有当前的ID
		ListAttributeMem::const_iterator cstItor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() == cstItor)
		{
			return;
		}

		// 获得属性项
		const CAttributeMem& attrMem = cstItor->second;
		
	}

	// 更新内存映射表
	bool CMemMap::UpdateMemTab( const uint64_t oldID, const uint64_t newID , IEntityBase* pIEntity)
	{
		// 写入标志位
		char szFlage = 1;
		m_pMemEng->Write(&szFlage, m_nFlag, (sizeof(char)));

	//	m_bUpdate = true;
		// 更新映射表
		UpdateAllMemMap(oldID);
		//UpdateMemMap(oldID);

		// 查找是否含有当前的ID
		ListAttributeMem::iterator itor = m_lstMemMap.find(oldID);
		if (m_lstMemMap.end() == itor)
		{
			// 当前映射表中不存在 当前的ID
			GetMapCurOffset();
			CAttributeMem attrMem(m_nCurPos, newID);

			// 获得当前引擎的移动光标
			size_t offset = m_pMemEng->GetCurOffset();
			offset = attrMem.SetItem(pIEntity->GetAttribute(), offset);
			m_lstMemMap[newID ] = attrMem;

			// 更新偏移量
			m_nCurPos += attrMem.GetSize();
			SetMapCurOffset();

			// 写入内存值
			m_pMemEng->Write(attrMem.GetData(), attrMem.GetOffset(), attrMem.GetSize());

			// 更新内存偏移量
			m_pMemEng->SetCurOffset(offset);

			
			// 更新当前的值
			m_nCurCount += attrMem.GetSize();
			m_pMemEng->Write(&m_nCurCount, m_nCurSizePos, (sizeof(int)));
			int nCount = (int)m_lstMemMap.size();
			m_pMemEng->Write(&nCount, n_nCountPos, (sizeof(int)));
		}

		szFlage = 0;
		m_pMemEng->Write(&szFlage, m_nFlag, (sizeof(char)));

//		m_bUpdate = true;

		return (true);
	}

	// 判断当前的内存映射表是否需要重新更新
	bool CMemMap::IsUpdateAllMemMap( const uint64_t ID ) const
	{
		// 从内存中读取数量为
		int nSize = 0;
		m_pMemEng->Read(&nSize,n_nCountPos, sizeof(int));

		const int nCount = m_lstMemMap.size();

		if ((nCount != nSize))
		{
			return (true);
		}

		// 获得标志位
		char szFlage = 0;
		m_pMemEng->Read(&szFlage, m_nFlag, (sizeof(char)));
		if (1 == szFlage)
		{
			ListAttributeMem::const_iterator cstItor = m_lstMemMap.find(ID);
			if (m_lstMemMap.end() == cstItor)
			{
				return (true);
			}
		}
		
		return (false);
	}

	// 更新所有的映射表
	void CMemMap::UpdateAllMemMap( const uint64_t ID ) const
	{
		VR_MUTEX_AUTO

		if (!IsUpdateAllMemMap(ID))
		{
			return ;
		}

		// 读取内存中的个数
		int nSize = 0;

		m_pMemEng->Read(&nSize, n_nCountPos, sizeof(int));

		int nSizePos = m_nCurSizePos;
		// 读取长度值
		m_pMemEng->Read(&m_nCurCount, m_nCurSizePos, sizeof(int));

		if (0 >= m_nCurCount)
		{
			return;
		}

		// 创建缓存值
		char* pszData = new char[m_nCurCount];
		memset(pszData, 0, m_nCurCount);
		m_pMemEng->Read(pszData, m_nDataPos, m_nCurCount);

		// 清空本地内存值
		m_lstMemMap.clear();

		int nOffset = 0;

		// 遍历所有个数 进行直接更新
		for (int index = 0; index < nSize; ++index)
		{
			// 读取第一个值
			int nAttrSize = 0;
			memcpy(&nAttrSize, (void*)(pszData + nOffset), sizeof(int));

			char* pszAttrMemData = new char[nAttrSize];
			memset(pszAttrMemData, 0, nAttrSize);
			memcpy(pszAttrMemData, (void*)(pszData + nOffset), nAttrSize);

			// 创建属性值
			CAttributeMem attrMem;
			attrMem.SetData(pszAttrMemData);

			m_lstMemMap[attrMem.GetID()] = attrMem;

			nOffset += attrMem.GetSize();

			VRSOFT_DELETE_ARRAY(pszAttrMemData);
		}

		VRSOFT_DELETE_ARRAY(pszData);
	}

	// 获得当前映射表偏移量
	size_t CMemMap::GetMapCurOffset( void )
	{
		m_pMemEng->Read((void*)&m_nCurPos, m_nStartPos, sizeof(size_t));
		return (m_nCurPos);
	}

	// 设置当前偏移量
	void CMemMap::SetMapCurOffset( void )
	{
		m_pMemEng->Write((void*)&m_nCurPos, m_nStartPos, sizeof(size_t));
	}

}
