#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteSystem.h"
#include "SatellitePlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Satellite System";
	////////////////////////////////////////

	CSatellitePlugin::CSatellitePlugin(void):m_pIComFactory(NULL)
	{
	}

	CSatellitePlugin::~CSatellitePlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CSatellitePlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CSatellitePlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CSatellitePlugin::GetPluginDiscribe(void) const
	{
		return (SATELLITESYSTEM_DISC);
	}

	// ��װ���
	void CSatellitePlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CSatelliteManagerFactory;
	}

	// ��ʼ�����
	void CSatellitePlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CSatellitePlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CSatellitePlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}


#define SATELLITE_PLUGIN_EXPOT

#ifndef SATELLITE_PLUGIN_EXPOT
#define SATELLITE_DLL VRSOFT_DLL_IMPORT
#else
#define SATELLITE_DLL VRSOFT_DLL_EXPORT
#endif

	// ע����
	REGISTER_VRSOFT_PLUGIN(CSatellitePlugin, SATELLITE_DLL)
}

