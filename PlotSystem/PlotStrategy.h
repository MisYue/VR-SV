/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ������ͷ�ļ�			                                        */
/* ʱ�䣺 2016-08-11                                                    */
/* �޸�ʱ��:                                                            */
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

		// �������е�
		void RebuildPlot(const std::vector<osg::Vec3d>& listPlotPoints);
		// �ؽ�
		virtual void Rebuild(const std::vector<osg::Vec3d>& listKeyPoints);

	protected:
		CPlot* m_pPlot;
	};
}


#endif // !_PLOTSTRATEGY_H_