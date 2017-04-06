#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroManipulator.h"
#include "zoom.h"
#include <iostream>

namespace VR_Soft
{
	Zoom::Zoom(CSynchroManipulator *pSynchroManipulator,const osg::Vec4& color,std::string *imagesFile):
    BaseWidget(color,osg::Vec2(0,0),osg::Vec2(20,140),imagesFile),m_pSynchroManipulator(pSynchroManipulator)
	{
		_clickCount[0]=0;
		_slider= createWidget("slider",imagesFile[2],osg::Vec2(18,12),osgWidget::Widget::LAYER_HIGH);
		_slider->setColor(osgWidget::Color(1.0f, 1.0f, 1.0f, 0.0f));
		_minusHoverWidget=createWidget(
			"minusHoverWidget",
			"F:\\3DScene\\bin\\release\\Resources\\hudImage\\zoom_minus.png",
			osg::Vec2(20,140),
			osgWidget::Widget::LAYER_LOW);
		_plusHoverWidget=createWidget(
			"plusHoverWidget",
			"F:\\3DScene\\bin\\release\\Resources\\hudImage\\zoom_plus.png",
			osg::Vec2(20,140),
			osgWidget::Widget::LAYER_LOW);
		_minusHoverWidget->setColor(osgWidget::Color(1.0f, 1.0f, 1.0f, 0.0f));
		_plusHoverWidget->setColor(osgWidget::Color(1.0f, 1.0f, 1.0f, 0.0f));


		// TODO:中间滑动控件，本版本暂时隐藏，不起作用
		//getBaseCanvas()->addWidget(_slider,1,65);
		getBaseCanvas()->addWidget(_plusHoverWidget,0,0);
		getBaseCanvas()->addWidget(_minusHoverWidget,0,0);
		getBaseCanvas()->getBackground()->addColor(0.0f,0.0f,0.0f,-0.6f);

		_sliderPingHengDianY=_slider->getY();


		getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f,1.0f);
		getBaseWidget()->setColor(0.0f,0.0f,0.0f,-0.5f);
		getSlider()->setColor(1.0f, 1.0f, 1.0f, 1.0f);		
		getPlusWidget()->setColor(1.0,1.0,1.0,0.0);
		getMinusWidget()->setColor(1.0,1.0,1.0,0.0);

	}

	Zoom::~Zoom()
	{

	}

	bool Zoom::mousePush(osgWidget::Event& event)
	{   
		_mouseState=MOUSE_PUSH;
		return true;
	}

	bool Zoom::mouseLeave(osgWidget::Event& event)
	{
		_isMouseOverBaseWidget=false;
		_mouseState=MOUSE_LEAVE;
		return true;
	}

	bool Zoom::mouseDrag(osgWidget::Event& event)
	{
		_mouseState=MOUSE_DRAG;

		if (_slider->getY()-_sliderPingHengDianY>=45)
		{
			event.y>=0?(_slider->setY(_sliderPingHengDianY+45)):(_slider->addY(event.y));
		}
		else if(_slider->getY()-_sliderPingHengDianY<=-45)
		{
			event.y>=0?(_slider->addY(event.y)):(_slider->setY(_sliderPingHengDianY-45));
		}
		else
			_slider->addY(event.y);
		_clickCount[0]+=event.y;
		std::cout<<"clickCount="<<_clickCount[0]<<std::endl;
		return true;
	}

	///控件位置更新
	void Zoom::resetCanvasPosition(double x,double y)
	{
		getBaseCanvas()->setX(x-83);
		getBaseCanvas()->setY(y-310);
		//getBaseCanvas()->update();
	}

	/// 发送鼠标点击位置
	void Zoom::sendClickCount(double value)
	{
		m_pSynchroManipulator->SlotZoom(value);
	}

}