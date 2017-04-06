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

	// ���������
	OsgEarthGeomtry* CFeatureGeomtryFactory::CreatePolygon( void )
	{
		return (new Polygon);
	}

	// �������������ַ���
	OsgEarthGeomtry* CFeatureGeomtryFactory::CreateLineString( void )
	{
		return (new LineString);
	}

}
