/********************************************************************
created:	2016/04/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2维曲线定义数据结构

*********************************************************************/

#ifndef BIT2DCURVE_H__
#define BIT2DCURVE_H__

#include "MathCalculationSupport_Global.h"

class MATHCALCULATIONSUPPORT_API Bit_2DCurve
{
public:
	//空构造函数
	Bit_2DCurve(void);
	// 结构初始化
	Bit_2DCurve( int n , double *XArray , double *YArray );
	// 构造拷贝构造函数
	Bit_2DCurve(const Bit_2DCurve &c2DCurve );
	// 重载构造函数“=”  
	Bit_2DCurve& operator= (const Bit_2DCurve& c2DCurve );
	// 重载"=="恒等判断
	bool operator == (const Bit_2DCurve& c2DCurve )const;

	~Bit_2DCurve(void);

	//初始化设置
	void Set_Initial(const int& n , const double XArray[], const double YArray[] );

	//得到点个数
	inline int Get_PointNumber(void) const;
	//得到X数组
	void Get_XArray( double XArray[] ) const;
	//得到Y数组
	void Get_YArray( double YArray[] ) const;

private:
	//2维曲线上点的个数
	int Number_;
	//X数组
	double *XArray_;
	//Y数组
	double *YArray_;
};

#endif