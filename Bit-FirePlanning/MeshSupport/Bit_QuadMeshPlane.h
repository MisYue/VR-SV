// #pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	已划分网格的平面

*********************************************************************/

#include "MeshSupport_Global.h"

////带单位制的坐标系
//#include "MathCalculationSupport/Bit_CSWithExpAndUS.h"
//单元定义
#include "Element_Surface_Quad.h"
//空间几何
#include "MathCalculationSupport/SpaceGeometry.h"

#ifndef BITQUADMESHPLANE_H__
#define BITQUADMESHPLANE_H__

class MESHSUPPORT_API Bit_QuadMeshPlane
{
public:
	// 空构造函数
	Bit_QuadMeshPlane(void);
	// 初始化构造函数
	Bit_QuadMeshPlane( int Element_N , Element_Surface_Quad ElementInPlane[] );
	// 拷贝构造函数
	Bit_QuadMeshPlane( const Bit_QuadMeshPlane & cQMP);
	// 重载"="等号
	Bit_QuadMeshPlane& operator= (const Bit_QuadMeshPlane& cQMP );
	// 重载"=="等号
	bool operator == (const Bit_QuadMeshPlane& cQMP )const;

	~Bit_QuadMeshPlane(void);

	// 设置初始参量
	void Set_Initial( const int& Element_N , const Element_Surface_Quad ElementInPlane[]);
	// 得到平面上的单元数
	inline int Get_ElementNumber(void)const;
	// 得到平面上的单元
	void Get_ElementInPlane( Element_Surface_Quad E[] )const;
	// 得到平面上所有单元的单元号
	void Get_ElementIdInPlane( int EId[] );
	// 根据单元号得到平面上的单元
	Element_Surface_Quad Get_ElementOnEId( const int& EId)const;
	// 得到平面上第n个单元(n从0开始)
	Element_Surface_Quad Get_ElementOnN( const int& N)const;
private:
	//平面上的单元数
	int Element_N_;
	//平面上的单元
	Element_Surface_Quad *ElementInPlane_;
	// 是否定义
	bool IfDefinition_;
};
#endif
