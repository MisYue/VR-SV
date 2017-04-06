#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroManipulator.h"
#include "walker.h"
#include <iostream>

namespace VR_Soft
{
	Walker::Walker(CSynchroManipulator *pSynchroManipulator, const osg::Vec4& color, std::string *imagesFile):
		BaseWidget(color,osg::Vec2(0,0),
		osg::Vec2(50,50),imagesFile),
		_direction(0.0,0.0),
		m_pSynchroManipulator(pSynchroManipulator)
	{
		getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0);
	}

	Walker::~Walker()
	{

	}

	///漫游方向向量发送器
	void Walker::sendPosition()
	{
		m_pSynchroManipulator->SlotTraval(_direction);
	}

	bool Walker::mousePush(osgWidget::Event& event)
	{   
		_mouseState=MOUSE_PUSH;
		_direction=osg::Vec2f(getXYcoord().x(),getXYcoord().y());
		_direction.normalize();
		
		return true;
	}
	bool Walker::mouseRelease(osgWidget::Event& event)
	{
		_direction=osg::Vec2f(0.0,0.0);

	   return true;
	}


	///控件位置更新
	void Walker::resetCanvasPosition(double x,double y)
	{
		getBaseCanvas()->setX(x-100);
		getBaseCanvas()->setY(y-160);
	}
}
