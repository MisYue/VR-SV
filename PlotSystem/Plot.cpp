#include "../../Public/PlotSystem/PlotSystem.h"
#include "Plot.h"

namespace VR_Soft
{
	CPlot::CPlot( const uint64_t ID, const VRString& strName )
		:CPlotImp<IPlot>(ID, strName)
	{

	}

	// Îö¹¹º¯Êý
	CPlot::~CPlot( void )
	{
	
	}

	void CPlot::Rebuild( const std::vector<osg::Vec3d>& listPlotPoints )
	{
		if (NULL == m_pIFeatureGeomtry)
		{
			return;
		}
		m_listPathPoints = listPlotPoints;
		m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);
	}

}
