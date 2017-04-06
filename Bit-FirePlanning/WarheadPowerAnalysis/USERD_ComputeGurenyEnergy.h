/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	用户自定义的格尼能计算

*********************************************************************/

#ifndef USERDCOMPUTEGURENYENERGY_H__
#define USERDCOMPUTEGURENYENERGY_H__

#include "WarheadPowerAnalysis_Global.h"

#include "MaterialDataBase\ChargeData.h"

class WARHEADPOWERANALYSIS_API USERD_ComputeGurenyEnergy
{
public:
	// 空构造函数
	USERD_ComputeGurenyEnergy(void);
	//初始化定义
	USERD_ComputeGurenyEnergy( Bit_UnitSystem US , double GurneyEnergy );

	~USERD_ComputeGurenyEnergy(void);

	//设置自定义格尼能的单位制
	inline void Set_US( const Bit_UnitSystem& US );
	// 得到单位制度是否定义
	inline bool Get_USIfDefinition(void)const;
	// 得到单位制
	inline Bit_UnitSystem Get_US(void)const;

	////设置自定义格尼能
	inline void Set_GurneyEnergy(const double& GurneyEnergy);
	// 设置自定义格尼能的单位制
	inline void Set_GurneyEnergyAndUS( const Bit_UnitSystem& US , const double& GurneyEnergy );


	//得到自定义格尼能
	inline double Get_GurneyEnergy(void)const;
	//自定义公式_1(不带Charge)
	inline double Get_GurneyEnergyOnUSER_NoCharge( void );
	//自定义公式_2(不带Charge)
	inline double Get_GurneyEnergyOnUSER_WithCharge( const ChargeData& ChargeD )const;

private:
	// 单位系
	Bit_UnitSystem US_;
	// 格尼能
	double GurneyEnergy_;
	// 是否设置了单位制
	bool IfUS_;
};

#endif