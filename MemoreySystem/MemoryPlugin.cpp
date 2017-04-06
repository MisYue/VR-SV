#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "MemorySystem.h"
#include "MemoryPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Memory System";
	////////////////////////////////////////

	// ���캯��
	CMemoryPlugin::CMemoryPlugin(void)
	{
	}

	// ��������
	CMemoryPlugin::~CMemoryPlugin(void)
	{
	}

	// ��ȡ�������
	const VRString& CMemoryPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CMemoryPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CMemoryPlugin::GetPluginDiscribe(void) const
	{
		return (MEMORYSYSTEM_DISC);
	}

	// ��װ���
	void CMemoryPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CMemoryManagerFactory;
	}

	// ��ʼ�����
	void CMemoryPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CMemoryPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CMemoryPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}

}
