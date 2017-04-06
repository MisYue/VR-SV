/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	面定义及相关计算函数

*********************************************************************/

#ifndef PLANE_H__
#define PLANE_H__

//定义坐标类
//#include "CoordinatesPosition.h"
//定义几何空间类
#include "SpaceGeometry.h"
//定义节点类
#include "Node.h"
//定义高等数据计算类
//#include "AdvancedMath.h"

//#pragma once
class MATHCALCULATIONSUPPORT_API Plane
{
public:
	// 构造空面
	Plane(void);
	// 构造初始化平面（1个节点）
	Plane( double Thickness , CoordinatesPosition Vec , Node NodeInSurface );
	// 构造初始化平面（1个坐标点）
	Plane( double Thickness , CoordinatesPosition Vec , CoordinatesPosition Point);
	// 三个坐标点构造一个平面
	Plane( double Thickness , CoordinatesPosition P1 , CoordinatesPosition P2, CoordinatesPosition P3 );
	// 大于三个节点构造一个平面
	Plane( double Thickness , int Node_Num , Node *N ); 

	// 拷贝构造函数
	Plane(const Plane &cPlane );
	// 重载构造函数“=”
	Plane &operator=( const Plane &cPlane  );
	// 重载构造函数“==”
	bool operator == (const Plane&cPlane )const;

	~Plane(void);

	//设置面中的厚度值
	inline void Set_Thickness(const double& Thickness );
	////设置面的法向量
	//inline void Set_NormalVector(const CoordinatesPosition& nV );
	//////设置面所包含的节点个数及节点(至少一个节点)
	//inline void Set_Node( const int& NodeNumber , const Node N[] );
	
	////得到面的厚度值
	inline double Get_Thickness()const;
	////得到面的法向量值
	inline CoordinatesPosition Get_NormalVector()const;
	//得到面所包含的节点
	inline void Get_Node( int * NodeNumber , Node N[] )const;

	// 面法向量与YZ面夹角(输出弧度值)，绕Y轴旋转用
	inline double AngleNormalVectorAndYZPlane( )const;
	// 面法向量与XZ面夹角(输出弧度值)，若Z轴旋转用
	inline double AngleNormalVectorAndXZPlane( )const;

private:
	// 面厚度
	double Thickness_; 
	// 面的法向量
	CoordinatesPosition Vec_;
	// 面所包含的节点个数（至少有一个）
	int Node_Num_;
	// 面所包含的节点
	Node *NodeInPlane_;
};
#endif
