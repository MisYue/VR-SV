//#pragma once
/********************************************************************
created:	2016/02/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	为装药数据库提供数据结构

*********************************************************************/

#ifndef CHARGEDATA_H__
#define CHARGEDATA_H__

#include "MaterialDataBase/MaterialDataBase_Global.h"
//单位制度
#include "BITUnitsSupport/Bit_UnitSystem.h"

class MATERIALDATABASE_API ChargeData
{
public:
	// 空构造函数
	ChargeData(void);
	// 结构体初始化
	ChargeData( int Charge_Id , Bit_UnitSystem US , double Density
		, double ExplosionVelocity , double ExplosionHeat , double ExplosinPressure );
	
	// 拷贝构造函数
	ChargeData( const ChargeData& cCharData );
	// 重载等号
	ChargeData& operator= (const ChargeData& cCharData );
	// 重载"=="恒等号
	bool operator == (const ChargeData& cCharData )const;
	// 析构
	~ChargeData(void);

	// **********所有数据转换到新的单位制中***********//
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );
	// 仅仅转换长度单位
	inline void TransitionLength( const int& Length );
	// 仅仅转换时间单位
	inline void TransitionTime( const int& Time );
	// 仅仅转换重量单位
	inline void TransitionMass( const int& Mass );
	// 转换单位并输出
	//ChargeData TransitionUS_Input( const Bit_UnitSystem& NewUS );

	//*************88

	//初始化设置
	void Set_Initial( const int& Charge_Id , const Bit_UnitSystem& US 
		, const double& Density , const double& ExplosionVelocity 
		, const double& ExplosionHeat , const double& ExplosinPressure );

	//得到是否定义
	inline bool Get_IfDefinition(void)const;
	//得到装药Id
	inline int Get_ChargeId(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;
	// 得到装药密度（与输入单位制一致）
	inline double Get_Density(void)const;
	// 得到装药爆速（与输入单位制一致）
	inline double Get_ExplosionVelocity(void)const;
	// 得到装药爆热（与输入单位制一致）
	inline double Get_ExplosionHeat(void)const;
	// 得到装药爆压（与输入单位制一致）
	inline double Get_ExplosinPressure(void)const;

	// 得到装药密度（mm-g-us单位系输出）
	inline double Get_DensityForC(void)const;
	// 得到装药爆速（mm-g-us单位系输出）
	inline double Get_ExplosionVelocityForC(void)const;
	// 得到装药爆热（mm-g-us单位系输出）
	inline double Get_ExplosionHeatForC(void)const;
	// 得到装药爆压（mm-g-us单位系输出）
	inline double Get_ExplosinPressureForC(void)const;

	//通过id号返回单位系（与输入单位制一致）
	Bit_UnitSystem Get_USOnId( const int& id )const;
	//通过id号返回装药密度（与输入单位制一致）
	inline double Get_DensityOnId( const int& id )const;
	//通过id号返回装药爆速（与输入单位制一致）
	inline double Get_ExplosionVelocityOnId( const int& id )const;
	//通过id号返回装药爆热（与输入单位制一致）
	inline double Get_ExplosionHeatOnId( const int& id )const;
	//通过id号装药爆压（与输入单位制一致）
	inline double Get_ExplosinPressureOnId( const int& id )const;
	

private:
	// 装药号（唯一识别符）
	int Charge_Id_;
	// 单位系
	Bit_UnitSystem US_;
	// 装药密度
	double Density_;
	// 装药爆速
	double ExplosionVelocity_;
	// 装药爆热
	double ExplosionHeat_;
	// 装药爆压
	double ExplosinPressure_;
	// 是否定义
	bool IfDefinition_;
};
#endif
