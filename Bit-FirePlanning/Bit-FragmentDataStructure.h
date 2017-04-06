/********************************************************************
Creating Date:	2016/04/25
 
File Ext:	h

Purpose:	单个破片毁伤数据结构

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "MathCalculationSupport/ProbabilityAndRandom.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "MathCalculationSupport/Line.h"
#include "MeshSupport/QuadMeshingQuad.h"
#include "Bit-FirePlanningGlobal.h"
#pragma once

class BIT_FIREPLANNING_API Bit_FragmentDataStructure
{
public:
	//空构造函数
	Bit_FragmentDataStructure();
	//构造函数初始化
	//id:破片ID号；US：单位制；StaticDisporaAngle：破片静态飞散角；StaticDirectonalAngle：破片静态方向角；
	//DynamicCircleAngle:破片动态周向角；DynamicDirectionalAngle:破片动态方向角；FlyDistance：破片飞行距离;
	//FragmentVelocity:破片初速；FragmentDynamicVelocity:每个破片动态飞散速度（破片实际速度）；FragmentPositionInRocketCoordinate:破片在弹体坐标系内坐标
	Bit_FragmentDataStructure( int &id , Bit_UnitSystem &US , double &Mass , double &StaticDisporaAngle , double &StaticDirectonalAngle ,
		double &DynamicCircleAngle , double &DynamicDirectionalAngle , double &FlyDistance , double &FragmentVelocity , double &FragmentDynamicVelocity ,
		CoordinatesPosition &FragmentPositionInRocketCoordinate , double &FragmentResidualVelocity );
	~Bit_FragmentDataStructure();
	//拷贝构造函数
	Bit_FragmentDataStructure( const Bit_FragmentDataStructure &Bit_Frag );
	//运算符“=”重载
	Bit_FragmentDataStructure &operator=( const Bit_FragmentDataStructure &Bit_Frag );

	//设置破片ID值
	void Set_FragmentID( int Frag_ID );
	//设置单位制
	void Set_FragmentUS( Bit_UnitSystem &Frag_US );
	//设置破片质量
	void Set_Mass( double &Frag_Mass );
	//设置破片静态飞散角
	void Set_StaticDisporaAngle( double &Frag_StaticDisporaAngle );
	//设置破片静态方向角
	void Set_StaticDirectonalAngle( double &Frag_StaticDirectonalAngle );
	//设置破片动态周向角
	void Set_DynamicCircleAngle( double Frag_DynamicCircleAngle );
	//设置破片动态方向角
	void Set_DynamicDirectionalAngle( double &Frag_DynamicDirectionalAngle );
	//设置破片飞行距离
	void Set_FlyDistance( double &Frag_FlyDistance );
	//设置破片初速
	void Set_FragmentVelocity( double &Frag_FragmentVelocity );
	//设置破片动态飞行速度
	void Set_FragmentDynamicVelocity( double &Frag_FragmentDynamicVelocity );
	//设置破片在弹体坐标系内坐标
	void Set_FragmentPositionInRocketCoordinate( CoordinatesPosition &Frag_FragmentPositionInRocketCoordinate );
	//设置破片剩余速度
	void Set_FragmentResidualVelocity( double &Frag_FragmentResidualVelocity );


	//得到破片ID
	int Get_FragmentID( void )const;
	//得到单位制
	Bit_UnitSystem Get_FragmentUS( void )const;
	//得到破片质量
	double Get_Mass( void )const;
	//得到破片静态飞散角
	double Get_StaticDisporaAngle( void )const;
	//得到破片静态方向角
	double Get_StaticDirectonalAngle( void )const;
	//得到破片动态周向角
	double Get_DynamicCircleAngle( void );
	//得到破片动态方向角
	double Get_DynamicDirectionalAngle( void )const;
	//得到破片飞行距离
	double Get_FlyDistance( void )const;
	//得到破片初速
	double Get_FragmentVelocity( void )const;
	//得到破片动态飞行速度
	double Get_FragmentDynamicVelocity( void )const;
	//得到破片在弹体坐标系内坐标
	CoordinatesPosition Get_FragmentPositionInRocketCoordinate( void )const;
	//得到破片剩余速度
	double Get_FragmentResidualVelocity( void )const;


private:
	Bit_UnitSystem US_;
	int id_;
	double Mass_;
	double StaticDisporaAngle_ ;
	double StaticDirectonalAngle_;
	double FlyDistance_;
	double DynamicCircleAngle_;
	double DynamicDirectionalAngle_;
	CoordinatesPosition FragmentPositionInRocketCoordinate_;
	double FragmentVelocity_;
	double FragmentDynamicVelocity_;
	//CoordinatesPosition FragmentPositionInAimCoordinate_;
	double FragmentResidualVelocity_;
};