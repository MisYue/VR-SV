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
		_ringShadowCanvas->setVisibilityMode(osgWidget::Window::VM_ENTIRE);///������ת�Ǵ��ڲ��������ü�

		/////��Compassͼ����С����������
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
		_direction=osg::Vec2f(getXYcoord().x(),getXYcoord().y());//��ȡ�����ʱ�����������е�λ������
		return true;
	}

	bool Compass::mouseLeave(osgWidget::Event& event)
	{
		_mouseState=MOUSE_LEAVE;
		_isMouseOverBaseWidget=false;
		_direction=osgWidget::XYCoord(0,0);//λ��������Ϊ������
		return true;
	}

	/*��ק��תʵ�ַ�����������ȡ��קǰ������ڵ�λ������getXYcoord()�����жϸõ�λ���Ƿ�仯��
	*������ȡ��קλ�ƣ�event.x��event.y��
	*��������קǰ������ڵ�λ��δ�䣬����λ�������ۼӣ�����λ������Ϊ��event.x��event.y��
	*������λ����������קǰ������ڵ�λ�ã��������ק�����λ������(getXYcoord()+)
	*/
	bool Compass::mouseDrag(osgWidget::Event& event)
	{
		_mouseState=MOUSE_DRAG;
		static osgWidget::XYCoord temp;
		int s=getXYcoord().x()*getXYcoord().x()+getXYcoord().y()*getXYcoord().y();   ////�ж����λ�����䣬��λ�ڹ۲�ͼ��(�۲�ͼ���СΪ����������)֮�⣬����Ӧ�϶���Ϣ��������Ӧ
		if(s<27*27)
			return true;
		osgWidget::XYCoord location=getXYcoord();

		///�ж���קǰ������ڵ�λ���Ƿ�仯���ǣ���קλ�Ʋ��ۼӣ�����קλ���ۼ�
		_deltaMove=temp==getXYcoord() ? (_deltaMove+osgWidget::XYCoord(event.x,event.y)) : (osgWidget::XYCoord(event.x,event.y));

		angle=atan2f(getXYcoord().y() + _deltaMove.y(),getXYcoord().x()+_deltaMove.x())*180/3.14;//��ק��ָ����λ�ýǶ�

		std::cout<<"angle="<<angle<<std::endl;
		temp=getXYcoord();
		return true;
	}

	///���η�������������
	void Compass::sendPosition()
	{
		m_pSynchroManipulator->SlotPitch(_direction);
	}

	///�ؼ�λ�ø���
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