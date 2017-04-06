
#include "MainUI.h"


#include <QDockWidget>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QLabel>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>



#include "ViewerUI.h"

#define __gl_h_
#include <CEGUI/System.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/ImageManager.h>
#include <CEGUI/WindowManager.h>

//#include <CEGUI/CEGUISystem.h>
//#include <CEGUI/RendererModules/OpenGLGUIRenderer/openglrenderer.h>
//#include <CEGUI/CEGUIScriptModule.h>
//#include <CEGUI/CEGUIFontManager.h>
//#include <CEGUI/CEGUISchemeManager.h>
//#include <CEGUI/CEGUIWindowManager.h>
//#include <CEGUI/CEGUIExceptions.h>
//#include <CEGUI/CEGUIImagesetManager.h>
//#include <CEGUI/CEGUIFontManager.h>




class CEGUIDrawable : public osg::Drawable
{
public:

	CEGUIDrawable();

	/** Copy constructor using CopyOp to manage deep vs shallow copy.*/
	CEGUIDrawable(const CEGUIDrawable& drawable,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY):
	Drawable(drawable,copyop) {}

	META_Object(osg,CEGUIDrawable);

	void loadScheme(const std::string& scheme);
	void loadFont(const std::string& font);
	void loadLayout(const std::string& layout);

	void drawImplementation(osg::RenderInfo& renderInfo) const;

protected:   

	virtual ~CEGUIDrawable();

	unsigned int _activeContextID;

};


struct CEGUIEventCallback : public osgGA::GUIEventHandler
{
	CEGUIEventCallback() {}

	/** do customized Event code. */
	virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
	{
		osgGA::EventVisitor* ev = dynamic_cast<osgGA::EventVisitor*>(nv);
		CEGUIDrawable* cd = dynamic_cast<CEGUIDrawable*>(obj);

		if (!ev || !cd) return false;

	/*	switch(ea.getEventType())
		{
		case(osgGA::GUIEventAdapter::DRAG):
		case(osgGA::GUIEventAdapter::MOVE):
			
			CEGUI::System::getSingleton().injectMousePosition(ea.getX(),ea.getY());
			return true;
		case(osgGA::GUIEventAdapter::PUSH):
			{
				CEGUI::System::getSingleton().injectMousePosition(ea.getX(), ea.getY());

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);

				return true;
			}
		case(osgGA::GUIEventAdapter::RELEASE):
			{
				CEGUI::System::getSingleton().injectMousePosition(ea.getX(), ea.getY());

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);

				return true;
			}
		case(osgGA::GUIEventAdapter::DOUBLECLICK):
			{
				// do we need to do something special here to handle double click???  Will just assume button down for now.
				CEGUI::System::getSingleton().injectMousePosition(ea.getX(), ea.getY());

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);

				return true;
			}
		case(osgGA::GUIEventAdapter::KEYDOWN):
			CEGUI::System::getSingleton().injectKeyDown( static_cast<CEGUI::uint>(ea.getKey()) );
			CEGUI::System::getSingleton().injectChar( static_cast<CEGUI::utf32>( ea.getKey() ) );
			return true;
		case(osgGA::GUIEventAdapter::KEYUP):
			CEGUI::System::getSingleton().injectKeyUp( static_cast<CEGUI::uint>(ea.getKey()) );
			return true;
		default:
			break;
		}
		*/
		return false;
	}
};

CEGUIDrawable::CEGUIDrawable()
{
	setSupportsDisplayList(false);

	setEventCallback(new CEGUIEventCallback());

	new CEGUI::System( new CEGUI::OpenGLRenderer(0)); 

	_activeContextID = 0;
}

CEGUIDrawable::~CEGUIDrawable()
{
	// delete CEGUI??
}

void CEGUIDrawable::loadScheme(const std::string& scheme)
{
	try
	{
		CEGUI::SchemeManager::getSingleton().loadScheme("TaharezLook.scheme");
		CEGUI::ImagesetManager::getSingleton().getImageset("TaharezLook");
	}
	catch (CEGUI::Exception e)
	{
		std::cout<<"CEGUIDrawable::loadScheme Error: "<<e.getMessage()<<std::endl;
	}
}

void CEGUIDrawable::loadFont(const std::string& font)
{
	try
	{
		if(CEGUI::FontManager::getSingleton().isFontPresent("SimHei-12"))
			CEGUI::FontManager::getSingleton().getFont("SimHei-12");
		else
			CEGUI::FontManager::getSingleton().createFont("SimHei-12.font");
		//CEGUI::FontManager::getSingleton().createFont(font.c_str());
	}
	catch (CEGUI::Exception e)
	{
		std::cout<<"CEGUIDrawable::loadFont Error: "<<e.getMessage()<<std::endl;
	}
}

void CEGUIDrawable::loadLayout(const std::string& layout)
{
	try
	{
		CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout("Demo8.layout");
		CEGUI::System::getSingleton().setGUISheet(myRoot);
	}
	catch (CEGUI::Exception e)
	{
		std::cout<<"CEGUIDrawable::loadLayout error: "<<e.getMessage()<<std::endl;
	}

}

void CEGUIDrawable::drawImplementation(osg::RenderInfo& renderInfo) const
{
	osg::State& state = *renderInfo.getState();

	if (state.getContextID()!=_activeContextID) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	state.disableAllVertexArrays();

	CEGUI::System::getSingleton().renderGUI();

	glPopAttrib();

	state.checkGLErrors("CEGUIDrawable::drawImplementation");
}

// #include "testlabel.h"
CMainUI::CMainUI(QWidget *parent, Qt::WFlags flags)
{
//	ui.setupUi(this);

	//setAttribute(Qt::WA_PaintOnScreen);
	//setAttribute(Qt::WA_NoSystemBackground);

	//setFocusPolicy(Qt::ClickFocus);

	// 初始化UI
//	InitUI();
	VR_Soft::IRenderManager* pIConFace = VR_Soft::CComManagerImp::GetComponent<\
		VR_Soft::IRenderManager>(VR_Soft::INSTANCE_NAME_RENDERSYSTEM);
	if (NULL == pIConFace)
	{
		return;
	}

//	m_p3DViewUI = new CViewerUI("mainView");
//	m_p2DViewUI = new CViewerUI("2DView");

	VR_Soft::IViewManager* pIViewManager = pIConFace->GetViewManager();
	// 注册界面
	pIViewManager->RegisterViewUI(this);
	pIViewManager->CreateView(GetUIName(), 0, 0, 640, 480);

	// 注册界面
//	pIViewManager->RegisterViewUI(m_p2DViewUI);
//	pIViewManager->CreateView(m_p2DViewUI->GetUIName(), 0, 0, 500, 500);

	// 添加布局器
	//QHBoxLayout *pGridLayout = new QHBoxLayout(this);

	//// 添加布局器
	//pGridLayout->addWidget(m_p3DViewUI);
//	pGridLayout->addWidget(m_p2DViewUI);
//	m_p2DViewUI->hide();

	// 地下防御
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL != pIEarthManager)
	{
//		pIEarthManager->RenderEarth(VR_Soft::IEarthManager::EARTH_2D, pIViewManager->GetRenderView("2DView"));
		pIEarthManager->RenderEarth(VR_Soft::IEarthManager::EARTH_3D, pIViewManager->GetRenderView("mainView"));
	}

	QWidget *dialog = new QWidget(this);
//	dialog->setWindowOpacity(0.8);
	dialog->setWindowTitle("Test");
	dialog->setLayout(new QVBoxLayout);
	dialog->move(180, 200);
	dialog->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and ")));
	dialog->setAttribute(Qt::WA_WState_WindowOpacitySet);
	dialog->setWindowOpacity(0.8);
//	dialog->setStyleSheet(QString::fromLocal8Bit("background-color: transparent;"));
	dialog->setStyleSheet("background-color: rgba(255, 170, 0, 50);");

	//first method add widget to scene with title
	//QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget;
	//proxy->setWindowFlags(Qt::Window);
	//proxy->setWidget(dialog);
	//this->addItem(proxy);

//	connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
//	_timer.start( 0 );
//	QTimer::singleShot(1, this, SLOT(update()));

	//QTimer::singleShot(0, this, SLOT(update()));
/*
	QGraphicsScene* pGraphicsScene = new QGraphicsScene();
	pGraphicsScene->setSceneRect(0, 0, 800, 600);

//	QGraphicsScene* pGrapiceScene = m_p3DViewUI->scene();
	if (NULL != pGraphicsScene)
	{
		QWidget *dialog = new QWidget;
		//dialog->setWindowOpacity(0.8);
		dialog->setWindowTitle("Test");
		dialog->setLayout(new QVBoxLayout);
		dialog->resize(60, 60);
		dialog->move(180, 200);
		dialog->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and ")));

		//first method add widget to scene with title
		//QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget;
		//proxy->setWindowFlags(Qt::Window);
		//proxy->setWidget(dialog);
		//this->addItem(proxy);

		//second method add widget to scene with title, this is vary important, QGraphicsProxyWidget ignore the window flags
		pGraphicsScene->addWidget(dialog, dialog->windowFlags());

		foreach(QGraphicsItem *item, pGraphicsScene->items()) 
		{
			item->setFlag(QGraphicsItem::ItemIsMovable);
			item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
		}
	
	}

	setScene(pGraphicsScene);
*/	
	//pGrapiceProxyWidget->setsy
	
	//pLabel->setWindowFlags(Qt::FramelessWindowHint);
	//pLabel->setAttribute(Qt::WA_TranslucentBackground);
	//pLabel->setStyleSheet(QString::fromLocal8Bit("background-color: transparent;"));
	//pLabel->setStyleSheet("background-color: rgba(255, 170, 0, 50);");
	
	//m_p3DViewUI->setAttribute(Qt::WA_PaintOnScreen, true);
	//pLabel->setWindowFlags(Qt::X11BypassWindowManagerHint);
	//pLabel->setPalette(QPalette(QColor(100,100,10,50)));
	
//	pLabel->setAutoFillBackground(true);
	//pLabel->setBackgroundRole(QPalette::Window);
	//pLabel->setPalette(QPalette(QColor(100,100,10,50)));
//	pLabel->setStyleSheet("background-color: rgba(255, 170, 0, 120);");
	//pLabel->setAttribute(Qt::WA_WindowModified);
	
//	pLabel->setre
//	pLabel->setAttribute(Qt::WA_TranslucentBackground, true);


	setWindowTitle(QString::fromLocal8Bit("二三维联动演示程序"));

	m_pIViewManager = pIViewManager;
}

CMainUI::~CMainUI()
{

}


void CMainUI::paintEvent(QPaintEvent *e)
{
	if (NULL != m_pIViewManager)
	{
		m_pIViewManager->Flush();
	}

	update();
	//updateSim();
}

// 初始化UI
void CMainUI::InitUI(void* param , int nParam )
{
	// Create the Graphics Context
	osg::GraphicsContext::Traits* pTraits = static_cast<osg::GraphicsContext::Traits*>(param);

	//pTraits->inheritedWindowData = new WindowData(winId());
	//pTraits->vsync = false;

	m_pGraphicsWindow = new osgQt::GraphicsWindowQt(this);

//	setViewport(pGlWidget);

	//osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(pTraits);
	//m_pGraphicsWindow = dynamic_cast<osgViewer::GraphicsWindow*>(gc);


	//	m_glview = new CGraphicsView(this);
	//	m_glview->
}

// 初始化相机
void CMainUI::InitCamera(osg::Camera* pCamera)
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

void CMainUI::CreateVRWindow( osgViewer::View* pView )
{
	osgViewer::StatsHandler* pStateHander = new osgViewer::StatsHandler;
	pView->addEventHandler(pStateHander);
	osgViewer::WindowSizeHandler* pWindowSizeHandler = new osgViewer::WindowSizeHandler;
	pView->addEventHandler(pWindowSizeHandler);
	pView->addEventHandler(new osgGA::StateSetManipulator(pView->getCamera()->getOrCreateStateSet()));
}

// 获得界面窗口
const VR_Soft::VRString CMainUI::GetUIName(void) const
{
	return ("mainView");
}

void CMainUI::resizeEvent( QResizeEvent* event )
{
//	CEventAdapter::resizeEvent(event);

	const QSize & size = event->size();

	m_pGraphicsWindow->getEventQueue()->windowResize(0, 0, size.width(), size.height() );
	m_pGraphicsWindow->resized(0, 0, size.width(), size.height());
	m_pCamera->setViewport( new osg::Viewport(0, 0, size.width(), size.height()) );
	m_pCamera->setProjectionMatrixAsPerspective(30.0, double(size.width()) / double(size.height()), 0.1f, 1000.0f);
}

void CMainUI::Update( void* param /*= NULL*/, int nParam /*= 0 */ )
{

}
