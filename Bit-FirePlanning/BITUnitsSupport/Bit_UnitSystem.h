/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	单位系定义及相关计算函数

*********************************************************************/
// #pragma once

#ifndef BITUNITSYSTEM_H__
#define BITUNITSYSTEM_H__

#include "BITUnitsSupport/Bit_UnitsTransform.h"
#include "MathCalculationSupport\CoordinatesPosition.h"

class BITUNITSSUPPORT_API Bit_UnitSystem
{
public:
	//构造空单位制
	Bit_UnitSystem(void);
	// 构造初始化单位制，确定三个单位选项
	Bit_UnitSystem( int Length , int Mass , int Time );
	// 构造初始化单位制（int 数组型）
	Bit_UnitSystem( int Units[3]);

	// 拷贝构造函数
	Bit_UnitSystem( const Bit_UnitSystem &cUS );
	// 重载"="等号
	Bit_UnitSystem& operator= (const Bit_UnitSystem& cUS );
	// 重载"=="恒等判断
	bool operator == (const Bit_UnitSystem& cUS )const;
	// 重载"!="恒等判断
	bool operator != (const Bit_UnitSystem& cUS )const;

	~Bit_UnitSystem(void);

	// 1.得到长度单位
	int Get_LengthUnit(void)const;
	// 2.得到质量单位
	int Get_MassUnit(void)const;
	// 3.得到时间单位
	int Get_TimeUnit(void)const;
	// 4.得到长度系数
	inline double Get_LengthCoefficient(void)const;
	// 5.得到质量系数
	inline double Get_MassCoefficient(void)const;
	// 6.得到时间系数
	inline double Get_TimeCoefficient(void)const;
	// 7.得到密度系数
	inline double Get_DensityCoefficient(void)const;
	// 8.得到力系数
	inline double Get_ForceCoefficient(void)const;
	// 9.得到压强系数
	inline double Get_PressureCoefficient(void)const;
	// 10.得到能量系数
	inline double Get_EnergyCoefficient(void)const;
	// 11.得到速度系数
	inline double Get_VelocityCoefficient(void)const;
	// 12.得到面积系数
	inline double Get_AreaCoefficient(void)const;
	// 13得到体积系数
	inline double Get_VolumCoefficient(void)const;
	// 14.得到对比距离系数
	inline double Get_ContrastDisCoefficient(void)const;
	// 15.得到应变率系数
	inline double Get_StrainRateCoefficient(void)const;
	// 16.得到基础长度单位下的坐标值
	inline CoordinatesPosition Get_CoordinateValueOnBaseU( const CoordinatesPosition &InputCoord)const;
	// 17.由基础长度单位下的坐标值得到当前坐标单位下的坐标值
	inline CoordinatesPosition Get_CoordinateValueOnBaseN( const CoordinatesPosition &InputCoord)const;
	// 18.得到速度衰减系数
	inline double Get_VRCCoefficient(void)const;

private:
	// 长度系数
	double LengthCoefficient_;
	// 质量系数
	double MassCoefficient_;
	// 时间系数
	double TimeCoefficient_;
};
#endif
