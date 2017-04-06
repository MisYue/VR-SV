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

		// ���ڴ��ж�ȡƫ����
		size_t nSize = 0;
		m_pMemEng->Read((void*)&nSize, m_nStartPos, sizeof(size_t));

		if (0 == nSize)
		{
			// ��һ�θմ����õ��ڴ�
			m_nCurPos = m_nStartPos + (sizeof(int) +( sizeof(size_t) << 1));
			// д���ڴ���
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

	// ����ڴ�ƫ����
	MemModel CMemMap::GetOffset(const uint64_t ID, const VRString& strName ) const
	{
		// ����ӳ���
		UpdateMemMap(ID);

		// �Ƿ��Ѿ�����
		ListAttributeMem::const_iterator cstItor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() != cstItor)
		{
			const CMemObj& memObj = cstItor->second.GetMenObj(strName);
			return (MemModel(memObj.GetOffset(), memObj.GetCount()));
		}

		return (MemModel(-1, -1));
	}

	// ���µ�ǰ��ӳ���
	void CMemMap::UpdateMemMap(const uint64_t ID) const
	{
		UpdateAllMemMap(ID);

		return;

		// �������� �ٽ��д����޸�ID����� ���ζԸ���������д��� time 2015-12-08
		// �����Ƿ��е�ǰ��ID
		ListAttributeMem::iterator itor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() == itor)
		{
			return;
		}

		// ���������
		CAttributeMem& attrMem = itor->second;

		// ��ô�С
		char* pszData = new char[attrMem.GetSize()];
		memset(pszData, 0, (int)attrMem.GetSize());
		m_pMemEng->Read(pszData, attrMem.GetOffset(), attrMem.GetSize());
		attrMem.SetData(pszData);
		VRSOFT_DELETE_ARRAY(pszData);

		// ������� ����״̬
	//	m_bUpdate = false;
	}

	// ���µ�ǰ������ڴ���
	void CMemMap::UpdateMemMapToMem(const uint64_t ID) const
	{
		VR_MUTEX_AUTO

		// �����Ƿ��е�ǰ��ID
		ListAttributeMem::const_iterator cstItor = m_lstMemMap.find(ID);
		if (m_lstMemMap.end() == cstItor)
		{
			return;
		}

		// ���������
		const CAttributeMem& attrMem = cstItor->second;
		
	}

	// �����ڴ�ӳ���
	bool CMemMap::UpdateMemTab( const uint64_t oldID, const uint64_t newID , IEntityBase* pIEntity)
	{
		// д���־λ
		char szFlage = 1;
		m_pMemEng->Write(&szFlage, m_nFlag, (sizeof(char)));

	//	m_bUpdate = true;
		// ����ӳ���
		UpdateAllMemMap(oldID);
		//UpdateMemMap(oldID);

		// �����Ƿ��е�ǰ��ID
		ListAttributeMem::iterator itor = m_lstMemMap.find(oldID);
		if (m_lstMemMap.end() == itor)
		{
			// ��ǰӳ����в����� ��ǰ��ID
			GetMapCurOffset();
			CAttributeMem attrMem(m_nCurPos, newID);

			// ��õ�ǰ������ƶ����
			size_t offset = m_pMemEng->GetCurOffset();
			offset = attrMem.SetItem(pIEntity->GetAttribute(), offset);
			m_lstMemMap[newID ] = attrMem;

			// ����ƫ����
			m_nCurPos += attrMem.GetSize();
			SetMapCurOffset();

			// д���ڴ�ֵ
			m_pMemEng->Write(attrMem.GetData(), attrMem.GetOffset(), attrMem.GetSize());

			// �����ڴ�ƫ����
			m_pMemEng->SetCurOffset(offset);

			
			// ���µ�ǰ��ֵ
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

	// �жϵ�ǰ���ڴ�ӳ����Ƿ���Ҫ���¸���
	bool CMemMap::IsUpdateAllMemMap( const uint64_t ID ) const
	{
		// ���ڴ��ж�ȡ����Ϊ
		int nSize = 0;
		m_pMemEng->Read(&nSize,n_nCountPos, sizeof(int));

		const int nCount = m_lstMemMap.size();

		if ((nCount != nSize))
		{
			return (true);
		}

		// ��ñ�־λ
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

	// �������е�ӳ���
	void CMemMap::UpdateAllMemMap( const uint64_t ID ) const
	{
		VR_MUTEX_AUTO

		if (!IsUpdateAllMemMap(ID))
		{
			return ;
		}

		// ��ȡ�ڴ��еĸ���
		int nSize = 0;

		m_pMemEng->Read(&nSize, n_nCountPos, sizeof(int));

		int nSizePos = m_nCurSizePos;
		// ��ȡ����ֵ
		m_pMemEng->Read(&m_nCurCount, m_nCurSizePos, sizeof(int));

		if (0 >= m_nCurCount)
		{
			return;
		}

		// ��������ֵ
		char* pszData = new char[m_nCurCount];
		memset(pszData, 0, m_nCurCount);
		m_pMemEng->Read(pszData, m_nDataPos, m_nCurCount);

		// ��ձ����ڴ�ֵ
		m_lstMemMap.clear();

		int nOffset = 0;

		// �������и��� ����ֱ�Ӹ���
		for (int index = 0; index < nSize; ++index)
		{
			// ��ȡ��һ��ֵ
			int nAttrSize = 0;
			memcpy(&nAttrSize, (void*)(pszData + nOffset), sizeof(int));

			char* pszAttrMemData = new char[nAttrSize];
			memset(pszAttrMemData, 0, nAttrSize);
			memcpy(pszAttrMemData, (void*)(pszData + nOffset), nAttrSize);

			// ��������ֵ
			CAttributeMem attrMem;
			attrMem.SetData(pszAttrMemData);

			m_lstMemMap[attrMem.GetID()] = attrMem;

			nOffset += attrMem.GetSize();

			VRSOFT_DELETE_ARRAY(pszAttrMemData);
		}

		VRSOFT_DELETE_ARRAY(pszData);
	}

	// ��õ�ǰӳ���ƫ����
	size_t CMemMap::GetMapCurOffset( void )
	{
		m_pMemEng->Read((void*)&m_nCurPos, m_nStartPos, sizeof(size_t));
		return (m_nCurPos);
	}

	// ���õ�ǰƫ����
	void CMemMap::SetMapCurOffset( void )
	{
		m_pMemEng->Write((void*)&m_nCurPos, m_nStartPos, sizeof(size_t));
	}

}
