/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	冲击波试验测试点数据的数据结构

*********************************************************************/

#ifndef BITSHOCKWAVETESTPOINTDATA_H__
#define BITSHOCKWAVETESTPOINTDATA_H__


// 战斗部数据动态库
#include "WarheadDataBase_Global.h"
// 柱坐标
#include "BITCoordinateSystemSupport/Bit_CylinderCoordinate.h"
// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 2D曲线
#include "MathCalculationSupport/Bit_2DCurve.h"

class WARHEADDATABASE_API Bit_ShockWaveTestPointData
{
public:
	// 空函数
	Bit_ShockWaveTestPointData(void);
	// 初始化构造函数
	Bit_ShockWaveTestPointData( int TestPoint_Id , string Exp 
		, Bit_UnitSystem US , Bit_CylinderCoordinate Position_CC 
		, Bit_2DCurve Curve );
	// 拷贝构造函数
	Bit_ShockWaveTestPointData( const Bit_ShockWaveTestPointData& cSWTPD );
	// 重载等号
	Bit_ShockWaveTestPointData& operator= (const Bit_ShockWaveTestPointData& cSWTPD );
	// 重载“==”等号
	bool operator == (const Bit_ShockWaveTestPointData& cSWTPD )const;

	~Bit_ShockWaveTestPointData(void);

	// 设置所有初始值
	void Set_Initial( const int& TestPoint_Id , const string& Exp ,const Bit_UnitSystem& US
		, const Bit_CylinderCoordinate& Position_CC , const Bit_2DCurve& Curve );
	// 设置超压峰值
	inline void Set_OverPressure( const double& OverPressure );
	// 设置比冲量
	inline void Set_SpecificImpulse( const double& SpecificImpulse );

	// 得到是否定义
	inline bool Get_IfDefinition(void)const; 
	// 得到测试点ID
	inline int Get_TestPointId(void)const;
	// 得到测试点描述
	inline string Get_Explain(void)const;
	// 得到测试点坐标(圆柱坐标系)
	inline Bit_CylinderCoordinate Get_PositionCC(void)const;
	// 得到单位制
	inline Bit_UnitSystem Get_US(void)const;
	// 得到测试点曲线
	inline Bit_2DCurve Get_2DCurve(void)const;
	// 得到超压
	inline double Get_OverPressure(void)const;
	// 得到比冲量
	inline double Get_SpecificImpulse(void)const;

	// 根据曲线获得超压

	// 根据曲线获得比冲量

private:
	//测试点ID
	int TestPoint_Id_;
	//测试点描述
	string Exp_;
	//测试点位置
	Bit_CylinderCoordinate Position_CC_;
	//存储单位制度
	Bit_UnitSystem US_;
	//测试点曲线
	Bit_2DCurve Curve_;
	// 超压
	double OverPressure_;
	// 比冲量
	double SpecificImpulse_;
	// 是否定义
	bool IfDefinition_;
	// 超压手工输入定义
	bool InPutOP_;
	// 比冲量手工输入定义
	bool InPutSP_;
};

#endif

