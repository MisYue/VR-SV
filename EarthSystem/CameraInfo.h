#pragma once

#include <osgViewer/Viewer>
#include <osgText/Text>

#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	//相机信息类，实时更新相机信息
	class CameraInfoCallback : public osg::NodeCallback
	{
	public:
		CameraInfoCallback( osg::Group *group, double width, double height);
		~CameraInfoCallback();

		virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

		osg::Camera *createCameraInfoHUD(double left, double right, 
			                             double bottom, double top);

		void setCameraInfo(const VRString& strInfo);
		std::string getCameraInfo();

		void UpdateCameraInfo();
		void Resize(double width, double height);

	private:
		osg::Camera        *m_pCamera;
		osgText::Text      *m_pText;
		osg::Group         *m_pCameraInfoGroup;

		VRString	        m_strInfo;
	};
}