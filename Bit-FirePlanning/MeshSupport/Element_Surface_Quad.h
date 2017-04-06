//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	四边形面单元及相关计算

*********************************************************************/

#ifndef ELEMENT_SURFACE_QUAD_H__
#define ELEMENT_SURFACE_QUAD_H__

#include "MeshSupport_Global.h"
// 面定义
#include "MathCalculationSupport/Plane.h"

#include "MathCalculationSupport/Line.h"

class MESHSUPPORT_API Element_Surface_Quad
{
public:
	// 构造空函数
	Element_Surface_Quad(void);
	// 构造初始化单元
	Element_Surface_Quad( int Id , int PartId , Node N[4] , double Thickness );
	// 拷贝构造函数
	Element_Surface_Quad( const Element_Surface_Quad& cElement_Quad);
	// 重载“=”
	Element_Surface_Quad& operator= (const Element_Surface_Quad& cElement_Quad );
	// 重载“==”
	bool operator == (const Element_Surface_Quad& cElement_Quad )const;
	// 析构函数
	~Element_Surface_Quad(void);
	
	//***************设置四变形单元结构中的私有变量**************
	//设置Id值
	inline void Set_Id(const int& Id );
	//设置PartId值
	inline void Set_PartId(const int& PartId );
	//设置单元厚度
	inline void Set_Thickness(const int& Thickness );
	//设置四个节点的数组(只能通过初始进行设置)
	/*inline void Set_Node( const Node N[4] );*/

	//***************得到四变形单元结构中的私有变量**************
	//得到Id
	inline int Get_id( void ) const;
	//得到PartId值
	inline int Get_Partid( void ) const;
	//得到单元厚度
	inline double Get_Thickness( void ) const;
	//得到4个节点
	void Get_Node( Node N[4] )const;
	//得到N[0],第1个节点
	inline Node Get_Node_0( void )const; 
	//得到N[1],第2个节点
	inline Node Get_Node_1( void )const; 
	//得到N[2],第3个节点
	inline Node Get_Node_2( void )const; 
	//得到N[3],第4个节点
	inline Node Get_Node_3( void )const; 
	//得到是否构造成
	inline bool Get_IfPorduct(void)const;

	//得到标准法向量(按前3点计算)
	inline CoordinatesPosition Get_StandardizationVector(void)const;

	//得到单元标准平面方程系数A(基于点0)
	inline double Get_PlaneFunctionCoefficient_A_OnN0(void)const;
	//得到单元标准平面方程系数B(基于点0)
	inline double Get_PlaneFunctionCoefficient_B_OnN0(void)const;
	//得到单元标准平面方程系数C(基于点0)
	inline double Get_PlaneFunctionCoefficient_C_OnN0(void)const;
	//得到单元标准平面方程系数D(基于点0)
	inline double Get_PlaneFunctionCoefficient_D_OnN0(void)const;
	//得到单元四个节点坐标的X值数组
	inline void Get_XArrayInNode( double XInN[4])const;
	//得到单元四个节点坐标的Y值数组
	inline void Get_YArrayInNode( double YInN[4])const;
	//得到单元四个节点坐标的Z值数组
	inline void Get_ZArrayInNode( double ZInN[4])const;
	//得到单元中所有节点X的最大值
	double Get_X_Max(void)const;
	//得到单元中所有节点X的最小值
	double Get_X_Min(void)const;
	//得到单元中所有节点Y的最大值
	double Get_Y_Max(void)const;
	//得到单元中所有节点Y的最小值
	double Get_Y_Min(void)const;
	//得到单元中所有节点Z的最大值
	double Get_Z_Max(void)const;
	//得到单元中所有节点Z的最小值
	double Get_Z_Min(void)const;

	//判断一个点是否在单元的平面上
	bool JudgePointIfInPlaneOnE(const CoordinatesPosition& P)const;
	//判断一条直线（或射线）是否在单元的平面上
	bool JudgeLineIfInPlaneOnE(const Line& L)const;
	//判断一个点是否和四个节点坐标中一个相等
	bool JudgeIfIn4Nodes( const CoordinatesPosition& P)const;
	//判断一条直线（或射线）是否与单元的平面平行
	bool JudgeIfParallelWithLine( const Line& L )const;
	//判断直线是否与单元所在的平面相交
	bool JudgeIfIntersectWithLine( const Line& L )const;

	// 在确定相交情况下计算直线与单元平面的相交点
	CoordinatesPosition ComputeIntersectPOnLineAndEPlane( const Line& L )const;
	// 在确定相交情况下判断直线与单元平面的交点是否是单元内
	bool JudgeIfInElementForIntersectPOnLine( const Line& L )const;
	// 在确定相交且点在单元内的情况下计算直线与单元的交点
	CoordinatesPosition ComputeIntersectPOnLineAndElement( const Line& L )const;

	//判断一条射线是否与单元所在的平面相交
	bool JudgeIfIntersectWithRLine( const Line& L )const;

	//判断并计算线或射线与平面的相交点
	bool ComputeIntersectPOnL_RLAndEPlane( const Line& L 
		, CoordinatesPosition *IntersectP )const;

	

private:
	// ID号
	int Id_;
	// 归属的PartId
	int PartId_;
	// 四个节点的数组
	Node N_[4];
	// 平面厚度
	double Thickness_;
	// 四个节点的单元是否生成
	bool IfPorduct_;
};

#endif
