#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/AirLineSystem/IAirLineManager.h"
#include "AirLineSystem.h"
#include "AirLineSystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft AirLine System";
	////////////////////////////////////////

	CAirLineSystemPlugin::CAirLineSystemPlugin(void):m_pIComFactory(NULL)
	{

	}

	CAirLineSystemPlugin::~CAirLineSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CAirLineSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CAirLineSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CAirLineSystemPlugin::GetPluginDiscribe(void) const
	{
		return (AIRLINESYSTEM_DISC);
	}

	// 安装插件
	void CAirLineSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CAirLineManagerFactory;
	}

	// 初始化插件
	void CAirLineSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CAirLineSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CAirLineSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

#define AIRLINE_PLUGIN_EXPOT

#ifndef AIRLINE_PLUGIN_EXPOT
#define AIRLINE_DLL VRSOFT_DLL_IMPORT
#else
#define AIRLINE_DLL VRSOFT_DLL_EXPORT
#endif

	// 注册插件
	REGISTER_VRSOFT_PLUGIN(CAirLineSystemPlugin, AIRLINE_DLL)
}
