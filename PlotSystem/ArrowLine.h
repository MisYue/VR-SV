/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  线箭头标绘的头文件	                                        */
/* 时间： 2016-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ARROWLINE_H_
#define _ARROWLINE_H_

#pragma once

#include "BaseContrl.h"
#include "PlotStrategy.h"

namespace VR_Soft
{
	// 线箭头控制
	class CArrowLine : public CBaseContrl
	{
	public:
		CArrowLine(CPlotStrategy* pPlotStrategy);
		virtual ~CArrowLine(void);

	public:
		// 添加鼠标点
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);
	};

	class CArrowLineStrategy : public CPlotStrategy
	{
	public:
		CArrowLineStrategy(CPlot* pPlot);
		virtual ~CArrowLineStrategy(void);

	public:
		// 重新构建
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

		// 计算两点长度
		double GetLengthTwoPoint( const osg::Vec3d& pS, const osg::Vec3d& pE );
	};

	/////////////////////////////单曲箭头/////////////////////////////////////////////
	class CArrowCureLine : public CBaseContrl
	{
	public:
		CArrowCureLine(CPlotStrategy* pPlotStrategy);
		virtual ~CArrowCureLine(void);

	public:
		// 添加鼠标点
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);
	};

	class CArrowCureLineStrategy : public CPlotStrategy
	{
	public:
		CArrowCureLineStrategy(CPlot* pPlot);
		virtual ~CArrowCureLineStrategy(void);

	public:
		// 重新构建
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

		// 计算两点长度
		double GetLengthTwoPoint( const osg::Vec3d& pS, const osg::Vec3d& pE );
	};

}
#endif // !_ARROWLINE_H_