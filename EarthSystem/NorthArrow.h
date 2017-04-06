#pragma once

#include <osg/Camera>

#include <osgWidget/Util>
#include <osgWidget/ViewerEventHandlers>

#include <osgViewer/Viewer>

#include "Compass.h"
#include "walker.h"
#include "zoom.h"

namespace VR_Soft
{
	class MyManipulator;
	class CameraInfoCallback;
	class CSynchroManipulator;

	//指北针类，实时变化
	class CNorthArrow
	{
	public:
		CNorthArrow(CSynchroManipulator* pSynchroManip, osg::Group *group, osgViewer::View *view, CameraInfoCallback* pCmic, double width, double height);
		~CNorthArrow();

		void initScreenWidget(osgViewer::View *view, double width, double height);

		Zoom *GetZoom()
		{
			return m_pZoom;
		}

		Walker *GetWalker()
		{
			return m_pWalker;
		}

		Compass *GetCompass()
		{
			return m_pCompass;
		}

		osgWidget::WindowManager *GetWinMgr()
		{
			return m_pWM;
		}

		void reSize(double width, double height);

	private:
		//------------------ 界面中各可视化控件------------------------------
		osgWidget::WindowManager* m_pWM;					        ///< 管理多个HUD Widget
		Zoom* m_pZoom;								///< 缩放HUD Widget
	    Walker* m_pWalker;							///< 漫游HUD Widget
		Compass* m_pCompass;							///< 指北针HUD Widget

		osg::ref_ptr<osg::Camera> m_pHudCamera;       ///< 屏幕操作器摄像机
		CSynchroManipulator* m_pSynchroManip; // 操作器
		CameraInfoCallback* m_pCameraIC; // 相机回调

	};
}