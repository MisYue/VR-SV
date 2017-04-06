
/*********************************************************************************
**该类是基类，该类包含一个窗口部件管理器_baseCanvas，窗口部件_widgetBase，_widgetDisplay
**_widgetBase在窗口管理器中处于上层，用于响应鼠标事件，_widgetDisplay仅作为显示用，
**在窗口管理器中处于下层。
********************************************************************************/
#pragma once
#include <osgWidget/Canvas>

namespace VR_Soft
{

#define ALPHA_ANIMATION_STEP	0.05		///< ALPHA动画步进0.05

	class BaseWidget
	{
	public:
		BaseWidget(const osg::Vec4& color,osg::Vec2 location,osg::Vec2 size, std::string *imagefiles);
		~BaseWidget(void);

		enum MOUSESTATE
		{		
			MOUSE_PUSH,			///< 鼠标按下
			MOUSE_RELEASE,		///< 鼠标松开
			MOUSE_LEAVE,		///< 鼠标离开
			MOUSE_OVER,			///< 鼠标停靠
			MOUSE_DRAG,			///< 鼠标拖拽
			DEFAULT
		};

		/// 获取鼠标所在位置（该位置以_widgetBase部件中心为坐标原点）
		osgWidget::XYCoord getXYcoord() {return _location;}		
		osgWidget::Canvas* getBaseCanvas() {return _baseCanvas;}
		osgWidget::Widget* getBaseWidget() {return _widgetBase;}
		osgWidget::Widget* getDisplayWidget() {return _widgetDisplay;}
		osgWidget::Widget* createWidget(std::string name,std::string imageFile,osg::Vec2 size, osgWidget::Widget::Layer layer);	

		MOUSESTATE _mouseState;
		static bool _isMouseOverBaseWidget; /// 静态变量，当鼠标位于_widgetBase范围内，该值为true，用于实现罗盘（Compass）漫步（Walker）缩放器（Zoom）控件渐入逐出同步。

	public:
		virtual bool mousePush(osgWidget::Event& event);
		virtual bool mouseRelease(osgWidget::Event& event);
		virtual bool mouseLeave(osgWidget::Event& event);
		virtual bool mouseOver(osgWidget::Event& event);
		virtual bool mouseDrag(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _baseCanvas;		///< _widgetBase部件所在管理取器
		osg::ref_ptr<osgWidget::Widget>  _widgetBase;		///< 鼠标事件处理窗口部件。
		osg::ref_ptr<osgWidget::Widget>  _widgetDisplay;	///< 显示窗口部件。
		osgWidget::XYCoord _location;						///< 鼠标所在位置（该位置以_widgetBase部件中心为坐标原点）
	};
}
