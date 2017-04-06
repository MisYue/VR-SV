/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	坐标定义及转换函数

*********************************************************************/

#ifndef COORDINATESPOSITION_H__
#define COORDINATESPOSITION_H__

#include "MathCalculationSupport/MathCalculationSupport_Global.h"

// 坐标点函数
//#include <iostream>
//#include <math.h>
//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API CoordinatesPosition
{
public:
	// 构造空的坐标
	CoordinatesPosition(void);
	// 构造初始值坐标
	CoordinatesPosition( double x, double y, double z );
	// 构造拷贝构造函数
	CoordinatesPosition( const CoordinatesPosition& cPositon);

	// 重载等号
	CoordinatesPosition& operator= (const CoordinatesPosition& cPositon );
	// 重载减号
	CoordinatesPosition operator- (const CoordinatesPosition& cPositon )const;
	// 重载加号
	CoordinatesPosition operator+ (const CoordinatesPosition& cPositon )const;
	// 重载（点）乘号，每个数相乘
	CoordinatesPosition operator* (const CoordinatesPosition& cPositon )const;

	// 重载恒等判断
	bool operator == (const CoordinatesPosition& cPositon )const;

	~CoordinatesPosition(void);

	// 角度转弧度
	inline double AngleToRadian(const double& angle) const;
	// 弧度转角度
	inline double RadianToAngle(const double& radian) const;

	//设置x值
	inline void Set_x(const double& xx );
	//设置y值
	inline void Set_y(const double& yy );
	//设置z值
	inline void Set_z(const double& zz );

	// 得到点中的x值
	inline double Get_x(void) const ;
	// 得到点中的y值
	inline double Get_y(void) const ;
	// 得到点中的z值
	inline double Get_z(void) const ;

	// 计算两点坐标间的距离
	inline double Distance(const CoordinatesPosition& p2) const;
	// 计算到原点的距离
	inline double DistanceOriginPosition(void) const;
	// 点距离XZ平面的夹角（输出为弧度）
	inline double AngleWithXZPlane(void) const;
	// 点距离XY平面的夹角（输出为弧度）
	inline double AngleWithXYPlane(void) const;
	// 点距离YZ平面的夹角（输出为弧度）
	inline double AngleWithYZPlane(void) const;
	// 点-原点连线与X轴的夹角（输出为弧度）
	inline double AngleWithXAxis(void) const;
	// 点-原点连线与Y轴的夹角（输出为弧度）
	inline double AngleWithYAxis(void) const;
	// 点-原点连线与Z轴的夹角（输出为弧度）
	inline double AngleWithZAxis(void) const;
	// 三维坐标轴平移
	inline void CoordinatesAfterTranslation(const double& dx, const double& dy, const double& dz);
	// 三维坐标绕X轴旋转（输入为角度值）
	void RotateAngleByXAxis(const double& angle );
	// 三维坐标绕Y轴旋转（输入为角度值）
	void RotateAngleByYAxis(const  double& angle );
	// 三维坐标绕Z轴旋转（输入为角度值）
	void RotateAngleByZAxis(const  double& angle );
	// 三维坐标绕X轴旋转（输入为弧度值）
	void RotateRadianByXAxis(const double& radian );
	// 三维坐标绕Y轴旋转（输入为弧度值）
	void RotateRadianByYAxis(const  double& radian );
	// 三维坐标绕Z轴旋转（输入为弧度值）
	void RotateRadianByZAxis(const  double& radian );
	//求空间内两点连线与X轴夹角
	double IncludedAngleOfXAxis(const CoordinatesPosition& p2) const;
	//求空间内两点连线与Y轴夹角
	double IncludedAngleOfYAxis(const CoordinatesPosition& p2) const;
	//求空间内连线与Z轴夹角
	double IncludedAngleOfZAxis(const CoordinatesPosition& p2) const;

	//根据地球上两个点的经度和纬度计算两点之间的距离；
	double DistanceFromLongitudeAndLatitude( const double &lon_a , const double &lat_a ,
		const double &lon_b , const double &lat_b ) const;

	//根据A、B两个点的经度和纬度计算B点相对A点的方位角度；
	double AzimuthFromLongitudeAndLatitude( const double &longaixs , const double &shortaixs ,
		 const double &lon_a , const double &lat_a , const double &lon_b , const double &lat_b )const ;


	////************坐标相互转换函数***********************
	//


	//弹体坐标系向(静止)目标坐标系转换函数
	//A_PitchingAngle：导弹俯仰角（静止目标/大地坐标系），度
	//A_YawAngle：导弹偏航角（静止目标/大地坐标系），
	//CoordinateInAmmunition：在弹体坐标中的点
	//WarheadCenterPosition：战斗部中心在目标坐标系中的坐标值
	CoordinatesPosition ComputeCoordinateInTargetFromAmmunition( 
		const double &A_PitchingAngle , const double &A_YawAngle, 
		const CoordinatesPosition &CoordinateInAmmunition ,
		const CoordinatesPosition &WarheadCenterPosition ) const;

private:
	double x_;
	double y_;
	double z_;
};
//}

#endif