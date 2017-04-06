#include <osg/Notify>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/VirtualProgram>
#include <osgEarth/Registry>
#include <osgEarth/Capabilities>
#include <osgEarth/ShaderUtils>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/Ocean>

#include "Common.h"

#include "UserOcean.h"

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::Group* root = new osg::Group();
	viewer->setSceneData( root );

	osg::Node* earthNode = osgDB::readNodeFile( "ocean.earth" );
	if (!earthNode)
	{
		return 0;
	}

	osg::ref_ptr<osgEarth::MapNode> mapNode = osgEarth::MapNode::get(earthNode);

	if ( !mapNode.valid() )
	{
		OE_WARN << "Loaded scene graph does not contain a MapNode - aborting" << std::endl;

		return 0L;
	}

	root->addChild( mapNode );



	{
		osgEarth::Util::SkyOptions options;

		osgEarth::Util::SkyNode* sky = osgEarth::Util::SkyNode::create(options, mapNode);
		if ( sky )
		{
			sky->attach( viewer, 0 );

			sky->setDateTime(osgEarth::DateTime(2011, 3, 6, 6));

			osgEarth::insertGroup(sky, mapNode->getParent(0));
		}
	}

	//{
	//	osgEarth::Util::OceanOptions options;

	//	osgEarth::Util::OceanNode* ocean = osgEarth::Util::OceanNode::create(options, mapNode);
	//	if ( ocean )
	//	{
	//		// if there's a sky, we want to ocean under it
	//		osg::Group* parent = osgEarth::findTopMostNodeOfType<osgEarth::Util::SkyNode>(root);

	//		if ( !parent ) 
	//			parent = root;

	//		parent->addChild( ocean );
	//	}
	//}

	{

		{
			UserOcean *ocean = new UserOcean(mapNode);

			// if there's a sky, we want to ocean under it
			osg::Group* parent = osgEarth::findTopMostNodeOfType<osgEarth::Util::SkyNode>(root);

			if ( !parent ) 
				parent = root;

			parent->addChild( ocean );
		}
	}

	osgEarth::Util::EarthManipulator *manip = new osgEarth::Util::EarthManipulator();
	manip->setHomeViewpoint(osgEarth::Viewpoint("Home", 0.0, 0.0, 0.0, 0.0, -90.0, 44520000 ));
	viewer->setCameraManipulator( manip );

	viewer->addEventHandler(new osgViewer::StatsHandler());
	viewer->addEventHandler(new osgViewer::WindowSizeHandler());
	viewer->addEventHandler(new osgViewer::ThreadingHandler());
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	return viewer->run();
}