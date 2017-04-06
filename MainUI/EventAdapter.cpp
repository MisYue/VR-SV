#include "EventAdapter.h"


CEventAdapter::CEventAdapter( QWidget* pWidget/* = NULL*/ )
	:QGraphicsView(pWidget)
{
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

CEventAdapter::~CEventAdapter( void )
{

}

void CEventAdapter::keyPressEvent(QKeyEvent* event)
{
	QPoint pos = QCursor::pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() <= 0)
	{
		setKeyboardModifiers(event);
		m_pGraphicsWindow->getEventQueue()->keyPress(
			(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
	}
	QGraphicsView::keyPressEvent(event);
}

void CEventAdapter::keyReleaseEvent(QKeyEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->keyRelease(
		(osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));

	QGraphicsView::keyReleaseEvent(event);
}

void CEventAdapter::mousePressEvent(QMouseEvent* event)
{
	QPoint pos = event->pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() > 0)
	{
		QGraphicsView::mousePressEvent(event);
	}
	else
	{
		int button = 0;
		switch (event->button())
		{
		case Qt::LeftButton: button = 1; break;
		case Qt::MidButton: button = 2; break;
		case Qt::RightButton: button = 3; break;
		case Qt::NoButton: button = 0; break;
		default: button = 0; break;
		}
		setKeyboardModifiers(event);
		m_pGraphicsWindow->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
	}
}

void CEventAdapter::mouseReleaseEvent(QMouseEvent* event)
{
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);

	QGraphicsView::mouseReleaseEvent(event);
}

void CEventAdapter::mouseDoubleClickEvent(QMouseEvent* event)
{
	QPoint pos = QCursor::pos();
	QList<QGraphicsItem*> listItems = items(mapToScene(pos.x(), pos.y()).toPoint());
	if (listItems.size() > 0)
	{
		return;
	}
	int button = 0;
	switch (event->button())
	{
	case Qt::LeftButton: button = 1; break;
	case Qt::MidButton: button = 2; break;
	case Qt::RightButton: button = 3; break;
	case Qt::NoButton: button = 0; break;
	default: button = 0; break;
	}
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

	QGraphicsView::mouseDoubleClickEvent(event);
}

void CEventAdapter::mouseMoveEvent(QMouseEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseMotion(event->x(), event->y());
	QGraphicsView::mouseMoveEvent(event);
}

void CEventAdapter::wheelEvent(QWheelEvent* event)
{
	setKeyboardModifiers(event);
	m_pGraphicsWindow->getEventQueue()->mouseScroll(
		event->orientation() == Qt::Vertical ?
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN) :
		(event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
	QGraphicsView::wheelEvent(event);
}

void CEventAdapter::resizeEvent(QResizeEvent *event)
{
	if (scene())
	{
		scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
	}

	const QSize& size = event->size();
	m_pGraphicsWindow->resized(x(), y(), size.width(), size.height());
	m_pGraphicsWindow->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
	m_pGraphicsWindow->requestRedraw();

	const QSize& oldSize = event->oldSize();
	int oldWidth = oldSize.width();
	int oldHeight = oldSize.height();

	int newWidth = size.width();
	int newHeight = size.height();

	double widthChangeRatio = double(newWidth) / double(oldWidth);
	double heigtChangeRatio = double(newHeight) / double(oldHeight);
	double aspectRatioChange = widthChangeRatio / heigtChangeRatio;
	QGraphicsView::resizeEvent(event);
}

void CEventAdapter::moveEvent(QMoveEvent* event)
{
	const QPoint& pos = event->pos();
	m_pGraphicsWindow->resized(pos.x(), pos.y(), width(), height());
	m_pGraphicsWindow->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

	QGraphicsView::moveEvent(event);
}

void CEventAdapter::timerEvent(QTimerEvent *event)
{
	scene()->update();
}

void CEventAdapter::setKeyboardModifiers( QInputEvent* event )
{
	int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);  
	unsigned int mask = 0;  
	if ( modkey & Qt::ShiftModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;  
	if ( modkey & Qt::ControlModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;  
	if ( modkey & Qt::AltModifier ) mask |= osgGA::GUIEventAdapter::MODKEY_ALT;  
	m_pGraphicsWindow->getEventQueue()->getCurrentEventState()->setModKeyMask( mask );  
}

