#pragma once
#include <QGraphicsView>  
#include <QGLWidget>  
#include <QtGui/QResizeEvent>  

#include "GLScene.h"  
class CGraphicsView  :   
	public QGraphicsView
{
public:
	CGraphicsView(QWidget* parent = NULL);
	~CGraphicsView(void);

protected:  
	//������ͼ��ʱ�򣬸��³���  
	void resizeEvent(QResizeEvent *event);  

public:  
	QGLWidget *m_widget;  
	GLScene *m_scene;  
};

