#define EQUIP_PLUGIN_EXPOT

#include "../../Public/EquipSystem/EquipSystem.h"
#include "EquipSystem.h"
#include "EquipPlgin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Equipment System";
	////////////////////////////////////////

	CEquipPlgin::CEquipPlgin(void):m_pIComFactory(NULL)
	{
	}

	CEquipPlgin::~CEquipPlgin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CEquipPlgin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CEquipPlgin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CEquipPlgin::GetPluginDiscribe(void) const
	{
		return (EQUIPSYSTEM_DISC);
	}

	// ��װ���
	void CEquipPlgin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CEquipManagerFactory;
	}

	// ��ʼ�����
	void CEquipPlgin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CEquipPlgin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CEquipPlgin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
