/********************************************************************
created:	2015/04/05
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行单位的转换

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

	//******压力单位制转换**********
	// 1巴（bar）=10^5帕（Pa） 
	inline double BarToPa( const double& bar) const ;
	// 1帕(Pa) = 10^-5巴(bar)
	inline double PaToBar( const double& pa) const ;
	// 1Psi = 0.00689Mpa
	inline double PsiToMPa( const double& psi) const;
	// 1MPa = 145.03725(Psi = 磅力/英寸2)
	inline double MpaToPsi( const double& mpa) const;

	//******质量单位制转换**********
	// 1磅(lb)=0.4536千克(kg)
	inline double BlToKg(const double& bl)const;
	// 1千克(Kg)=2.2046磅(Bl)
	inline double KgToBl(const double& kg)const;
	// 克(g)=10^-3千克(kg)
	inline double GToKg( const double& g )const;
	// 1千克(kg) = 10^3克(g)
	inline double KgToG( const double& kg )const;

	//*******长度单位制转换*********
	//1米(Mi)=1e-3千米(Km)
	inline double MiToKm( const double& mi)const;
	// 1米(M)=39.37英寸(in)
	inline double MiToIn( const double& mi)const;
	// 1英寸(in)=0.0254米(M)
	inline double InToMi( const double& in)const;
	// 1米(M)=3.2808英尺(Ft)
	inline double MiToFt( const double& mi)const;
	// 1英尺(Ft)=0.3048米(M)
	inline double FtToMi( const double& ft)const;
	// 1米(m) = 1000毫米(mm)
	inline double MiToMm( const double& mi )const;
	// 1毫米(mm) = 1e-6千米(km)
	inline double MmToKm( const double& mm )const;
	// 1毫米(mm) = 0.001米(m)
	inline double MmToMi( const double& mm )const;
	// 1毫米(mm) = 0.1厘米(cm)
	inline double MmToCm( const double& mm )const;
	// 1毫米(mm) = 0.01分米(dm)
	inline double MmToDm( const double& mm )const;
	// 1厘米(cm) = 10毫米(mm)
	inline double CmToMm( const double& cm )const;
	// 1厘米(cm) = 0.1分米(dm)
	inline double CmToDm( const double& cm )const ;
	// 1厘米(cm) = 0.01米(m)
	inline double CmToMi( const double& cm )const;
	// 1厘米(cm) = 1e-5千米(Km)
	inline double CmToKm( const double& cm )const;
	// 1千米(Km) = 1e3米(m)
	inline double KmToMi( const double& km )const;
	// 1千米(Km) = 1e4分米(dm)
	inline double KmToDm( const double& km )const;
	// 1千米(Km) = 1e5厘米(cm)
	inline double KmToCm( const double& km )const;
	// 1千米(Km) = 1e6豪米(mm)
	inline double KmToMm( const double& km )const;

	//*******体积单位制转换*********
	//1立方厘米(cm^3) = 10^3立方毫米(mm^3)
	inline double CubeCmToCubeMm( const double& cubecm)const ;
	//1立方毫米(mm^3) = = 10^-3立方厘米(cm^3)
	inline double CubeMmToCubeCm( const double& cubemm)const ;
	//1立方米（m^3） = 10^9立方毫米(mm^3)	
	inline double CubeMiToCubeMm( const double& cubemi)const ;
	//1立方毫米(mm^3) = 10^-9立方米(m^3)
	inline double CubeMmToCubeMi( const double& cubemm)const ;

	//*******密度单位转换***********
	// 1g/cm^3=1000 kg/m^3
	inline double GCubeCmToKgCubeMi( const double& gcc )const ;
	// 1g/mm^3=1000g/cm^3 
	inline double GCubeMmToGCubeCm( const double& gcm )const ;

	//*******角度单位转换***********
	//度分秒转成小数
	inline double DMSUnitToDecimal(const double& Degree , const double& Minute , const double& Second)const;
	// 角度转弧度
	inline double AngleToRadian(const double& angle) const;
	// 弧度转角度
	inline double RadianToAngle(const double& radian) const;

	//*******时间单位转换***********
	// 1us=10^-6s
	inline double UsToS( const double& us )const ;
	// 1ms=10^-3s
	inline double MsToS( const double& ms )const ;
	// 1s =10^6us
	inline double SToUs( const double& s )const ;
	// 1s =10^3ms
	inline double SToMs( const double& s )const ;

	//*******能量单位制转换*********
	// kg-m-s单位制转换成g-mm-us单位制
	inline double EnergyKgMiSToGMmUs( const double &KgMiS)const;
	// g-mm-us单位制转换成kg-m-s单位制
	inline double EnergyGMmUsToKgMiS( const double &GMmUs)const;

	//*****对比距离单位制转换********
	// kg-m-s单位制转换成g-mm-us单位制度
	inline double ContrastDisKgMiSToGMmUs( const double &KgMiS)const;
};
//}


#endif