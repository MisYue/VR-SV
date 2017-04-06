#pragma once

#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;

	/**
	 *	缩放器
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

		/// 获取_slider平衡位置Y坐标
		int getSliderPingHengDianY() {return _sliderPingHengDianY;}

		/// 更新控件屏幕位置
		void resetCanvasPosition(double x,double y);
		/// 发送鼠标点击位置
		void sendClickCount(double value);
	
	public:
		/// 重写部分鼠标事件处理函数
		virtual bool mousePush(osgWidget::Event& event);
		virtual bool mouseLeave(osgWidget::Event& event);
		virtual bool mouseDrag(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Widget>  _slider;			///< 滑块
		osg::ref_ptr<osgWidget::Widget>  _plusHoverWidget;	///<“＋”控件
		osg::ref_ptr<osgWidget::Widget>  _minusHoverWidget;	///< "_"控件

		int _sliderPingHengDianY;			///< _slider窗口的平衡位置的Y坐标（_baseCanvas坐标系中的Y坐标）。
		int _clickCount[1];					///< _clickCount[0]保存缩放比例，正：为放大倍数；负：缩小倍数
		CSynchroManipulator *m_pSynchroManipulator;
	};
}

