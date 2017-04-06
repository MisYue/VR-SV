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
	//��ʼ������
	void InitWidget();
	//��ʼ��������
	void InitTool();
	// ��ʼ���˵�
	void InitMenu(void);
protected:
	// ���̰���
	virtual void OnKeyDown(int key);
protected slots:
		// �˳�
		void Exit(void);
		// �������
		void AddInManager(void);

		void slotHome(bool);
		void slotShowText(bool);
		void slotTrackNode(bool);
		void slotFullScreen(bool);
		void slotShowFlyPath(bool);

		void slotDockWgt();
		// ��ʼ���ڴ�
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
		// ������
		void GraticuleState( void );
		// ���㹦��
		void DistaceEnable(void);
		// �ǹ�����
		void PlotNotRule();
protected:
	QTimer _timer;
private:
	Ui::CMainFrameClass ui;
	//����ʵ��
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
	CViewWidget* m_pVieweWidget; // ��ʾ��ͼ����
	//
	//�������
	QToolButton* m_pStartBtn;                // ��ʼ��ť
	QToolButton* m_pStopBtn;                 // ֹͣ��ť
	QToolButton* m_pAccelerateBtn;           // ǰ����ť
	QToolButton* m_pDecelerateBtn;           // ���˰�ť
	QToolButton* m_pPauseBtn;                // ��ͣ��ť
	QToolButton* m_pFollowTarget;            //���浯�� 
	//����,Ŀ���������
	QToolButton* m_pMissile;                // ����༭
	QToolButton* m_pTarget;                 // Ŀ��༭
	QToolButton* m_pCalculationDisplayed;   // ���������ʾ
	//���ݱ�������
	QToolButton* m_pSaveVariableFile;          //�����������
	QToolButton* m_pOpenVariableFile;          //ѡ����������ļ�
	//����,ս��������
	QToolButton* m_DamageLineYDamage;   // ��Ŀ�������н�������
	QToolButton* m_DamageLineNDamage;   // ��Ŀ�������н��������˺�
	QToolButton* m_DamageLineNAttack;   // ��Ŀ������û�н�������
	QToolButton* m_CylinderShow;        // ս������ʾ����
	//�ص����ƻ�����
	QToolButton* m_BeginLineCall;   // ��ʼ�ص���
	QToolButton* m_StopLineCall;   // ��ͣ�ص���
	QToolButton* m_RestorLineCall;   // ���»ص���
	//����ʵ��
	//VR_Soft::IEntityBase* pIEntityBase;
	//�������Ƿ�����ʾ
	bool b_DisplayClose;
	Bit_UnitSystem System_US;
	//XD
	ArgumentDialog *_wdialog;          //�����������
	TargetZoneDialog *_pTargetDialog; //Ŀ�����򲿼�
	ViewerWidget* _FrameZoon;
	//Ŀ�����
	TargetAreaParameter _TargetArea;
	osg::Vec3 BoomPos;
	osg::Vec3 BeginPos;
	//�������
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
	//�����Ƿ����
	bool IsFuncOK;
	//ը���Ƿ�ը
	bool IsRockBoom;
	//
	QHBoxLayout *_pHbox;
	QDockWidget *_ParameterList;
	QGroupBox* _FrameZoonArgument;
	QGridLayout* _pVbox;
	QTimer *posTimer;
	//private����
	void GetUnitListToShow(int,int,int);
protected slots:
	/**************������༭Ŀ���������******************/
	void CreatesEditsTargetArea();
	/************��������Ŀ��***********/
	void CreatesEditsMissile();
	//�Ƿ�������
	void RockAreaFuncOK(bool b);
	//
	void GetCsvNum();
	/**************��ʾ����������***********/
	void DisplayCloseWindow();
	/**************��Ŀ�������н�������***********/
	void DamageLineYDamage();
	/**************��Ŀ������û�н�������***********/
	void DamageLineNAttack();
	/**************��Ŀ�����򽻻���û����***********/
	void DamageLineNDamage();
	/**************ս����Բ����ʾ������*********/
	void CylinderWarheadShow();
	//��ѯ������
	void LineCallPlot();
	//�����ļ�����
	//��ʹ�������ò����ļ�
	void OpenParameterFile();
	//�������úò����ļ�
	void SaveParameterFile();
	//ʱ�̻�ȡ�����λ��
	void GetTheRockPos();
	//��ʾ������ɲ���
	void ShowTheDamageWidget();
};
#endif // MAINFRAME_H
