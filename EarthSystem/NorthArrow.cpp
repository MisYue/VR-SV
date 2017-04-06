#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "NorthArrow.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osg/Texture2D>

#include "zoomEventHandle.h"
#include "compassEventHandle.h"
#include "walkerEventHandle.h"
#include "CameraInfo.h"
#include "EarthManipulator3D.h"

namespace VR_Soft
{

	class CRenderCallBace : public osgGA::GUIEventHandler
	{
	public:
		CRenderCallBace(CNorthArrow* pNorthArrow)
			:m_width(0), m_height(0), m_pNorthArrow(pNorthArrow)
		{
		}

		/// 动画事件处理
		virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&aa)
		{
			bool bResize = false;
			osgViewer::View* pView = dynamic_cast<osgViewer::View*>(&aa);
			if (NULL == pView)
			{
				return (false);
			}

			osg::Viewport* vp = pView->getCamera()->getViewport();
			if (m_width != vp->width())
			{
				m_width = vp->width();
				bResize = true;
			}

			if (m_height != vp->height())
			{
				m_height = vp->height();
				bResize = true;
			}

			if (bResize && (NULL != m_pNorthArrow))
			{
				m_pNorthArrow->reSize(m_width, m_height);
			}

			return (false);

		}

	private:
		int m_width;
		int m_height;
		CNorthArrow* m_pNorthArrow;
	};

	CNorthArrow::CNorthArrow(CSynchroManipulator* pSynchroManip, osg::Group *group, osgViewer::View *view, CameraInfoCallback* pCmic,  double width, double height)
		:m_pSynchroManip(pSynchroManip), m_pCameraIC(pCmic)
	{
	//	m_pHudCamera = new osg::Camera;

		((CEarthManipulator3D*)m_pSynchroManip)->SetCameraInfoCallback(m_pCameraIC);

		initScreenWidget(view, width, height);

		group->addChild( m_pHudCamera.get() );

		//if (pMyManipulator)
		//{
		//	connect(m_pZoom, SIGNAL(sendClickCount(double)), pMyManipulator, SLOT(slotZoom(double)));
		//	connect(m_pWalker, SIGNAL(emitPosition(osg::Vec2)), pMyManipulator, SLOT(slotTraval(osg::Vec2)));
		//	connect(m_pCompass, SIGNAL(emitPosition(osg::Vec2)), pMyManipulator, SLOT(slotPitch(osg::Vec2)));
		//	connect(pMyManipulator, SIGNAL(emitHeading(double)), m_pCompass, SLOT(slotHeading(double)));
		//}
		
	}

	CNorthArrow::~CNorthArrow()
	{

	}

	void CNorthArrow::initScreenWidget(osgViewer::View *view, double width, double height)
	{
		m_pWM = new osgWidget::WindowManager(view, width, width, 0x0C000000);

		// 获取背景色，并将alph设置为0，该色用做窗口背景色；
		const osg::Vec4& color = view->getCamera()->getClearColor()-osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f);

		const VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath();

		// 图片资源：第一个是背景，在父控件中使用
		std::string walkerImages[3] = {
			strPath + "/Data/hudImage/look_background.png",
			strPath + "/Data/hudImage/move_norm.png",
			strPath + "/Data/hudImage/spotlight.png" };

		std::string compassImages[5] = {
			strPath + "/Data/hudImage/lookbackground.png",
			strPath + "/Data/hudImage/looknorm.png",
			strPath + "/Data/hudImage/spotlight.png",
			strPath + "/Data/hudImage/n.png",
			strPath + "/Data/hudImage/nhover.png" };

		std::string zoomImages[3] = {
			strPath + "/Data/hudImage/zoombackground.png",
			strPath + "/Data/hudImage/zoomactive.png",
			strPath + "/Data/hudImage/zoombar_norm.png" };

		m_pCompass = new Compass(m_pSynchroManip, color,compassImages);
		m_pWalker = new Walker(m_pSynchroManip, color,walkerImages);
		m_pZoom = new Zoom(m_pSynchroManip, color,zoomImages);

		m_pWM->addChild(m_pCompass->getShadowCanvas());
		m_pWM->addChild(m_pCompass->getRingShadowCanvas());
		m_pWM->addChild(m_pCompass->getBaseCanvas());

		m_pWM->addChild(m_pWalker->getShadowCanvas());
		m_pWM->addChild(m_pWalker->getBaseCanvas());

		m_pWM->addChild(m_pZoom->getBaseCanvas());


		m_pHudCamera = m_pWM->createParentOrthoCamera();
		m_pHudCamera->setNodeMask(0x0C000000);

		view->addEventHandler(new osgWidget::MouseHandler(m_pWM));
		view->addEventHandler(new osgWidget::ResizeHandler(m_pWM, m_pHudCamera));

		view->addEventHandler(new zoomEventHandle(m_pZoom));
		view->addEventHandler(new walkerEventHandle(m_pWalker));
		view->addEventHandler(new compassEventHandle(m_pCompass));
		view->addEventHandler(new CRenderCallBace(this));
		//view->
	}

	void CNorthArrow::reSize(double width, double height)
	{
		if (m_pCompass)
		{
			m_pCompass->resetCanvasPosition(width,height);
		}

		if (m_pWalker)
		{
			m_pWalker->resetCanvasPosition(width,height);
		}

		if (m_pZoom)
		{
			m_pZoom->resetCanvasPosition(width,height);
		}

		if (m_pWM)
		{
			m_pWM->setWindowSize(width, height);
			m_pWM->resizeAllWindows();
		}

		if (NULL != m_pCameraIC)
		{
			m_pCameraIC->Resize(width, height);
		}
	}
}