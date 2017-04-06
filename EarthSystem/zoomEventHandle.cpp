#include "zoomEventHandle.h"
#include <iostream>

namespace VR_Soft
{
	zoomEventHandle::zoomEventHandle(Zoom* zoom)
		:_zoom(zoom),
		_alpha(0.0)
	{
	}

	zoomEventHandle::~zoomEventHandle(void)
	{
	}

	bool zoomEventHandle::handle(const osgGA::GUIEventAdapter&ea,osgGA::GUIActionAdapter& aa)
	{		
		switch(_zoom->_mouseState)
		{	
		case Zoom::MOUSE_PUSH:////可在该处发送缩放值
			{
				if (BaseWidget::_isMouseOverBaseWidget)
				{
					//响应点击“＋”,“－”时动画
					double y=_zoom->getXYcoord().y(); 
					_zoom->setClickCout(y);
					//////鼠标位于缩放控件组“+”位置，置_plusHoverWidget，_minusHoverWidget，_widgetDisplay的alpha为1.0,0.0,0.0即只显示_plusHoverWidget
					if(y>=50)
					{ 		
						_zoom->getPlusWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						_zoom->getMinusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 0);
					}
					//////鼠标位于缩放控件组“-”位置，置_plusHoverWidget，_minusHoverWidget，_widgetDisplay的alpha为0.0,1.0,0.0即只显示_minusHoverWidget
					else if(y<=-50)
					{ 
						_zoom->getPlusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getMinusWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 0);
					}
					////////鼠标位于缩放控件组其它位置，置_plusHoverWidget，_minusHoverWidget，_widgetDisplay的alpha为0.0,0.0,1.0即只显示_widgetDisplay
					else
					{
						_zoom->getPlusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getMinusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f,1.0);
					}
				}
				
				break;
			}
		case Zoom::MOUSE_RELEASE:
			{
				_zoom->getSlider()->setY(_zoom->getSliderPingHengDianY());

				_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f,1.0);
				_zoom->getSlider()->setColor(1.0f, 1.0f, 1.0f, 1.0f);		
				_zoom->getPlusWidget()->setColor(1.0,1.0,1.0,0.0);
				_zoom->getMinusWidget()->setColor(1.0,1.0,1.0,0.0);
				break;
			}
		default:
			break;
		}
		return false;    
	}
}
