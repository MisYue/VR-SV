/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘的头文件			                                        */
/* 时间： 2016-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PLOT_H_
#define _PLOT_H_
#endif //  _PLOT_H_

#pragma once

namespace VR_Soft
{
	class CPlot : public CPlotImp<IPlot>
	{
	public:
		// 构造函数
		CPlot(const uint64_t ID, const VRString& strName);
		// 析构函数
		virtual ~CPlot(void);

	public:
		
		void Rebuild( const std::vector<osg::Vec3d>& listPlotPoints );
	

	};
}


