#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "FeatureGeomtryFactory.h"

#include <osgEarthSymbology/Geometry>

using namespace osgEarth;
using namespace osgEarth::Symbology;

namespace VR_Soft
{
	CFeatureGeomtryFactory::CFeatureGeomtryFactory(void)
	{
	}


	CFeatureGeomtryFactory::~CFeatureGeomtryFactory(void)
	{
	}

	// 创建多边形
	OsgEarthGeomtry* CFeatureGeomtryFactory::CreatePolygon( void )
	{
		return (new Polygon);
	}

	// 创建连续的行字符串
	OsgEarthGeomtry* CFeatureGeomtryFactory::CreateLineString( void )
	{
		return (new LineString);
	}

}
