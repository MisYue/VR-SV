//
/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	柱面坐标系的定义

*********************************************************************/

#ifndef BITCYLINDERCOSYSTEM_H__
#define BITCYLINDERCOSYSTEM_H__


// 动态库导出
#include "BITCoordinateSystemSupport_Global.h"
// 直角坐标坐标系类
#include "CoordinateSystem.h"
// 柱面坐标
//#include "Bit_CylinderCoordinate.h"

//#include "MathCalculationSupport/SpaceGeometry.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CylinderCoSystem
{
public:
	// 空构造函数
	Bit_CylinderCoSystem(void);
	// 初始构造函数
	Bit_CylinderCoSystem( CoordinatesPosition OriginalPoint 
		, CoordinatesPosition Polar_Vector , CoordinatesPosition Z_Vector );

	// 拷贝构造函数
	Bit_CylinderCoSystem( const Bit_CylinderCoSystem &cCCS );
	// 重载"="等号
	Bit_CylinderCoSystem& operator= (const Bit_CylinderCoSystem& cCCS );
	// 重载"=="恒等判断
	bool operator == (const Bit_CylinderCoSystem& cCCS )const;

	~Bit_CylinderCoSystem(void);

	// 初始化设置
	void Set_Initial( const CoordinatesPosition& OriginalPoint 
		, const CoordinatesPosition& Polar_Vector ,const CoordinatesPosition& Z_Vector);
	
	//空间坐标系转换到柱面坐标系
	void TransformFromCSToCCS( const int &XorY , const CoordinateSystem &CP_CS );
	//空间坐标系(指针)转换到柱面坐标系
	void TransformFromCS_PToCCS( const int &XorY , const CoordinateSystem *CP_CS );
	
	// 得到原点
	inline CoordinatesPosition Get_OriginalPoint(void) const ;
	// 得到极轴向量
	inline CoordinatesPosition Get_PolarAixVector(void) const ;
	// 得到Z轴向量
	inline CoordinatesPosition Get_ZAixVector(void) const;
	

private:
	// 坐标原点
	CoordinatesPosition OriginalPoint_;
	// 极轴向量
	CoordinatesPosition Polar_AixVector_;
	// Z轴向量
	CoordinatesPosition Z_AixVector_;
};

#endif

