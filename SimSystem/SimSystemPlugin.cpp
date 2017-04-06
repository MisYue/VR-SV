#define SIMULATION_PLUGIN_EXPOT

#include "../../Public/VRSoft.h"
#include "../../Public/SimSystem/SimSystem.h"
#include "SimSystem.h"
#include "SimSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Sim System";
	////////////////////////////////////////

	// ���캯��
	CSimSystemPlugin::CSimSystemPlugin(void)
	{
	}

	//��������
	CSimSystemPlugin::~CSimSystemPlugin(void)
	{
	}

	// ��ȡ�������
	const VRString& CSimSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CSimSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CSimSystemPlugin::GetPluginDiscribe(void) const
	{
		return (SIMSYSTEM_DISC);
	}

	// ��װ���
	void CSimSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CSimManagerFactory;
	}

	// ��ʼ�����
	void CSimSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CSimSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CSimSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
