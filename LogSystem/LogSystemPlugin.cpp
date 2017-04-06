#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "LogSystem.h"
#include "LogSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Log System";
	////////////////////////////////////////

	CLogSystemPlugin::CLogSystemPlugin(void):
		m_pIComFactory(NULL)
	{
		
	}


	CLogSystemPlugin::~CLogSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CLogSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CLogSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CLogSystemPlugin::GetPluginDiscribe(void) const
	{
		return (LOGSYSTEM_DISC);
	}

	// 安装插件
	void CLogSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CLogManagerFactory;
	}

	// 初始化插件
	void CLogSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CLogSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CLogSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}
}
