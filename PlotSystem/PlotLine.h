/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  直线标绘的头文件		                                        */
/* 时间： 2016-08-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PLOTLINE_H_
#define _PLOTLINE_H_

#pragma once

#include <osgEarthAnnotation/FeatureNode>

namespace VR_Soft
{
	class CPlotLine 
	{
	public:
		// 构造函数
		CPlotLine(IEntityBase* pIEntityBase);
		// 析构函数
		virtual ~CPlotLine(void);

	private:
		osgEarth::Annotation::FeatureNode* m_pFeatureNode;
	};

}


#endif // !_PLOTLINE_H_