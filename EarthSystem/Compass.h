#pragma once

#include "../../Public/VRSoft.h"
#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;
	/**
	*	����/ָ����
	*/
	class Compass : public BaseWidget
	{
	public:
		Compass(CSynchroManipulator *pSynchroManipulator,const osg::Vec4& color, VRString *imagefiles);
		~Compass();

		osgWidget::Widget* getPotlight() { return _widgetPotLight; }
		osgWidget::Canvas* getShadowCanvas() { return _shadowCanvas; }

		osgWidget::Canvas* getRingShadowCanvas() { return _ringShadowCanvas; }
		double getAngle() { return angle; }

		/// ���η�������������,�ú���ʹ��ʱ���д
		void sendPosition();

		/// ���¿ؼ���Ļλ��
		void resetCanvasPosition(double x,double y);

	public:
		/// ��д��������¼�������
		bool mousePush(osgWidget::Event& event);
		bool mouseLeave(osgWidget::Event& event);
		bool mouseDrag(osgWidget::Event& event);

	public:
		/// ����ָ����
		void slotHeading(double heading);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _shadowCanvas;		///< ����ƶ��Ƕ����ؼ����ڵĴ��ڹ�������
		osg::ref_ptr<osgWidget::Canvas>  _ringShadowCanvas;	///< ָ����ؼ����ڹ�������
		osg::ref_ptr<osgWidget::Widget>  _widgetPotLight;	///< ����ƶ������ؼ�
		osg::ref_ptr<osgWidget::Widget>  _widgetHoverN;		///< ָ��������Բ�ؼ�
		osg::ref_ptr<osgWidget::Widget>  _widgetN;			///< ��ק��ָ���붯���ؼ�
		osg::ref_ptr<osgWidget::Widget>  _widgetRingShadow;

		const double PI	;				///< Բ����
		double angle;					///< ָ������ת�Ƕ�
		osgWidget::XYCoord _deltaMove;	///< ��קʱ�ۼ�λ�ơ�
		osgWidget::XYCoord _direction;	///< �����ʱ�����������е�λ����������λ������������Ϊԭ�㣩��

		CSynchroManipulator *m_pSynchroManipulator; // ������
	};
}