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

		// �������ڣ�������ߺ󱳾���Ȼ��ʾ��Ч��
		_widgetBase= createWidget("widgetBase",imagefiles[0], size, osgWidget::Widget::LAYER_HIGH);
		_widgetBase->setEventMask(osgWidget::EVENT_ALL);///���ô��ڲ�����Ӧ��������¼���
		_widgetBase->setColor(1.0f, 1.0f, 1.0f, 1.0f);

		// ���䴰�ڣ���ʼ��Ϊ��ȫ͸��ģʽ�����أ�
		_widgetDisplay=createWidget("widgetDisplay",imagefiles[1],size,osgWidget::Widget::LAYER_LOW);
		_widgetDisplay->setColor(1.0f,1.0f,1.0f,0.0f);

		// ��_widgetBase����������¼�����Ӧ�¼�������
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


	/*����¼�������*/
	bool BaseWidget::mouseLeave(osgWidget::Event& event)
	{
	   _mouseState=MOUSE_LEAVE;
	   _isMouseOverBaseWidget=false;
		return true;
	}
	bool BaseWidget::mouseOver(osgWidget::Event& event)
	{
		_mouseState=MOUSE_OVER;
		_location = event.getWindow()->localXY(event.x, event.y);//��ȡ���λ�ã���λ���Դ��ڲ���������_baseCanvas���½�Ϊԭ�㣩
		_location-=osgWidget::XYCoord(_baseCanvas->getWidth()*0.5,_baseCanvas->getHeight()*0.5);///��ԭ��ת����_baseCanvas����
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
