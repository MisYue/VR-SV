#pragma once

#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;

	/**
	 *	������
	 */
	class Zoom : public BaseWidget
	{
	public:
		Zoom(CSynchroManipulator *pSynchroManipulator, const osg::Vec4& color, std::string *imagefiles);
		~Zoom(void);

		osgWidget::Widget* getSlider() {return _slider;}
		osgWidget::Widget* getPlusWidget() {return _plusHoverWidget;}
		osgWidget::Widget* getMinusWidget() {return _minusHoverWidget;}

		int* getClickCount(){return _clickCount;}
		void setClickCout(int i) { _clickCount[0] = i; sendClickCount(_clickCount[0]);}

		/// ��ȡ_sliderƽ��λ��Y����
		int getSliderPingHengDianY() {return _sliderPingHengDianY;}

		/// ���¿ؼ���Ļλ��
		void resetCanvasPosition(double x,double y);
		/// ���������λ��
		void sendClickCount(double value);
	
	public:
		/// ��д��������¼�������
		virtual bool mousePush(osgWidget::Event& event);
		virtual bool mouseLeave(osgWidget::Event& event);
		virtual bool mouseDrag(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Widget>  _slider;			///< ����
		osg::ref_ptr<osgWidget::Widget>  _plusHoverWidget;	///<�������ؼ�
		osg::ref_ptr<osgWidget::Widget>  _minusHoverWidget;	///< "_"�ؼ�

		int _sliderPingHengDianY;			///< _slider���ڵ�ƽ��λ�õ�Y���꣨_baseCanvas����ϵ�е�Y���꣩��
		int _clickCount[1];					///< _clickCount[0]�������ű���������Ϊ�Ŵ�����������С����
		CSynchroManipulator *m_pSynchroManipulator;
	};
}

