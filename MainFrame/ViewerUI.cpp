#define VRSOFT_PLUGIN_EXPORT
#include <QGridLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <osgDB/ReadFile>
#include <osgEarthUtil/EarthManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "../../Public/ElectMagSystem/IRadar.h"
#include "ViewerUI.h"

CViewerUI::CViewerUI(void)
{
	// 支持拖拽进入
	setAcceptDrops(true);
	connect( &_timer, SIGNAL(timeout()), this, SLOT(UpdateView()) );
	_timer.start( 0 );
}


CViewerUI::~CViewerUI(void)
{
	m_pGraphicsWindowQt = NULL;
}

// 初始化UI
void CViewerUI::InitUI(void* param , int nParam )
{
	// Create the Graphics Context
	osg::GraphicsContext::Traits* pTraits = static_cast<osg::GraphicsContext::Traits*>(param);
	osgQt::GLWidget* pGlWidget = new osgQt::GLWidget(this);
	pTraits->inheritedWindowData = new osgQt::GraphicsWindowQt::WindowData(pGlWidget);
	m_pGraphicsWindowQt = new osgQt::GraphicsWindowQt(pTraits);
}

// 初始化相机
void CViewerUI::InitCamera(osg::Camera* pCamera)
{
	pCamera->setGraphicsContext( m_pGraphicsWindowQt );

	const osg::GraphicsContext::Traits* traits = m_pGraphicsWindowQt->getTraits();

	pCamera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
	pCamera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
	pCamera->setNearFarRatio(0.000003);	
}

// 获得界面窗口
const VR_Soft::VRString CViewerUI::GetUIName(void) const
{
	return "mainView";
}

// 完成初始化
void CViewerUI::CreateVRWindow(osgViewer::View* pView)
{
	QGridLayout* pLayout = new QGridLayout;
	setLayout(pLayout);

	pLayout->setContentsMargins(0, 0, 0, 0);

	pLayout->addWidget(m_pGraphicsWindowQt->getGLWidget());
	pView->setCameraManipulator(new osgEarth::Util::EarthManipulator);
	pView->addEventHandler(new osgViewer::StatsHandler());
	pView->addEventHandler(new osgViewer::WindowSizeHandler());
	pView->addEventHandler(new osgGA::StateSetManipulator(pView->getCamera()->getOrCreateStateSet()));
}

void CViewerUI::paintEvent(QPaintEvent *)
{
	
}

// 更新UI
void CViewerUI::Update(void* param, int nParam)
{

}

void CViewerUI::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("custon/name"))
	{
		event->acceptProposedAction();
	}
	else
	{
		event->ignore();
		QWidget::dragEnterEvent(event);
	}
}

void CViewerUI::dragLeaveEvent(QDragLeaveEvent *event)
{
	
}

void CViewerUI::dragMoveEvent(QDragMoveEvent *event)
{
	
}

void CViewerUI::dropEvent(QDropEvent *event)
{
	QString qstrTypeName = event->mimeData()->data("custon/parentname");

	VR_Soft::VRString  strComType = qstrTypeName.toLocal8Bit().toStdString();
	VR_Soft::VRString strTypeName = event->mimeData()->data("custon/name").toStdString();
	// 获得经纬高度
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("地球组件获取失败", ERROR_NOT_COM);
		return;
	}

	// 获得高程
	double lat, lon, height;
	VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
	
	float y = geometry().height() - event->posF().y();
	pIEarth->GetLongLatHightByPoint(event->posF().x(), y, lat, lon, height);
	
	VR_Soft::IEntityComposite* pIEntityComp = VR_Soft::IComManager::GetInstance().GetEntityComposite();
	VR_Soft::IEntityBase* pIEntitBase = dynamic_cast<VR_Soft::IEntityBase*>(\
		pIEntityComp->CreateEntity(strComType, strTypeName));
	if (NULL == pIEntitBase)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("加载模型失败");
		return;
	}

	 pIEarth->AddModel(pIEntitBase, lat, lon, 0);
}

// 刷新视图
void CViewerUI::UpdateView(void)
{
	VR_Soft::IComManager::GetInstance().LoopRun();
}

void CViewerUI::​mousePressEvent(QMouseEvent *event)
{
	if (Qt::LeftButton == event->buttons())
	{
		// 获得经纬高度
		VR_Soft::IAirLineManager* pIAirLineManager = dynamic_cast<VR_Soft::IAirLineManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_AIRLINESYSTEM));
		if (NULL == pIAirLineManager)
		{
			VR_Soft::IComManager::GetInstance().WriteLogMsg("航线组件获取失败", ERROR_NOT_COM);
			return;
		}

		// 获得编辑航线
		VR_Soft::IAirLine* pIAirLine = pIAirLineManager->GetEidtAirLine();
		if (NULL == pIAirLine)
		{
			return;
		}

		// 获得经纬高度
		VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
		if (NULL == pIEarthManager)
		{
			VR_Soft::IComManager::GetInstance().WriteLogMsg("地球组件获取失败", ERROR_NOT_COM);
			return;
		}

		// 获得高程
		double lat, lon, height;
		VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();

		float y = geometry().height() - event->pos().y();
		pIEarth->GetLongLatHightByPoint(event->pos().x(), y, lat, lon, height);

		VR_Soft::CTimePoint pt(lat, lon, height);
		pIAirLine->AddAirLinePoint(pt);
	}
	else if (Qt::RightButton == event->button())
	{
		// 获得经纬高度
		VR_Soft::IAirLineManager* pIAirLineManager = dynamic_cast<VR_Soft::IAirLineManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_AIRLINESYSTEM));
		if (NULL == pIAirLineManager)
		{
			VR_Soft::IComManager::GetInstance().WriteLogMsg("航线组件获取失败", ERROR_NOT_COM);
			return;
		}

		pIAirLineManager->EndEidtAirLine();
	}
	
}
