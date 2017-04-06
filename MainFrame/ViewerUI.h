#ifndef _VIEWERUI_H_
#define _VIEWERUI_H_

#pragma once

#include <QWidget>
#include <QGLWidget>
#include <QTimer>
#include <osgQt/GraphicsWindowQt>
#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"

class CViewerUI : public QGLWidget, public VR_Soft::IRenderViewUI
{
	Q_OBJECT

public:
	CViewerUI(void);
	virtual ~CViewerUI(void);

public:
	// 初始化UI
	virtual void InitUI(void* param = NULL, int nParam = 0);
	// 初始化相机
	virtual void InitCamera(osg::Camera* pCamera);
	// 获得界面窗口
	virtual const VR_Soft::VRString GetUIName(void) const;
	// 完成初始化
	virtual void CreateVRWindow(osgViewer::View* pView);
	virtual void paintEvent(QPaintEvent *);
	// 更新UI
	virtual void Update(void* param = NULL, int nParam = 0 );

protected slots:
	// 刷新视图
	void UpdateView(void);

protected:
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
	virtual void ​mousePressEvent(QMouseEvent * event);
	//void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	osgQt::GraphicsWindowQt* m_pGraphicsWindowQt;	
	QTimer _timer;
};


#endif

