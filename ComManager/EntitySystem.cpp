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

	// ��ʼ��
	void CEntitySystem::Init(void)
	{
		m_pIEntityComposite = new CEntityManager("EntityRoot");
		m_pIAttributeUiFactory = new CAttributeUIFactory;
		m_pStrategeManager = new CStrategyManager;
		m_pStrategeManager->Init();
	}

	CEntitySystem::~CEntitySystem()
	{
		// ɾ�����е�ʵ��
		if (NULL != m_pIEntityComposite)
		{
			m_pIEntityComposite->RemoveAllEntity();
			VRSOFT_DELETE(m_pIEntityComposite);
		}

		// ɾ�����еĲ���
		if (NULL != m_pStrategeManager)
		{
			m_pStrategeManager->RemoveAllStrategy();
		}

		VRSOFT_DELETE(m_pIAttributeManager);
		
		// ������е�ֵ
		UnRegisterAllUI();
	}


	// ���ʵ�����
	IEntityComposite* CEntitySystem::GetEntityManagerInstance(void)
	{
		return m_pIEntityComposite;
	}

	// ��ò��Լ���
	IStrategyManager* CEntitySystem::GetStrategyManagerInstance(void)
	{
		return (m_pStrategeManager);
	}

	// ������Ͻڵ�
	IEntityComposite* CEntitySystem::CreateEntityComponent(const VRString& strComponentName)
	{
		IEntityComposite* pIEntityComposite = new CEntityManager(strComponentName);
		if (NULL == pIEntityComposite)
		{
			IComManager::GetInstance().WriteLogMsg("����ʵ������Ŀ¼ʧ��");
			VRSOFT_DELETE(pIEntityComposite);
			return (NULL);
		}
		
		return (pIEntityComposite);
	}

	// ������Թ������
	IAttributeManager* CEntitySystem::GetAttributeManagerInstance(void)
	{
		// Ϊ��ӵ�ʵ��
		if (NULL == m_pIAttributeManager)
		{
			VR_MUTEX_AUTO;
			if (NULL == m_pIAttributeManager)
			{
				m_pIAttributeManager = new CAttributeManager;
				IComManager::GetInstance().WriteLogMsg("�ɹ��������Թ���");
			}
		}
		return m_pIAttributeManager;
	}

	// ע�����
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

	// ж�ؽ���
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

	// �������еĽ���
	void CEntitySystem::UnRegisterAllUI(void)
	{
		for (MapStrPluginUI::iterator itor = m_mapStrPluginUI.begin(); \
			m_mapStrPluginUI.end() != itor; ++itor)
		{
			itor->second->UnInit();
			itor->second = NULL;
		}

		m_mapStrPluginUI.clear();

		// ɾ������
		for (MapStrPluginUI::iterator itor = m_mapStrPluginUIed.begin(); \
			m_mapStrPluginUIed.end() != itor; ++itor)
		{
			itor->second->UnInit();
			itor->second = NULL;
		}

		m_mapStrPluginUIed.clear();
	}

	// ���½���
	void CEntitySystem::UpdateUI(void)
	{
		// �̰߳�ȫ
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

	// ���������UI����
	IAttributeUIFactory* CEntitySystem::GetAttributeUIFactory(void) const
	{
		return (m_pIAttributeUiFactory);
	}

	// ע��δ��ӽ���
	void CEntitySystem::RegisterBeforeAddUI(IPluginUI* pPluginUI)
	{
		// �����Ƿ���ڵ�ǰ�Ľ���
		MapStrPluginUI::const_iterator cstItor = m_mapStrPluginUI.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUI.end() != cstItor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "�����Ѿ�������");
			return;
		}

		m_mapStrPluginUI[pPluginUI->GetUIName()] = pPluginUI;

		IEntityComponent* pIEntityComponent = GetEntityManagerInstance();
		// ��ʼ������
		pPluginUI->InitUI(pIEntityComponent);
	}

	// ע������ӽ���
	void CEntitySystem::RegisterAddedUI(IPluginUI* pPluginUI)
	{
		// �����Ƿ���ڵ�ǰ�Ľ���
		MapStrPluginUI::const_iterator cstItor = m_mapStrPluginUIed.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUIed.end() != cstItor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "�����Ѿ�������");
			return;
		}

		m_mapStrPluginUIed[pPluginUI->GetUIName()] = pPluginUI;

		IEntityComponent* pIEntityComponent = GetEntityManagerInstance();
		// ��ʼ������
		pPluginUI->InitUI(pIEntityComponent);
	}

	// ж�ؽ���
	void CEntitySystem::UnRegisterAddedUI(IPluginUI* pPluginUI)
	{
		// �����Ƿ����
		// �����Ƿ���ڵ�ǰ�Ľ���
		MapStrPluginUI::iterator itor = m_mapStrPluginUIed.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUIed.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "������");
			return;
		}

		itor->second = NULL;
		// ɾ��
		m_mapStrPluginUIed.erase(itor);
	}

	// ж�ؽ���
	void CEntitySystem::UnRegisterBeforeAddUI(IPluginUI* pPluginUI)
	{
		// �����Ƿ����
		// �����Ƿ���ڵ�ǰ�Ľ���
		MapStrPluginUI::iterator itor = m_mapStrPluginUI.find(pPluginUI->GetUIName());
		if (m_mapStrPluginUI.end() == itor)
		{
			IComManager::GetInstance().WriteLogMsg(pPluginUI->GetUIName() + "������");
			return;
		}

		itor->second = NULL;
		// ɾ��
		m_mapStrPluginUI.erase(itor);
	}
}
