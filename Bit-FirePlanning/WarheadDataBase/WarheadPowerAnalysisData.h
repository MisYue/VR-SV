/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	为战斗部威力分析提供数据结构

*********************************************************************/

#ifndef WARHEADDATABASE_H__
#define WARHEADDATABASE_H__

// 单位制数据
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 战斗部数据动态库
#include "WarheadDataBase_Global.h"
// 装药数据库
//#include "MaterialDataBase\ChargeData.h"

class WARHEADDATABASE_API WarheadPowerAnalysisData
{
public:
	// 空构造函数
	WarheadPowerAnalysisData(void);
	// 结构体初始化
	WarheadPowerAnalysisData( int Warhead_Id , Bit_UnitSystem US , double ShellMass_Clylinder
		, double ChargeMass_Clylinder , double AllMass_Whole , double ChargeMass_Whole , int ChargeID
		, int StructureType , double ShellInterDiameter , double ShellOuterDiameter 
		,double ShellBrokenDiameter , double WarheadLength_Whole , double WarheadLength_Clylinder );

	// 拷贝构造函数
	WarheadPowerAnalysisData( const WarheadPowerAnalysisData& cWarData );
	// 重载等号
	WarheadPowerAnalysisData& operator= (const WarheadPowerAnalysisData& cWarData );

	// 重载“==”等号
	bool operator == (const WarheadPowerAnalysisData& cWarData )const;

	~WarheadPowerAnalysisData(void);

	// 初始化设置
	void Set_Initial( const int& Warhead_Id , const Bit_UnitSystem& US ,const double& ShellMass_Clylinder
		, const double& ChargeMass_Clylinder , const double& AllMass_Whole
		, const double& ChargeMass_Whole , const int& ChargeID , const int&StructureType 
		, const double& ShellInterDiameter , const double &ShellOuterDiameter 
		, const double&ShellBrokenDiameter , const double &WarheadLength_Whole
		, const double& WarheadLength_Clylinder );

	// **********所有数据转换到新的单位制中***********//
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	// 得到是否定义
	inline bool Get_IfDefinition(void)const; 
	// 得到战斗部编号
	inline int Get_WarheadId(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;
	// 得到圆柱段壳体质量（只针对圆柱形）
	inline double Get_ShellMassClylinder(void)const;
	// 得到圆柱段装药质量（只针对圆柱形）
	inline double Get_ChargeMassClylinder(void)const;
	// 得到战斗部整体质量
	inline double Get_AllMassWhole(void)const;
	// 战斗部整体装药质量
	inline double Get_ChargeMassWhole(void)const;
	// 战斗部结构类型
	inline int Get_StructureType(void)const;
	// 壳体内直径（只针对圆柱形）
	inline double Get_ShellInterDiameter(void)const;
	// 壳体外直径（只针对圆柱形）
	inline double Get_ShellOuterDiameter(void)const;
	// 壳体破裂直径（只针对圆柱形）
	inline double Get_ShellBrokenDiameter(void)const;
	// 战斗部整体长度
	inline double Get_WarheadLengthWhole(void)const;
	// 战斗部圆柱段长度
	inline double Get_WarheadLengthClylinder(void)const;
	// 得到装药号
	inline int Get_ChargeId(void)const;

	//**********通过ID返回************
	// 通过ID返回单位系
	Bit_UnitSystem Get_USOnId( const int& id )const;
	// 通过ID返回装药号
	int Get_ChargeIdOnId( const int& id )const;

private:
	// 战斗部Id号
	int Warhead_Id_;
	// 单位系
	Bit_UnitSystem US_;
	// 战斗部结构类型
	int StructureType_;
	// 壳体内直径（只针对圆柱形）
	double ShellInterDiameter_;
	// 壳体外直径（只针对圆柱形）
	double ShellOutterDiameter_;
	// 壳体破裂直径（只针对圆柱形）
	double ShellBrokenDiameter_;
	// 战斗部整体长度
	double WarheadLength_Whole_;
	// 战斗部圆柱段长度
	double WarheadLength_Clylinder_;
	// 圆柱段壳体质量
	double ShellMass_Clylinder_; 
	// 圆柱段装药质量
	double ChargeMass_Clylinder_; 
	// 战斗部整体质量
	double AllMass_Whole_;
	// 战斗部整体装药质量
	double ChargeMass_Whole_;
	// 装药ID号
	int ChargeID_;
	// 是否定义
	bool IfDefinition_;
};
#endif
