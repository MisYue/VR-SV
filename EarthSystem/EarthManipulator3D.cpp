#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "EarthManipulator3D.h"
#include "SynchroManipManager.h"
#include <osgViewer/Viewer>
#include <osgEarth/ElevationQuery>
#include <osgearth/Terrain>

#include "CameraInfo.h"
#include "Compass.h"


namespace VR_Soft
{
	CEarthManipulator3D::CEarthManipulator3D(void)
		:m_pCamCB(NULL),m_distance(0.0),  m_latitude(0.0), m_longtitude(0.0), m_height(0.0),\
		_map(NULL), _terrain(NULL), _query(NULL)
	{
	}


	CEarthManipulator3D::~CEarthManipulator3D(void)
	{
	}

	void CEarthManipulator3D::SetTrackEntity( IEntityBase* pIEntity )
	{
		osg::Node* pNode = pIEntity->GetDrawManager()->GetRootDrawObj();
		setTetherNode(pNode, 5.0);
		getSettings()->setTetherMode(this->TETHER_CENTER);
	}

	// 事件处理器
	bool CEarthManipulator3D::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
	{
		
	//	return(osgEarth::Util::EarthManipulator::handle(ea, aa));

		osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
		if (!viewer)
			return false;

		if (ea.getEventType() == osgGA::GUIEventAdapter::FRAME)
		{
			m_pCompass->slotHeading(getViewpoint().getHeading());

			m_distance = getViewpoint().getRange();
		}

		if ( ea.getHandled() )
		{
			return false;
		}


		switch( ea.getEventType() )
		{
		case osgGA::GUIEventAdapter::MOVE:
		case osgGA::GUIEventAdapter::SCROLL:
			{
				osgUtil::LineSegmentIntersector::Intersections intersections;
				if ((_mapNode.valid()) && (viewer->computeIntersections(ea.getX(),ea.getY(), intersections)))
				{	
					osg::Vec3d vec = intersections.begin()->getWorldIntersectPoint(); 
					osgEarth::GeoPoint ConvertPoint;
					ConvertPoint.fromWorld(_mapNode->getMapSRS(), vec);

					m_latitude = ConvertPoint.x();
					m_longtitude = ConvertPoint.y();
					m_height = ConvertPoint.z();
				}	
			}
			break;


		default:
			break;
		}

		// 整理数据进行更新到视图上去

		// 摄像机信息			
		char buff1[64];
		memset(buff1, 0, 64);

		char buff2[64];
		memset(buff2, 0, 64);

		char buff3[64];
		memset(buff3, 0, 64);

		char buff[254];
		memset(buff, 0, 254);

		if (m_latitude >= 0.0)
		{
			sprintf(buff1, " 北纬: %f 度", m_latitude);
		}
		else
		{
			sprintf(buff1, " 南纬: %f 度", -m_latitude);
		}

		if (m_longtitude >= 0.0)
		{
			sprintf(buff2, " 东经: %f 度", m_longtitude);
		}
		else
		{
			sprintf(buff2, " 西经: %f 度", -m_longtitude);
		}

		if (m_distance >= 1000.0)
		{
			m_distance = m_distance/1000.0;
			sprintf(buff3, " 视角海拔高度：%f 公里", m_distance);
		}
		else
		{
			sprintf(buff3, " 视角海拔高度：%f 米", m_distance);
		}	

		sprintf(buff, " %s, %s, 海拔: %f 米               %s", buff2, buff1, m_height, buff3);
		VRString str = buff;
//		m_pCamCB->setCameraInfo( str );
	
		return(osgEarth::Util::EarthManipulator::handle(ea, aa));
			
		return false;
	}

	void CEarthManipulator3D::SetCameraInfoCallback( CameraInfoCallback* pCamCB )
	{
		m_pCamCB = pCamCB;
	}

	// 设置地图节点
	void CEarthManipulator3D::SetEarthMapNode( osgEarth::MapNode* pMapNode )
	{
		_map = pMapNode->getMap();
		_terrain = pMapNode->getTerrain();
		_query = new osgEarth::ElevationQuery(pMapNode->getMap());
		_query->setMaxTilesToCache(10);
		_query->setFallBackOnNoData( false );
	}

	
}
