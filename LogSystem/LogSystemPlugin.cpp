#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "LogSystem.h"
#include "LogSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Log System";
	////////////////////////////////////////

	CLogSystemPlugin::CLogSystemPlugin(void):
		m_pIComFactory(NULL)
	{
		
	}


	CLogSystemPlugin::~CLogSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CLogSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CLogSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CLogSystemPlugin::GetPluginDiscribe(void) const
	{
		return (LOGSYSTEM_DISC);
	}

	// ��װ���
	void CLogSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CLogManagerFactory;
	}

	// ��ʼ�����
	void CLogSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CLogSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CLogSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}
}
