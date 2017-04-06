#include "GLScene.h"  


GLScene::GLScene(QObject *parent):  
QGraphicsScene(parent)  
	,m_viewer(NULL)  
	,timer_id(0)  
{  
	//OSG初始化  
	timer_id = startTimer(0);//当定时器触发时，应用程序会发送一个QTimerEvent,如果参数为0，那么定时器事件每次发生时没有窗口系统事件处理。  
}  


GLScene::~GLScene(void)  
{  
}  

//绘制场景  
void GLScene::drawBackground( QPainter *painter, const QRectF &rect )   
{  
	painter->beginNativePainting();  
	painter->setRenderHint(QPainter::Antialiasing);//抗锯齿  
	//m_viewer->getViewerBase()->frame();  
	painter->endNativePainting();  

}  

//窗口更新函数  
void GLScene::timerEvent(QTimerEvent *)  
{  
	this->update();  
}  

void GLScene::mousePressEvent( QGraphicsSceneMouseEvent * mouseEvent )  
{  
	//std::cout<<"mousePressEvent"<<std::endl;  
	QGraphicsScene::mousePressEvent(mouseEvent);  

	int button = 0;  
	switch ( mouseEvent->button() )  
	{  
	case Qt::LeftButton: button = 1; break;  
	case Qt::MidButton: button = 2; break;  
	case Qt::RightButton: button = 3; break;  
	case Qt::NoButton: button = 0; break;  
	default: button = 0; break;  
	}  
	//_gw->getEventQueue()->mouseButtonRelease( event->x(), event->y(), button );  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->mouseButtonPress( mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), button );  
}  

void GLScene::mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent )  
{  
	//std::cout<<"mouseReleaseEvent"<<std::endl;  
	QGraphicsScene::mouseReleaseEvent(mouseEvent);  

	int button = 0;  
	switch ( mouseEvent->button() )  
	{  
	case Qt::LeftButton: button = 1; break;  
	case Qt::MidButton: button = 2; break;  
	case Qt::RightButton: button = 3; break;  
	case Qt::NoButton: button = 0; break;  
	default: button = 0; break;  
	}  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->mouseButtonRelease( mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), button );  

}  



void GLScene::mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent )  
{  
	//std::cout<<"mouseMoveEvent"<<std::endl;  
	QGraphicsScene::mouseMoveEvent(mouseEvent);  

	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->mouseMotion( mouseEvent->scenePos().x(), mouseEvent->scenePos().y());  
}  

void GLScene::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * mouseEvent )  
{  
	//std::cout<<"mouseDoubleClickEvent"<<std::endl;  
	QGraphicsScene::mouseDoubleClickEvent(mouseEvent);  
	int button = 0;  
	switch ( mouseEvent->button() )  
	{  
	case Qt::LeftButton: button = 1; break;  
	case Qt::MidButton: button = 2; break;  
	case Qt::RightButton: button = 3; break;  
	case Qt::NoButton: button = 0; break;  
	default: button = 0; break;  
	}  

	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->mouseDoubleButtonPress( mouseEvent->scenePos().x(), mouseEvent->scenePos().y(), button );  
}  

void GLScene::wheelEvent( QGraphicsSceneWheelEvent * wheelEvent )  
{  
	//std::cout<<"wheelEvent"<<std::endl;  
	QGraphicsScene::wheelEvent(wheelEvent);  

	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->mouseScroll(  
		wheelEvent->orientation() == Qt::Vertical ?  
		(wheelEvent->delta()>0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :  
		(wheelEvent->delta()>0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT) );  

}  

void GLScene::keyPressEvent( QKeyEvent * keyEvent )  
{  
	setKeyboardModifiers(keyEvent);  

	/*int value = s_QtKeyboardMap.remapKey( keyEvent );  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->keyPress( value );  */
	QGraphicsScene::keyPressEvent(keyEvent);  
}  

void GLScene::keyReleaseEvent( QKeyEvent * keyEvent )  
{  
	//std::cout<<"keyReleaseEvent"<<std::endl;  
	QGraphicsScene::keyReleaseEvent(keyEvent);  

	//int value = s_QtKeyboardMap.remapKey( keyEvent );  
	//(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->keyRelease( value );  
	QGraphicsScene::keyPressEvent(keyEvent);  
}  

//OSG场景窗口更新  
void GLScene::resizeViewer()  
{  
	//更新OSG窗口大小  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->resized(this->sceneRect().x(),this->sceneRect().y(),this->sceneRect().width(),this->sceneRect().height());  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->windowResize(this->sceneRect().x(),this->sceneRect().y(),this->sceneRect().width(),this->sceneRect().height());//?  更新状态S按键  

	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->requestRedraw();//?  

}  

//组合键  
void GLScene::setKeyboardModifiers( QInputEvent* event )  
{  
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);  
	unsigned int mask = 0;  
	if ( modkey & Qt::ShiftModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;  
	if ( modkey & Qt::ControlModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;  
	if ( modkey & Qt::AltModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;  
	(dynamic_cast<osgViewer::GraphicsWindow*> (m_viewer->getCamera()->getGraphicsContext()))->getEventQueue()->getCurrentEventState()->setModKeyMask( mask );  
}  