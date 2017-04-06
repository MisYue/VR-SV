/********************************************************************
created:	2015/04/05
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	������ظ��ʷ������������

*********************************************************************/

//#pragma once

#ifndef PROBABILITYANDRANDOM_H__
#define PROBABILITYANDRANDOM_H__

#include "MathCalculationSupport_Global.h"
#include "CoordinatesPosition.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API ProbabilityAndRandom
{
public:
	ProbabilityAndRandom(void);
	~ProbabilityAndRandom(void);
	// �������������

	// number��������ķ�Χ��amount�������������randomNumber[]�����������
	bool GenerateRandom( const double& number , const int& amount  , double randomnumber[] )const;
	// ���������������������0-1��֮��������
	//int:��������>0�����������(0-1֮��������)��õ�ֵ���������
	bool SampleOnSampleNumber( const int& sn , double rn_aepa[])const;
	//�õ�1D��׼��̬�ֲ������
	double Get1DStandardNormalDistributionRandom( const int& r_num0_1 )const;

	// �õ�2D��׼��̬�ֲ�����cos��
	inline double Get2DStandardNormalDistributionRandom_cos( const double& r1 , const double& r2 )const;
	// �õ�2D��׼��̬�ֲ�����sin��
	inline double Get2DStandardNormalDistributionRandom_sin( const double& r1 , const double& r2 )const;

	// ����һ�����е�ƽ��
	double ComputeAverageValueInArray(const int& n, const double array[] )const ;
	// ����N�����еı�׼��
	double ComputeStandardDifference( const int& n , const double array[])const;

	// ��ö���ռ���ƽ��ֵ
	CoordinatesPosition GetExpectationOnMultiPoint( const int& n , const CoordinatesPosition point[] )const;
	
};

//}
#endif
