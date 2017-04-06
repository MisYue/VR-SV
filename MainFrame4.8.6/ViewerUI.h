#ifndef _VIEWERUI_H_
#define _VIEWERUI_H_

#pragma once

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <osgQt/GraphicsWindowQt>
#include <osg/Camera>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"


class CViewerUI : public QObject, public VR_Soft::IRenderViewUI
{
	Q_OBJECT

public:
	CViewerUI(const VR_Soft::VRString& strUIName);
	virtual ~CViewerUI(void);

public: 
	// 获得三维窗口
	QWidget* GetRenderWindow(void) const;

public:
	// 初始化UI
	virtual void InitUI(void* param = NULL, int nParam = 0);
	// 初始化相机
	virtual void InitCamera(osg::Camera* pCamera);
	// 获得界面窗口
	virtual const VR_Soft::VRString GetUIName(void) const;
	// 完成初始化
	virtual void CreateVRWindow(osgViewer::View* pView);
	//virtual void paintEvent(QPaintEvent *);
	// 更新UI
	virtual void Update(void* param = NULL, int nParam = 0 );

protected : // slots:
	// 刷新视图
	void UpdateView(void);

protected:
	bool eventFilter(QObject *obj, QEvent *event);

protected:
	void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event) ;
	void mousePressEvent ( QMouseEvent * event );
//	void resizeEvent( QResizeEvent* event );
	//void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	osgQt::GraphicsWindowQt* m_pGraphicsWindowQt;	
	VR_Soft::VRString m_strUIName;
	osg::Camera* m_pCamera;
};


#endif

