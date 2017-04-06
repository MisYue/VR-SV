#define ELECTMAG_PLUGIN_EXPOT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectMagSystem.h"
#include "ElectMagSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft ElecMag System";
	////////////////////////////////////////

	CElectMagSystemPlugin::CElectMagSystemPlugin(void):m_pIComFactory(NULL)
	{
	}

	CElectMagSystemPlugin::~CElectMagSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CElectMagSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CElectMagSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CElectMagSystemPlugin::GetPluginDiscribe(void) const
	{
		return (ELECMAGSYSTEM_DISC);
	}

	// 安装插件
	void CElectMagSystemPlugin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CElecMagManagerFactory;
	}

	// 初始化插件
	void CElectMagSystemPlugin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CElectMagSystemPlugin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CElectMagSystemPlugin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}