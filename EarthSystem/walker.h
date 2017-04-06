#pragma once

#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;
	/**
	 *	���οؼ�
	 */
	class Walker : public BaseWidget
	{
	public:
		Walker(CSynchroManipulator *pSynchroManipulator,const osg::Vec4& color, std::string *imagefiles);
		~Walker();

		osgWidget::Widget* getPotlight() {return _widgetPotLight;}
		osgWidget::Canvas* getShadowCanvas() {return _shadowCanvas;}

		/// ���η�������������,�ú���ʹ��ʱ���д
		void sendPosition();	

		/// ���¿ؼ���Ļλ��
		void resetCanvasPosition(double x,double y);
	
	public:
		///��д�˲�������¼�������
		bool mousePush(osgWidget::Event& event);
		bool mouseRelease(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _shadowCanvas;		///< ����ƶ��Ƕ����ؼ����ڵĴ��ڹ�����
		osg::ref_ptr<osgWidget::Widget>  _widgetPotLight;	///< �����ؼ�
		osg::Vec2f _direction;								///< �������εķ�������������ֹͣʱ��ֵ�ã�������
		CSynchroManipulator *m_pSynchroManipulator; // ������
	};
}