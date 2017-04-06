#define OSGPLOT_PLUGIN_EXPORT

#include "../../Public/PlotSystem/PlotSystem.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "PlotContrlHandle.h"
#include "Plot.h"
#include "FeatureGeomtryFactory.h"
#include "FeatureGeomtry.h"
#include "PlotSystem.h"

#include "ArrowLine.h"
#include "PlotPlaceGeomtry.h"

#include <osgViewer/View>

#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgEarthUtild.lib")
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "osgTerraind.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")
#pragma comment(lib, "osgEarthFeaturesd.lib")

#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgEarthUtil.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib, "osgTerrain.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#pragma comment(lib, "osgEarthFeatures.lib")
#endif // _DEBUG


namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CPlotManagerFactory::FACTORY_TYPE_NAME = PLOTSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CPlotSystem::CPlotSystem(const VRString& strName)
		:m_pPlotContrlHandle(NULL)
	{
		// ��������
		SetName(strName);
	}


	CPlotSystem::~CPlotSystem(void)
	{
	}

	IPlot* CPlotSystem::CreatePlot( const PLOT_MASK plotMask, const uint64_t ID, const VRString& strPlot )
	{
		if (NULL == m_pPlotContrlHandle)
		{
			ILogManager::GetInstance().SetLogMessage("�¼�������û�б���ʼ�� CreatePlot", ERROR_NOT_FIND);
			return (NULL);
		}

		CPlot* pPlot = new CPlot(ID, strPlot);
		IFeatureGeomtry* pFeatureGeomtry = NULL;
		if (0 == plotMask)
		{
			CFeatureGeomtryFactory featureGeomtryFactory;
			pFeatureGeomtry = new CFeatureGeomtry(featureGeomtryFactory.CreateLineString());

			CPlotStrategy* pPlotStrategy = new CArrowCureLineStrategy(pPlot);
			// ���ÿ��Ƶ��㷨
			CBaseContrl* pArrowLine = new CArrowCureLine(pPlotStrategy);
			m_pPlotContrlHandle->SetContrl(pArrowLine);
		}
		else
		{
			pFeatureGeomtry = new CPlotPlaceGeomtry;
		}
		
		
		pPlot->SetFeatureGeomtry(pFeatureGeomtry);

		pFeatureGeomtry->SetClamping(IFeatureGeomtry::CLAMP_TO_TERRAIN);
		pFeatureGeomtry->SetTechnique(IFeatureGeomtry::TECHNIQUE_GPU);


		

		return (pPlot);
	}

	// ��ʼ��ϵͳ
	void CPlotSystem::Init( void )
	{

	}

	const VRString& CPlotSystem::GetTypeName( void ) const
	{
		return (CPlotManagerFactory::FACTORY_TYPE_NAME);
	}

	// ������ͼ����
	void CPlotSystem::SetViewerName( const VRString& strViewName )
	{
		// ��ȡ��ͼ
		IRenderManager* pIRenderManger = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManger)
		{
			ILogManager::GetInstance().SetLogMessage("û���ҵ���Ⱦ��� SetViewerName", ERROR_NOT_FIND);
			return ;
		}

		// ������ͼ
		IRenderView* pIViewer = pIRenderManger->GetViewManager()->GetRenderView(strViewName);
		if (NULL == pIViewer)
		{
			ILogManager::GetInstance().SetLogMessage("��ͼ������ SetViewerName", ERROR_NOT_FIND);
			return;
		}

		m_pPlotContrlHandle = new CPlotContrlHandle;
		pIViewer->GetView()->addEventHandler(m_pPlotContrlHandle);
	}

	// �༭������
	void CPlotSystem::EidtPlot(IPlot* pIplot)
	{
		if (NULL == pIplot)
		{
			ILogManager::GetInstance().SetLogMessage("�༭���󲻴���", ERROR_NOT_FIND);
			return;
		}

		if (NULL == m_pPlotContrlHandle)
		{
			ILogManager::GetInstance().SetLogMessage("�༭���߲����ڣ�����ϵ����ṩ��", ERROR_NOT_FIND);
			return;
		}

		IFeatureGeomtry* pIFeatrueGeomtry = pIplot->GetFeatureGeomtry();
		if (NULL == pIFeatrueGeomtry)
		{
			ILogManager::GetInstance().SetLogMessage("���λ�ͼ������", ERROR_NOT_FIND);
			return;
		}
		// ���û��ƵĶ���
		m_pPlotContrlHandle->SetFeartureGeomtry(pIFeatrueGeomtry);
	}

}

