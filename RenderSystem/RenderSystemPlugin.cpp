#define OSGRENDER_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "RenderSystem.h"
#include "RenderSystemPlugin.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Render System";
	////////////////////////////////////////

	CRenderSystemPlugin::CRenderSystemPlugin(void):m_pIComFactory(NULL)
	{
	}

	CRenderSystemPlugin::~CRenderSystemPlugin(void)
	{
		VRSOFT_DELETE(m_pIComFactory);
	}

	// ��ȡ�������
	const VRString& CRenderSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}


	// ��ò���汾
	const VRString CRenderSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CRenderSystemPlugin::GetPluginDiscribe(void) const
	{
		return (RENDERSYSTEM_DISC);
	}


	// ��װ���
	void CRenderSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CRenderManagerFactory;
	}

	// ��ʼ�����
	void CRenderSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CRenderSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CRenderSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}
}

