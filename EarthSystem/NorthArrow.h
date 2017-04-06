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

	//ָ�����࣬ʵʱ�仯
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
		//------------------ �����и����ӻ��ؼ�------------------------------
		osgWidget::WindowManager* m_pWM;					        ///< ������HUD Widget
		Zoom* m_pZoom;								///< ����HUD Widget
	    Walker* m_pWalker;							///< ����HUD Widget
		Compass* m_pCompass;							///< ָ����HUD Widget

		osg::ref_ptr<osg::Camera> m_pHudCamera;       ///< ��Ļ�����������
		CSynchroManipulator* m_pSynchroManip; // ������
		CameraInfoCallback* m_pCameraIC; // ����ص�

	};
}