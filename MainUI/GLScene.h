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
	//���Ƴ���  
	void drawBackground(QPainter *painter, const QRectF &rect);  
	//���ڸ��º�����ʹ�ö�ʱ������ʱ����  
	void timerEvent(QTimerEvent *);  

protected:  
	//����¼�  
	void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);  
	void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);  

	//���̰���  
	void keyPressEvent(QKeyEvent * keyEvent);  
	void keyReleaseEvent(QKeyEvent * keyEvent);  

	int   timer_id;  

public:  
	//����OSG����  
	void resizeViewer();  
	void setKeyboardModifiers( QInputEvent* event );//��ϼ�  
public:  
	osg::ref_ptr<osgViewer::View> m_viewer;  
};  