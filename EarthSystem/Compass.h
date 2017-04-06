#pragma once

#include "../../Public/VRSoft.h"
#include "baseWidget.h"

namespace VR_Soft
{
	class CSynchroManipulator;
	/**
	*	罗盘/指北针
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

		/// 漫游方向向量发送器,该函数使用时需改写
		void sendPosition();

		/// 更新控件屏幕位置
		void resetCanvasPosition(double x,double y);

	public:
		/// 重写部分鼠标事件处理函数
		bool mousePush(osgWidget::Event& event);
		bool mouseLeave(osgWidget::Event& event);
		bool mouseDrag(osgWidget::Event& event);

	public:
		/// 更新指北针
		void slotHeading(double heading);

	private:
		osg::ref_ptr<osgWidget::Canvas>  _shadowCanvas;		///< 鼠标移动是动画控件所在的窗口管理器。
		osg::ref_ptr<osgWidget::Canvas>  _ringShadowCanvas;	///< 指北针控件窗口管理器。
		osg::ref_ptr<osgWidget::Widget>  _widgetPotLight;	///< 鼠标移动动画控件
		osg::ref_ptr<osgWidget::Widget>  _widgetHoverN;		///< 指北针所在圆控件
		osg::ref_ptr<osgWidget::Widget>  _widgetN;			///< 拖拽是指北针动画控件
		osg::ref_ptr<osgWidget::Widget>  _widgetRingShadow;

		const double PI	;				///< 圆周率
		double angle;					///< 指北针旋转角度
		osgWidget::XYCoord _deltaMove;	///< 拖拽时累计位移。
		osgWidget::XYCoord _direction;	///< 鼠标点击时所处于罗盘中的位置向量（该位置以罗盘中心为原点）；

		CSynchroManipulator *m_pSynchroManipulator; // 操作器
	};
}