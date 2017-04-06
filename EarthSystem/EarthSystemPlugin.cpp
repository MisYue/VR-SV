#define OSGERATH_PLUGIN_EXPOT
#include "../../Public/EarthSystem/EarthSystem.h"
#include "EarthSystem.h"
#include "EarthSystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Earth System";
	////////////////////////////////////////

	CEarthSystemPlugin::CEarthSystemPlugin(void):m_pIComFactory(NULL)
	{
		
	}

	CEarthSystemPlugin::~CEarthSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CEarthSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CEarthSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CEarthSystemPlugin::GetPluginDiscribe(void) const
	{
		return (EARTHSYSTEM_DISC);
	}

	// 安装插件
	void CEarthSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CEarthManagerFactory;
	}

	// 初始化插件
	void CEarthSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CEarthSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CEarthSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
