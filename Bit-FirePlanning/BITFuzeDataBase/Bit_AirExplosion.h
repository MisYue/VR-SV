/********************************************************************
created:	2016/08/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	空爆引信相关

*********************************************************************/

#include "Bit_FuzeDataBase_Global.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#ifndef BITAIREXPLOSION_H__
#define BITAIREXPLOSION_H__

class BITFUZEDATABASE_API Bit_AirExplosion
{
public:
	// 空函数
	Bit_AirExplosion(void);
	// 初始构造函数
	Bit_AirExplosion( const Bit_UnitSystem& US , const double& AirExplosionHE 
		, const double& AirExplosionHS );
	// 拷贝构造函数
	Bit_AirExplosion( const Bit_AirExplosion& cAE );
	// 重载等号
	Bit_AirExplosion& operator= (const Bit_AirExplosion& cAE );
	// 重载“==”等号
	bool operator == (const Bit_AirExplosion& cAE )const;
	// 重载“!=”等号
	bool operator != (const Bit_AirExplosion& cAE )const;

	~Bit_AirExplosion(void);

	// 设置初始化
	inline void Set_Initial( const Bit_UnitSystem& US 
		, const double& AirExplosionHE , const double& AirExplosionHS );
	// 转换单位
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//得到是否定义
	inline bool Get_USDefinition(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;

	// 空炸高度期望
	inline double Get_AirExplosionHE(void)const;
	// 空炸高度标准差
	inline double Get_AirExplosionHS(void)const;

private:
	// 单位制
	Bit_UnitSystem US_;
	// 空炸高度期望
	double AirExplosionHE_;
	// 空炸高度标准差
	double AirExplosionHS_;
	//单位制定义
	bool USDefinition_;
};
#endif
