#pragma once

#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;
	/**
	 *	漫游控件
	 */
	class Walker : public BaseWidget
	{
	public:
		Walker(CSynchroManipulator *pSynchroManipulator,const osg::Vec4& color, std::string *imagefiles);
		~Walker();

		osgWidget::Widget* getPotlight() {return _widgetPotLight;}
		osgWidget::Canvas* getShadowCanvas() {return _shadowCanvas;}

		/// 漫游方向向量发送器,该函数使用时需改写
		void sendPosition();	

		/// 更新控件屏幕位置
		void resetCanvasPosition(double x,double y);
	
	public:
		///重写了部分鼠标事件处理函数
		bool mousePush(osgWidget::Event& event);
		bool mouseRelease(osgWidget::Event& event);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _shadowCanvas;		///< 鼠标移动是动画控件所在的窗口管理器
		osg::ref_ptr<osgWidget::Widget>  _widgetPotLight;	///< 动画控件
		osg::Vec2f _direction;								///< 保存漫游的方向向量，漫游停止时该值置０向量；
		CSynchroManipulator *m_pSynchroManipulator; // 操作器
	};
}