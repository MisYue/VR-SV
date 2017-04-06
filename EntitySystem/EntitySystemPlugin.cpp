#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/EntitySystem/IEntityManager.h"
#include "EntitySystem.h"
#include "EntitySystemPlugin.h"


namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Entity System";
	////////////////////////////////////////

	CEntitySystemPlugin::CEntitySystemPlugin(void):m_pIComFactory(NULL)
	{
		
	}


	CEntitySystemPlugin::~CEntitySystemPlugin(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CEntitySystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CEntitySystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CEntitySystemPlugin::GetPluginDiscribe(void) const
	{
		return (ENTITYSYSTEM_DISC);
	}

	// ��װ���
	void CEntitySystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CEntityManagerFactory;
	}

	// ��ʼ�����
	void CEntitySystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CEntitySystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CEntitySystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
