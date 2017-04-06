/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ģ�͹������	                                                */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENTITYSYSTEM_H_
#define _ENTITYSYSTEM_H_

// #include "entitysystem_global.h"
#pragma once

namespace VR_Soft
{
	class CEntityFactoryManager;
	class CStrategyManager;
	class CEntityManager;

	class CEntitySystem : public IEntityManager
	{
	public:
		explicit CEntitySystem(void);
		virtual ~CEntitySystem();

	public:
		// ��ʼ��ϵͳ
		virtual void Init(void);
		// ���ʵ�����
		virtual IEntityComposite* GetEntityManagerInstance(void);
		// ��ò��Լ���
		virtual IStrategyManager* GetStrategyManagerInstance(void);
		// ������Ͻڵ�
		virtual IEntityComposite* CreateEntityComponent(const VRString& strComponentName);
		// ������Թ������
		virtual IAttributeManager* GetAttributeManagerInstance(void);
		// ע�����
		virtual void RegisterUI( IPluginUI* pPluginUI, const ENU_EntityManager emt);
		// ж�ؽ���
		virtual void UnRegisterUI(IPluginUI* pPluginUI, const ENU_EntityManager emt);
		// ���½���
		virtual void UpdateUI(void);
		// ���������UI����
		virtual IAttributeUIFactory* GetAttributeUIFactory(void) const;

	protected:
		// �������еĽ���
		void UnRegisterAllUI(void);
		// ע��δ��ӽ���
		void RegisterBeforeAddUI(IPluginUI* pPluginUI);
		// ע������ӽ���
		void RegisterAddedUI(IPluginUI* pPluginUI);
		// ж�ؽ���
		virtual void UnRegisterAddedUI(IPluginUI* pPluginUI);
		// ж�ؽ���
		virtual void UnRegisterBeforeAddUI(IPluginUI* pPluginUI);

	private:
		VRString m_strName;
		CEntityManager* m_pIEntityComposite; // ʵ��������
		IAttributeManager* m_pIAttributeManager;
		IAttributeUIFactory* m_pIAttributeUiFactory; // ���湤��
		CStrategyManager* m_pStrategeManager; // ���Լ���

	protected:
		typedef std::map<VRString, IPluginUI*> MapStrPluginUI;

	private:
		MapStrPluginUI m_mapStrPluginUI; // ���ͽ��漯��
		MapStrPluginUI m_mapStrPluginUIed; // ���漯��

		VR_AUTO_MUTEX

	};
}

#endif // _ENTITYSYSTEM_H_
