#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "TimeSystem.h"
#include "TimeSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Time System";
	////////////////////////////////////////
	CTimeSystemPlugin::CTimeSystemPlugin(void)
	{
	}

	CTimeSystemPlugin::~CTimeSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CTimeSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CTimeSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CTimeSystemPlugin::GetPluginDiscribe(void) const
	{
		return (TIMESYSTEM_DISC);
	}

	// 安装插件
	void CTimeSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CTimeManagerFactory;
	}

	// 初始化插件
	void CTimeSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CTimeSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CTimeSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
