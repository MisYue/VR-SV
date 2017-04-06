#include "ViewWidget.h"
#include <QHBoxLayout>
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/PlotSystem/PlotSystem.h"


CViewWidget::CViewWidget(void)
{
	Init();
}


CViewWidget::~CViewWidget(void)
{
}

// ��ʼ��
void CViewWidget::Init( void )
{

	VR_Soft::IRenderManager* pIConFace = VR_Soft::CComManagerImp::GetComponent<\
		VR_Soft::IRenderManager>(VR_Soft::INSTANCE_NAME_RENDERSYSTEM);
	if (NULL == pIConFace)
	{
		return;
	}

	m_p3DViewUI = new CViewerUI("mainView");
//	m_p2DViewUI = new CViewerUI("2DView");

	m_pIViewrManager = pIConFace->GetViewManager();
	// ע�����
	m_pIViewrManager->RegisterViewUI(m_p3DViewUI);
	m_pIViewrManager->CreateView(m_p3DViewUI->GetUIName(), 0, 0, 500, 500);

	//// ע�����
// 	m_pIViewrManager->RegisterViewUI(m_p2DViewUI);
// 	m_pIViewrManager->CreateView(m_p2DViewUI->GetUIName(), 0, 0, 500, 500);

	// ��Ӳ�����
	QHBoxLayout *pGridLayout = new QHBoxLayout(this);
	pGridLayout->setSpacing(0);
	// ��Ӳ�����
	pGridLayout->addWidget(m_p3DViewUI->GetRenderWindow());
//	pGridLayout->addWidget(m_p2DViewUI);

	
	{
		// ���·���
		VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
		if (NULL != pIEarthManager)
		{
			pIEarthManager->RenderEarth(VR_Soft::IEarthManager::EARTH_3D, m_pIViewrManager->GetRenderView("mainView"));
//			pIEarthManager->RenderEarth(VR_Soft::IEarthManager::EARTH_2D, m_pIViewrManager->GetRenderView("2DView"));
		}
	}

	// ��ʼ�����
	VR_Soft::IPlotManager* pIPlotManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IPlotManager>(VR_Soft::INSTANCE_NAME_PLOTSYSTEM);
	if (NULL == pIPlotManager)
	{
		return;
	}

	pIPlotManager->SetViewerName("mainView");
}

// ���3D��ͼ
CViewerUI* CViewWidget::Get3DViewe( void )
{
	return (m_p3DViewUI);
}

// ���2D��ͼ
CViewerUI* CViewWidget::Get2DViewe( void )
{
	return (m_p2DViewUI);
}

// ����
void CViewWidget::paintEvent( QPaintEvent *e )
{
	if (NULL != m_pIViewrManager)
	{
		m_pIViewrManager->Flush();
	}

	// updateSim();
	update();
}


void CViewWidget::Show2D( void )
{
	m_p3DViewUI->GetRenderWindow()->hide();//0, 0, 1, 1);
	m_p3DViewUI->GetRenderWindow()->show();

}

void CViewWidget::Show3D( void )
{
	m_p3DViewUI->GetRenderWindow()->hide();//0, 0, 1, 1);
	m_p3DViewUI->GetRenderWindow()->show();
}

void CViewWidget::show23D( void )
{
	m_p3DViewUI->GetRenderWindow()->hide();//0, 0, 1, 1);
	m_p3DViewUI->GetRenderWindow()->show();
}

