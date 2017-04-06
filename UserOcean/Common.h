#pragma once

#ifdef _DEBUG

#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgTextd.lib")
#pragma comment(lib, "osgWidgetd.lib")

#pragma comment(lib, "osgShadowd.lib")
#pragma comment(lib, "osgAnimationd.lib")
#pragma comment(lib, "osgParticled.lib")
//#pragma comment(lib, "osgdManipulatord.lib")

#pragma comment(lib, "osgSim.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#else

#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osgText.lib")
#pragma comment(lib, "osgWidget.lib")
#pragma comment(lib, "osgShadow.lib")
#pragma comment(lib, "osgAnimation.lib")
#pragma comment(lib, "osgParticle.lib")
#pragma comment(lib, "osgManipulator.lib")
#pragma comment(lib, "osgSim.lib")      
//#pragma comment(lib, "osgQt.lib")

#pragma comment(lib, "OpenGL32.lib")

#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#pragma comment(lib, "osgEarthFeatures.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthUtil.lib")

#endif