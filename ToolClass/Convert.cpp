
#define VRSOFT_TOOLCLASS_EXPORT


#include <osgEarth/GeoData>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"

#ifdef DEBUG
#pragma comment(lib, "osgEarthd.lib")
#else
#pragma comment(lib, "osgEarth.lib")
#endif


namespace VR_Soft
{
	CConvert::CConvert(void)
	{
	}

	// ��γ�߶�ת������������
	void CConvert::LatLongHeightToWord(const double latitude, const double longitude, const double height, \
		double& X, double& Y, double& Z)
	{
		// ������ڵ������
		double flattening = (WGS_84_RADIUS_EQUATOR - WGS_84_RADIUS_POLAR)/WGS_84_RADIUS_EQUATOR;
		double _eccentricitySquared = 2*flattening - flattening*flattening;

		// ��õ������
		double sin_latitude = sin(latitude);
		double cos_latitude = cos(latitude);
		double N = WGS_84_RADIUS_EQUATOR / sqrt( 1.0 - _eccentricitySquared*sin_latitude*sin_latitude);
		X = (N+height)*cos_latitude*cos(longitude);
		Y = (N+height)*cos_latitude*sin(longitude);
		Z = (N*(1-_eccentricitySquared)+height)*sin_latitude;
		
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

	template <class T>
	bool CConvert::CanvartType(const IAttributeItem* pAttributeItem, T& var)
	{
		// �������
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
}
