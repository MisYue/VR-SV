#include <QGridLayout>
#include <QToolBar>
#include <QDockWidget>
#include <QTabWidget>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>
#include <osg/GraphicsContext>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/UndergroundSystem/UndergroundSystem.h"
#include "../../Public/ComManager/IPluginManagerUI.h"
#include "ViewerUI.h"
#include "EntityManagerUI.h"
#include "EntityTypeUI.h"
#include "AttributeUI.h"

#include "PluginManagerUI.h"
#include "TimerCtrlUI.h"
#include "MainFrame.h"

CMainFrame::CMainFrame(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*VR_Soft::IRenderManager* pIConFace = dynamic_cast<VR_Soft::IRenderManager*>(\
		VR_Soft::IComInstanceMerator::GetInstance().GetComInstance(VR_Soft::INSTANCE_NAME_RENDERSYSTEM));*/
	VR_Soft::IRenderManager* pIConFace = VR_Soft::CComManagerImp::GetComponent<\
		VR_Soft::IRenderManager>(VR_Soft::INSTANCE_NAME_RENDERSYSTEM);
	if (NULL == pIConFace)
	{
		return;
	}

	CViewerUI* pMainViewUI = new CViewerUI;

	VR_Soft::IViewManager* pIViewManager = pIConFace->GetViewManager();
	// 注册界面
	pIViewManager->RegisterViewUI(pMainViewUI);
	pIViewManager->CreateView(pMainViewUI->GetUIName(), 0, 0, 500, 500);

	// 注册窗口
	setCentralWidget(pMainViewUI);

	{
		// 地下防御
		VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
			VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
		if (NULL != pIEarthManager)
		{
			pIEarthManager->SetViewName("mainView");
		}
	}



	// 添加实体管理
	VR_Soft::IEntityManager* pIEntityComponenet = dynamic_cast<VR_Soft::IEntityManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_ENTITYSYSTEM));

	InitTool();

	//pIConFace->Render();

	//connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
//	_timer.start( 0 );

	setWindowTitle("VR_Viewer");
}

CMainFrame::~CMainFrame()
{
	VRSOFT_DELETE(m_pAttributeUI);
}

/*
void CMainFrame::paintEvent(QPaintEvent *e)
{
	/*static bool bFirst = false;
	if (!bFirst)
	{
		bFirst = true;

		VR_Soft::IRenderManager* pIConFace = VR_Soft::CComManagerImp::GetComponent<\
			VR_Soft::IRenderManager>(VR_Soft::INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIConFace)
		{
			return;
		}
		pIConFace->Render();
	}
	//VR_Soft::IComManager::GetInstance().LoopRun();


}
*/
void CMainFrame::InitTool(void)
{

	InitMenu();

	QToolBar* pToolBar = new QToolBar;
	addToolBar(pToolBar);
	QTabWidget* pTabWidget = new QTabWidget;
	pTabWidget->addTab(new CTimerCtrlUI, QString::fromLocal8Bit("时间控制"));
	pTabWidget->addTab(new QWidget, "2");
	pToolBar->addWidget(pTabWidget);

	// 设置模型
	QDockWidget* pDocWidget = new QDockWidget(QString::fromLocal8Bit("系统已有模型"));
	addDockWidget(Qt::LeftDockWidgetArea, pDocWidget);
	pDocWidget->setWidget(new CEntityManagerUI);

	pDocWidget = new QDockWidget(QString::fromLocal8Bit("系统模型"));
	addDockWidget(Qt::LeftDockWidgetArea, pDocWidget);
	CEntityTypeUI* pEntityTypeUI = new CEntityTypeUI;
	pDocWidget->setWidget(pEntityTypeUI);

	// 初始化属性表
	pDocWidget = new QDockWidget(QString::fromLocal8Bit("属性列表"));
	addDockWidget(Qt::RightDockWidgetArea, pDocWidget);
	m_pAttributeUI = new CAttributeUI;
	pDocWidget->setWidget(m_pAttributeUI);
}

// 初始化菜单
void CMainFrame::InitMenu(void)
{
	// 创建文件菜单
	QMenu* pMenu = new QMenu(QString::fromLocal8Bit("文件"),this);
	QAction* pAction = new QAction(QString::fromLocal8Bit("退出"), pMenu);
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(Exit()));
	pMenu->addAction(pAction);
	ui.menuBar->addMenu(pMenu);

	// 插件系统
	pMenu = new QMenu(QString::fromLocal8Bit("插件"),this);
	pAction = new QAction(QString::fromLocal8Bit("插件管理"), pMenu);
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(AddInManager()));
	pMenu->addAction(pAction);
	ui.menuBar->addMenu(pMenu);
}

// 退出
void CMainFrame::Exit()
{
	close();
}

// 插件管理
void CMainFrame::AddInManager(void)
{
	CPluginManagerUI* pPluginManager = new CPluginManagerUI;
	pPluginManager->show();
}
