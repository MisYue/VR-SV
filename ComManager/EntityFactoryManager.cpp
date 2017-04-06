
#include "../../Public/VRSoft.h"
#include "EntityFactoryManager.h"
#include "EntityManager.h"
#include "EntityFileManager.h"

namespace VR_Soft
{
	CEntityFactoryManager::CEntityFactoryManager(void)
	{
		m_pEntityFileManager = new CEntityFileManager;
		m_pEntityFileManager->LoadEntityFile();
	}


	CEntityFactoryManager::~CEntityFactoryManager(void)
	{
		RemoveAll();

		VRSOFT_DELETE(m_pEntityFileManager);

		m_listEntityTypeUIs.clear();
	}

	// ע�Ṥ��
	void CEntityFactoryManager::RegisterFactory(IEntityBaseFactory* pIEntityFactory)
	{
		VR_MUTEX_AUTO;

		const VRString strName = pIEntityFactory->GetEntiryBaseType();
		// ��ȡ��������
		ListStrEntityBaseFactories::iterator itor = m_factorys.find(strName);
		if (m_factorys.end() != itor)
		{
			return;
		}

		// ��ӽ���
		m_factorys.insert(ListStrEntityBaseFactories::value_type(strName, pIEntityFactory));

		// ֪ͨ������
		for (ListEntityTypeUIs::iterator itor = m_listEntityTypeUIs.begin(); \
			m_listEntityTypeUIs.end() != itor; ++itor)
		{
			(*itor)->UpdateNewItem(pIEntityFactory);
		}
	}

	// ж�ع���
	void CEntityFactoryManager::UnRegisterFactory(const VRString& strFactoryType)
	{
		VR_MUTEX_AUTO;

		// �������еĹ���
		ListStrEntityBaseFactories::iterator itor = m_factorys.find(strFactoryType);
		if (m_factorys.end() == itor)
		{
			return;
		}

		// �Ƴ�����
		CEntityManager* pEntityManager = dynamic_cast<CEntityManager*>(IEntityManager::GetInstancePtr());
		if (NULL != pEntityManager)
		{
			pEntityManager->RemoveFactory(itor->second);
		}

		// �ҵ�������Ӧʵ��, ֱ��ɾ��
		VRSOFT_DELETE(itor->second);
		// �Ƴ�
		m_factorys.erase(itor);
	}

	// �����Ƿ���ڵ�ǰ����
	bool CEntityFactoryManager::IsHave(const VRString& strType) const
	{
		// �������еĹ���
		ListStrEntityBaseFactories::const_iterator cstItor = m_factorys.find(strType);
		if (m_factorys.end() == cstItor)
		{
			return (false);
		}

		return (true);
	}

	// ��ù���ʵ��
	IEntityBaseFactory* CEntityFactoryManager::GetEntityFactory(const VRString& strType) const
	{
		VR_MUTEX_AUTO;

		// �������еĹ���
		ListStrEntityBaseFactories::const_iterator cstItor = m_factorys.find(strType);
		if (m_factorys.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	// ɾ�����й���
	void CEntityFactoryManager::RemoveAll(void)
	{
		VR_MUTEX_AUTO;

		ListStrEntityBaseFactories::iterator itor = m_factorys.begin();
		while (itor != m_factorys.end())
		{
			VRSOFT_DELETE(itor->second);
			++itor;
		}

		m_factorys.clear();
	}

	// ��ù����б�
	const ListString CEntityFactoryManager::GetAllEntityFactory(void) const
	{
// 		ListString listFactories;
// 		ListStrEntityBaseFactories::const_iterator itor = m_factorys.begin();
// 		while (itor != m_factorys.end())
// 		{
// 			listFactories.push_back(itor->second->GetEntiryBaseType());
// 			++itor;
// 		}
// 
// 		// ���ģ�͹���
// 		

		ListString listString = m_pEntityFileManager->GetAllEntityFile();
		// ����ģ��
		return (listString);
	}

	// ��ӹ۲���
	void CEntityFactoryManager::Attach( IEntityTypeUI* pIEntityTypeUI )
	{
		m_listEntityTypeUIs.insert(pIEntityTypeUI);

		pIEntityTypeUI->Init(this);
	}

	// �Ƴ��۲���
	void CEntityFactoryManager::Detach( IEntityTypeUI* pIEntityTypeUI )
	{
		ListEntityTypeUIs::iterator itor = m_listEntityTypeUIs.find(pIEntityTypeUI);
		if (m_listEntityTypeUIs.end() != itor)
		{
			m_listEntityTypeUIs.erase(itor);
		}
	}

}

