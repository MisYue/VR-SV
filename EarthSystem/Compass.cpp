#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroManipulator.h"
#include "Compass.h"
#include <iostream>

namespace VR_Soft
{
	Compass::Compass(CSynchroManipulator *pSynchroManipulator,const osg::Vec4& color, VRString *imagefiles)
	:BaseWidget(color,osg::Vec2(0,0),osg::Vec2(80,80),imagefiles)
	,_direction(0.0,0.0)
	,PI(3.14)
	,angle(0.0)
	,_deltaMove(0.0,0.0),
	m_pSynchroManipulator(pSynchroManipulator)
	{
		_widgetN=createWidget("potlightWidget",imagefiles[3],osg::Vec2(30,30),osgWidget::Widget::LAYER_LOW);
		_widgetN->setColor(osgWidget::Color(1.0f, 1.0f, 1.0f, 1.0f));
		_widgetHoverN=createWidget("potlightWidget",imagefiles[4],osg::Vec2(30,30),osgWidget::Widget::LAYER_LOW);
		_widgetHoverN->setColor(osgWidget::Color(1.0f, 1.0f, 1.0f, 0.0f));

		_ringShadowCanvas=new osgWidget::Canvas("ringShadowCanvas");
		_ringShadowCanvas->getBackground()->setColor(color.x(),color.y(),color.z(),color.w());
		_ringShadowCanvas->addWidget(_widgetHoverN,0.0f,0.0f);
		_ringShadowCanvas->addWidget(_widgetN,0.0f,0.0f);
		_ringShadowCanvas->setRotate(45);
		_ringShadowCanvas->setVisibilityMode(osgWidget::Window::VM_ENTIRE);///设置旋转是窗口部件不被裁剪

		/////将Compass图表缩小放置与中心
		getDisplayWidget()->setSize(50,50);
		getDisplayWidget()->setOrigin(15,15);

		getDisplayWidget()->setColor(1.0f, 1.0f, 1.0f, 1.0);
		m_pSynchroManipulator->SetCompass(this);
	}

	Compass::~Compass()
	{

	}

	bool Compass::mousePush(osgWidget::Event& event)
	{   
		_mouseState=MOUSE_PUSH;
		_direction=osg::Vec2f(getXYcoord().x(),getXYcoord().y());//获取鼠标点击时所处于罗盘中的位置向量
		return true;
	}

	bool Compass::mouseLeave(osgWidget::Event& event)
	{
		_mouseState=MOUSE_LEAVE;
		_isMouseOverBaseWidget=false;
		_direction=osgWidget::XYCoord(0,0);//位置向量置为０向量
		return true;
	}

	/*拖拽旋转实现方法：１，获取拖拽前鼠标所在点位置向量getXYcoord()，并判断该点位置是否变化；
	*２，获取拖拽位移（event.x，event.y）
	*３，若拖拽前鼠标所在点位置未变，是则位移向量累加，否则位移向量为（event.x，event.y）
	*４，由位移向量和拖拽前鼠标所在点位置，计算出拖拽后鼠标位置向量(getXYcoord()+)
	*/
	bool Compass::mouseDrag(osgWidget::Event& event)
	{
		_mouseState=MOUSE_DRAG;
		static osgWidget::XYCoord temp;
		int s=getXYcoord().x()*getXYcoord().x()+getXYcoord().y()*getXYcoord().y();   ////判断鼠标位置区间，若位于观察图标(观察图标大小为２７×２７)之外，这响应拖动消息，否则不响应
		if(s<27*27)
			return true;
		osgWidget::XYCoord location=getXYcoord();

		///判断拖拽前鼠标所在点位置是否变化，是：拖拽位移不累加，否：拖拽位移累加
		_deltaMove=temp==getXYcoord() ? (_deltaMove+osgWidget::XYCoord(event.x,event.y)) : (osgWidget::XYCoord(event.x,event.y));

		angle=atan2f(getXYcoord().y() + _deltaMove.y(),getXYcoord().x()+_deltaMove.x())*180/3.14;//拖拽后指北针位置角度

		std::cout<<"angle="<<angle<<std::endl;
		temp=getXYcoord();
		return true;
	}

	///漫游方向向量发送器
	void Compass::sendPosition()
	{
		m_pSynchroManipulator->SlotPitch(_direction);
	}

	///控件位置更新
	void Compass::resetCanvasPosition(double x,double y)
	{
		getBaseCanvas()->setX(x-112);
		getBaseCanvas()->setY(y-100);

		_ringShadowCanvas->setX(x-112+40);
		_ringShadowCanvas->setY(y-100+40);
	}

	//////////////////////////////////////////////////////////////////////////
	void Compass::slotHeading(double heading)
	{
		getRingShadowCanvas()->setRotate(heading-45+90);
		getRingShadowCanvas()->update();
	}
}