#pragma once  
#include <QGraphicsScene>  
#include <qgraphicsscene.h>  
#include <QGraphicsSceneEvent>  
#include <QInputEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QTimerEvent>
#include <QtGui/QPainter>  

#include <osgViewer/Viewer>  
#include <osgDB/ReadFile>  
#include <osgGA/TrackballManipulator>  
#include <osgViewer/ViewerEventHandlers>  


class GLScene :  
	public QGraphicsScene  
{  
public:  
	GLScene(QObject *parent = 0);  
	~GLScene(void);  

protected:  
	//绘制场景  
	void drawBackground(QPainter *painter, const QRectF &rect);  
	//窗口更新函数：使用定时器，定时更新  
	void timerEvent(QTimerEvent *);  

protected:  
	//鼠标事件  
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);  

	//键盘按键  
	void keyPressEvent(QKeyEvent * keyEvent);  
	void keyReleaseEvent(QKeyEvent * keyEvent);  

	int   timer_id;  

public:  
	//更新OSG窗口  
	void resizeViewer();  
	void setKeyboardModifiers( QInputEvent* event );//组合键  
public:  
	osg::ref_ptr<osgViewer::View> m_viewer;  
};  