/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �߼�ͷ����ͷ�ļ�	                                        */
/* ʱ�䣺 2016-08-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ARROWLINE_H_
#define _ARROWLINE_H_

#pragma once

#include "BaseContrl.h"
#include "PlotStrategy.h"

namespace VR_Soft
{
	// �߼�ͷ����
	class CArrowLine : public CBaseContrl
	{
	public:
		CArrowLine(CPlotStrategy* pPlotStrategy);
		virtual ~CArrowLine(void);

	public:
		// �������
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);
	};

	class CArrowLineStrategy : public CPlotStrategy
	{
	public:
		CArrowLineStrategy(CPlot* pPlot);
		virtual ~CArrowLineStrategy(void);

	public:
		// ���¹���
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

		// �������㳤��
		double GetLengthTwoPoint( const osg::Vec3d& pS, const osg::Vec3d& pE );
	};

	/////////////////////////////������ͷ/////////////////////////////////////////////
	class CArrowCureLine : public CBaseContrl
	{
	public:
		CArrowCureLine(CPlotStrategy* pPlotStrategy);
		virtual ~CArrowCureLine(void);

	public:
		// �������
		virtual void AddMousePoint(const osg::Vec3d& vMousePoint);
	};

	class CArrowCureLineStrategy : public CPlotStrategy
	{
	public:
		CArrowCureLineStrategy(CPlot* pPlot);
		virtual ~CArrowCureLineStrategy(void);

	public:
		// ���¹���
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

		// �������㳤��
		double GetLengthTwoPoint( const osg::Vec3d& pS, const osg::Vec3d& pE );
	};

}
#endif // !_ARROWLINE_H_