#include "../../Public/VRSoft.h"
#include "walkerEventHandle.h"
#include <iostream>

namespace VR_Soft
{
	walkerEventHandle::walkerEventHandle(Walker* walker):
	_walker(walker),
	_alpha(0.0)
	{

	}

	walkerEventHandle::~walkerEventHandle(void)
	{
	}

	bool walkerEventHandle::handle(const osgGA::GUIEventAdapter&,osgGA::GUIActionAdapter& aa)
	{
		switch(_walker->_mouseState)
		{		
		case Walker::MOUSE_PUSH:
			{
				////�ô�������������
				_walker->sendPosition();
				break;
			}
		case Walker::MOUSE_OVER:
			{
				// TODO: ��ʾ��BUG����BUG��683
				//double angle=atan2f(_walker->getXYcoord().y(),_walker->getXYcoord().x())*180/3.14;
				//_walker->getShadowCanvas()->setRotate(angle-45);
				//_walker->getShadowCanvas()->update();
				break;
			}		
		default:
			break;
		}

		return false;    
	}
}