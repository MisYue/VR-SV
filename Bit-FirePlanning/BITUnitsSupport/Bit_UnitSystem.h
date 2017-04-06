/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��λϵ���弰��ؼ��㺯��

*********************************************************************/
// #pragma once

#ifndef BITUNITSYSTEM_H__
#define BITUNITSYSTEM_H__

#include "BITUnitsSupport/Bit_UnitsTransform.h"
#include "MathCalculationSupport\CoordinatesPosition.h"

class BITUNITSSUPPORT_API Bit_UnitSystem
{
public:
	//����յ�λ��
	Bit_UnitSystem(void);
	// �����ʼ����λ�ƣ�ȷ��������λѡ��
	Bit_UnitSystem( int Length , int Mass , int Time );
	// �����ʼ����λ�ƣ�int �����ͣ�
	Bit_UnitSystem( int Units[3]);

	// �������캯��
	Bit_UnitSystem( const Bit_UnitSystem &cUS );
	// ����"="�Ⱥ�
	Bit_UnitSystem& operator= (const Bit_UnitSystem& cUS );
	// ����"=="����ж�
	bool operator == (const Bit_UnitSystem& cUS )const;
	// ����"!="����ж�
	bool operator != (const Bit_UnitSystem& cUS )const;

	~Bit_UnitSystem(void);

	// 1.�õ����ȵ�λ
	int Get_LengthUnit(void)const;
	// 2.�õ�������λ
	int Get_MassUnit(void)const;
	// 3.�õ�ʱ�䵥λ
	int Get_TimeUnit(void)const;
	// 4.�õ�����ϵ��
	inline double Get_LengthCoefficient(void)const;
	// 5.�õ�����ϵ��
	inline double Get_MassCoefficient(void)const;
	// 6.�õ�ʱ��ϵ��
	inline double Get_TimeCoefficient(void)const;
	// 7.�õ��ܶ�ϵ��
	inline double Get_DensityCoefficient(void)const;
	// 8.�õ���ϵ��
	inline double Get_ForceCoefficient(void)const;
	// 9.�õ�ѹǿϵ��
	inline double Get_PressureCoefficient(void)const;
	// 10.�õ�����ϵ��
	inline double Get_EnergyCoefficient(void)const;
	// 11.�õ��ٶ�ϵ��
	inline double Get_VelocityCoefficient(void)const;
	// 12.�õ����ϵ��
	inline double Get_AreaCoefficient(void)const;
	// 13�õ����ϵ��
	inline double Get_VolumCoefficient(void)const;
	// 14.�õ��ԱȾ���ϵ��
	inline double Get_ContrastDisCoefficient(void)const;
	// 15.�õ�Ӧ����ϵ��
	inline double Get_StrainRateCoefficient(void)const;
	// 16.�õ��������ȵ�λ�µ�����ֵ
	inline CoordinatesPosition Get_CoordinateValueOnBaseU( const CoordinatesPosition &InputCoord)const;
	// 17.�ɻ������ȵ�λ�µ�����ֵ�õ���ǰ���굥λ�µ�����ֵ
	inline CoordinatesPosition Get_CoordinateValueOnBaseN( const CoordinatesPosition &InputCoord)const;
	// 18.�õ��ٶ�˥��ϵ��
	inline double Get_VRCCoefficient(void)const;

private:
	// ����ϵ��
	double LengthCoefficient_;
	// ����ϵ��
	double MassCoefficient_;
	// ʱ��ϵ��
	double TimeCoefficient_;
};
#endif
