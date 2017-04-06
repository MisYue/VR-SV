/********************************************************************
created:	2015/04/05
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行相关概率分析及随机抽样

*********************************************************************/

//#pragma once

#ifndef PROBABILITYANDRANDOM_H__
#define PROBABILITYANDRANDOM_H__

#include "MathCalculationSupport_Global.h"
#include "CoordinatesPosition.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API ProbabilityAndRandom
{
public:
	ProbabilityAndRandom(void);
	~ProbabilityAndRandom(void);
	// 产生随机数函数

	// number：随机数的范围，amount：随机数个数，randomNumber[]产生的随机数
	bool GenerateRandom( const double& number , const int& amount  , double randomnumber[] )const;
	// 根据样本进行随机抽样（0-1）之间的随机数
	//int:样本量（>0），随机抽样(0-1之间的随机数)获得的值放入的数组
	bool SampleOnSampleNumber( const int& sn , double rn_aepa[])const;
	//得到1D标准正态分布随机数
	double Get1DStandardNormalDistributionRandom( const int& r_num0_1 )const;

	// 得到2D标准正态分布基于cos的
	inline double Get2DStandardNormalDistributionRandom_cos( const double& r1 , const double& r2 )const;
	// 得到2D标准正态分布基于sin的
	inline double Get2DStandardNormalDistributionRandom_sin( const double& r1 , const double& r2 )const;

	// 计算一组数中的平均
	double ComputeAverageValueInArray(const int& n, const double array[] )const ;
	// 计算N个数中的标准差
	double ComputeStandardDifference( const int& n , const double array[])const;

	// 获得多个空间点的平均值
	CoordinatesPosition GetExpectationOnMultiPoint( const int& n , const CoordinatesPosition point[] )const;
	
};

//}
#endif
