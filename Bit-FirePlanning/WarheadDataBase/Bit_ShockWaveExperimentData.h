/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�������������������ݵ����ݽṹ

*********************************************************************/

#ifndef BITSHOCKWAVEEXPERIMENTDATA_H__
#define BITSHOCKWAVEEXPERIMENTDATA_H__

// ս�������ݶ�̬��
#include "WarheadDataBase_Global.h"


#include "Bit_ShockWaveTestPointData.h"

class WARHEADDATABASE_API Bit_ShockWaveExperimentData
{
public:
	Bit_ShockWaveExperimentData(void);
	~Bit_ShockWaveExperimentData(void);

private:
	//�洢��λ�ƶ�
	Bit_UnitSystem US_;
	//ս����ID��(��������һֱ)
	int Warhead_Id_;
	//�����������
	string ExperimentDiscribe_; 
	//�𱬵㾭��
	double Detonate_Lon_;
	////�𱬵�γ��
	double Detonate_Lag_;
	////�𱬵�߶�
	double Detonate_Hig_;
	////����ľ���
	double PolarAxis_Lon_;
	////�����γ��
	double PolarAxis_Lag_;
	// ���Ե����
	int TestPoint_N_;
	// ������Ե�
	Bit_ShockWaveTestPointData *TestPointData_;
};
#endif
