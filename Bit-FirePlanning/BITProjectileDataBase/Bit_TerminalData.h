/********************************************************************
created:	2016/8/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	弹药终端数据

*********************************************************************/

#ifndef BITTERMINALDATA_H__
#define BITTERMINALDATA_H__

#include "BITProjectileDataBase/Bit_ProjectileDataBase_Global.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"

class BITPROJECTILEDATABASE_API Bit_TerminalData
{
public:
	// 空函数
	Bit_TerminalData(void);
	// 构造函数
	Bit_TerminalData( Bit_UnitSystem US , double TerminalV , double CEP );
	// 拷贝构造函数
	Bit_TerminalData( const Bit_TerminalData& cTD );
	// 重载等号
	Bit_TerminalData& operator= (const Bit_TerminalData& cTD );
	// 重载“==”等号
	bool operator == (const Bit_TerminalData& cTD )const;
	// 重载“!=”等号
	bool operator != (const Bit_TerminalData& cTD )const;

	~Bit_TerminalData(void);

	// 设置初始化
	inline void Set_Initial( const Bit_UnitSystem& US , const double& TerminalV , const double& CEP );
	// 转换单位
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//得到是否定义
	inline bool Get_USDefinition(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;
	// 得到终端速度
	inline double Get_TerminalV(void)const;
	// 得到CEP
	inline double Get_CEP(void)const;

private:
	// 单位制
	Bit_UnitSystem US_;
	// 终端速度
	double TerminalV_;
	// CEP
	double CEP_;
	//单位制定义
	bool USDefinition_;
};
#endif
