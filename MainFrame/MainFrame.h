#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QTimer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>

#include <osgDB/ReadFile>

#include <osgQt/GraphicsWindowQt>

#include <QtWidgets/QMainWindow>
#include "ui_MainFrame.h"

class CAttributeUI;

class CMainFrame : public QMainWindow
{
	Q_OBJECT

public:
	CMainFrame(QWidget *parent = 0);
	~CMainFrame();


protected:
	//virtual void paintEvent(QPaintEvent *e);

	void InitTool(void);

	// ��ʼ���˵�
	void InitMenu(void);

protected slots:
		//void UpdateViewer (void);
		// �˳�
		void Exit(void);
		// �������
		void AddInManager(void);

protected:

	QTimer _timer;

private:
	Ui::CMainFrameClass ui;

	CAttributeUI* m_pAttributeUI;
};

#endif // MAINFRAME_H
