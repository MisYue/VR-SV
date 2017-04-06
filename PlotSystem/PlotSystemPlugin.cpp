#define OSGPLOT_PLUGIN_EXPORT

#include "../../Public/PlotSystem/PlotSystem.h"
#include "PlotSystemPlugin.h"
#include "PlotSystem.h"

namespace VR_Soft
{
	////////////////////////////////////////
	const VRString g_sPluginName = "VRSoft Plot System";
	////////////////////////////////////////

	CPlotSystemPlugin::CPlotSystemPlugin(void):m_pIComFactory(NULL)
	{
	}


	CPlotSystemPlugin::~CPlotSystemPlugin(void)
	{
	}

	// ��ȡ�������
	const VRString& CPlotSystemPlugin::GetPluginName(void) const
	{
		return (g_sPluginName);
	}

	// ��ò���汾
	const VRString CPlotSystemPlugin::GetPluginVersion(void) const
	{
		return ("1.0");
	}

	// ��ò������
	const VRString& CPlotSystemPlugin::GetPluginDiscribe(void) const
	{
		return (PLOTSYSTEM_DISC);
	}
	
	// ��װ���
	void CPlotSystemPlugin::Install(void) 
	{
		// ������������
		m_pIComFactory = new CPlotManagerFactory;
	}

	// ��ʼ�����
	void CPlotSystemPlugin::Initialise(void)
	{
		// ע�����������������
		IComManager::GetInstance().RegisterComManagerFactory(m_pIComFactory);
	}

	// ������
	void CPlotSystemPlugin::Shutdown(void)
	{
		// �Ƴ�������������
		IComManager::GetInstance().UnRegisterComManagerFactory(m_pIComFactory);
	}

	// ж�ز��
	void CPlotSystemPlugin::UnInstall(void)
	{
		// ɾ������
		VRSOFT_DELETE(m_pIComFactory);
	}
}

