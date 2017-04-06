#pragma once
#ifdef _DEBUG
#pragma comment(lib, "OpenThreadsd.lib")  
#pragma comment(lib, "osgd.lib")  
#pragma comment(lib, "osgAnimationd.lib")  
#pragma comment(lib, "osgDBd.lib")  
#pragma comment(lib, "osgFXd.lib")  
#pragma comment(lib, "osgGAd.lib")  
#pragma comment(lib, "osgManipulatord.lib")  
#pragma comment(lib, "osgParticled.lib")  
#pragma comment(lib, "osgQtd.lib")  
#pragma comment(lib, "osgShadowd.lib")  
#pragma comment(lib, "osgSimd.lib")  
#pragma comment(lib, "osgTerraind.lib")  
#pragma comment(lib, "osgTextd.lib")  
#pragma comment(lib, "osgUtild.lib")  
#pragma comment(lib, "osgViewerd.lib")  
#pragma comment(lib, "osgVolumed.lib")  
#pragma comment(lib, "osgWidgetd.lib")
#pragma comment(lib, "QtCored4.lib")
#pragma comment(lib, "QtGuid4.lib")
#else
#pragma comment(lib, "OpenThreads.lib")  
#pragma comment(lib, "osg.lib")  
#pragma comment(lib, "osgAnimation.lib")  
#pragma comment(lib, "osgDB.lib")  
#pragma comment(lib, "osgFX.lib")  
#pragma comment(lib, "osgGA.lib")  
#pragma comment(lib, "osgManipulator.lib")  
#pragma comment(lib, "osgParticle.lib")  
#pragma comment(lib, "osgQt.lib")  
#pragma comment(lib, "osgShadow.lib")  
#pragma comment(lib, "osgSim.lib")  
#pragma comment(lib, "osgTerrain.lib")  
#pragma comment(lib, "osgText.lib")  
#pragma comment(lib, "osgUtil.lib")  
#pragma comment(lib, "osgViewer.lib")  
#pragma comment(lib, "osgVolume.lib")  
#pragma comment(lib, "osgWidget.lib")  
#endif

#include<QtCore/QTimer>
#include<QtGui/QApplication>
#include<QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QHBoxLayout>
#include <QObject>
#include <QtGui/QPushButton>
#include <QtGui/QColorDialog>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>


#include<osgViewer/Viewer>
#include<osgDB/ReadFile>
#include<osgQt/GraphicsWindowQt>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/OrbitManipulator >
#include <osg/ShadeModel>
#include <osg/ShapeDrawable>
#include <osg/NodeCallback>
#include <osg/Material>
#include <osg/NodeVisitor>  
#include <osg/AnimationPath>  
#include <osg/Drawable>

#include <osg/Texture2D>  
#include <osg/Texture3D>  

#include <osgGA/GUIEventAdapter>  

#include <osg/Light>  
#include <osg/LightModel>  
#include <osg/LightSource>
#include <osg/BlendFunc>
#include <vector>
#include <iostream>
#include <fstream>