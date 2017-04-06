#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QTimer>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QLabel>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "../../Public/PlotSystem/PlotSystem.h"
#include "ViewerUI.h"
#include "EntityManagerUI.h"
#include "EntityTypeUI.h"
#include "ToolWidget.h"
#include "AttributeUI.h"

#include <QMainWindow>
#include "ui_MainFrame.h"

#include "InitParameterDialog.h"
#include "CsvNumDialog.h"
#include "HeightSeting.h"
#include "XMLOperation.h"

#include <QSplashScreen>

class CAttributeUI;
class CTrajectoryFrame;
class CSatelliteFrame;
class CViewWidget;
class QtTreePropertyBrowser;

class CMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	CMainFrame(QWidget *parent = 0,QSplashScreen *screen = 0);
	~CMainFrame();
protected:
	virtual void paintEvent(QPaintEvent *e);
	//初始化部件
	void InitWidget();
	//初始化工具栏
	void InitTool();
	// 初始化菜单
	void InitMenu(void);
protected:
	// 键盘按下
	virtual void OnKeyDown(int key);
protected slots:
		// 退出
		void Exit(void);
		// 插件管理
		void AddInManager(void);

		void slotHome(bool);
		void slotShowText(bool);
		void slotTrackNode(bool);
		void slotFullScreen(bool);
		void slotShowFlyPath(bool);

		void slotDockWgt();
		// 初始化内存
		bool InitMemonry();
		bool StartSim();
		bool PauseSim();
		bool StopSim();
		bool AccelerateSim();
		bool DecelerateSim();
		bool updateSim();
		bool CreatePathOfParticle(osg::Vec3d m_vStart,osg::Vec3d m_vStop,double m_dHeight);
		bool CreatePathOfMissile();
		void LookAt();
		// 网格线
		void GraticuleState( void );
		// 量算功能
		void DistaceEnable(void);
		// 非规则标绘
		void PlotNotRule();
protected:
	QTimer _timer;
private:
	Ui::CMainFrameClass ui;
	//导弹实体
	VR_Soft::IEntityBase* pIEntityBase;

	CAttributeUI* m_pAttributeUI;

	bool m_bFullScreen;
	QDockWidget* m_pDocWidget;
	bool m_bShowText;

	QPoint mMousePoint;
	bool mMousePressed;
	bool mMax;
	QRect mLocationRect;

	QPoint m_dragPos;
	QLabel m_qLabelSimTime;
	CViewWidget* m_pVieweWidget; // 显示视图窗口
	//
	//仿真控制
	QToolButton* m_pStartBtn;                // 开始按钮
	QToolButton* m_pStopBtn;                 // 停止按钮
	QToolButton* m_pAccelerateBtn;           // 前进按钮
	QToolButton* m_pDecelerateBtn;           // 后退按钮
	QToolButton* m_pPauseBtn;                // 暂停按钮
	QToolButton* m_pFollowTarget;            //跟随弹体 
	//弹体,目标参数设置
	QToolButton* m_pMissile;                // 弹体编辑
	QToolButton* m_pTarget;                 // 目标编辑
	QToolButton* m_pCalculationDisplayed;   // 计算界面显示
	//数据保存重用
	QToolButton* m_pSaveVariableFile;          //保存参数设置
	QToolButton* m_pOpenVariableFile;          //选择参数配置文件
	//毁伤,战斗部控制
	QToolButton* m_DamageLineYDamage;   // 和目标区域有交互的线
	QToolButton* m_DamageLineNDamage;   // 和目标区域有交汇线无伤害
	QToolButton* m_DamageLineNAttack;   // 和目标区域没有交互的线
	QToolButton* m_CylinderShow;        // 战斗部显示隐藏
	//回调绘制毁伤线
	QToolButton* m_BeginLineCall;   // 开始回调线
	QToolButton* m_StopLineCall;   // 暂停回调线
	QToolButton* m_RestorLineCall;   // 重新回调线
	//弹体实体
	//VR_Soft::IEntityBase* pIEntityBase;
	//界面结果是否已显示
	bool b_DisplayClose;
	Bit_UnitSystem System_US;
	//XD
	ArgumentDialog *_wdialog;          //弹体参数部件
	TargetZoneDialog *_pTargetDialog; //目标区域部件
	ViewerWidget* _FrameZoon;
	//目标参数
	TargetAreaParameter _TargetArea;
	osg::Vec3 BoomPos;
	osg::Vec3 BeginPos;
	//弹体参数
	LGRockParameter _RockObject;

	ParameterTree *_pParaTree;
	OperationDisplay *_pOpDisplay;

	DamageAreaData*_pArgument;

	CSVDialog *_pCsvDialog;
	XMLOperation *_pXML;
	ThreadRcokArea *pThread;
	HeightSetingWidget *H_seting;
	//
	//
	bool b_CylinderWarhead;
	bool b_LineNDamage;
	bool b_LineYDamage;
	bool b_LineNAttack;
	//运算是否完成
	bool IsFuncOK;
	//炸弹是否爆炸
	bool IsRockBoom;
	//
	QHBoxLayout *_pHbox;
	QDockWidget *_ParameterList;
	QGroupBox* _FrameZoonArgument;
	QGridLayout* _pVbox;
	QTimer *posTimer;
	//private函数
	void GetUnitListToShow(int,int,int);
protected slots:
	/**************创建或编辑目标区域参数******************/
	void CreatesEditsTargetArea();
	/************弹道导弹目标***********/
	void CreatesEditsMissile();
	//是否计算完成
	void RockAreaFuncOK(bool b);
	//
	void GetCsvNum();
	/**************显示计算结果界面***********/
	void DisplayCloseWindow();
	/**************和目标区域有交互的线***********/
	void DamageLineYDamage();
	/**************和目标区域没有交互的线***********/
	void DamageLineNAttack();
	/**************和目标区域交互但没毁伤***********/
	void DamageLineNDamage();
	/**************战斗部圆柱显示与隐藏*********/
	void CylinderWarheadShow();
	//轮询绘制线
	void LineCallPlot();
	//数据文件操作
	//打开使用已配置参数文件
	void OpenParameterFile();
	//保存配置好参数文件
	void SaveParameterFile();
	//时刻获取弹体的位置
	void GetTheRockPos();
	//显示运算完成部件
	void ShowTheDamageWidget();
};
#endif // MAINFRAME_H
