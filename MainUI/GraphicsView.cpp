#include "GraphicsView.h"


CGraphicsView::CGraphicsView(QWidget* parent):
	QGraphicsView(parent)  
	,m_widget(new QGLWidget(QGLFormat(QGL::DoubleBuffer)))  
	,m_scene(new GLScene(this))  
{
	this->resize(800,600);//设置视口大小  
	this->setViewport(m_widget);//将m_widget设置为视口：为了使用OpenGL渲染，你要设置一个新的QGLWidget作为QGraphicsView的视口  
	m_widget->setMouseTracking(true);//鼠标追踪  
	this->viewport()->setMinimumSize(1,1);  

	this->setScene(m_scene);  
	this->setMinimumSize(1,1); //设置视图的最小尺寸  
	this->scene()->setSceneRect(0,0,this->width(),this->height());//设置场景大小  
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//设置视图的更新方式：整个视图更新  
}


CGraphicsView::~CGraphicsView(void)
{
}

void CGraphicsView::resizeEvent( QResizeEvent *event )
{
	//更新场景大小  
	m_scene->setSceneRect(this->rect().left(),this->rect().right(),this->rect().width(),this->rect().height());  
	m_scene->resizeViewer();  
}
