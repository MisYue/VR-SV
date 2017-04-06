#include "../../Public/PlotSystem/PlotSystem.h"
#include "PlotContrlHandle.h"
#include <osgViewer/View>

#include "BaseContrl.h"
#include "FeatureGeomtry.h"


namespace VR_Soft
{
	CPlotContrlHandle::CPlotContrlHandle(void)
		:m_pBaseContrl(NULL), m_pFeatureGeomtry(NULL),_finished(false),_mouseDown(false), \
		_mouseButton (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON),m_intersectionMask (0xffffffff), \
		m_gotFirstLocation  (false), _lastPointTemporary(false)
	{
	}


	CPlotContrlHandle::~CPlotContrlHandle(void)
	{
	}

	
	bool CPlotContrlHandle::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if ( ea.getHandled() )
		{
			return false;
		}

		if ((NULL == m_pBaseContrl) || (NULL == m_pFeatureGeomtry))
		{
			return (false);
		}

		// 判断是否结束绘制
		if (m_pBaseContrl->IsEndDraw())
		{
			return (false);
		}

		osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());                
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH && ea.getButton() == _mouseButton)
		{        
			_mouseDown = true;
			_mouseDownX = ea.getX();
			_mouseDownY = ea.getY();
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
		{        
			float eps = 1.0f;
			_mouseDown = false;
			if (osg::equivalent(ea.getX(), _mouseDownX) && osg::equivalent(ea.getY(), _mouseDownY))
			{
				double lon, lat;
				if (GetLocationAt(view, ea.getX(), ea.getY(), lon, lat))
				{
					if (!m_gotFirstLocation)
					{
						_finished = false;
						m_gotFirstLocation = true;
						m_pBaseContrl->AddMousePoint(osg::Vec3d( lon, lat, 0 ));
					}
					else
					{
						if (_lastPointTemporary)
						{
							m_pBaseContrl->AddMousePoint(osg::Vec3d( lon, lat, 0 ));
							//_feature->getGeometry()->back() = osg::Vec3d( lon, lat, 0 );
							_lastPointTemporary = false;
						}
						else
						{
							m_pBaseContrl->AddMousePoint(osg::Vec3d( lon, lat, 0 ));
							//_feature->getGeometry()->push_back( osg::Vec3d( lon, lat, 0 ) );
						}

						

						//_featureNode->init();

						//_gotFirstLocation = false;
						//_finished = true;
						if (_finished ) {
							m_gotFirstLocation = false;
						}

					//	fireDistanceChanged();
						aa.requestRedraw();
					}
				}
			}
		}  
		else if (ea.getEventType() == osgGA::GUIEventAdapter::DOUBLECLICK) {        
			if (m_gotFirstLocation)
			{
				//_gotFirstLocation = false;
				m_pBaseContrl->SetEndDraw(true);
				_finished = true;    
				aa.requestRedraw(); 
				return true;
			}
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
		{
			if (m_gotFirstLocation)
			{
				double lon, lat;
				if (GetLocationAt(view, ea.getX(), ea.getY(), lon, lat))
				{
					if (!_lastPointTemporary)
					{
						//_feature->getGeometry()->push_back( osg::Vec3d( lon, lat, 0 ) ); 
						m_pBaseContrl->AddMouseMovePoint(osg::Vec3d( lon, lat, 0 ));
						_lastPointTemporary = true;
					}                        
					else
					{
						m_pBaseContrl->AddMouseMovePoint(osg::Vec3d( lon, lat, 0 ));
						//_feature->getGeometry()->back() = osg::Vec3d( lon, lat, 0 );
					}
					//_featureNode->init();
					//fireDistanceChanged();
					aa.requestRedraw();
				}
			}
		}    
		return false;
	}

	// 设置控制器
	void CPlotContrlHandle::SetContrl( CBaseContrl* pBaseContrl )
	{
		m_pBaseContrl = pBaseContrl;
	}

	void CPlotContrlHandle::SetFeartureGeomtry( IFeatureGeomtry* pFeatureGeomtry )
	{
		m_pFeatureGeomtry = dynamic_cast<CFeatureGeomtry*>(pFeatureGeomtry);
	}

	// 获得点下的位置
	bool CPlotContrlHandle::GetLocationAt( osgViewer::View* view, double x, double y, double &lon, double &lat )
	{
		osgUtil::LineSegmentIntersector::Intersections results;  

		osgEarth::MapNode* pMapNode = m_pFeatureGeomtry->GetMap3D();
		if ( pMapNode &&  view->computeIntersections( x, y, results, m_intersectionMask ) )
		{
			// find the first hit under the mouse:
			osgUtil::LineSegmentIntersector::Intersection first = *(results.begin());
			osg::Vec3d point = first.getWorldIntersectPoint();

			double lat_rad, lon_rad, height;       
			pMapNode->getMap()->getProfile()->getSRS()->getEllipsoid()->convertXYZToLatLongHeight( 
				point.x(), point.y(), point.z(), lat_rad, lon_rad, height );

			lat = osg::RadiansToDegrees( lat_rad );
			lon = osg::RadiansToDegrees( lon_rad );
			return true;
		}
		return false;
	}

}
