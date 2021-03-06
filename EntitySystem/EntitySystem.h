/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  模型管理组件	                                                */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENTITYSYSTEM_H_
#define _ENTITYSYSTEM_H_

// #include "entitysystem_global.h"
#pragma once

namespace VR_Soft
{
	class CEntityFactoryManager;
	class CStrategyManager;

	class CEntitySystem : public IEntityManager
	{
	public:
		explicit CEntitySystem(const VRString& strName);
		virtual ~CEntitySystem();

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);
		// 获得实体管理
		virtual IEntityComposite* GetEntityManagerInstance(void);
		// 获得策略集合
		virtual IStrategyManager* GetStrategyManagerInstance(void);
		// 创建组合节点
		virtual IEntityComposite* CreateEntityComponent(const VRString& strComponentName);
		// 获得属性管理对象
		virtual IAttributeManager* GetAttributeManagerInstance(void);
		// 注册界面
		virtual void RegisterUI(const EntityManager_Typ emt, IPluginUI* pPluginUI);
		// 卸载界面
		virtual void UnRegisterUI(const EntityManager_Typ emt,IPluginUI* pPluginUI);
		// 更新界面
		virtual void UpdateUI(void);
		// 获得属性项UI工厂
		virtual IAttributeUIFactory* GetAttributeUIFactory(void) const;
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		// 消除所有的界面
		void UnRegisterAllUI(void);
		// 注册未添加界面
		void RegisterBeforeAddUI(IPluginUI* pPluginUI);
		// 注册已添加界面
		void RegisterAddedUI(IPluginUI* pPluginUI);
		// 卸载界面
		virtual void UnRegisterAddedUI(IPluginUI* pPluginUI);
		// 卸载界面
		virtual void UnRegisterBeforeAddUI(IPluginUI* pPluginUI);

	private:
		VRString m_strName;
		IEntityComposite* m_pIEntityComposite; // 实体管理对象
		IAttributeManager* m_pIAttributeManager;
		IAttributeUIFactory* m_pIAttributeUiFactory; // 界面工厂
		CStrategyManager* m_pStrategeManager; // 策略集合

	protected:
		typedef std::map<VRString, IPluginUI*> MapStrPluginUI;

	private:
		MapStrPluginUI m_mapStrPluginUI; // 类型界面集合
		MapStrPluginUI m_mapStrPluginUIed; // 界面集合

		VR_AUTO_MUTEX

	};

	// 注册工厂
	REGISTER_COMFACTORY(CEntitySystem, EntityManager, ENTITYSYSTEM_TYPENAME, INSTANCE_NAME_ENTITYSYSTEM, ENTITYSYSTEM_DISC );
}

#endif // _ENTITYSYSTEM_H_
