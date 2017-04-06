/********************************************************************
created:	2016/6/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行弹体坐标系上的破片场分析
include:	
*********************************************************************/

#ifndef BITFRAGMENTFIELDPCSANALYSIS_H__
#define BITFRAGMENTFIELDPCSANALYSIS_H__
// 动态库导出
#include "WarheadPowerAnalysis_Global.h"
// 破片数据库
#include "WarheadDataBase/Bit_SFragVPData_P.h"

class WARHEADPOWERANALYSIS_API Bit_FragmentFieldPCSAnalysis
{
public:
	Bit_FragmentFieldPCSAnalysis(void);
	~Bit_FragmentFieldPCSAnalysis(void);
	
	// 设置所有初始值（开辟n个破片数据的存储空间）
	void Set_Initial( const int& Number_Frg );
	
	// 设置第i（<N）个破片的初速
	void Set_SFInitV( const int& Number , const double& SFInitV);

	// 得到第i（<N）个破片的速度
	inline double Get_SFInitV(const int& Number)const;

private:
	// 破片数目
	int Number_Frg_;
	Bit_SFragVPData_P *SFD_;
	// 是否进行了初始化设置
	bool IfInitialFinished_;

};
#endif
