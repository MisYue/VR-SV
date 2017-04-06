#include "compassEventHandle.h"
#include <iostream>

namespace VR_Soft
{
	compassEventHandle::compassEventHandle(Compass* compass):
	_compass(compass),
	_alpha(0.0)
	{

	}

	compassEventHandle::~compassEventHandle(void)
	{
	}

	bool compassEventHandle::handle(const osgGA::GUIEventAdapter&,osgGA::GUIActionAdapter& aa)
	{
		switch(_compass->_mouseState)
		{		
		case Compass::MOUSE_PUSH:
			{
				////该处发送漫游向量
				_compass->sendPosition();
				break;
			}
		case Compass::MOUSE_OVER:
			{
				// TODO: 显示有BUG；见BUG库683
				/*///鼠标移动是控件动画控制
				double angle=atan2f(_compass->getXYcoord().y(),_compass->getXYcoord().x())*180/3.14;
				_compass->getShadowCanvas()->setRotate(angle-45);
				_compass->getShadowCanvas()->update();*/
				break;
			}
		default:
			break;
		}
		return false;    
	}
}
