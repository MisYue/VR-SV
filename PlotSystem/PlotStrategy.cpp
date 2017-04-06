#include "../../Public/PlotSystem/PlotSystem.h"
#include "PlotStrategy.h"
#include "Plot.h"

namespace VR_Soft
{
	CPlotStrategy::CPlotStrategy(CPlot* pPlot)
		:m_pPlot(pPlot)
	{
	}


	CPlotStrategy::~CPlotStrategy(void)
	{
	}

	// 重建
	void CPlotStrategy::Rebuild( const std::vector<osg::Vec3d>& listKeyPoints )
	{
		RebuildPlot(listKeyPoints);
	}

	// 更新所有点
	void CPlotStrategy::RebuildPlot( const std::vector<osg::Vec3d>& listPlotPoints )
	{
		if (NULL == m_pPlot)
		{
			return;
		}

		m_pPlot->Rebuild(listPlotPoints);
	}

}

