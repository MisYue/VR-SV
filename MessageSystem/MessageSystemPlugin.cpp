#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "MessageSystem.h"
#include "MessageSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Message System";
	////////////////////////////////////////

	CMessageSystemPlugin::CMessageSystemPlugin(void):m_pIComFactory(NULL)
	{
	}


	CMessageSystemPlugin::~CMessageSystemPlugin(void)
	{
	}


	// ��ȡ�������
	const VRString& CMessageSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CMessageSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CMessageSystemPlugin::GetPluginDiscribe(void) const
	{
		return (MESSAGESYSTEM_DISC);
	}

	// ��װ���
	void CMessageSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CMessageManagerFactory;
	}

	// ��ʼ�����
	void CMessageSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CMessageSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CMessageSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
