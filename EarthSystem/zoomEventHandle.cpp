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
		case Zoom::MOUSE_PUSH:////���ڸô���������ֵ
			{
				if (BaseWidget::_isMouseOverBaseWidget)
				{
					//��Ӧ���������,������ʱ����
					double y=_zoom->getXYcoord().y(); 
					_zoom->setClickCout(y);
					//////���λ�����ſؼ��顰+��λ�ã���_plusHoverWidget��_minusHoverWidget��_widgetDisplay��alphaΪ1.0,0.0,0.0��ֻ��ʾ_plusHoverWidget
					if(y>=50)
					{ 		
						_zoom->getPlusWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						_zoom->getMinusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 0);
					}
					//////���λ�����ſؼ��顰-��λ�ã���_plusHoverWidget��_minusHoverWidget��_widgetDisplay��alphaΪ0.0,1.0,0.0��ֻ��ʾ_minusHoverWidget
					else if(y<=-50)
					{ 
						_zoom->getPlusWidget()->setColor(1.0f, 1.0f, 1.0f, 0.0f);
						_zoom->getMinusWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0f);
						_zoom->getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 0);
					}
					////////���λ�����ſؼ�������λ�ã���_plusHoverWidget��_minusHoverWidget��_widgetDisplay��alphaΪ0.0,0.0,1.0��ֻ��ʾ_widgetDisplay
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
