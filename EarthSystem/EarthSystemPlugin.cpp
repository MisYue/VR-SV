#define OSGERATH_PLUGIN_EXPOT
#include "../../Public/EarthSystem/EarthSystem.h"
#include "EarthSystem.h"
#include "EarthSystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Earth System";
	////////////////////////////////////////

	CEarthSystemPlugin::CEarthSystemPlugin(void):m_pIComFactory(NULL)
	{
		
	}

	CEarthSystemPlugin::~CEarthSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CEarthSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CEarthSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CEarthSystemPlugin::GetPluginDiscribe(void) const
	{
		return (EARTHSYSTEM_DISC);
	}

	// ��װ���
	void CEarthSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CEarthManagerFactory;
	}

	// ��ʼ�����
	void CEarthSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CEarthSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CEarthSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
