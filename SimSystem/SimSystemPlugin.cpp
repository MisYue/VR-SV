#define SIMULATION_PLUGIN_EXPOT

#include "../../Public/VRSoft.h"
#include "../../Public/SimSystem/SimSystem.h"
#include "SimSystem.h"
#include "SimSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Sim System";
	////////////////////////////////////////

	// 构造函数
	CSimSystemPlugin::CSimSystemPlugin(void)
	{
	}

	//析构函数
	CSimSystemPlugin::~CSimSystemPlugin(void)
	{
	}

	// 获取插件名称
	const VRString& CSimSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CSimSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CSimSystemPlugin::GetPluginDiscribe(void) const
	{
		return (SIMSYSTEM_DISC);
	}

	// 安装插件
	void CSimSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CSimManagerFactory;
	}

	// 初始化插件
	void CSimSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CSimSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CSimSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
