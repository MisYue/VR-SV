#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "MemorySystem.h"
#include "MemoryPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Memory System";
	////////////////////////////////////////

	// 构造函数
	CMemoryPlugin::CMemoryPlugin(void)
	{
	}

	// 析构函数
	CMemoryPlugin::~CMemoryPlugin(void)
	{
	}

	// 获取插件名称
	const VRString& CMemoryPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// 获得插件版本
	const VRString CMemoryPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CMemoryPlugin::GetPluginDiscribe(void) const
	{
		return (MEMORYSYSTEM_DISC);
	}

	// 安装插件
	void CMemoryPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CMemoryManagerFactory;
	}

	// 初始化插件
	void CMemoryPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CMemoryPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CMemoryPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
