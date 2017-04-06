#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/EnvironmentSystem/EnvironmentSystem.h"
#include "EnvironmentSystem.h"
#include "EnvironmentPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Environment System";
	////////////////////////////////////////

	CEnvironmentPlugin::CEnvironmentPlugin(void):m_pIComFactory(NULL)
	{
	}


	CEnvironmentPlugin::~CEnvironmentPlugin(void)
	{
	}

	// ��ȡ�������
	const VRString& CEnvironmentPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CEnvironmentPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CEnvironmentPlugin::GetPluginDiscribe(void) const
	{
		return (ENVIRONEMNTSYSTEM_DISC);
	}

	// ��װ���
	void CEnvironmentPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CEnvironmentManagerFactory;
	}

	// ��ʼ�����
	void CEnvironmentPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CEnvironmentPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CEnvironmentPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
