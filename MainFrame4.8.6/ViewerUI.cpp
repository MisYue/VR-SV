#include <QGridLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <osgDB/ReadFile>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#define VRSOFT_PLUGIN_EXPORT
#include <osgGA/TrackballManipulator>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "ViewerUI.h"
#include "TrajectoryFrame.h"

CViewerUI::CViewerUI( const VR_Soft::VRString& strUIName)
	:m_strUIName(strUIName)
{
	
// 	connect( &_timer, SIGNAL(timeout()), this, SLOT(UpdateView()) );
// 	_timer.start( 0 );
}


CViewerUI::~CViewerUI(void)
{
	m_pGraphicsWindowQt->getGLWidget()->removeEventFilter(this);
	m_pGraphicsWindowQt = NULL;
}

// ��ʼ��UI
void CViewerUI::InitUI(void* param , int nParam )
{
	// Create the Graphics Context
	osg::GraphicsContext::Traits* pTraits = static_cast<osg::GraphicsContext::Traits*>(param);
//	osgQt::GLWidget* pGlWidget = new osgQt::GLWidget(this);
//	pTraits->inheritedWindowData = new osgQt::GraphicsWindowQt::WindowData(this);
	m_pGraphicsWindowQt = new osgQt::GraphicsWindowQt(pTraits);

	// ֧����ק����
	m_pGraphicsWindowQt->getGLWidget()->setAcceptDrops(true);

	// ��װ�¼�������
	m_pGraphicsWindowQt->getGLWidget()->installEventFilter(this);
}

// ��ʼ�����
void CViewerUI::InitCamera(osg::Camera* pCamera)
{
	m_pCamera = pCamera;
	pCamera->setGraphicsContext( m_pGraphicsWindowQt );

	const osg::GraphicsContext::Traits* traits = m_pGraphicsWindowQt->getTraits();

	pCamera->setClearColor( osg::Vec4(0.0, 0.0, 0.0, 1.0) );
	pCamera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 0.1f, 1000.0f );
	pCamera->setNearFarRatio(0.00002);
	/*pCamera->setNearFarRatio(0.00000003);	
	pCamera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);*/
}

// ��ý��洰��
const VR_Soft::VRString CViewerUI::GetUIName(void) const
{
	return (m_strUIName);
}

// ��ɳ�ʼ��
void CViewerUI::CreateVRWindow(osgViewer::View* pView)
{
	osgViewer::StatsHandler* pStateHander = new osgViewer::StatsHandler;
	pView->addEventHandler(pStateHander);
	pView->addEventHandler(new osgViewer::LODScaleHandler);
	pView->addEventHandler(new osgGA::StateSetManipulator(pView->getCamera()->getOrCreateStateSet()));
	pView->addEventHandler(new  osgViewer::ThreadingHandler);
	pView->addEventHandler(new  osgViewer::WindowSizeHandler);
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
//		QWidget::dragEnterEvent(event);
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
	// ��þ�γ�߶�
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("���������ȡʧ��", ERROR_NOT_COM);
		return;
	}

	VR_Soft::IEntityBase* pIEntitBase = 
		VR_Soft::IEntityManager::GetInstance().CreateEntity( strTypeName, VR_Soft::CGUID::Generate());
	if (NULL == pIEntitBase)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("����ģ��ʧ��");
		return;
	}

	pIEarthManager->AddEntity(pIEntitBase);

	// ��þ�γ�߶�
	int nX = event->pos().x();
	int nY = GetRenderWindow()->geometry().height() - event->pos().y();
	double lat = 0.0, lon = 0.0, heigh = 0.0;
	pIEarthManager->GetLongLatHightByPoint(nX, nY, lat, lon, heigh);

	VR_Soft::IEntityDrawAttribute* pIEntitytDrawAttribute = pIEntitBase->GetEntityDrawAttribute();
	if (NULL != pIEntitytDrawAttribute)
	{
		pIEntitytDrawAttribute->GetItem("λ��")->SetValue(osg::Vec3d(lat, lon, heigh));
	}
	

	/*VR_Soft::IDrawAttribute* pIDrawAttribute = (VR_Soft::IDrawAttribute*)pIEntitBase->GetAttribute("ʵ����Ⱦ����");
	pIDrawAttribute->GetItem("��άʵ��")->SetValue(VR_Soft::VRString("DFH4"));*/


	//// ������Ⱦ�����
	//VR_Soft::IEntityDrawManager* pIDrawEntityMnaagre = VR_Soft::CDrawAttributeFacoty::CreateEntityDrawManagerInstance(pIEntitBase);
	//pIEntitBase->SetDrawManager(pIDrawEntityMnaagre);

//	 pIEarth->AddModel(pIEntitBase, lat, lon, height);
}

// ����UI
void CViewerUI::Update(void* param, int nParam)
{

}
//
//void CViewerUI::resizeEvent( QResizeEvent* event )
//{
//	QSize size = event->size();
//	osg::GraphicsContext::Traits* pTraits = const_cast<osg::GraphicsContext::Traits*>(m_pGraphicsWindowQt->getTraits());
//	pTraits->width = size.width();
//	pTraits->height = size.height();
// 	m_pCamera->setViewport( new osg::Viewport(0, 0, size.width(), size.height()) );
// 	m_pCamera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(size.width())/static_cast<double>(size.height()), 0.1f, 1000.0f );
//}

// ˢ����ͼ
void CViewerUI::UpdateView( void )
{

}

// �����ά����
QWidget* CViewerUI::GetRenderWindow( void ) const
{
	if (NULL != m_pGraphicsWindowQt)
	{
		return (m_pGraphicsWindowQt->getGLWidget());
	}

	return (NULL);
}

// �¼�������
bool CViewerUI::eventFilter( QObject *obj, QEvent *event )
{
	if ((NULL == m_pGraphicsWindowQt) || (obj != m_pGraphicsWindowQt->getGLWidget()))
	{
		return (QObject::eventFilter(obj, event));
	}

	// ���ק���¼�
	if (event->type() == QEvent::DragEnter)
	{
		dragEnterEvent((QDragEnterEvent*)event);
	}
	else if (QEvent::Drop == event->type())
	{
		dropEvent((QDropEvent*)event);
	}

	return (QObject::eventFilter(obj, event));
}
