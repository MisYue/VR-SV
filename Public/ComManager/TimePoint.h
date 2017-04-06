/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线点				                                        */
/* 时间： 2015-08-04                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _AIRLINEPOINT_H_
#define _AIRLINEPOINT_H_

#pragma once

#include <osg/Vec3d>

namespace VR_Soft
{
	class VRSOFT_DLL CTimePoint
	{
	public:
		// 构造函数
		explicit CTimePoint(void);
		explicit CTimePoint(const osg::Vec3d& v, double dt = 0.0);
		explicit CTimePoint(double x, double y, double z, double dt = 0.0);
		~CTimePoint(void);
		// 赋值
		CTimePoint &operator= (const CTimePoint& other);
		// 和时间进行比较
		bool operator< (double dt);
		bool operator== (double dt);
		bool operator== (const CTimePoint& other);
		
	public:
		// 获得顶点
		osg::Vec3d GetPoint(void) const;

	private:
		osg::Vec3d m_point; // 点
		double m_dt; // 时间
	};
}

#endif // _AIRLINEPOINT_H_