/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	坐标系定义

*********************************************************************/

#ifndef COORDINATESYSTEM_H__
#define COORDINATESYSTEM_H__

#include "BITCoordinateSystemSupport_Global.h"
// 坐标点类
#include "MathCalculationSupport/CoordinatesPosition.h"
// 空间类
#include "MathCalculationSupport/SpaceGeometry.h"

class BITCOORDINATESYSTEMSUPPORT_API CoordinateSystem
{
public:
	// 构造空的坐标系
	CoordinateSystem(void);
	// 构造坐标系(由原点、向量一和向量一)
	CoordinateSystem( int n , CoordinatesPosition OriginalPoint 
		, CoordinatesPosition One_AixV , CoordinatesPosition Two_AixV );
	// 拷贝构造函数
	CoordinateSystem( const CoordinateSystem &cCS );
	// 重载"="等号
	CoordinateSystem& operator= (const CoordinateSystem& cCS );
	// 重载"=="恒等判断
	bool operator == (const CoordinateSystem& cCS )const;

	~CoordinateSystem(void);
	
	// 初始化设置
	void Set_Initial( const int& n , const CoordinatesPosition& OriginalPoint 
		, const CoordinatesPosition& One_AixV , const CoordinatesPosition& Two_AixV );

	// 得到原点
	inline CoordinatesPosition Get_OriginalPoint(void) const ;
	// 得到X轴向量
	inline CoordinatesPosition Get_XAixVector(void) const ;
	// 得到Y轴向量
	inline CoordinatesPosition Get_YAixVector(void) const ;
	// 得到Z轴向量
	inline CoordinatesPosition Get_ZAixVector(void) const ;

	//根据给定B坐标系在A坐标系中的位置计算A坐标系中的点在B坐标系中点的坐标
	CoordinatesPosition TransformCoordinateFromCSAToCSB( const CoordinatesPosition& BCS_OriginInACS 
		, const CoordinatesPosition& BCS_ZAxisVecInACS , const CoordinatesPosition& BCS_XAxisVecInACS 
		, const CoordinatesPosition& PointInACS) const ;

private:
	// 坐标原点
	CoordinatesPosition OriginalPoint_;
	// X轴向量
	CoordinatesPosition X_AixVector_;
	// Y轴向量
	CoordinatesPosition Y_AixVector_;
	// Z轴向量
	CoordinatesPosition Z_AixVector_;
};
#endif