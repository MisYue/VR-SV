
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

	// 注册工厂
	void CEntityFactoryManager::RegisterFactory(IEntityBaseFactory* pIEntityFactory)
	{
		VR_MUTEX_AUTO;

		const VRString strName = pIEntityFactory->GetEntiryBaseType();
		// 获取工厂类型
		ListStrEntityBaseFactories::iterator itor = m_factorys.find(strName);
		if (m_factorys.end() != itor)
		{
			return;
		}

		// 添加进入
		m_factorys.insert(ListStrEntityBaseFactories::value_type(strName, pIEntityFactory));

		// 通知遍历者
		for (ListEntityTypeUIs::iterator itor = m_listEntityTypeUIs.begin(); \
			m_listEntityTypeUIs.end() != itor; ++itor)
		{
			(*itor)->UpdateNewItem(pIEntityFactory);
		}
	}

	// 卸载工厂
	void CEntityFactoryManager::UnRegisterFactory(const VRString& strFactoryType)
	{
		VR_MUTEX_AUTO;

		// 遍历所有的工厂
		ListStrEntityBaseFactories::iterator itor = m_factorys.find(strFactoryType);
		if (m_factorys.end() == itor)
		{
			return;
		}

		// 移除工厂
		CEntityManager* pEntityManager = dynamic_cast<CEntityManager*>(IEntityManager::GetInstancePtr());
		if (NULL != pEntityManager)
		{
			pEntityManager->RemoveFactory(itor->second);
		}

		// 找到工厂对应实例, 直接删除
		VRSOFT_DELETE(itor->second);
		// 移除
		m_factorys.erase(itor);
	}

	// 查找是否存在当前工厂
	bool CEntityFactoryManager::IsHave(const VRString& strType) const
	{
		// 遍历所有的工厂
		ListStrEntityBaseFactories::const_iterator cstItor = m_factorys.find(strType);
		if (m_factorys.end() == cstItor)
		{
			return (false);
		}

		return (true);
	}

	// 获得工厂实例
	IEntityBaseFactory* CEntityFactoryManager::GetEntityFactory(const VRString& strType) const
	{
		VR_MUTEX_AUTO;

		// 遍历所有的工厂
		ListStrEntityBaseFactories::const_iterator cstItor = m_factorys.find(strType);
		if (m_factorys.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	// 删除所有工厂
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

	// 获得工厂列表
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
// 		// 获得模型管理
// 		

		ListString listString = m_pEntityFileManager->GetAllEntityFile();
		// 返回模型
		return (listString);
	}

	// 添加观察者
	void CEntityFactoryManager::Attach( IEntityTypeUI* pIEntityTypeUI )
	{
		m_listEntityTypeUIs.insert(pIEntityTypeUI);

		pIEntityTypeUI->Init(this);
	}

	// 移除观察者
	void CEntityFactoryManager::Detach( IEntityTypeUI* pIEntityTypeUI )
	{
		ListEntityTypeUIs::iterator itor = m_listEntityTypeUIs.find(pIEntityTypeUI);
		if (m_listEntityTypeUIs.end() != itor)
		{
			m_listEntityTypeUIs.erase(itor);
		}
	}

}

