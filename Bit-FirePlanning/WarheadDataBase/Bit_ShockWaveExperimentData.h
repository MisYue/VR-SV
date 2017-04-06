/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	冲击波试验测试试验数据的数据结构

*********************************************************************/

#ifndef BITSHOCKWAVEEXPERIMENTDATA_H__
#define BITSHOCKWAVEEXPERIMENTDATA_H__

// 战斗部数据动态库
#include "WarheadDataBase_Global.h"


#include "Bit_ShockWaveTestPointData.h"

class WARHEADDATABASE_API Bit_ShockWaveExperimentData
{
public:
	Bit_ShockWaveExperimentData(void);
	~Bit_ShockWaveExperimentData(void);

private:
	//存储单位制度
	Bit_UnitSystem US_;
	//战斗部ID号(与其余相一直)
	int Warhead_Id_;
	//试验放置描述
	string ExperimentDiscribe_; 
	//起爆点经度
	double Detonate_Lon_;
	////起爆点纬度
	double Detonate_Lag_;
	////起爆点高度
	double Detonate_Hig_;
	////极轴的经度
	double PolarAxis_Lon_;
	////极轴的纬度
	double PolarAxis_Lag_;
	// 测试点个数
	int TestPoint_N_;
	// 试验测试点
	Bit_ShockWaveTestPointData *TestPointData_;
};
#endif
