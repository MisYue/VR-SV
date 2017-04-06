/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	在math.h基础上进行更高一层次数学计算

*********************************************************************/

// #include <cstdlib>
// #include <time.h>
// #include <math.h>

// #pragma once
#ifndef ADVANCEDMATH_H__
#define ADVANCEDMATH_H__

#include "MathCalculationSupport_Global.h"
// 坐标点类
#include "CoordinatesPosition.h"

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API AdvancedMath
{
public:
	AdvancedMath(void);
	~AdvancedMath(void);

	// 角度转弧度
	inline double AngleToRadian(const double& angle) const;
	// 弧度转角度
	inline double RadianToAngle(const double& radian) const;
	// 求插值
	double LinearInterpolation(const double& xx, const double x_table[], const double y_table[], const int&jj)const;
	//计算Delta(德尔塔)
	inline double ComputeDelta(const double& aa , const double& bb , const double& cc)const;
	// 求解一元二次方程( a * x^2 + b * x + c = 0)
	double function_1yuan2ci(const double& aa, const double& bb, const double& cc, const double& x_min, const double& x_max)const;
	// 求一元二次方程较大解( a * x^2 + b * x + c = 0)
	double function_1yuan2ci_Max(const double& aa, const double& bb, const double& cc)const ;
	// 求一元二次方程较小解( a * x^2 + b * x + c = 0)
	double function_1yuan2ci_Min(const double& aa, const double& bb, const double& cc)const ;

	//==========[尹鹏 修改 2015-7-8]==========
	// 求解二元二次方程( a * x^2 + b * y^2 + c * x * y + d * x + e * y + f = 0)
	double function_2yuan2ci(const double& aa, const  double& bb, const double& cc, const double& dd, const double& ee,
		const double& ff, const double& y_min, const double& y_max, const double& xx)const ;
	// 二元二次方程求导( a * x^2 + b * y^2 + c * x * y + d * x + e * y + f = 0) 
	/*double function2yuan2ci_differential(const double& aa, const double& bb, const double& cc, const double& dd, const double& ee,
		const double& ff, const double& y_min, const double& y_max, const double& xx)const ;*/

	//==========[尹鹏 改用模板函数较好 2015-7-8]==========
	// 两个整数之差
	inline int TheDefferenceofTwoIntegers(const int& n_max, const int& n_min)const ;
	// 两个浮点数之差
	inline double TheDefferenceofTwoFloatNumber(const double& n_max ,const double& n_min)const ;

	// 求两个数中的较小数
	inline double CompareForMin(const double& aa , const double& bb)const ;
	// 求两个数中的较大数
	inline double CompareForMax(const double& aa , const double& bb)const ;
	// 求一组(int)数中的最小数函数
	int ComputeMinValueInArrayOnInt(const int& n, const int array[])const;
	// 求一组(int)数中的最大数函数
	int ComputeMaxValueInArrayOnInt(const int& n, const int array[])const;
	// 求一组(double)数中的最小数函数
	double ComputeMinValueInArrayOnDouble(const int& n, const double array[])const ;
	// 计算一组(double)数中的最大值
	double ComputeMaxValueInArrayOnDouble(const int& n, const double array[] )const ;
	// 计算一组数中最大的两个值的差(正值)
	double ComputeMaxTwoValueDiffereconst (int& n, const double array[] )const ;
	// 计算一组数中最小的两个值的差（正值）
	double ComputeMinTwoValueDiffereconst (int& n, const double array[] )const ;

	// 去除数组中的某个数，形成一个新的数组
	int DeleteValueInArray(const int&old_n , const double &value , const double old_array[], double new_array[] )const;

	// 计算某一个数在一组数中排序
	int ComputeSNInArray( const int& n, const double array[] , const double & value )const ;

	//去除重复坐标点返回新的坐标点数组
	void NewArrayPointDistinct( const int&Old_n , const CoordinatesPosition Old_P[], int *New_n , CoordinatesPosition New_P[] ) const;

	// 计算非独立事件的“与”（1-(1-P1)(1-P2)...）函数
	double TheAndComputation(const int& n, const double single_p[] )const ;

	// 计算余弦定理（知道三个边计算角度）
	//IncludedAngleSideOneLength：夹角边1长度，
	//IncludedAngleSideTwoLength：夹角边2长度，
	//IncludedAngleFaceSideLength：夹角对边长度
	double ComputeFaceSideAngle(const double& angle_side_one_length ,
		const double& angle_side_another_length , const double& face_side_length )const ;

	// 将标准值周围值近似为标准值
	double ComputeSimilarStandardValue( const double& similar_value ,
		const double& input_value , const double& tolerance_value )const ;
	// 大于某值量小于1e-12近似为某值
	inline double ApproximateValueForBiggerLittle( const double& Value , const double& Input_value )const;
	// 小于某值量小于1e-12近似为某值
	inline double ApproximateValueForSmallerLittle( const double& Value , const double& Input_value )const;

	// 静态数组计算长度
	inline int ComputeIntArrayLenth_Static(const int Arry[] )const;

	// 动态数组计算int型数组长度
	inline int ComputeIntArrayLenth_Dynamic( const int *N )const;
	// 动态数组计算double型数组长度
	inline int ComputeDoubleArrayLenth_Dynamic( const double *N )const;

	// *************公式拟合算法***********
	//实现对 y = ax 形式函数的参数a进行估计,采用最小二乘法
	double FitAFor_Ax (const int& n , const double dx[], const double dy[] )const;

	//**************排列组合计算*************
	// 计算n的阶乘
	int ComputeFactorialForN( const int& n)const;
};
//}

#endif