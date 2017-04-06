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

	// ��ȡ�������
	const VRString& CElectMagSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CElectMagSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CElectMagSystemPlugin::GetPluginDiscribe(void) const
	{
		return (ELECMAGSYSTEM_DISC);
	}

	// ��װ���
	void CElectMagSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CElecMagManagerFactory;
	}

	// ��ʼ�����
	void CElectMagSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CElectMagSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CElectMagSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}