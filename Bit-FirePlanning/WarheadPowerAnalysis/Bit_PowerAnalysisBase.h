/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行基础计算

*********************************************************************/

#ifndef BITPOWERANALYSISBASE_H__
#define BITPOWERANALYSISBASE_H__
// 动态库导出
//#include "WarheadPowerAnalysis_Global.h"

#include "WarheadDataBase\WarheadPowerAnalysisData.h"

//计算哥尼能的用户自定义
#include "USERD_ComputeGurenyEnergy.h"
//#include "MathCalculationSupport\UnitSystem.h"

class WARHEADPOWERANALYSIS_API Bit_PowerAnalysisBase
{
public:
	// 空构造函数
	Bit_PowerAnalysisBase(void);
	// 结构体初始化
	Bit_PowerAnalysisBase( Bit_UnitSystem US );

	//***********************非战斗部、装药数据结构参量计算****************************
	//返回：战斗部整体装药与壳体质量比
	double ComputeMassRatioForChargeAndShell( const double& WholeMass, const double& ChargesMass, const double& ShellMass)const;
	//计算战斗部圆柱段装药和壳体质量比
	inline double ComputeMassRatioForChargeAndShellInClinder( const double& ChargeMassInClinder , const double &ShellMassInClinder )const;
	//计算战斗部装填系数
	inline double ComputeFillCoefficient( const double& WholeMass, const double& ChargeWholeMass )const;
	//基于爆热的TNT当量计算(输入TNT爆炸和炸药爆热)
	inline double ComputeTNTNLOnQv(const double& ChargeMass , const double &ChargeQv , const double &TNTQV)const;
	//计算带壳装药相当于裸露装药的当量公式1
	double ComputeChargeEquivalentMassWithShell_F1(const double& ChargeWithshell , const double& R_0 
		, const double& R_P0 , const double &aa , const double &bb , const double& PolytropicE , const double&WLC)const;
	//运动装药向静止装药转换公式1(使用过程中需注意单位制的统一)
	double ComputeMotionChargeEquivalentMass_F1( const double& ChargeMovie_Kg, const double& ChargeVelocity_MS, const double& ChargeQv_JKg )const;

	////////********按战斗部、装药数据结构参数计算参量******************
	// 战斗部整体装药与壳体质量比
	double ComputeMassRatioForChargeAndShellOnWarD( const WarheadPowerAnalysisData &WarheadD)const;
	// 计算战斗部圆柱段装药和壳体质量比
	double ComputeMassRatioForChargeAndShellInClinderOnWarD( const WarheadPowerAnalysisData &WarheadD )const;
	// 计算战斗部装填系数
	double ComputeFillCoefficientOnWarD( const WarheadPowerAnalysisData &WarheadD )const;
	
	///////************按公式计算参量******************
	// 计算格尼能（输入公式号）
	double ComputeGurneyEnergy( const int& Function_Number , const ChargeData& ChargeD )const;
	// 用户自定义计算格尼能（输入公式号）
	double ComputeGurneyEnergy_USER( const int& Number , const ChargeData& ChargeD , USERD_ComputeGurenyEnergy &USERD_GE )const;
	// 计算TNT当量（输入公式号）_不带壳（输入公式号）
	double ComputeTNTEquivalentWithoutShell( const int& Function_Number , const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD )const;
	// 计算装药爆炸气体的多方指数（输入公式号）
	double ComputeExplosionGasPolytropicExponent( const int& Function_Number , const ChargeData& ChargeD )const;
	// 计算带壳装药的等效质量（输入公式号）
	double ComputeChargeEquivalentMassWithShellOnWarD( const int& Function_Number , const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD , const int& PECompute_Num )const;

	///////////*******成熟算子************************
	// 计算格尼能公式1
	double GurenyEnergy_F1( const ChargeData& ChargeD )const;
	// 计算格尼能公式2
	double GurenyEnergy_F2( const ChargeData& ChargeD )const;
	// 计算TNT当量公式1（不带壳）
	double TNTEquivalentWithoutShell_F1( const WarheadPowerAnalysisData &WarheadData , const ChargeData& ChargeD )const;
	// 计算多方指数(绝热指数)公式1
	double ExplosionGasPolytropicExponent_F1( const ChargeData& ChargeD )const;
	// 计算多方指数(绝热指数)公式2
	double ExplosionGasPolytropicExponent_F2( const ChargeData& ChargeD )const;

	// 计算带壳装药的等效装药质量公式1
	double ChargeEquivalentMassWithShellOnWarD_F1( const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD , const int& PECompute_Num )const;
	
	
	~Bit_PowerAnalysisBase(void);


private:
	// 单位系
	Bit_UnitSystem US_;
	// 定义是否初始化单位系数
	bool IfUS_;
};

#endif