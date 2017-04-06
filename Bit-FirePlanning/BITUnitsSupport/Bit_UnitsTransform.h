/********************************************************************
created:	2015/04/05
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���е�λ��ת��

*********************************************************************/

//#pragma once

#ifndef BITUNITSTRANSFORM_H__
#define BITUNITSTRANSFORM_H__

#include "Bit_UnitsSupport_Global.h"

//namespace BIT
//{
class BITUNITSSUPPORT_API Bit_UnitsTransform
{
public:
	Bit_UnitsTransform(void);
	~Bit_UnitsTransform(void);

	//******ѹ����λ��ת��**********
	// 1�ͣ�bar��=10^5����Pa�� 
	inline double BarToPa( const double& bar) const ;
	// 1��(Pa) = 10^-5��(bar)
	inline double PaToBar( const double& pa) const ;
	// 1Psi = 0.00689Mpa
	inline double PsiToMPa( const double& psi) const;
	// 1MPa = 145.03725(Psi = ����/Ӣ��2)
	inline double MpaToPsi( const double& mpa) const;

	//******������λ��ת��**********
	// 1��(lb)=0.4536ǧ��(kg)
	inline double BlToKg(const double& bl)const;
	// 1ǧ��(Kg)=2.2046��(Bl)
	inline double KgToBl(const double& kg)const;
	// ��(g)=10^-3ǧ��(kg)
	inline double GToKg( const double& g )const;
	// 1ǧ��(kg) = 10^3��(g)
	inline double KgToG( const double& kg )const;

	//*******���ȵ�λ��ת��*********
	//1��(Mi)=1e-3ǧ��(Km)
	inline double MiToKm( const double& mi)const;
	// 1��(M)=39.37Ӣ��(in)
	inline double MiToIn( const double& mi)const;
	// 1Ӣ��(in)=0.0254��(M)
	inline double InToMi( const double& in)const;
	// 1��(M)=3.2808Ӣ��(Ft)
	inline double MiToFt( const double& mi)const;
	// 1Ӣ��(Ft)=0.3048��(M)
	inline double FtToMi( const double& ft)const;
	// 1��(m) = 1000����(mm)
	inline double MiToMm( const double& mi )const;
	// 1����(mm) = 1e-6ǧ��(km)
	inline double MmToKm( const double& mm )const;
	// 1����(mm) = 0.001��(m)
	inline double MmToMi( const double& mm )const;
	// 1����(mm) = 0.1����(cm)
	inline double MmToCm( const double& mm )const;
	// 1����(mm) = 0.01����(dm)
	inline double MmToDm( const double& mm )const;
	// 1����(cm) = 10����(mm)
	inline double CmToMm( const double& cm )const;
	// 1����(cm) = 0.1����(dm)
	inline double CmToDm( const double& cm )const ;
	// 1����(cm) = 0.01��(m)
	inline double CmToMi( const double& cm )const;
	// 1����(cm) = 1e-5ǧ��(Km)
	inline double CmToKm( const double& cm )const;
	// 1ǧ��(Km) = 1e3��(m)
	inline double KmToMi( const double& km )const;
	// 1ǧ��(Km) = 1e4����(dm)
	inline double KmToDm( const double& km )const;
	// 1ǧ��(Km) = 1e5����(cm)
	inline double KmToCm( const double& km )const;
	// 1ǧ��(Km) = 1e6����(mm)
	inline double KmToMm( const double& km )const;

	//*******�����λ��ת��*********
	//1��������(cm^3) = 10^3��������(mm^3)
	inline double CubeCmToCubeMm( const double& cubecm)const ;
	//1��������(mm^3) = = 10^-3��������(cm^3)
	inline double CubeMmToCubeCm( const double& cubemm)const ;
	//1�����ף�m^3�� = 10^9��������(mm^3)	
	inline double CubeMiToCubeMm( const double& cubemi)const ;
	//1��������(mm^3) = 10^-9������(m^3)
	inline double CubeMmToCubeMi( const double& cubemm)const ;

	//*******�ܶȵ�λת��***********
	// 1g/cm^3=1000 kg/m^3
	inline double GCubeCmToKgCubeMi( const double& gcc )const ;
	// 1g/mm^3=1000g/cm^3 
	inline double GCubeMmToGCubeCm( const double& gcm )const ;

	//*******�Ƕȵ�λת��***********
	//�ȷ���ת��С��
	inline double DMSUnitToDecimal(const double& Degree , const double& Minute , const double& Second)const;
	// �Ƕ�ת����
	inline double AngleToRadian(const double& angle) const;
	// ����ת�Ƕ�
	inline double RadianToAngle(const double& radian) const;

	//*******ʱ�䵥λת��***********
	// 1us=10^-6s
	inline double UsToS( const double& us )const ;
	// 1ms=10^-3s
	inline double MsToS( const double& ms )const ;
	// 1s =10^6us
	inline double SToUs( const double& s )const ;
	// 1s =10^3ms
	inline double SToMs( const double& s )const ;

	//*******������λ��ת��*********
	// kg-m-s��λ��ת����g-mm-us��λ��
	inline double EnergyKgMiSToGMmUs( const double &KgMiS)const;
	// g-mm-us��λ��ת����kg-m-s��λ��
	inline double EnergyGMmUsToKgMiS( const double &GMmUs)const;

	//*****�ԱȾ��뵥λ��ת��********
	// kg-m-s��λ��ת����g-mm-us��λ�ƶ�
	inline double ContrastDisKgMiSToGMmUs( const double &KgMiS)const;
};
//}


#endif