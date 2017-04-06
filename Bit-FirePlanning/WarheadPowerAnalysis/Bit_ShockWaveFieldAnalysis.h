/*#pragma once*/
/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���г����������
include:    �뱬������һ��ĳ������ѹ������ʱ�䡢�ȳ����Լ�����ѹ���ȼ���
*********************************************************************/

#ifndef BITSHOCKWAVEFIELDANALYSIS_H__
#define BITSHOCKWAVEFIELDANALYSIS_H__
// ��̬�⵼��
#include "WarheadPowerAnalysis_Global.h"

// ��λ��
//#include "BITUnitsSupport\Bit_UnitSystem.h"
//�ߵ����ݼ���
#include "MathCalculationSupport\AdvancedMath.h"

//ս���������������ݽṹ
#include "WarheadDataBase\WarheadPowerAnalysisData.h"
//װҩ���ݽṹ
#include "MaterialDataBase\ChargeData.h"

class WARHEADPOWERANALYSIS_API Bit_ShockWaveFieldAnalysis
{
public:
	Bit_ShockWaveFieldAnalysis(void);

	//// �ṹ���ʼ��
	Bit_ShockWaveFieldAnalysis( Bit_UnitSystem US );

	~Bit_ShockWaveFieldAnalysis(void);

	////////********������λ�ƵĻ�������ʽ***************////
	// ����װҩ�ĶԱȾ���(������λ�Ƽ���)
	double ComputeContrastDistance( const double& ChargeMass_kg, const double& Distance_m )const;
	// (���ڶԱȾ���)����������ѹ��ֵ(������λ��)
	double ComputeShockWavePressureOnCDis(const double& aa, const double& bb, const double& cc
		, const double& dd, const double &ConDis_Min , const double &ConDis_Max ,const double& ContrastDistance)const;
	// (����װҩ�����;���)����������ѹ��ֵ(������λ�Ƽ���)
	inline double ComputeShockWavePressureOnDis(const double& aa, const double& bb, const double& cc , const double& dd
		, const double &ConDis_Min , const double &ConDis_Max ,const double& ChargeMass_kg
		, const double& Distance_m , double *ContrastDistance )const;
	// ���������䳬ѹ(������λ�Ƽ��㣬����������λ��һ��) 
	inline double ComputeVerticalReflectionPressure( const double& IncomingOverPressure , 
		const double& AirPressure )const;
	// ��������б���䳬ѹ(������λ�Ƽ��㣬����������λ��һ��)
	double ComputeRegularObliqueReflectionPressure( const double& AirPressure
		, const double& IncomingAngle_R , const double& IncomingPressure
		, const double& kk_AirIsentropicIndex )const ;

	// ������շ��䳬ѹ(������λ�Ƽ��㣬����������λ��һ��)
	inline double ComputeMachReflectionPressure( const double& IncomingOverPressure, 
		const double& IncomingAngle_R )const;

	// ��շ����ٽ�Ƕȼ���(������λ�Ƽ���)
	double ComputeMachReCriticalAngle( const double &ChargeMass_kg 
		, const double &ExplosionH_m)const;

	//������ѹ������ʱ��

	//��ѹ������ѹ����ʱ��ı仯

	////////********����λ�ƵĻ�������ʽ***************////
	// ����װҩ�ĶԱȾ���(����λ�Ƽ���)
	double ComputeContrastDistance_US( const Bit_UnitSystem& US , const double& ChargeMass 
		, const double& Distance ,double *ContrastDistance_IUS )const;
	
	////////********�����ݽṹ�Ļ�������ʽ***************////
	// ����װҩ�ĶԱȾ���(����λ�ơ���װҩ�ṹ)
	double ComputeConstrastDistance_Data( const Bit_UnitSystem& US , const double& Distance 
		, const WarheadPowerAnalysisData &WarheadData , double *ContrastDistance_IUS , double *ContrastDistance_WarUS )const;

private:
	// ��λϵ
	Bit_UnitSystem US_;
	// ��λϵ�Ƿ���
	bool IfUS_;
};

#endif

