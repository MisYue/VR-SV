/*#pragma once*/
/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行冲击波场计算
include:    离爆心任意一点的冲击波超压、作用时间、比冲量以及反射压力等计算
*********************************************************************/

#ifndef BITSHOCKWAVEFIELDANALYSIS_H__
#define BITSHOCKWAVEFIELDANALYSIS_H__
// 动态库导出
#include "WarheadPowerAnalysis_Global.h"

// 单位制
//#include "BITUnitsSupport\Bit_UnitSystem.h"
//高等数据计算
#include "MathCalculationSupport\AdvancedMath.h"

//战斗部威力分析数据结构
#include "WarheadDataBase\WarheadPowerAnalysisData.h"
//装药数据结构
#include "MaterialDataBase\ChargeData.h"

class WARHEADPOWERANALYSIS_API Bit_ShockWaveFieldAnalysis
{
public:
	Bit_ShockWaveFieldAnalysis(void);

	//// 结构体初始化
	Bit_ShockWaveFieldAnalysis( Bit_UnitSystem US );

	~Bit_ShockWaveFieldAnalysis(void);

	////////********不带单位制的基本计算式***************////
	// 计算装药的对比距离(不带单位制计算)
	double ComputeContrastDistance( const double& ChargeMass_kg, const double& Distance_m )const;
	// (基于对比距离)计算冲击波超压峰值(不带单位制)
	double ComputeShockWavePressureOnCDis(const double& aa, const double& bb, const double& cc
		, const double& dd, const double &ConDis_Min , const double &ConDis_Max ,const double& ContrastDistance)const;
	// (基于装药质量和距离)计算冲击波超压峰值(不带单位制计算)
	inline double ComputeShockWavePressureOnDis(const double& aa, const double& bb, const double& cc , const double& dd
		, const double &ConDis_Min , const double &ConDis_Max ,const double& ChargeMass_kg
		, const double& Distance_m , double *ContrastDistance )const;
	// 计算正反射超压(不带单位制计算，输入和输出单位制一样) 
	inline double ComputeVerticalReflectionPressure( const double& IncomingOverPressure , 
		const double& AirPressure )const;
	// 计算正规斜反射超压(不带单位制计算，输入和输出单位制一样)
	double ComputeRegularObliqueReflectionPressure( const double& AirPressure
		, const double& IncomingAngle_R , const double& IncomingPressure
		, const double& kk_AirIsentropicIndex )const ;

	// 计算马赫反射超压(不带单位制计算，输入和输出单位制一样)
	inline double ComputeMachReflectionPressure( const double& IncomingOverPressure, 
		const double& IncomingAngle_R )const;

	// 马赫反射临界角度计算(不带单位制计算)
	double ComputeMachReCriticalAngle( const double &ChargeMass_kg 
		, const double &ExplosionH_m)const;

	//计算正压区作用时间

	//正压区作用压力随时间的变化

	////////********带单位制的基本计算式***************////
	// 计算装药的对比距离(带单位制计算)
	double ComputeContrastDistance_US( const Bit_UnitSystem& US , const double& ChargeMass 
		, const double& Distance ,double *ContrastDistance_IUS )const;
	
	////////********带数据结构的基本计算式***************////
	// 计算装药的对比距离(带单位制、带装药结构)
	double ComputeConstrastDistance_Data( const Bit_UnitSystem& US , const double& Distance 
		, const WarheadPowerAnalysisData &WarheadData , double *ContrastDistance_IUS , double *ContrastDistance_WarUS )const;

private:
	// 单位系
	Bit_UnitSystem US_;
	// 单位系是否定义
	bool IfUS_;
};

#endif

