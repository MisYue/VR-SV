#pragma once

#include <QGraphicsView>
#include <QInputEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QTimerEvent>
#include <osgViewer/GraphicsWindow>

class CEventAdapter : public QGraphicsView
{
public:
	CEventAdapter(QWidget* pWidget = NULL);
	~CEventAdapter(void);

protected:
	// 处理按键事件
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);

	// 处理鼠标单击事件
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

	// 处理鼠标双击事件
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);

	// 处理鼠标中轮滑动事件
	virtual void wheelEvent(QWheelEvent* event);

	// 处理窗口大小改变事件
	virtual void resizeEvent(QResizeEvent *event);

	// 处理鼠标移动事件
	virtual void moveEvent(QMoveEvent* event);

	// timerEvent事件
	virtual void timerEvent(QTimerEvent *event);

private:
	void setKeyboardModifiers(QInputEvent* event);

protected:
	osgViewer::GraphicsWindow* m_pGraphicsWindow;
};

