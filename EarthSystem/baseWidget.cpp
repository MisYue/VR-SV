#include "../../Public/VRSoft.h"
#include "BaseWidget.h"
#include <iostream>

namespace VR_Soft
{

	bool BaseWidget::_isMouseOverBaseWidget=false;

	BaseWidget::BaseWidget(const osg::Vec4& color,osg::Vec2 location,osg::Vec2 size, std::string *imagefiles):
	_location(0, 0)
	{

		_baseCanvas = new osgWidget::Canvas("baseCanvas");
		_baseCanvas->getBackground()->setColor(color.x(),color.y(),color.z(),color.w());
		_baseCanvas->setPosition(osgWidget::matrix_type(location.x()),osgWidget::matrix_type(location.y()),0);

		// 基本窗口，鼠标移走后背景仍然显示的效果
		_widgetBase= createWidget("widgetBase",imagefiles[0], size, osgWidget::Widget::LAYER_HIGH);
		_widgetBase->setEventMask(osgWidget::EVENT_ALL);///设置窗口部件响应所有鼠标事件。
		_widgetBase->setColor(1.0f, 1.0f, 1.0f, 1.0f);

		// 渐变窗口：初始化为完全透明模式（隐藏）
		_widgetDisplay=createWidget("widgetDisplay",imagefiles[1],size,osgWidget::Widget::LAYER_LOW);
		_widgetDisplay->setColor(1.0f,1.0f,1.0f,0.0f);

		// 绑定_widgetBase部件的鼠标事件与响应事件处理函数
		_widgetBase->addCallback(new osgWidget::Callback(&BaseWidget::mouseLeave, this, osgWidget::EVENT_MOUSE_LEAVE));
		_widgetBase->addCallback(new osgWidget::Callback(&BaseWidget::mouseOver, this, osgWidget::EVENT_MOUSE_OVER));
		_widgetBase->addCallback(new osgWidget::Callback(&BaseWidget::mousePush, this, osgWidget::EVENT_MOUSE_PUSH));
		_widgetBase->addCallback(new osgWidget::Callback(&BaseWidget::mouseRelease, this, osgWidget::EVENT_MOUSE_RELEASE));
		_widgetBase->addCallback(new osgWidget::Callback(&BaseWidget::mouseDrag,this, osgWidget::EVENT_MOUSE_DRAG));
		

		_baseCanvas->addWidget(_widgetBase,0.0f,0.0f);
		_baseCanvas->addWidget(_widgetDisplay,0.0f,0.0f);
		_baseCanvas->resize();
	}

	BaseWidget::~BaseWidget(void)
	{
	}


	osgWidget::Widget* BaseWidget::createWidget(std::string name,std::string imageFile,osg::Vec2 size, osgWidget::Widget::Layer layer) 
	{
		osg::ref_ptr<osgWidget::Widget> widget=new osgWidget::Widget(name,osgWidget::point_type(size.x()),osgWidget::point_type(size.y()));
		widget->setImage(imageFile);
		widget->setTexCoord(0.0f, 0.0f, osgWidget::Widget::LOWER_LEFT);
		widget->setTexCoord(1.0f, 0.0f, osgWidget::Widget::LOWER_RIGHT);
		widget->setTexCoord(1.0f, 1.0f, osgWidget::Widget::UPPER_RIGHT);
		widget->setTexCoord(0.0f, 1.0f, osgWidget::Widget::UPPER_LEFT);
		widget->setLayer(layer);
		return widget.release();
	}


	/*鼠标事件处理函数*/
	bool BaseWidget::mouseLeave(osgWidget::Event& event)
	{
	   _mouseState=MOUSE_LEAVE;
	   _isMouseOverBaseWidget=false;
		return true;
	}
	bool BaseWidget::mouseOver(osgWidget::Event& event)
	{
		_mouseState=MOUSE_OVER;
		_location = event.getWindow()->localXY(event.x, event.y);//获取鼠标位置（该位置以窗口部件管理器_baseCanvas左下角为原点）
		_location-=osgWidget::XYCoord(_baseCanvas->getWidth()*0.5,_baseCanvas->getHeight()*0.5);///将原点转换到_baseCanvas中心
		_isMouseOverBaseWidget=true;
		return true;
	}
	bool BaseWidget::mousePush(osgWidget::Event& event)
	{
	   _mouseState=MOUSE_PUSH;
		 return true;
	}
	bool BaseWidget::mouseRelease(osgWidget::Event& event)
	{
		_mouseState=MOUSE_RELEASE;
		return true;
	}
	bool BaseWidget::mouseDrag(osgWidget::Event& event)
	{
		_mouseState=MOUSE_DRAG;
		return true;
	}
}
