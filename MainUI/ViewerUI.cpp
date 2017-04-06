#include <QGridLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <osgDB/ReadFile>
#include <osgEarthUtil/EarthManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgViewer/GraphicsWindow>
#define VRSOFT_PLUGIN_EXPORT
#include <osgGA/TrackballManipulator>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "ViewerUI.h"
#include "../MainFrame4.8.6/ViewerUI.h"


#if defined(WIN32) && !defined(__CYGWIN__)

#include <osgViewer/api/Win32/GraphicsWindowWin32>
typedef HWND WindowHandle;
typedef osgViewer::GraphicsWindowWin32::WindowData WindowData;

#elif defined(__APPLE__)  // Assume using Carbon on Mac.

#include <osgViewer/api/Carbon/GraphicsWindowCarbon>
typedef WindowRef WindowHandle;
typedef osgViewer::GraphicsWindowCarbon::WindowData WindowData;

#else // all other unix

#include <osgViewer/api/X11/GraphicsWindowX11>
typedef Window WindowHandle;
typedef osgViewer::GraphicsWindowX11::WindowData WindowData;

#endif

CViewerUI::CViewerUI(const VR_Soft::VRString& strUIName)
	:m_strUIName(strUIName)
{
	// 支持拖拽进入
	setAcceptDrops(true);

	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	setFocusPolicy(Qt::ClickFocus);

// 	connect( &_timer, SIGNAL(timeout()), this, SLOT(UpdateView()) );
// 	_timer.start( 0 );
}


CViewerUI::~CViewerUI(void)
{
	 // m_pGraphicsWindowQt = NULL;
}

// 初始化UI
void CViewerUI::InitUI(void* param , int nParam )
{
	// Create the Graphics Context
	osg::GraphicsContext::Traits* pTraits = static_cast<osg::GraphicsContext::Traits*>(param);

	//pTraits->inheritedWindowData = new WindowData(winId());
	pTraits->vsync = false;

	osgQt::GLWidget* pGlWidget = new osgQt::GLWidget(this);
	m_pGraphicsWindow = new osgQt::GraphicsWindowQt(pGlWidget);

	setViewport(pGlWidget);

	//osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(pTraits);
	//m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(gc);


//	m_glview = new CGraphicsView(this);
//	m_glview->
}

// 初始化相机
void CViewerUI::InitCamera(osg::Camera* pCamera)
{
	m_pCamera = pCamera;
	
	pCamera->setGraphicsContext( m_pGraphicsWindow );

	pCamera->setClearColor( osg::Vec4(1.0, 0.0, 0.0, 1.0) );
	pCamera->setViewport( new osg::Viewport(0, 0, 500, 500) );
	pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(500)/static_cast<double>(500), 0.1f, 1000.0f );
	pCamera->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_FAR_USING_PRIMITIVES);
	pCamera->setNearFarRatio(0.000001f);
	//pCamera->setSmallFeatureCullingPixelSize(.2f);
}

// 获得界面窗口
const VR_Soft::VRString CViewerUI::GetUIName(void) const
{
	return (m_strUIName);
}

// 完成初始化
void CViewerUI::CreateVRWindow(osgViewer::View* pView)
{
	osgViewer::StatsHandler* pStateHander = new osgViewer::StatsHandler;
	pView->addEventHandler(pStateHander);
	osgViewer::WindowSizeHandler* pWindowSizeHandler = new osgViewer::WindowSizeHandler;
	pView->addEventHandler(pWindowSizeHandler);
	pView->addEventHandler(new osgGA::StateSetManipulator(pView->getCamera()->getOrCreateStateSet()));
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
	QString qstrTypeName = QString::fromLocal8Bit(event->mimeData()->data("custon/parentname"));

	VR_Soft::VRString  strComType = qstrTypeName.toLocal8Bit().data();
	VR_Soft::VRString strTypeName = QString::fromLocal8Bit(event->mimeData()->data("custon/name")).toLocal8Bit().data();
	// 获得经纬高度
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("地球组件获取失败", ERROR_NOT_COM);
		return;
	}

	VR_Soft::IEntityBase* pIEntitBase = 
		VR_Soft::IEntityManager::GetInstance().CreateEntity( strTypeName, VR_Soft::CGUID::Generate());
	if (NULL == pIEntitBase)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("加载模型失败");
		return;
	}

	pIEarthManager->AddEntity(pIEntitBase);

	/*VR_Soft::IDrawAttribute* pIDrawAttribute = (VR_Soft::IDrawAttribute*)pIEntitBase->GetAttribute("实体渲染属性");
	pIDrawAttribute->GetItem("三维实体")->SetValue(VR_Soft::VRString("DFH4"));*/


	//// 创建渲染体管理
	//VR_Soft::IEntityDrawManager* pIDrawEntityMnaagre = VR_Soft::CDrawAttributeFacoty::CreateEntityDrawManagerInstance(pIEntitBase);
	//pIEntitBase->SetDrawManager(pIDrawEntityMnaagre);

//	 pIEarth->AddModel(pIEntitBase, lat, lon, height);
}

// 更新UI
void CViewerUI::Update(void* param, int nParam)
{

}
/*
void CViewerUI::mousePressEvent ( QMouseEvent * event )
{
	osgQt::GLWidget::mousePressEvent(event);

	if (Qt::RightButton == event->button())
	{
		// 鑾峰緱缁忕含楂樺害
		VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
		if (NULL == pIEarthManager)
		{
			VR_Soft::IComManager::GetInstance().WriteLogMsg("鍦扮悆缁勪欢鑾峰彇澶辫触", ERROR_NOT_COM);
			return;
		}
		// 鑾峰緱楂樼▼
		double lat, lon, height;
// 		VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
// 
// 		float y = geometry().height() - event->pos().y();
// 		pIEarth->GetLongLatHightByPoint(event->pos().x(), y, lat, lon, height);
// 		pTrajectoryFrame->SetPosition(osg::Vec3d(lat, lon, height));
	}
	
}
*/


void CViewerUI::resizeEvent( QResizeEvent* event )
{
	CEventAdapter::resizeEvent(event);

	const QSize & size = event->size();

	m_pGraphicsWindow->getEventQueue()->windowResize(0, 0, size.width(), size.height() );
	m_pGraphicsWindow->resized(0, 0, size.width(), size.height());
	m_pCamera->setProjectionMatrixAsPerspective(30.0, double(size.width()) / double(size.height()), 0.1f, 1000.0f);
}

// 刷新视图
void CViewerUI::UpdateView( void )
{

}
