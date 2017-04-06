#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/EnvironmentSystem/EnvironmentSystem.h"
#include "EnvironmentSystem.h"
#include "EnvironmentPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Environment System";
	////////////////////////////////////////

	CEnvironmentPlugin::CEnvironmentPlugin(void):m_pIComFactory(NULL)
	{
	}


	CEnvironmentPlugin::~CEnvironmentPlugin(void)
	{
	}

	// 获取插件名称
	const VRString& CEnvironmentPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CEnvironmentPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CEnvironmentPlugin::GetPluginDiscribe(void) const
	{
		return (ENVIRONEMNTSYSTEM_DISC);
	}

	// 安装插件
	void CEnvironmentPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CEnvironmentManagerFactory;
	}

	// 初始化插件
	void CEnvironmentPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CEnvironmentPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CEnvironmentPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
