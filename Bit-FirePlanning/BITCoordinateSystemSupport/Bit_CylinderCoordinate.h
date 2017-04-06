/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	圆柱坐标系的坐标点

*********************************************************************/
#ifndef BITCYLINDERCOORDINATE_H__
#define BITCYLINDERCOORDINATE_H__

// 动态库导出
#include "BITCoordinateSystemSupport_Global.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CylinderCoordinate
{
public:
	Bit_CylinderCoordinate(void);
	// 初始化构造函数
	Bit_CylinderCoordinate( double Radius, double AngleR, double z );
	// 拷贝构造函数
	Bit_CylinderCoordinate( const Bit_CylinderCoordinate& cCCPositon);

	// 重载等号
	Bit_CylinderCoordinate& operator= (const Bit_CylinderCoordinate& cCCPositon );
	// 重载减号
	Bit_CylinderCoordinate operator- (const Bit_CylinderCoordinate& cCCPositon )const;
	// 重载加号
	Bit_CylinderCoordinate operator+ (const Bit_CylinderCoordinate& cCCPositon )const;
	// 重载恒等判断
	bool operator == (const Bit_CylinderCoordinate& cCCPositon )const;

	~Bit_CylinderCoordinate(void);

	// 角度转弧度
	inline double AngleToRadian(const double& angle) const;
	// 弧度转角度
	inline double RadianToAngle(const double& radian) const;
	
	//设置所有参数
	inline void Set_Initial( const double& Radius , const double& AngleR ,const double& z);

	//设置径向距离值
	inline void Set_Radius(const double& Radius );
	//设置角度(弧度)值
	inline void Set_AngleR(const double& AngleR );
	//设置高度z值
	inline void Set_z(const double& z );

	// 得到点中的径向距离值
	inline double Get_Radius(void) const ;
	// 得到点中的角度(弧度)值
	inline double Get_AngleR(void) const ;
	// 得到点中的z值
	inline double Get_z(void) const;

private:
	double Radius_;
	double AngleR_;
	double z_;
};

#endif

