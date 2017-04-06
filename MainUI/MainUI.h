#ifndef MAINUI_H
#define MAINUI_H

#include <QtGui/QWidget>
#include "ui_MainUI.h"

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <osgQt/GraphicsWindowQt>
#include <osg/Camera>

#ifndef Q_MOC_RUN
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#endif
#include "EventAdapter.h"

namespace VR_Soft
{
	class IViewManager;
}

class CViewerUI;

class CMainUI : public osgQt::GLWidget, public VR_Soft::IRenderViewUI
{
	Q_OBJECT

public:
	CMainUI(QWidget *parent = 0, Qt::WFlags flags = 0);
	virtual ~CMainUI();

public:
	// ��ʼ��UI
	virtual void InitUI(void* param = NULL, int nParam = 0);
	// ��ʼ�����
	virtual void InitCamera(osg::Camera* pCamera);
	// ��ý��洰��
	virtual const VR_Soft::VRString GetUIName(void) const;
	// ��ɳ�ʼ��
	virtual void CreateVRWindow(osgViewer::View* pView);
	//virtual void paintEvent(QPaintEvent *);
	// ����UI
	virtual void Update(void* param = NULL, int nParam = 0 );

	protected slots:
		// ˢ����ͼ
		//void UpdateView(void);

protected:
	/*void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event) ;*/
	//	void mousePressEvent ( QMouseEvent * event );
	void resizeEvent( QResizeEvent* event );
	//void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	//	osgQt::GraphicsWindowQt* m_pGraphicsWindowQt;
	//	CGraphicsView* m_glview;
	//	osgViewer::GraphicsWindow* m_pGraphicsWindow;
	VR_Soft::VRString m_strUIName;
	osg::Camera* m_pCamera;

protected:
	void paintEvent(QPaintEvent *e);

private:
//	Ui::CMainUIClass ui;

private:
	VR_Soft::IViewManager* m_pIViewManager;
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
	//CViewerUI* m_p3DViewUI;
	//CViewerUI* m_p2DViewUI;
};

#endif // MAINUI_H
