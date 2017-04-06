/********************************************************************
created:	2016/01/26
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	弹目交汇的撞击点分析

*********************************************************************/


// #pragma once

#ifndef HAE_HITPOINTANALYSIS_H__
#define HAE_HITPOINTANALYSIS_H__

#include "HitAndExplsionPointAnalysis_Global.h"

// 调用头文件（高等数学计算）
#include "MathCalculationSupport\AdvancedMath.h"
// 调用头文件（空间几何）
#include "MathCalculationSupport\CoordinatesPosition.h"


class HITANDEXPLSIONPOINTANALYSIS_API HAE_HitPointAnalysis
{

public:
	HAE_HitPointAnalysis(void);
	~HAE_HitPointAnalysis(void);

	//**************根据弹道表计算落速和落角*******************//
	
	//根据大地(地球)坐标系中射击点和目标中心点的经纬度值计算落角
	double ComputeFallAngleOnLoLA_Table( const double& Start_Lo , const double& Start_La , const double& End_Lo
		, const double& End_La , const int&n ,  const double FirDistance[] , const double FallAngle[] )const ;

	//根据大地(地球)坐标系中射击点和目标中心点的经纬度值计算落速



	//根据射程查表线性插值计算落角和落速
	void ComputeFallAngleAndVelocityOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] , const double FallAngle[] 
	    , const double FallVelocity[] , double *Fall_Angle , double *Fall_Velocity )const;
	//根据射程查表线性插值计算落角
	double ComputeFallAngleOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] 
	    , const double FallAngle[] )const ;
	//根据射程查表线性插值计算落速
	double ComputeFallVelocityOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] 
		, const double FallVelocity[])const ;

	//***************根据火炮射击时射击方向和目标的真方位角（大地坐标系）计算目标坐标系中弹药相对目标的方位角

	//*********根据弹药相对目标的方位角和高低角计算末端弹道
	//计算制导平面上的瞄准点（根据目标坐标系下的瞄准点、弹药相对目标的方位角(度)和高低角(度)，Z轴向上的，X轴指向目标前部）
	CoordinatesPosition ComputeAimPositionOnGuide( const CoordinatesPosition& AmmunitionAimPoint_Tar ,
		const double&AmmunitionYawAngle_Tar , const double&AmmunitionPitchingAngle_Tar )const;

};
#endif

