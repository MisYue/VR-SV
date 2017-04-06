#include <QGridLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QKeyEvent>
#include <QSettings>
#include <QDateTime>
#include <QDomDocument>
#include <QTextStream>
#include <QDomNode>
#include <QDomElement>
#include <QMessageBox>
#include <QSplitter>
#include <QDomProcessingInstruction>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgEarth/Viewpoint>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>
#include <osg/GraphicsContext>

#include "PluginManagerUI.h"
//#include "TimerCtrlUI.h"
#include "MainFrame.h"
#include "TrajectoryFrame.h"
#include "SatelliteFrame.h"
#include "SimCtrlFrame.h"
#include "LayerManagerUI.h"
#include "ViewWidget.h"
#include "PropertyBrowser/qttreepropertybrowser.h"
#include "PropertyBrowser/qteditorfactory.h"


CMainFrame::CMainFrame(QWidget *parent,QSplashScreen *screen)
	: QMainWindow(parent),m_pAttributeUI(NULL),m_bFullScreen(false),m_pVieweWidget(NULL)
{
	///ZXD
	b_DisplayClose = false;
	UnitSystemDialog *_unitDialog = new UnitSystemDialog;
	_unitDialog->exec();

	QPixmap pixmap("Image/StartImage.png");
	screen->setPixmap(pixmap);
	screen->show();  
	screen->showMessage("", Qt::AlignCenter, Qt::red);  


	int UnitTime(1);
	int UnitLength(1);
	int UnitMass(1);
	_unitDialog->GetUnitSystemValue(UnitMass , UnitTime , UnitLength);
	System_US = Bit_UnitSystem(UnitLength, UnitMass , UnitTime);
	GetUnitListToShow(UnitLength,UnitMass,UnitTime);

	_pOpDisplay = new OperationDisplay;
	_pOpDisplay->GetUnitSeting(System_US);
	std::vector<int> _vUnit;
	_vUnit.push_back(UnitLength);
	_vUnit.push_back(UnitTime);
	_vUnit.push_back(UnitMass);


	_pParaTree = new ParameterTree;
	_pParaTree->GetUnitSystemParameter(_vUnit);

	////////////////
	ui.setupUi(this);
	InitWidget();
	setWindowTitle(QString::fromLocal8Bit("RocKieSS V1.0"));
	b_LineNDamage = true;
	b_LineYDamage = true;
	b_LineNAttack = true;
	b_CylinderWarhead = false;
	IsFuncOK = false;
	IsRockBoom = false;
	//timer->start(1000);
	_pXML = new XMLOperation("my.xml");
	_pXML->SetLocalUnity(&System_US);
	H_seting = new HeightSetingWidget;
	pThread = new ThreadRcokArea;
	//
	_pCsvDialog = new CSVDialog("");
}

CMainFrame::~CMainFrame()
{
	VRSOFT_DELETE(m_pAttributeUI);

	VR_Soft::IComManager* pComManager = VR_Soft::IComManager::GetInstancePtr();
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Stop);
}


void CMainFrame::paintEvent(QPaintEvent *e)
{

}

void CMainFrame::InitWidget(void)
{
	QWidget *_pCentraWidget = new QWidget;
	_pHbox = new QHBoxLayout;
	_pCentraWidget->setLayout(_pHbox);
	setCentralWidget(_pCentraWidget);


	m_pVieweWidget = new CViewWidget;
	_pHbox->addWidget(m_pVieweWidget);

	QString qstrRes = VR_Soft::IComManager::GetInstance().GetComManagerConfig()->GetCurPath().c_str();
	// ����ģ��
	m_pDocWidget = new QDockWidget(QString::fromLocal8Bit("�����б�"));
	m_pDocWidget->setMaximumWidth(_pCentraWidget->rect().height()*0.5);
	addDockWidget(Qt::RightDockWidgetArea, m_pDocWidget);
	m_pDocWidget->setWidget(new CEntityManagerUI);


	/*	QDockWidget* pDocWidget = new QDockWidget(QString::fromLocal8Bit("ϵͳģ��"));
	pDocWidget->setMaximumWidth(_pCentraWidget->rect().height()*0.3);
	addDockWidget(Qt::LeftDockWidgetArea, pDocWidget);
	CEntityTypeUI* pEntityTypeUI = new CEntityTypeUI;
	pDocWidget->setWidget(pEntityTypeUI);*/

	 //��ʼ�����Ա�
	QDockWidget* pDocWidget = new QDockWidget(QString::fromLocal8Bit("�����б�"));
	pDocWidget->setMaximumWidth(_pCentraWidget->rect().height()*0.5);
	//addDockWidget(Qt::RightDockWidgetArea, pDocWidget);
	m_pAttributeUI = new CAttributeUI;
	pDocWidget->setWidget(m_pAttributeUI);

	// Dock�зָ�
	tabifyDockWidget(m_pDocWidget,pDocWidget);

	//XD
	//�����б���ʾ
	_ParameterList = new QDockWidget;
	_ParameterList->setWindowTitle(QString::fromLocal8Bit("�����б�"));
	_ParameterList->setMaximumWidth(_pCentraWidget->rect().height()*0.5);

	_ParameterList->setWidget(_pParaTree);
	addDockWidget(Qt::RightDockWidgetArea,_ParameterList);

	//��ӻ���ʾ����������
	_FrameZoonArgument = new QGroupBox;

	_pVbox = new QGridLayout;
	_pArgument = new DamageAreaData(0.0,0.0,0.0);
	_FrameZoonArgument->setMinimumWidth(_pCentraWidget->rect().width()*0.5);
	_FrameZoonArgument->setLayout(_pVbox);

	_pVbox->addWidget(_pArgument,4,0,1,1);
	_pHbox->addWidget(_FrameZoonArgument);
	_FrameZoonArgument->hide();

	//
	InitMenu();
	InitTool();
}
//
void CMainFrame::InitTool()
{
	// ��ʼ��ť
	m_pStartBtn = new QToolButton;
	m_pStartBtn->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/��ʼ.png")));
	m_pStartBtn->setFixedSize(30,30);
	m_pStartBtn->setToolTip(QString::fromLocal8Bit("��ʼ����"));
	// ֹͣ��ť
	m_pStopBtn = new QToolButton;
	m_pStopBtn->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/Stop.png")));
	m_pStopBtn->setFixedSize(30,30);
	m_pStopBtn->setToolTip(QString::fromLocal8Bit("ֹͣ����"));
	// �����ť
	m_pAccelerateBtn = new QToolButton;
	m_pAccelerateBtn->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/����.png")));
	m_pAccelerateBtn->setFixedSize(30,30);
	m_pAccelerateBtn->setToolTip(QString::fromLocal8Bit("����"));
	// ���˰�ť
	m_pDecelerateBtn = new QToolButton;
	m_pDecelerateBtn->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/����.png")));
	m_pDecelerateBtn->setFixedSize(30,30);
	m_pDecelerateBtn->setToolTip(QString::fromLocal8Bit("����"));
	// ��ͣ��ť
	m_pPauseBtn = new QToolButton;
	m_pPauseBtn->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/��ͣ.png")));
	m_pPauseBtn->setFixedSize(30,30);
	m_pPauseBtn->setToolTip(QString::fromLocal8Bit("��ͣ����"));
	//����Ŀ��
	m_pFollowTarget = new QToolButton;
	m_pFollowTarget->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/Telescope.png")));
	m_pFollowTarget->setFixedSize(30,30);
	m_pFollowTarget->setToolTip(QString::fromLocal8Bit("���浯��"));



	//ѡ��������������ļ�
	m_pOpenVariableFile = new QToolButton;
	m_pOpenVariableFile->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/OpenFile.png")));
	m_pOpenVariableFile->setFixedSize(30,30);
	m_pOpenVariableFile->setToolTip(QString::fromLocal8Bit("�򿪷��������ļ�"));
	//����������������ļ�
	m_pSaveVariableFile = new QToolButton;
	m_pSaveVariableFile->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/SaveFile.png")));
	m_pSaveVariableFile->setFixedSize(30,30);
	m_pSaveVariableFile->setToolTip(QString::fromLocal8Bit("������������ļ�"));



	// ����༭��ť
	m_pMissile = new QToolButton;
	m_pMissile->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/missile_1.png")));
	m_pMissile->setFixedSize(30,30);
	m_pMissile->setToolTip(QString::fromLocal8Bit("��������"));
	m_pMissile->setEnabled(false);
	// Ŀ��༭��ť
	m_pTarget = new QToolButton;
	m_pTarget->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/target.png")));
	m_pTarget->setFixedSize(30,30);
	m_pTarget->setToolTip(QString::fromLocal8Bit("����Ŀ��"));
	// ��������ʾ
	m_pCalculationDisplayed = new QToolButton;
	m_pCalculationDisplayed->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/show.png")));
	m_pCalculationDisplayed->setFixedSize(30,30);
	m_pCalculationDisplayed->setToolTip(QString::fromLocal8Bit("������"));
	// ��Ŀ�������н�������
	m_DamageLineYDamage = new QToolButton;
	m_DamageLineYDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineYDamage.png")));
	m_DamageLineYDamage->setFixedSize(30,30);
	m_DamageLineYDamage->setToolTip(QString::fromLocal8Bit("��ʾ���ؽ�����"));

	// ��Ŀ��������û���˺�
	m_DamageLineNDamage = new QToolButton;
	m_DamageLineNDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineNoDamage.png")));
	m_DamageLineNDamage->setFixedSize(30,30);
	m_DamageLineNDamage->setToolTip(QString::fromLocal8Bit("��ʾ����δ�˺�������"));

	// ��Ŀ������û�н�������
	m_DamageLineNAttack = new QToolButton;
	m_DamageLineNAttack->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineNoAttack.png")));
	m_DamageLineNAttack->setFixedSize(30,30);
	m_DamageLineNAttack->setToolTip(QString::fromLocal8Bit("��ʾ����δ������"));

	// ս��������ʾ��ر�
	m_CylinderShow = new QToolButton;
	m_CylinderShow->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/cylinderShow.png")));
	m_CylinderShow->setFixedSize(30,30);
	m_CylinderShow->setToolTip(QString::fromLocal8Bit("��ʾս����Բ��"));

	//�ص����ƻ�����
	//��ʼ�ص���ʾ
	m_BeginLineCall = new QToolButton;
	m_BeginLineCall->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/BeginPlot.png")));
	m_BeginLineCall->setFixedSize(30,30);
	m_BeginLineCall->setToolTip(QString::fromLocal8Bit("��ʼ�ص���ʾ"));
	m_BeginLineCall->setObjectName("BeginPlot");
	//��ͣ�ص���ʾ
	m_StopLineCall = new QToolButton;
	m_StopLineCall->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/StopPlot.png")));
	m_StopLineCall->setFixedSize(30,30);
	m_StopLineCall->setToolTip(QString::fromLocal8Bit("��ͣ�ص���ʾ"));
	m_StopLineCall->setObjectName("StopPlot");
	//���»ص���ʾ
	m_RestorLineCall = new QToolButton;
	m_RestorLineCall->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/RestorePlot.png")));
	m_RestorLineCall->setFixedSize(30,30);
	m_RestorLineCall->setToolTip(QString::fromLocal8Bit("���»ص���ʾ"));
	m_RestorLineCall->setObjectName("RestoPlot");


	QToolBar *_pComputational = new QToolBar;
	this->addToolBar(Qt::LeftToolBarArea,_pComputational);
	_pComputational->addWidget(m_pTarget);
	_pComputational->addWidget(m_pMissile);
	//_pComputational->addWidget(m_pCalculationDisplayed);


	_pComputational->addWidget(m_CylinderShow);
	_pComputational->addWidget(m_DamageLineYDamage);
	_pComputational->addWidget(m_DamageLineNDamage);
	_pComputational->addWidget(m_DamageLineNAttack);
	//_pComputational->addWidget(m_CylinderShow);

	_pComputational->addWidget(m_BeginLineCall);
	_pComputational->addWidget(m_StopLineCall);
	_pComputational->addWidget(m_RestorLineCall);

	// �����ļ�����
	QToolBar *_pFileAction = new QToolBar;
	this->addToolBar(Qt::LeftToolBarArea,_pFileAction);
	_pFileAction->addWidget(m_pOpenVariableFile);
	_pFileAction->addWidget(m_pSaveVariableFile);

	// �������
	QToolBar *_pSimControlTitle = new QToolBar;
	this->addToolBar(Qt::LeftToolBarArea,_pSimControlTitle);
	_pSimControlTitle->addWidget(m_pStartBtn);
	_pSimControlTitle->addWidget(m_pDecelerateBtn);
	_pSimControlTitle->addWidget(m_pAccelerateBtn);
	_pSimControlTitle->addWidget(m_pPauseBtn);
	_pSimControlTitle->addWidget(m_pStopBtn);
	//_pSimControlTitle->addWidget(m_pFollowTarget);

	connect(m_pStartBtn,SIGNAL(clicked()),this,SLOT(StartSim()));
	connect(m_pStopBtn,SIGNAL(clicked()),this,SLOT(StopSim()));
	connect(m_pAccelerateBtn,SIGNAL(clicked()),this,SLOT(AccelerateSim()));
	connect(m_pDecelerateBtn,SIGNAL(clicked()),this,SLOT(DecelerateSim()));
	connect(m_pPauseBtn,SIGNAL(clicked()),this,SLOT(PauseSim()));

	connect(m_pMissile,SIGNAL(clicked()),this,SLOT(CreatesEditsMissile()));
	connect(m_pTarget,SIGNAL(clicked()),this,SLOT(CreatesEditsTargetArea()));

	connect(m_DamageLineYDamage,SIGNAL(clicked()),this,SLOT(DamageLineYDamage()));
	connect(m_DamageLineNAttack,SIGNAL(clicked()),this,SLOT(DamageLineNAttack()));
	connect(m_DamageLineNDamage,SIGNAL(clicked()),this,SLOT(DamageLineNDamage()));
	connect(m_CylinderShow,SIGNAL(clicked()),this,SLOT(CylinderWarheadShow()));

	connect(m_pCalculationDisplayed,SIGNAL(clicked()),this,SLOT(DisplayCloseWindow()));


	connect(m_pOpenVariableFile,SIGNAL(clicked()),this,SLOT(OpenParameterFile()));
	connect(m_pSaveVariableFile,SIGNAL(clicked()),this,SLOT(SaveParameterFile()));


	connect(m_BeginLineCall,SIGNAL(clicked()),this,SLOT(LineCallPlot()));
	connect(m_StopLineCall,SIGNAL(clicked()),this,SLOT(LineCallPlot()));
	connect(m_RestorLineCall,SIGNAL(clicked()),this,SLOT(LineCallPlot()));
};
// ��ʼ���˵�
void CMainFrame::InitMenu(void)
{
	 
}
// �˳�
void CMainFrame::Exit()
{
	close();
}

// �������
void CMainFrame::AddInManager(void)
{
	CPluginManagerUI* pPluginManager = new CPluginManagerUI;
	pPluginManager->show();
}


void CMainFrame::slotHome(bool)
{
	VR_Soft::IRenderManager* pIEarthManager = dynamic_cast<VR_Soft::IRenderManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_RENDERSYSTEM));
	VR_Soft::IManipulatorManager* pManipulator = pIEarthManager->GetViewManager()->GetRenderView("mainView")->GetManipulatorManager();
	VR_Soft::IEarthManipulator* pIEarthManipulator = dynamic_cast<VR_Soft::IEarthManipulator*>(pManipulator->GetManipulator("MyEarthManipulator"));
	if (NULL == pIEarthManipulator)
	{
		return;
	}

	pIEarthManipulator->LookHome();
}

void CMainFrame::slotShowText(bool)
{
	// �����Ⱦ����
	VR_Soft::IRenderManager* pIRenderManager = dynamic_cast<VR_Soft::IRenderManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_RENDERSYSTEM));
	if (NULL == pIRenderManager)
	{
		return;
	}
	VR_Soft::IScreenHUD* pIScreenHUD = pIRenderManager->GetScreenManager()->GetScreenHUD("MissleInfo");
	if (NULL == pIScreenHUD)
	{
		return;
	}

	if (m_bShowText)
	{
		pIScreenHUD->Show();
	}
	else
	{
		pIScreenHUD->Hide();
	}

	m_bShowText = !m_bShowText;
}

void CMainFrame::slotTrackNode(bool)
{
	
}

void CMainFrame::slotFullScreen(bool)
{
	 
}

void CMainFrame::slotShowFlyPath(bool)
{
	
}

// ���̰���
void CMainFrame::OnKeyDown(int key)
{
	if (VR_Soft::KEY_Escape == key && m_bFullScreen)
	{
	 
	}
}

void CMainFrame::slotDockWgt()
{

	m_pDocWidget->setMaximumWidth(1000000000);
}


// ��ʼ���ڴ�
bool CMainFrame::InitMemonry()
{
	return (true);
}
bool CMainFrame::StartSim( )
{
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Start);
	posTimer = new QTimer;
	connect(posTimer,SIGNAL(timeout()),this,SLOT(GetTheRockPos()));
	connect(posTimer,SIGNAL(timeout()),this,SLOT(ShowTheDamageWidget()));
	posTimer->start(1000);
	return (true);
}

bool CMainFrame::PauseSim()
{
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Pause);
	return (true);
}

bool CMainFrame::StopSim()
{
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Stop);
	 pIEntityBase->GetEntityDrawAttribute()->SetPosition(BeginPos);
	/*((VR_Soft::IEntityMoveAttribute*)pIEntityBase->GetAttribute(QString::fromLocal8Bit("�˶�����").toStdString()))->SetIndex(0);
	pIEntityBase->NeedUpdate();
	IsRockBoom = false;
	if (posTimer != NULL)
	{
	posTimer->start(1000);
	}*/
	return (true);
}

bool CMainFrame::AccelerateSim()
{
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Accelerate);
	return (true);
}

bool CMainFrame::DecelerateSim()
{
	VR_Soft::ISimManager::GetInstance().SetSimCmd(VR_Soft::ISimManager::Decelerate);
	return (true);
}

bool CMainFrame::updateSim()
{
	const VR_Soft::CDateTime& dtSim = VR_Soft::ISimManager::GetInstance().GetSimTime();
	VR_Soft::VRString strText = dtSim.ToVRString();
	//QString qstrTime = QString QString("%1-%2-%3 %4:%5:%6").arg(nYear).arg(nMonth).arg(nDay).arg(nHour).arg(nMin).arg(dSec);
	m_qLabelSimTime.setText(QString::fromLocal8Bit(strText.c_str()));
	return (true);
}

bool CMainFrame::CreatePathOfParticle(osg::Vec3d m_vStart,osg::Vec3d m_vStop,double m_dHeight)
{
	VR_Soft::IAirLineManager* pIAirLineManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IAirLineManager>(VR_Soft::INSTANCE_NAME_AIRLINESYSTEM);
	if (NULL == pIAirLineManager)
	{
		return false;
	}

	// ����
	VR_Soft::IFeatureGeomtryFactory* pIFeatureGeomteryFactory = pIAirLineManager->GetFeatureGeomtryFactory();
	VR_Soft::IFeatureGeomtry* pIFeatureGeomtry = pIAirLineManager->CreateFeatureGeomtry(pIFeatureGeomteryFactory->CreateLineString());
	VR_Soft::IPath* pIPath = VR_Soft::IPathManager::GetInstance().Create(12345678, "����·��0", pIFeatureGeomtry, NULL);
		double h_s = m_vStart.z();
		double h_c = m_dHeight;
		double h_e = m_vStop.z();
		double x_s = 0.0;
		double x_c = std::sqrt((pow(m_vStart.x() - m_vStop.x(),2)+pow(m_vStart.y() - m_vStop.y(),2)))/2.0;
        double x_e = std::sqrt(pow(m_vStart.x() - m_vStop.x(),2)+pow(m_vStart.y() - m_vStop.y(),2));


		double c = h_s;
		double a = (((h_c - h_s)/x_c) - ((h_e - h_s)/x_e))/(x_c - x_e);
		double b = (h_c - h_s)/x_c - a*x_c;

		double  NStop = 10.0;
		double _NumLon  = (m_vStop.x() - m_vStart.x())/NStop; 
		double _NumLat  = (m_vStop.y() - m_vStart.y())/NStop; 
		double _NumHeight = (m_dHeight - m_vStop.z())/NStop;

		std::vector<osg::Vec3d> _xdList;
		for (double i = 0; i <=NStop; i += 1.0)
		{
			osg::Vec3d  _p;
			double hh = a*(pow(_NumLon*i,2)+pow(_NumLat*i,2))+sqrt(pow(_NumLon*i,2)+pow(_NumLat*i,2))*b+c;
			_p.set(m_vStart.x()+i*_NumLon,m_vStart.y()+i*_NumLat,hh);
			pIPath->AddKeyPoint(_p);
		}
	pIFeatureGeomtry->SetClamping(VR_Soft::IFeatureGeomtry::CLAMP_NONE);
	pIFeatureGeomtry->SetTechnique(VR_Soft::IFeatureGeomtry::TECHNIQUE_GPU);

	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("���������ȡʧ��", ERROR_NOT_COM);
		return (false);
	}

	 // ��ø߳�
	 pIEarthManager->AddFeatureGeometry(pIFeatureGeomtry);
	//����
	pIEntityBase = VR_Soft::IEntityManager::GetInstance().CreateEntity(QString::fromLocal8Bit("����").toStdString(), 123456789);
	// ����˶�����
	VR_Soft::IEntityMoveAttribute* pIMoveAttribute = dynamic_cast<VR_Soft::IEntityMoveAttribute*>(pIEntityBase->GetAttribute("�˶�����"));
	if (NULL == pIMoveAttribute)
	{
		return (false);
	}
	pIMoveAttribute->SetMovePath(pIPath);
	pIEarthManager->AddEntity(pIEntityBase);

	return (false);
}

bool CMainFrame::CreatePathOfMissile()
{
	VR_Soft::IEntityBase* pIEntity = VR_Soft::IEntityManager::GetInstance().CreateEntity("���������켣", VR_Soft::CGUID::Generate());
	//VR_Soft::IAttributeManager::GetInstance().SetCurrentEntityBase(pIEntity);
	// ��þ�γ�߶�
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("���������ȡʧ��", ERROR_NOT_COM);
		return (false);
	}

	// ��ø߳�
// 	VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
// 	pIEarth->AddModel(pIEntity, 0, 0, 0);
// 
	return (false);
}

void CMainFrame::LookAt()
{
	VR_Soft::IEarthManager* pEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	VR_Soft::ISynchroManIpManager* pISynchroManipManager = pEarthManager->GetSynchroManIpManager();

//	pISynchroManipManager->SetViewPoint(osgEarth::Viewpoint(120.0, 24.0, 0, 0, 9000));
}

// ������
void CMainFrame::GraticuleState( void )
{
	// ��õ�����
	VR_Soft::IEarthManager* pEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pEarthManager)
	{
		return;
	}

	QAction* pAction = (QAction*)sender();
	if (!pAction->isChecked())
	{
		pEarthManager->SetGraticuleState(false);
		pAction->setChecked(false);
	}
	else 
	{
		pEarthManager->SetGraticuleState(true);
		pAction->setChecked(true);
	}
}

// ���㹦��
void CMainFrame::DistaceEnable(void)
{
	// ��õ�����
	VR_Soft::IEarthManager* pEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pEarthManager)
	{
		return;
	}

	QAction* pAction = (QAction*)sender();
	if (!pAction->isChecked())
	{
		pEarthManager->DistanceEnable(false);
		pAction->setChecked(false);
	}
	else 
	{
		pEarthManager->DistanceEnable(true);
		pAction->setChecked(true);
	}
}

// �ǹ�����
void CMainFrame::PlotNotRule(void)
{
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("���������ȡʧ��", ERROR_NOT_COM);
		return ;
	}

	VR_Soft::IPlotManager* pIPlotManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IPlotManager>(VR_Soft::INSTANCE_NAME_PLOTSYSTEM);
	if (NULL == pIPlotManager)
	{
		return;
	}

	VR_Soft::IPlot* pIPlot = pIPlotManager->CreatePlot(1, 12345678);

	VR_Soft::IPlaceFeatureGeomtry* pIPlaceFeatureGeomtry = (VR_Soft::IPlaceFeatureGeomtry*)(pIPlot->GetFeatureGeomtry());
	pIEarthManager->AddFeatureGeometry(pIPlaceFeatureGeomtry);
	pIPlaceFeatureGeomtry->SetIcon("D:/test.png");
	pIPlaceFeatureGeomtry->SetText("hello");

	pIPlaceFeatureGeomtry->SetPoint(0, osg::Vec3d(120, 24, 0));


	// �༭��ǰ���
//	pIPlotManager->EidtPlot(pIPlot);
};
//
//��ȡ��λϵͳ
void CMainFrame::GetUnitListToShow(int _len,int _mass,int _time)
{
	QStringList _unitList;
	QString _ss;
	switch(_len)
	{
	case 1:
		_ss = QString::fromLocal8Bit("���ȵ�λ��mm(����)");
		break;
	case 2:
		_ss = QString::fromLocal8Bit("���ȵ�λ��cm(����)");
		break;
	case 3:
		_ss = QString::fromLocal8Bit("���ȵ�λ��m(��)");
		break;
	case 4:
		_ss = QString::fromLocal8Bit("���ȵ�λ��km(ǧ��)");
		break;
	}
	_unitList.push_back(_ss);
	_ss.clear();

	switch(_mass)
	{
	case 1:
		_ss = QString::fromLocal8Bit("������λ��g(��)");
		break;
	case 2:
		_ss = QString::fromLocal8Bit("������λ��kg(ǧ��)");
		break;
	}
	_unitList.push_back(_ss);
	_ss.clear();

	switch(_time)
	{
	case 1:
		_ss = QString::fromLocal8Bit("ʱ�䵥λ��us(΢��)");
		break;
	case 2:
		_ss = QString::fromLocal8Bit("ʱ�䵥λ��ms(����)");
		break;
	case 3:
		_ss = QString::fromLocal8Bit("ʱ�䵥λ��s(��)");
		break;
	}
	_unitList.push_back(_ss);

	//��ʼ��Ŀ���趨�͵����趨����
	_wdialog = new ArgumentDialog(_unitList);               //����
	connect(_wdialog,SIGNAL(EmitChoiseFile()),this,SLOT(GetCsvNum()));
	_pTargetDialog = new TargetZoneDialog(_unitList);       //Ŀ��
};
//
void CMainFrame::CreatesEditsTargetArea()
{
	_pTargetDialog->exec();
	if (_pTargetDialog->IsOKOrCancancle())
	{
		_TargetArea = _pTargetDialog->GetTargetZoneData();
		_wdialog->GetAimLatLon(_TargetArea.AimCenterPointLat,_TargetArea.AimCenterPointLon);
		_pOpDisplay->GetAreaZoneSeting(_TargetArea);
		double AllArea = _TargetArea.Aim_Long*_TargetArea.Aim_Wide;
		_pArgument->GetAllAreaData(AllArea);
		_pParaTree->GetTargetAreaParameter(_TargetArea);
		m_pMissile->setEnabled(true);
	}
	else
	{
		m_pMissile->setEnabled(false);
	}
};
/************������༭��������Ŀ��***********/
void CMainFrame::CreatesEditsMissile()
{
	_wdialog->exec();

	if (_wdialog->IsOKOrCancancle())
	{
		_RockObject = _wdialog->ReadRockParameter();
		//
		_pCsvDialog->SelectCSVfile(_RockObject.FireDistance,_RockObject.FallingAngle);
		_RockObject.InterpolationNumber = _pCsvDialog->GetNumCount();

		_pOpDisplay->GetRockSeting(_RockObject);

		pThread->SetOperationDisplay(_pOpDisplay);
		pThread->start();
		connect(pThread,SIGNAL(EmitFuncOK(bool)),this,SLOT(RockAreaFuncOK(bool)));
		//�����ֵ�������ӹ켣�ߺ�ʵ��
		H_seting->exec();
		double h_s,h_e,h_m;
		H_seting->GetHeightValue(h_s,h_e,h_m);
		osg::Vec3d _pS(_RockObject.FireLon,_RockObject.FireLat,h_s);
		osg::Vec3d _pE(_RockObject.AimLon,_RockObject.AimLat,h_e);
		BoomPos.set(_RockObject.AimLon,_RockObject.AimLat,h_e);
		BeginPos.set(_RockObject.FireLon,_RockObject.FireLat,h_s);

		CreatePathOfParticle(_pS,_pE,h_m);
		_pParaTree->GetRockObjcetParameter(_RockObject);
	}
};
//
void CMainFrame::RockAreaFuncOK(bool b)
{
	if (b)
	{
		IsFuncOK = true;
	}
};
//
void CMainFrame::GetCsvNum()
{
	QString fileName = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("�����ļ�"), "F:/vrSoftJob/BJ_LG/TEGACS(heban)", tr("Image Files (*.csv)"));
	//
	_pCsvDialog->SetFileName(fileName);
	_pCsvDialog->exec();
};
/**************��ʾ����������***********/
void CMainFrame::DisplayCloseWindow()
{
	if (b_DisplayClose == false)
	{
		_FrameZoonArgument->show();
		b_DisplayClose = true;
	} 
	else if (b_DisplayClose == true)
	{
		_FrameZoonArgument->hide();
		b_DisplayClose = false;
	}
};
//
void CMainFrame::CylinderWarheadShow()
{
	int a = 0;
	osg::Node *_pNode;
	if (b_CylinderWarhead == false)
	{
		b_CylinderWarhead = true;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "Cylinder")
			{
				_pNode->setNodeMask(1);
			}
		}
	}
	else if (b_CylinderWarhead == true)
	{
		b_CylinderWarhead = false;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "Cylinder")
			{
				_pNode->setNodeMask(0x0);
			}
		}
	}
};
/**************��Ŀ�����򽻻㲢���л���Ч������***********/
void CMainFrame::DamageLineYDamage()
{
	int a = 0;
	osg::Node *_pNode;
	if (b_LineYDamage == false)
	{
		b_LineYDamage = true;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "DamageLine")
			{
				_pNode->setNodeMask(1);
			}
			m_DamageLineYDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineYDamage.png")));
		}
	}
	else if (b_LineYDamage == true)
	{
		b_LineYDamage = false;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			m_DamageLineYDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/Unable.png")));
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "DamageLine")
			{
				_pNode->setNodeMask(0x0);
			}
		}
	}
}
/**************��Ŀ������û�н������***********/
void CMainFrame::DamageLineNAttack()
{
	int a = 0;
	osg::Node *_pNode;
	if (b_LineNAttack == false)
	{
		b_LineNAttack = true;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			m_DamageLineNAttack->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineNoAttack.png")));
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "NOAttackLine")
			{
				_pNode->setNodeMask(1);
			}
		}
	}
	else if (b_LineNAttack == true)
	{
		b_LineNAttack = false;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			m_DamageLineNAttack->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/Unable.png")));
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "NOAttackLine")
			{
				_pNode->setNodeMask(0x0);
			}
		}
	}
}
/**************��Ŀ�������н��������˺�***********/
void CMainFrame::DamageLineNDamage()
{
	int a = 0;
	osg::Node *_pNode;
	if (b_LineNDamage == false)
	{
		b_LineNDamage = true;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			m_DamageLineNDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/LineNoDamage.png")));
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "LineNoDamage")
			{
				_pNode->setNodeMask(1);
			}
		}
	}
	else if (b_LineNDamage == true)
	{
		b_LineNDamage = false;
		a = _pOpDisplay->GetTheRootGroup()->getNumChildren();
		for (int i = 1; i < a;++i)
		{
			m_DamageLineNDamage->setIcon(QIcon(QString::fromLocal8Bit(":/MainWindow/Image/Unable.png")));
			_pNode = _pOpDisplay->GetTheRootGroup()->getChild(i);
			if (_pNode->getName() == "LineNoDamage")
			{
				_pNode->setNodeMask(0x0);
			}
		}
	}
};
//
//��ѯ������
void CMainFrame::LineCallPlot()
{
	QToolButton* _pButton = dynamic_cast<QToolButton*>(sender());
	if (_pButton != NULL)
	{
		if (_pButton->objectName() == "BeginPlot")
		{
			_pOpDisplay->SetContrlType(1);
		}
		else if (_pButton->objectName() == "StopPlot")
		{
			_pOpDisplay->SetContrlType(2);
		}
		else if(_pButton->objectName() == "RestoPlot")
		{
			_pOpDisplay->SetContrlType(3);
		}
	}
};
//
void CMainFrame::OpenParameterFile()
{
	if (_pXML->OpenXMLFile())
	{
		//
		_TargetArea = _pXML->GetAreaParameter();
		_pTargetDialog->GetConfigZone(_TargetArea);
		_pTargetDialog->exec();
		if (_pTargetDialog->IsOKOrCancancle())
		{
			_TargetArea = _pTargetDialog->GetTargetZoneData();
			_wdialog->GetAimLatLon(_TargetArea.AimCenterPointLat,_TargetArea.AimCenterPointLon);
			_pOpDisplay->GetAreaZoneSeting(_TargetArea);
			double AllArea = _TargetArea.Aim_Long*_TargetArea.Aim_Wide;
			_pArgument->GetAllAreaData(AllArea);
			_pParaTree->GetTargetAreaParameter(_TargetArea);
			m_pMissile->setEnabled(true);
		}
		else
		{
			m_pMissile->setEnabled(false);
		}
		//

		_RockObject = _pXML->GetLgRockParameter();
		int interpolationN = _RockObject.InterpolationNumber;
		std::vector<double> FillAngle = _RockObject.FallingAngle;
		std::vector<double> FillDis = _RockObject.FireDistance;


		_wdialog->GetConfigFileSettings(_RockObject);
		_wdialog->exec();

		if (_wdialog->IsOKOrCancancle())
		{
			_RockObject = _wdialog->ReadRockParameter();

			//�������ѡ��CSV�ļ�
			_pCsvDialog->SelectCSVfile(_RockObject.FireDistance,_RockObject.FallingAngle);
			_RockObject.InterpolationNumber = _pCsvDialog->GetNumCount();
			if (_RockObject.InterpolationNumber == 0)
			{
				_RockObject.InterpolationNumber = interpolationN;
				_RockObject.FallingAngle = FillAngle;
				_RockObject.FireDistance = FillDis;
			}

			_pOpDisplay->GetRockSeting(_RockObject);
			_pOpDisplay->GetRockSeting(_RockObject);
			pThread->SetOperationDisplay(_pOpDisplay);
			pThread->start();
			connect(pThread,SIGNAL(EmitFuncOK(bool)),this,SLOT(RockAreaFuncOK(bool)));
			H_seting->exec();
			double h_s,h_e,h_m;
			H_seting->GetHeightValue(h_s,h_e,h_m);
			osg::Vec3d _pS(_RockObject.FireLon,_RockObject.FireLat,h_s);
			osg::Vec3d _pE(_RockObject.AimLon,_RockObject.AimLat,h_e);

			BoomPos.set(_RockObject.AimLon,_RockObject.AimLat,h_e);
			CreatePathOfParticle(_pS,_pE,h_m);

			_pParaTree->GetRockObjcetParameter(_RockObject);
		}
	}
};
//
void CMainFrame::SaveParameterFile()
{
	_pXML->GetTheUnitSystem(System_US.Get_LengthUnit(),System_US.Get_TimeUnit(),System_US.Get_MassUnit());
	_pXML->SaveXMLFile(_TargetArea,_RockObject);
};
//
void CMainFrame::GetTheRockPos()
{
	osg::Vec3 Rock_pos = pIEntityBase->GetEntityDrawAttribute()->GetPosition();
	double x_ = BoomPos.x() - Rock_pos.x();
	double y_ = BoomPos.y() - Rock_pos.y();
	if ((x_<0.1)&&(y_<0.1))
	{
		IsRockBoom = true;
	}
};
//
void CMainFrame::ShowTheDamageWidget()
{
	if (IsFuncOK&&IsRockBoom)
	{
		_FrameZoon = new ViewerWidget(_pOpDisplay->GetTheRootGroup());
		_FrameZoon->setAttribute(Qt::WA_TranslucentBackground, true);
		connect(_FrameZoon,SIGNAL(SendLevelAndColor(int,QColor)),_pOpDisplay,SLOT(GetChangeLevelColor(int,QColor)));

		_pVbox->addWidget(_FrameZoon,0,0,4,1);
		//��ȡ�������˵����
		_pArgument->GetDamageAreaData(_pOpDisplay->GetDamageAreaData());
		_pArgument->GetMassiveData(_pOpDisplay->GetMassive());

		m_pVieweWidget->hide();
		_FrameZoonArgument->show();
		b_DisplayClose = true;
		posTimer->stop();
	}
};