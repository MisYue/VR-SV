#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/AirLineSystem/IAirLineManager.h"
#include "AirLineSystem.h"
#include "AirLineSystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft AirLine System";
	////////////////////////////////////////

	CAirLineSystemPlugin::CAirLineSystemPlugin(void):m_pIComFactory(NULL)
	{

	}

	CAirLineSystemPlugin::~CAirLineSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CAirLineSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CAirLineSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CAirLineSystemPlugin::GetPluginDiscribe(void) const
	{
		return (AIRLINESYSTEM_DISC);
	}

	// ��װ���
	void CAirLineSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CAirLineManagerFactory;
	}

	// ��ʼ�����
	void CAirLineSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CAirLineSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CAirLineSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

#define AIRLINE_PLUGIN_EXPOT

#ifndef AIRLINE_PLUGIN_EXPOT
#define AIRLINE_DLL VRSOFT_DLL_IMPORT
#else
#define AIRLINE_DLL VRSOFT_DLL_EXPORT
#endif

	// ע����
	REGISTER_VRSOFT_PLUGIN(CAirLineSystemPlugin, AIRLINE_DLL)
}
