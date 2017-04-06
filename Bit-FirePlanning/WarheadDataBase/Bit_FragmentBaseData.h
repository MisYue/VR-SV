//#pragma once
/********************************************************************
created:	2016/06/22
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	破片基本数据

*********************************************************************/

#ifndef BITFRAGMENTBASEDAtA_H__
#define BITFRAGMENTBASEDAtA_H__

// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 金属材料
#include "MaterialDataBase/Bit_MetalData.h"
// 战斗部数据动态库
#include "WarheadDataBase_Global.h"

class WARHEADDATABASE_API Bit_FragmentBaseData
{
public:
	//空函数
	Bit_FragmentBaseData(void);
	// 拷贝构造函数
	Bit_FragmentBaseData( const Bit_FragmentBaseData& cFBD );
	// 重载等号
	Bit_FragmentBaseData& operator= (const Bit_FragmentBaseData& cFBD );
	// 重载“==”等号
	bool operator == (const Bit_FragmentBaseData& cFBD )const;

	~Bit_FragmentBaseData(void);

	//参数初始化设置
	void Set_Initial( const Bit_UnitSystem& US , const int& FragmentShape 
		, const Bit_MetalData *FragMaterial , const double& VRCoefficient
		, const bool &USDefinition, const double & Mass );

private:
	//单位制
	Bit_UnitSystem US_;
	//破片形状
	int FragmentShape_;
	//（金属）破片材料
	Bit_MetalData *FragMaterial_;
	//破片的速度衰减(Velocity Reduction)系数
	double VRCoefficient_;
	//单位制定义
	bool USDefinition_;
	//破片质量
	double Mass_;
};
#endif
