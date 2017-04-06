#define OSGPLOT_PLUGIN_EXPORT

#include "../../Public/PlotSystem/PlotSystem.h"
#include "PlotSystemPlugin.h"
#include "PlotSystem.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Plot System";
	////////////////////////////////////////

	CPlotSystemPlugin::CPlotSystemPlugin(void):m_pIComFactory(NULL)
	{
	}


	CPlotSystemPlugin::~CPlotSystemPlugin(void)
	{
	}

	// 获取插件名称
	const VRString& CPlotSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CPlotSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CPlotSystemPlugin::GetPluginDiscribe(void) const
	{
		return (PLOTSYSTEM_DISC);
	}
	
	// 安装插件
	void CPlotSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CPlotManagerFactory;
	}

	// 初始化插件
	void CPlotSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CPlotSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CPlotSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}
}

