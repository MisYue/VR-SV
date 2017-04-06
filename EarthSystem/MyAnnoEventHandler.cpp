#define VRSOFT_PLUGIN_EXPORT
#include <osgEarthUtil/AnnotationEvents>
#include <osgEarthAnnotation/AnnotationNode>
#include "../../Public/VRSoft.h"
#include "MyAnnoEventHandler.h"

namespace VR_Soft
{
	CMyAnnoEventHandler::CMyAnnoEventHandler(void)
	{
	}


	CMyAnnoEventHandler::~CMyAnnoEventHandler(void)
	{
	}

	void CMyAnnoEventHandler::onClick( osgEarth::Util::AnnotationNode* node, const osgEarth::Util::AnnotationEventHandler::EventArgs& details )
	{
		VRString strName = node->getName();
		int n = 0;
		n = 1;
	}
}

