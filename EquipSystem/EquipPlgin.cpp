#define EQUIP_PLUGIN_EXPOT

#include "../../Public/EquipSystem/EquipSystem.h"
#include "EquipSystem.h"
#include "EquipPlgin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Equipment System";
	////////////////////////////////////////

	CEquipPlgin::CEquipPlgin(void):m_pIComFactory(NULL)
	{
	}

	CEquipPlgin::~CEquipPlgin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// 获取插件名称
	const VRString& CEquipPlgin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// 获得插件版本
	const VRString CEquipPlgin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// 获得插件描述
	const VRString& CEquipPlgin::GetPluginDiscribe(void) const
	{
		return (EQUIPSYSTEM_DISC);
	}

	// 安装插件
	void CEquipPlgin::Install(void) 
	{
		// 创建工厂对象
		m_pIComFactory = new CEquipManagerFactory;
	}

	// 初始化插件
	void CEquipPlgin::Initialise(void)
	{
		// 注册进入组件管理组件中
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// 清除插件
	void CEquipPlgin::Shutdown(void)
	{
		// 移除组件管理组件中
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// 卸载插件
	void CEquipPlgin::UnInstall(void)
	{
		// 删除工厂
		VRSOFT_DELETE(m_pIComFactory);
	}

}
