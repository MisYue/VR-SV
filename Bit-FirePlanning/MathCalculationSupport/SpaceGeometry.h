/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	进行空间几何相关计算

*********************************************************************/

//#pragma once
#include "MathCalculationSupport_Global.h"
////坐标类
//#include "CoordinatesPosition.h"
////节点类
#include "Node.h"
////高等数学类
#include "AdvancedMath.h"
//
//#include "Surface.h"

#ifndef SPACEGEOMETRY_H__
#define SPACEGEOMETRY_H__
//#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API SpaceGeometry
{
public:
	SpaceGeometry(void);
	~SpaceGeometry(void);

	//************空间二维线段计算***************
	//1.基于两条线的方向计算空间内两条线的锐角夹角，输出弧度
	double AcuteAngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	// 基于两条线的方向计算空间内两条线的夹角，输出弧度
    double AngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	//基于两个方向向量计算锐角夹角，输出弧度
	inline double AcuteAngleInTwoVetor( const CoordinatesPosition &V1 , const CoordinatesPosition &V2) const;
    //基于两个方向向量计算夹角，输出弧度
	inline double AngleInTwoVetor( const CoordinatesPosition &V1 , const CoordinatesPosition &V2) const;

	//2.判断一条线上的三个点中一个点是否在两个点之间
	bool JudgePointSiteBetweenTwoPoint( const CoordinatesPosition& JudgePoint ,
		const CoordinatesPosition& FristPoint, const CoordinatesPosition& SecondPoint) const;

	// 判断空间两条直线是否相交
	bool JudgeIfIntereFor2Lines( const CoordinatesPosition &Ponint_one ,const CoordinatesPosition &Ponint_two
		, const CoordinatesPosition &Vector_one , const CoordinatesPosition &Vector_two )const;

	//3.计算空间两条直线的交点（直线以一个点和直线向量的方式给出）
	bool  ComputeIntersectionPointToTwoLine(const CoordinatesPosition &Ponint_one 
		,const CoordinatesPosition &Ponint_two, const CoordinatesPosition &Vector_one 
		, const CoordinatesPosition &Vector_two , CoordinatesPosition *InterePoint ) const;
	//4.由空间内1个点、参数方程方向数和截距计算另一点
	CoordinatesPosition GetAnotherPoint(const CoordinatesPosition& p1  
		, const double& aa , const double &bb , const double& cc , const double& dis) const;
	//5.判断三个点是否在一条直线上
	bool JudgeIfLineFor3Points( const CoordinatesPosition &P1 , const CoordinatesPosition &P2 , const CoordinatesPosition &P3 ) const;
	// 判断一个点在一个三角形内
	bool JudgeIfPointInTriangle( const CoordinatesPosition &JP , const CoordinatesPosition &P1 
		, const CoordinatesPosition &P2 , const CoordinatesPosition &P3  )const;
	// 判断四个点组成的四变形是否是凸四边形
	bool JudgeIfConvexQuadOn4Points( const CoordinatesPosition P[4] )const;
	
	// 判断4个点中是否有3个点共线的(数组输入)
	bool JudgeIf3PointsIn1LineFor4Points( const CoordinatesPosition P[4])const;
	// 判断4个点中是否有3个点共线的(4点输入)
	bool JudgeIf3PointsIn1LineFor4Points( const CoordinatesPosition& P0 ,const CoordinatesPosition& P1
		, const CoordinatesPosition& P2 ,const CoordinatesPosition& P3)const;

	//***********************空间向量计算***************
	// 向量单位化计算
	inline CoordinatesPosition VectorStandardization( const CoordinatesPosition &V )const;
	//6.计算两个向量的叉乘
	inline CoordinatesPosition ComputeCrossProducts( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;
	//7. 计算两个个向量的点乘
	inline double ComputeDotProducts( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;
	//根据两个向量计算法向量，返回法向量
	inline CoordinatesPosition NormalVectorOn2Vectors( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;

	//8.通过三个点计算平面的法向量VV，返回法向量
	CoordinatesPosition NormalVectorOn3points( const CoordinatesPosition &P1 , const CoordinatesPosition &P2 , const CoordinatesPosition &P3 ) const;
	//9. 通过大于三个点算平面的法向量VV，返回法向量
	CoordinatesPosition NormalVectorOnNpoints( int &n , const CoordinatesPosition Num[] )const;
	//10.判断空间四点是否共面，共面返回true，不共面返回flase
	bool JudgeIfCoplanarityFor4Points( const CoordinatesPosition& P1 , const CoordinatesPosition& P2
		, const CoordinatesPosition& P3 , const CoordinatesPosition& P4)const;
    //11. 判断大于等于3个点是否共面，共面返回true，不共面返回flase
    bool JudgeIfCoplanarityForNPoints( const int& n , const CoordinatesPosition Num[] )const;
	//12. 判断3个及以上节点（Node）是否在一个平面上（n<3退出程序）
	bool JudgeIfCoplanarityForNNodes( const int& n , const Node Nu[] )const;
	
	//******************几何结构体积计算*******************
	//13.计算圆台的体积（基于几何坐标量）
	//R：大圆半径、r：小圆半径，H：高
	inline double ComputeFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//14.计算半圆台的体积（基于几何坐标量）
	//R：大圆半径、r：小圆半径，H：高
	inline double ComputeHalfFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//15.计算圆柱体的体积（基于几何坐标量）
	//Diameter：圆直径、Height：高
	inline double ComputeCylinderVolume( const double& Diameter , const double& Height ) const;
	//16.计算半圆柱体的体积（基于几何坐标量）
	//Diameter：圆直径、Height：高
	inline double ComputeHalfCylinderVolume( const double& Diameter , const double& Height ) const;
	//17.计算圆锥体的体积（基于几何坐标量）
	//Radius：底圆半径、Height：高
	inline double ComputeConeVolume( const double& Radius , const double& Height ) const;
	//18.计算半圆锥体的体积（基于几何坐标量）
	//Radius：底圆半径、Height：高
	inline double ComputeHalfConeVolume( const double& Radius , const double& Height )const;
	//19.计算球形体积（基于几何坐标量）
	inline double ComputeSphereVolume( const double& Diameter )const;
	//20.计算长方体的体积（基于几何坐标量）
	inline double ComputeCuboidVolume( const double& XLength , const double& YLength , const double& ZLength )const;

	///******************由物理量求计算*******************
	//21.计算体积(基于质量和密度)
	//Mass：质量，g；Density：密度，g/cm^3
	inline double ComputeVolumeOnMassAndDensity( const double& Mass , const double& Density )const;

	//******************由体积计算几何物理量*******************
	//22.由球体积计算球半径
	inline double ComputeSphereRadiusOnVolume( const double& Volume )const;

};
#endif
//}

