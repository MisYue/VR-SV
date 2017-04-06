//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	线段定义及相关计算函数

*********************************************************************/

#ifndef SEGMENT_H__
#define SEGMENT_H__

//#include "MathCalculationSupport_Global.h"
// 坐标点类
#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Segment
{
public:
	Segment(void);
	// 构造初始化线段（两个坐标点（起点、终点））
	Segment( CoordinatesPosition Point_1 , CoordinatesPosition Point_2 );

	// 拷贝构造函数
	Segment( const Segment &cSeg );
	// 重载“=”
	Segment &operator=( const Segment &cSeg );

	~Segment(void);
	

    // 得到第一个点
	inline CoordinatesPosition Get_FristPoint(void) const;
	// 得到第二个点
	inline CoordinatesPosition Get_SecondPoint(void) const;
	// 得到单位向量
    inline CoordinatesPosition Get_SVector(void) const;
	////判断一个点是否在线段上
	bool JudgePointIfInSegment( const CoordinatesPosition &Point)const;
	////判断两个线段是否有交点
	/*bool JudgeIfInterFor2Segments( const Segment &Seg_1 ,  const Segment &Seg_2 ) const;*/
	//// 计算两个线段的交点坐标(不进行两个线段是否在一个平面上的检查、而且两个线段必然相交有交点)
	CoordinatesPosition ComputePointBetween2Segments_NoCheck( const Segment& S1 , const Segment& S2 )const;

private:
	// 第一个点
	CoordinatesPosition Point_Frist_;
	// 第二个点
	CoordinatesPosition Point_Sencod_;
	// 标准化向量
	CoordinatesPosition SVer_;
};

#endif

