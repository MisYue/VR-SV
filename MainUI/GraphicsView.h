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
	//更新视图的时候，更新场景  
	void resizeEvent(QResizeEvent *event);  

public:  
	QGLWidget *m_widget;  
	GLScene *m_scene;  
};

