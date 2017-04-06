#define VRSOFT_EXPORT
#include <map>
#include <vector>
#include "../../Public/VRSoft.h"

#include "EntityManager.h"
#include "StrategyManager.h"
#include "AttributeManager.h"
#include "EntityFactoryManager.h"
#include "AttributeUIFactory.h"
#include "StateMachine.h"
#include "EntitySystem.h"

namespace VR_Soft
{
	CEntitySystem::CEntitySystem(void):
		m_pIEntityComposite(NULL),m_pIAttributeManager(NULL)
	{
		Init();
	}

	// 初始化
	void CEntitySystem::Init(void)
	{
		m_pIEntityComposite = new CEntityManager("EntityRoot");
		m_pIAttributeUiFactory = new CAttributeUIFactory;
		m_pStrategeManager = new CStrategyManager;
		m_pStrategeManager->Init();
	}

	CEntitySystem::~CEntitySystem()
	{
		// 删除所有的实体
		if (NULL != m_pIEntityComposite)
		{
			m_pIEntityComposite->RemoveAllEntity();
			VRSOFT_DELETE(m_pIEntityComposite);
		}

		// 删除所有的策略
		if (NULL != m_pStrategeManager)
		{
			m_pStrategeManager->RemoveAllStrategy();
		}

		VRSOFT_DELETE(m_pIAttributeManager);
		
		// 清除所有的值
		UnRegisterAllUI();
	}


	// 获得实体管理
	IEntityComposite* CEntitySystem::GetEntityManagerInstance(void)
	{
		return m_pIEntityComposite;
	}

	// 获得策略集合
	IStrategyManager* CEntitySystem::GetStrategyManagerInstance(void)
	{
		return (m_pStrategeManager);
	}

	// 创建组合节点
	IEntityComposite* CEntitySystem::CreateEntityComponent(const VRString& strComponentName)
	{
		IEntityComposite* pIEntityComposite = new CEntityManager(strComponentName);
		if (NULL == pIEntityComposite)
		{
			IComManager::GetInstance().WriteLogMsg("创建实体管理根目录失败");
			VRSOFT_DELETE(pIEntityComposite);
			return (NULL);
		}
		
		return (pIEntityComposite);
	}

	// 获得属性管理对象
	IAttributeManager* CEntitySystem::GetAttributeManagerInstance(void)
	{
		// 为添加的实体
		if (NULL == m_pIAttributeManager)
		{
			VR_MUTEX_AUTO;
			if (NULL == m_pIAttributeManager)
			{
				m_pIAttributeManager = new CAttributeManager;
				IComManager::GetInstance().WriteLogMsg("成功创建属性管理");
			}
		}
		return m_pIAttributeManager;
	}

	// 注册界面
	void CEntitySystem::RegisterUI(IPluginUI* pPluginUI , const ENU_EntityManager emt)
	{
		if (emt == EMT_ADDED)
		{
			RegisterAddedUI(pPluginUI);
		}
		else
		{
			RegisterBeforeAddUI(pPluginUI);
		}
	}

	// 卸载界面
	void CEntitySystem::UnRegisterUI(IPluginUI* pPluginUI, const ENU_EntityManager emt)
	{
		if (emt == EMT_ADDED)
		{
			RegisterAddedUI(pPluginUI);
		}
		else
		{
			RegisterBeforeAddUI(pPluginUI);
		}
	}

	// 消除所有的界面
	void CEntitySystem::UnRegisterAllUI(void)
	{
		for (MapStrPluginUI::iterator itor = m_mapStrPluginUI.begin(); \
			m_mapStrPluginUI.end() != itor; ++itor)
		{
			itor->second->UnInit();
			itor->second = NULL;
		}

		m_mapStrPluginUI.clear();

		// 删除名称
		for (MapStrPluginUI::iterator itor = m_mapStrPluginUIed.begin(); \
			m_mapStrPluginUIed.end() != itor; ++itor)
		{
			itor->second->UnInit();
			itor->second = NULL;
		}

		m_mapStrPluginUIed.clear();
	}

	// 更新界面
	void CEntitySystem::UpdateUI(void)
	{
		// 线程安全
		VR_MUTEX_AUTO;
		for (MapStrPluginUI::iterator itor = m_mapStrPluginUIed.begin(); \
			m_mapStrPluginUIed.end() != itor; ++itor)
		{
			itor->second->Update(m_pIEntityComposite);
		}

		for (MapStrPluginUI::iterator itor = m_mapStrPluginUI.begin(); \
			m_mapStrPluginUI.end() != itor; ++itor)
		{
			itor->second->Update(m_pIEntityComposite);
		}
	}

	// 获得属性项UI工厂
	IAttributeUIFactory* CEntitySystem::GetAttributeUIFactory(void) const
	{
		return (m_pIAttributeUiFactory);
	}

	// 注册未添加界面
	void CEntitySystem::RegisterBeforeAddUI(IPluginUI* pPluginUI)
	{
		// 查找是否存在当前的界面
		MapStrPluginUI::const_iterator cstItor = m_mapStrPluginUI.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUI.end() != cstItor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "界面已经被加载");
			return;
		}

		m_mapStrPluginUI[pPluginUI->GetUIName()] = pPluginUI;

		IEntityComponent* pIEntityComponent = GetEntityManagerInstance();
		// 初始化界面
		pPluginUI->InitUI(pIEntityComponent);
	}

	// 注册已添加界面
	void CEntitySystem::RegisterAddedUI(IPluginUI* pPluginUI)
	{
		// 查找是否存在当前的界面
		MapStrPluginUI::const_iterator cstItor = m_mapStrPluginUIed.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUIed.end() != cstItor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "界面已经被加载");
			return;
		}

		m_mapStrPluginUIed[pPluginUI->GetUIName()] = pPluginUI;

		IEntityComponent* pIEntityComponent = GetEntityManagerInstance();
		// 初始化界面
		pPluginUI->InitUI(pIEntityComponent);
	}

	// 卸载界面
	void CEntitySystem::UnRegisterAddedUI(IPluginUI* pPluginUI)
	{
		// 查找是否存在
		// 查找是否存在当前的界面
		MapStrPluginUI::iterator itor = m_mapStrPluginUIed.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUIed.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "不存在");
			return;
		}

		itor->second = NULL;
		// 删除
		m_mapStrPluginUIed.erase(itor);
	}

	// 卸载界面
	void CEntitySystem::UnRegisterBeforeAddUI(IPluginUI* pPluginUI)
	{
		// 查找是否存在
		// 查找是否存在当前的界面
		MapStrPluginUI::iterator itor = m_mapStrPluginUI.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUI.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "不存在");
			return;
		}

		itor->second = NULL;
		// 删除
		m_mapStrPluginUI.erase(itor);
	}
}
