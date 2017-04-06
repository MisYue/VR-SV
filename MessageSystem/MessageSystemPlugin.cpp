#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "MessageSystem.h"
#include "MessageSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Message System";
	////////////////////////////////////////

	CMessageSystemPlugin::CMessageSystemPlugin(void):m_pIComFactory(NULL)
	{
	}


	CMessageSystemPlugin::~CMessageSystemPlugin(void)
	{
	}


	// 获取插件名称
	const VRString& CMessageSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CMessageSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CMessageSystemPlugin::GetPluginDiscribe(void) const
	{
		return (MESSAGESYSTEM_DISC);
	}

	// 安装插件
	void CMessageSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CMessageManagerFactory;
	}

	// 初始化插件
	void CMessageSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CMessageSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CMessageSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
