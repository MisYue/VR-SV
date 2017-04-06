#include "GraphicsView.h"


CGraphicsView::CGraphicsView(QWidget* parent):
	QGraphicsView(parent)  
	,m_widget(new QGLWidget(QGLFormat(QGL::DoubleBuffer)))  
	,m_scene(new GLScene(this))  
{
	this->resize(800,600);//�����ӿڴ�С  
	this->setViewport(m_widget);//��m_widget����Ϊ�ӿڣ�Ϊ��ʹ��OpenGL��Ⱦ����Ҫ����һ���µ�QGLWidget��ΪQGraphicsView���ӿ�  
	m_widget->setMouseTracking(true);//���׷��  
	this->viewport()->setMinimumSize(1,1);  

	this->setScene(m_scene);  
	this->setMinimumSize(1,1); //������ͼ����С�ߴ�  
	this->scene()->setSceneRect(0,0,this->width(),this->height());//���ó�����С  
	this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);//������ͼ�ĸ��·�ʽ��������ͼ����  
}


CGraphicsView::~CGraphicsView(void)
{
}

void CGraphicsView::resizeEvent( QResizeEvent *event )
{
	//���³�����С  
	m_scene->setSceneRect(this->rect().left(),this->rect().right(),this->rect().width(),this->rect().height());  
	m_scene->resizeViewer();  
}
