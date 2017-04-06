/********************************************************************
created:	2016/01/26
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��Ŀ�����ײ�������

*********************************************************************/


// #pragma once

#ifndef HAE_HITPOINTANALYSIS_H__
#define HAE_HITPOINTANALYSIS_H__

#include "HitAndExplsionPointAnalysis_Global.h"

// ����ͷ�ļ����ߵ���ѧ���㣩
#include "MathCalculationSupport\AdvancedMath.h"
// ����ͷ�ļ����ռ伸�Σ�
#include "MathCalculationSupport\CoordinatesPosition.h"


class HITANDEXPLSIONPOINTANALYSIS_API HAE_HitPointAnalysis
{

public:
	HAE_HitPointAnalysis(void);
	~HAE_HitPointAnalysis(void);

	//**************���ݵ�����������ٺ����*******************//
	
	//���ݴ��(����)����ϵ��������Ŀ�����ĵ�ľ�γ��ֵ�������
	double ComputeFallAngleOnLoLA_Table( const double& Start_Lo , const double& Start_La , const double& End_Lo
		, const double& End_La , const int&n ,  const double FirDistance[] , const double FallAngle[] )const ;

	//���ݴ��(����)����ϵ��������Ŀ�����ĵ�ľ�γ��ֵ��������



	//������̲�����Բ�ֵ������Ǻ�����
	void ComputeFallAngleAndVelocityOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] , const double FallAngle[] 
	    , const double FallVelocity[] , double *Fall_Angle , double *Fall_Velocity )const;
	//������̲�����Բ�ֵ�������
	double ComputeFallAngleOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] 
	    , const double FallAngle[] )const ;
	//������̲�����Բ�ֵ��������
	double ComputeFallVelocityOnDistance_Table( const double& Fire_Distance , const int&n ,  const double FirDistance[] 
		, const double FallVelocity[])const ;

	//***************���ݻ������ʱ��������Ŀ����淽λ�ǣ��������ϵ������Ŀ������ϵ�е�ҩ���Ŀ��ķ�λ��

	//*********���ݵ�ҩ���Ŀ��ķ�λ�Ǻ͸ߵͽǼ���ĩ�˵���
	//�����Ƶ�ƽ���ϵ���׼�㣨����Ŀ������ϵ�µ���׼�㡢��ҩ���Ŀ��ķ�λ��(��)�͸ߵͽ�(��)��Z�����ϵģ�X��ָ��Ŀ��ǰ����
	CoordinatesPosition ComputeAimPositionOnGuide( const CoordinatesPosition& AmmunitionAimPoint_Tar ,
		const double&AmmunitionYawAngle_Tar , const double&AmmunitionPitchingAngle_Tar )const;

};
#endif

