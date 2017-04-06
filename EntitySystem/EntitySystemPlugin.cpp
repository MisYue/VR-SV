#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/EntitySystem/IEntityManager.h"
#include "EntitySystem.h"
#include "EntitySystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Entity System";
	////////////////////////////////////////

	CEntitySystemPlugin::CEntitySystemPlugin(void):m_pIComFactory(NULL)
	{
		
	}


	CEntitySystemPlugin::~CEntitySystemPlugin(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CEntitySystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CEntitySystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CEntitySystemPlugin::GetPluginDiscribe(void) const
	{
		return (ENTITYSYSTEM_DISC);
	}

	// 安装插件
	void CEntitySystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CEntityManagerFactory;
	}

	// 初始化插件
	void CEntitySystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CEntitySystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CEntitySystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
