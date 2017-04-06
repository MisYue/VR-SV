#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "EntityFactoryManager.h"

namespace VR_Soft
{
	CEntityFactoryManager::CEntityFactoryManager(void)
	{
	}


	CEntityFactoryManager::~CEntityFactoryManager(void)
	{
		RemoveAll();
	}

	// ע�Ṥ��
	void CEntityFactoryManager::RegisterFactory(IEntityBaseFactory* pIEntityFactory)
	{
		VR_MUTEX_AUTO;

		// ��ȡ��������
		const VRString strType = pIEntityFactory->GetEntiryBaseType();
		bool bHave = IsHave(strType);
		if (bHave)
		{
			return;
		}

		m_factorys.push_back(pIEntityFactory);

		// ���½���
		IEntityManager::GetInstance().UpdateUI();
	}

	// ж�ع���
	void CEntityFactoryManager::UnRegisterFactory(const VRString& strFactoryType)
	{
		VR_MUTEX_AUTO;

		// ��ȡ��������
		bool bHave = IsHave(strFactoryType);
		if (!bHave)
		{
			return;
		}

		// �������еĹ���
		LstFactroys::iterator itor = m_factorys.begin();
		for (; m_factorys.end() != itor; ++itor)
		{
			// ת��ʵ��
			const VRString strFactoryType = (*itor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strFactoryType))
			{
				// �ҵ�������Ӧʵ��, ֱ��ɾ��
				VRSOFT_DELETE(*itor);
				m_factorys.erase(itor);
				break;
			}
		}

		// ���½���
		IEntityManager::GetInstance().UpdateUI();
	}

	// �����Ƿ���ڵ�ǰ����
	bool CEntityFactoryManager::IsHave(const VRString& strType) const
	{
		// �������еĹ���
		LstFactroys::const_iterator cstItor = m_factorys.begin();
		for (; m_factorys.end() != cstItor; ++cstItor)
		{
			// ת��ʵ��
			const VRString strFactoryType = (*cstItor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strType))
			{
				// �ҵ�������Ӧʵ����ֱ�ӷ���
				return (true);
			}
		}

		return (false);
	}

	// ��ù���ʵ��
	IEntityBaseFactory* CEntityFactoryManager::GetEntityFactory(const VRString& strType) const
	{
		VR_MUTEX_AUTO;

		// �������еĹ���
		LstFactroys::const_iterator cstItor = m_factorys.begin();
		for (; m_factorys.end() != cstItor; ++cstItor)
		{
			// ת��ʵ��
			const VRString strFactoryType = (*cstItor)->GetEntiryBaseType();
			if (0 == strFactoryType.compare(strType))
			{
				// �ҵ�������Ӧʵ����ֱ�ӷ���
				return (*cstItor);
			}
		}

		// ���ؿ�ֵ
		return (NULL);
	}

	// ɾ�����й���
	void CEntityFactoryManager::RemoveAll(void)
	{
		VR_MUTEX_AUTO;

		LstFactroys::iterator itor = m_factorys.begin();
		while (itor != m_factorys.end())
		{
			VRSOFT_DELETE(*itor);
			++itor;
		}

		m_factorys.clear();

		// ���½���
		IEntityManager::GetInstance().UpdateUI();
	}

	// ��ù����б�
	const CEntityFactoryManager::LstFactroys& CEntityFactoryManager::GetAllEntityFactory(void) const
	{
		return (m_factorys);
	}
}

