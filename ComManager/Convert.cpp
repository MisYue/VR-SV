#include "../../Public/VRSoft.h"

#include <osgEarth/GeoData>
#include <osgEarth/SpatialReference>


#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgEarthd.lib")
#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgEarth.lib")
#endif

namespace VR_Soft
{

	osgEarth::SpatialReference* CConvert::m_pSpatial = NULL;

	CConvert::CConvert(void)
	{
	}

	// 经纬高度转换成世界坐标
	void CConvert::LatLongHeightToWord(const double latitude, const double longitude, const double height, \
		double& X, double& Y, double& Z)
	{
		osg::Vec3d vWorld;
		LatLongHeightToWord(osg::Vec3d(latitude, longitude, height), vWorld);
		X = vWorld.x();
		Y = vWorld.y();
		Z = vWorld.z();
		//// 如果存在地球组件
		//double flattening = (WGS_84_RADIUS_EQUATOR - WGS_84_RADIUS_POLAR)/WGS_84_RADIUS_EQUATOR;
		//double _eccentricitySquared = 2*flattening - flattening*flattening;

		//// 获得地球组件
		//double sin_latitude = sin(latitude);
		//double cos_latitude = cos(latitude);
		//double N = WGS_84_RADIUS_EQUATOR / sqrt( 1.0 - _eccentricitySquared*sin_latitude*sin_latitude);
		//X = (N+height)*cos_latitude*cos(longitude);
		//Y = (N+height)*cos_latitude*sin(longitude);
		//Z = (N*(1-_eccentricitySquared)+height)*sin_latitude;
		//
		/*double clat, slat, clon, slon, d, n, nph;
		const double a=6378137.0;
		const double e=0.0818191908426;
		const double ome2 = 0.99330562000987;
		const double pi=3.1415926535898;
		double lat=latitude*pi/180;
		double lon=longitude*pi/180;
		clat = cos(lat);
		slat = sin(lat);
		clon = cos(lon);
		slon = sin(lon);
		d = e*slat;
		n = a/sqrt(1.0E0-d*d);
		nph = n + height;
		X = nph*clat*clon;
		Y = nph*clat*slon;
		Z = (ome2*n+height)*slat;
		*/
	}

	// 经纬高度转换成世界坐标
	void CConvert::LatLongHeightToWord(const osg::Vec3d& vGeo, osg::Vec3d& vWord)
	{
		assert(NULL != m_pSpatial);

		const osg::EllipsoidModel* pEllipsoidModle = m_pSpatial->getEllipsoid();
		/*if (pEllipsoidModle->isWGS84())
		{
			
		}*/

		pEllipsoidModle->convertLatLongHeightToXYZ(osg::DegreesToRadians(vGeo.y()), osg::DegreesToRadians(vGeo.x()), \
			vGeo.z(), vWord.x(), vWord.y(), vWord.z());
		/*	vWord.x() *= R2D;
		vWord.y() *= R2D;*/
		//geoPoint.createLocalToWorld(matrixWorld);*/
		//geoPoint.toWorld(vWord);
		//vWord = matrixWorld.getTrans();
	}

	template <class T>
	bool CConvert::CanvartType(const IAttributeItem* pAttributeItem, T& var)
	{
		// 获得类型
		try
		{
			var = boost::any_cast<T>(pAttributeItem->GetVariant());
			
		}
		catch (const boost::bad_any_cast &e)
		{
			return (false);
		}

		return (true);
		
	}

	// 世界坐标转换成地理坐标
	void CConvert::WordToLatLongHeight( const osg::Vec3d& vWord, osg::Vec3d& vGeo )
	{
		assert(NULL != m_pSpatial);

		const osg::EllipsoidModel* pEllipsoidModle = m_pSpatial->getEllipsoid();
		pEllipsoidModle->convertXYZToLatLongHeight(vWord.x(), vWord.y(), vWord.z(), vGeo.y(), vGeo.x(), vGeo.z());
		vGeo.x() = osg::RadiansToDegrees(vGeo.x());
		vGeo.y() = osg::RadiansToDegrees(vGeo.y());


		/*osgEarth::GeoPoint geoPoint;
		geoPoint.fromWorld(m_pSpatial, vWord);
		vGeo = geoPoint.vec3d();*/
	}

	// 世界坐标转换成地理坐标
	void CConvert::WordToLatLongHeight( const double X, const double Y, const double Z, \
		double& latitude, double& longitude, double& height)
	{
		osg::Vec3d vGeo;
		WordToLatLongHeight(osg::Vec3d(X, Y, Z), vGeo);
		latitude = vGeo.x();
		longitude = vGeo.y();
		height = vGeo.z();
	}
}
