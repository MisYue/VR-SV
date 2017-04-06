/********************************************************************
created:	2016/06/02
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	单个破片在弹体坐标系中的速度和位置

*********************************************************************/

#ifndef BITSFRAGVPDATA_H__
#define BITSFRAGVPDATA_H__

// 破片基本数据
#include "Bit_FragmentBaseData.h"
// 战斗部数据动态库
#include "WarheadDataBase_Global.h"
// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 坐标位置
#include "MathCalculationSupport/CoordinatesPosition.h"
// 材料
#include "MaterialDataBase/Bit_MetalData.h"

class WARHEADDATABASE_API Bit_SFragVPData_P
{
public:
	Bit_SFragVPData_P(void);
	// 拷贝构造函数
	Bit_SFragVPData_P( const Bit_SFragVPData_P& cSFD );
	// 重载等号
	Bit_SFragVPData_P& operator= (const Bit_SFragVPData_P& cSFD );
	// 重载“==”等号
	bool operator == (const Bit_SFragVPData_P& cSFD )const;

	~Bit_SFragVPData_P(void);

	//参数初始化设置
	void Set_Initial( const Bit_UnitSystem& US , const int& FId , const Bit_FragmentBaseData& FraBaData
		, const double& SEVelocity , const CoordinatesPosition &SPosition_PCS 
		, const CoordinatesPosition &RPosition_PCS
		, const double& RealSVelocity , const double& RealRTVelocity );

	// 设置基本参数
	void Set_BaseParameters( const Bit_UnitSystem& US , const int& FId ,const double& Mass 
		, const int& FragmentShape);
	// 设置破片静爆初始速度
	inline void Set_SEVelocity( const double& SEVelocity );
	// 设置在弹体坐标系中的初始位置
	inline void Set_SPosition_PCS( const double& SPosition_PCS );
	// 设置在弹体坐标系中的实时位置
	inline void Set_RPosition_PCS( const double& RPosition_PCS );
	// 破片实际初始速度(带弹体牵连的)

	// 破片实际实时速度(带弹体牵连的)

	// 破片的速度衰减(Velocity Reduction)系数

	//*********得到参数***********//
	//得到破片静爆初始速度
	inline double Get_SEVelocity( void )const;

private:
	//单位制
	Bit_UnitSystem US_;
	//破片Id
	int FId_;
	//破片基本数据
	Bit_FragmentBaseData FraBaData_;
	//破片静爆初始速度
	double SEVelocity_;
	//在弹体坐标系中的初始位置
	CoordinatesPosition SPosition_PCS_;
	//在弹体坐标系中的实时位置
	CoordinatesPosition RPosition_PCS_;
	//破片实际初始速度(带弹体牵连的)
	double RealSVelocity_;
	//破片实际实时速度(带弹体牵连的)
	double RealRTVelocity_;
	//单位制定义
	bool USDefinition_;
};
#endif
