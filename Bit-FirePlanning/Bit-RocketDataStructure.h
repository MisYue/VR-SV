/********************************************************************
Creating Date:	2016/04/26
 
File Ext:	h

Purpose:	火箭弹（含弹体坐标系）数据结构

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "Bit-FirePlanningGlobal.h"
#pragma once
class BIT_FIREPLANNING_API Bit_RocketDataStructure
{
public:
	//构造函数初始化
	//id:火箭弹ID号；US：单位制；PitchingAngle:火箭弹俯仰角（弹体坐标系下）；YawAngle：火箭弹偏航角（弹体坐标系下）；
	//WarheadStaticDisporaAngle:火箭弹战斗部静态飞散角;WarheadStaticAngleCentralLine:火箭弹战斗部静态飞散角分布中心线与弹体坐标系x轴夹角
	//RocketVelocity:火箭弹速度;RocketCEP:火箭弹CEP
	Bit_RocketDataStructure( int &id , Bit_UnitSystem &US , double &PitchingAngle , double &YawAngle , double &WarheadStaticDisporaAngle , double &WarheadStaticAngleCentralLine ,
		double &RocketVelocity , double &RocketCEP );
	~Bit_RocketDataStructure();
	//拷贝构造函数
	Bit_RocketDataStructure( const Bit_RocketDataStructure &Bit_Rock );
	//运算符“=”重载
	Bit_RocketDataStructure &operator=( const Bit_RocketDataStructure &Bit_Rock );

	//设置火箭弹ID值
	void Set_RocketID( int &Rock_ID );
	//设置火箭弹单位制
	void Set_RocketUS( Bit_UnitSystem &Rock_US );
	//设置火箭弹俯仰角
	void Set_RocketPitchingAngle( double &Rock_PitchingAngle );
	//设置火箭弹偏航角
	void Set_RocketYawAngle( double &Rock_YawAngle );
	//设置火箭弹战斗部静态飞散角
	void Set_WarheadStaticDisporaAngle( double &Rock_WarheadStaticDisporaAngle );
	//设置火箭弹战斗部静态飞散角分布中心线与弹体坐标系x轴夹角
	void Set_WarheadStaticAngleCentralLine( double &Rock_WarheadStaticAngleCentralLine );
	//设置火箭弹速度
	void Set_RocketVelocity( double &Rock_Velocity );
	//设置火箭弹速度
	void Set_RocketCEP( double &Rock_CEP );


	//得到火箭弹ID
	int Get_RocketID( void )const;
	//得到火箭弹单位制
	Bit_UnitSystem Get_RocketUS( void )const;
	//得到火箭弹俯仰角
	double Get_RocketPitchingAngle( void )const;
	//得到火箭弹偏航角
	double Get_RocketYawAngle( void )const;
	//得到火箭弹战斗部静态飞散角
	double Get_WarheadStaticDisporaAngle( void )const;
	//得到火箭弹战斗部静态飞散角分布中心线与弹体坐标系x轴夹角
	double Get_WarheadStaticAngleCentralLine( void )const;
	//得到火箭弹速度
	double Get_RocketVelocity( void )const;
	//得到火箭弹CEP
	double Get_RocketCEP( void )const;

private:
	Bit_UnitSystem US_;
	int id_;
	double PitchingAngle_;
	double YawAngle_;
	double WarheadStaticDisporaAngle_;
	double WarheadStaticAngleCentralLine_;
	double RocketVelocity_;
	double RocketCEP_;
};