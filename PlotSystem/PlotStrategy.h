/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘计算头文件			                                        */
/* 时间： 2016-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PLOTSTRATEGY_H_
#define _PLOTSTRATEGY_H_

#pragma once

#include <vector>
#include <osg/Vec3d>


namespace VR_Soft
{
	class CPlot;

	class CPlotStrategy
	{
	public:
		CPlotStrategy(CPlot* pPlot);
		virtual ~CPlotStrategy(void);

		// 更新所有点
		void RebuildPlot(const std::vector<osg::Vec3d>& listPlotPoints);
		// 重建
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

	protected:
		CPlot* m_pPlot;
	};
}


#endif // !_PLOTSTRATEGY_H_