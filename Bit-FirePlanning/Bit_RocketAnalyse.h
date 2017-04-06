/********************************************************************
Creating Date:	2016/05/06
 
File Ext:	h

Purpose:	火箭弹战斗部威力计算

*********************************************************************/


#include "WarheadDataBase/WarheadPowerAnalysisData.h"
#include "WarheadPowerAnalysis/Bit_PowerAnalysisBase.h"
#include "MaterialDataBase/ChargeData.h"
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "HitAndExplosionPointAnalysis/HAE_HitPointAnalysis.h"
#include "MathCalculationSupport/ProbabilityAndRandom.h"
#include "Bit-RocketDataStructure.h"
#include "Bit-FirePlanningGlobal.h"
class BIT_FIREPLANNING_API Bit_RocketAnalyse
{
public:

	//空构造函数
	Bit_RocketAnalyse();
	//构造函数初始化
	Bit_RocketAnalyse( Bit_UnitSystem &US );
	~Bit_RocketAnalyse();
	//拷贝构造函数
	Bit_RocketAnalyse( const Bit_RocketAnalyse &Bit_Rock );
	//运算符“=”重载
	Bit_RocketAnalyse &operator=( const Bit_RocketAnalyse &Bit_Rock );

	//计算破片初速（Gurney公式）
	//USForVelocity:计算单位制
	double ComputeFragmentVelocityViaGurney( WarheadPowerAnalysisData &WarheadData , ChargeData &ChargeD , Bit_UnitSystem &USForVelocity )const;
	//速度衰减后破片剩余速度(FragmentVelocity:破片初速；FlyDistance：破片飞行距离；AttenuationCoefficient：速度衰减系数)
	double ComputeFragmentVelocityAttenuation( double &FragmentVelocity , double &FlyDistance , double &AttenuationCoefficient )const;
	//速度衰减系数(ResistanceCoefficient：气动阻力系数；LocalAirDencity：当地空气密度；FragmentFrontalArea：破片展现面积；FragmentMass：破片质量)
	double ComputeVelocityAttenuationCoefficient( double &ResistanceCoefficient , double &LocalAirDencity , double &FragmentFrontalArea , double &FragmentMass , Bit_UnitSystem &US )const;
	//当地空气密度(AboveSeaLevel：海拔高度)
	double ComputeLocalAirDensity( double &AboveSeaLevel , Bit_UnitSystem &US )const;
	//破片展现面积(ShapeCoefficient:形状系数；FragmentMass：破片质量)
	double ComputeFragmentFrontalArea( double &ShapeCoefficient , double &FragmentMass , Bit_UnitSystem &US )const;


	//********************计算带CEP的火箭弹在目标平面上瞄准点******************//
	//计算瞄准点在目标坐标系内位置（考虑CEP）
	//AimPointWithoutCEP：瞄准点在目标坐标系内坐标（未带CEP）；CEP：火箭弹CEP；PitchingAngle：火箭弹俯仰角；YawAngle：火箭弹偏航角
	CoordinatesPosition AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure )const;
	////计算瞄准点在目标坐标系内位置（考虑CEP，NRotate）
	////AimPointWithoutCEP：瞄准点在目标坐标系内坐标（未带CEP）；CEP：火箭弹CEP；PitchingAngle：火箭弹俯仰角；YawAngle：火箭弹偏航角
	//CoordinatesPosition AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure )const;
	//抽样计算得到炸点坐标
	//AimPointWithCEP：瞄准点（带CEP）在目标坐标系位置；BurstHighE：引信炸高期望；BurstHighD：引信炸高方差
	CoordinatesPosition BurstPoint( CoordinatesPosition &AimPointWithCEP , double &BurstHighE , double &BurstHighD , Bit_RocketDataStructure &RockDataStructure )const;

	

private:
	Bit_UnitSystem US_;

};