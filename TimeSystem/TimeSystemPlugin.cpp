#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "TimeSystem.h"
#include "TimeSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Time System";
	////////////////////////////////////////
	CTimeSystemPlugin::CTimeSystemPlugin(void)
	{
	}

	CTimeSystemPlugin::~CTimeSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CTimeSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CTimeSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CTimeSystemPlugin::GetPluginDiscribe(void) const
	{
		return (TIMESYSTEM_DISC);
	}

	// ��װ���
	void CTimeSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CTimeManagerFactory;
	}

	// ��ʼ�����
	void CTimeSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CTimeSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CTimeSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
