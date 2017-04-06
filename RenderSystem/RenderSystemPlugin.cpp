#define OSGRENDER_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "RenderSystem.h"
#include "RenderSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Render System";
	////////////////////////////////////////

	CRenderSystemPlugin::CRenderSystemPlugin(void):m_pIComFactory(NULL)
	{
	}

	CRenderSystemPlugin::~CRenderSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CRenderSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CRenderSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CRenderSystemPlugin::GetPluginDiscribe(void) const
	{
		return (RENDERSYSTEM_DISC);
	}


	// 安装插件
	void CRenderSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CRenderManagerFactory;
	}

	// 初始化插件
	void CRenderSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CRenderSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CRenderSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}
}

