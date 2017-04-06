#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteSystem.h"
#include "SatellitePlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Satellite System";
	////////////////////////////////////////

	CSatellitePlugin::CSatellitePlugin(void):m_pIComFactory(NULL)
	{
	}

	CSatellitePlugin::~CSatellitePlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CSatellitePlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CSatellitePlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CSatellitePlugin::GetPluginDiscribe(void) const
	{
		return (SATELLITESYSTEM_DISC);
	}

	// 安装插件
	void CSatellitePlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CSatelliteManagerFactory;
	}

	// 初始化插件
	void CSatellitePlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CSatellitePlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CSatellitePlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}


#define SATELLITE_PLUGIN_EXPOT

#ifndef SATELLITE_PLUGIN_EXPOT
#define SATELLITE_DLL VRSOFT_DLL_IMPORT
#else
#define SATELLITE_DLL VRSOFT_DLL_EXPORT
#endif

	// 注册插件
	REGISTER_VRSOFT_PLUGIN(CSatellitePlugin, SATELLITE_DLL)
}

