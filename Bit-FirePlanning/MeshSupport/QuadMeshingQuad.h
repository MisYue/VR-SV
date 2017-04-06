//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	四边形面单元自动划分四变形面单元

*********************************************************************/

#ifndef QUADMESHINGQUAD_H__
#define QUADMESHINGQUAD_H__

#include "MeshSupport_Global.h"
//四面体单元
#include "Element_Surface_Quad.h"
//坐标系定义
#include "BITCoordinateSystemSupport\CoordinateSystem.h"
//线
#include "MathCalculationSupport\Line.h"
//线段
#include "MathCalculationSupport\Segment.h"

class MESHSUPPORT_API QuadMeshingQuad
{
public:
	QuadMeshingQuad(void);
	// 构造初始化单元
	QuadMeshingQuad( Element_Surface_Quad EQ , int LineId );
	// 拷贝构造函数
	QuadMeshingQuad( const QuadMeshingQuad & cQMQ);
	// 重载"="等号
	QuadMeshingQuad& operator= (const QuadMeshingQuad& cQMQ );
	// 重载"=="等号
	bool operator == (const QuadMeshingQuad& cQMQ )const;

	~QuadMeshingQuad(void);

	// 获得初始四边形单元
	inline Element_Surface_Quad Get_InQuadElement(void) const;
	// 获得单元坐标系
	inline CoordinateSystem Get_CSInElement(void) const;
	// 获得单元上的线
	inline void Get_LineInElement( Line LineInE[4] ) const;
	// 获得线0和2上划分网格的数量
	inline int Get_DividNInLine02( void )const;
	// 获得线1和3上划分网格的数量
	inline int Get_DividNInLine13( void )const;
	// 获得网格是否已进行划分
	inline bool Get_IfDivid(void)const;
	// 获得单元上的节点数
	inline int Get_NodeNumber(void)const;
	// 获得单元上的单元数
	inline int Get_ElementNumber(void)const;
	// 获得单元上节点
	void Get_NodeInElement( int * NodeNumber , Node N[] )const;
	// 获得单元上单元
	void Get_ElementInElement( int * ElementNumber , Element_Surface_Quad E[] )const;
	//进行四边形网格划分（得到单元是在单元坐标系中的坐标）
	void MeshQuad( const int& FristNum_Node, const int& FristNum_Element 
		, const int& N_L02 , const int &N_L13);

private:
	// 初始四边形单元
	Element_Surface_Quad Element_Quad_;
	// 单元坐标系
	CoordinateSystem CS_E_;
	// 定义单元上的线
	Line LineInElement_[4];
	// 0、2线上划分的数量
	int DividLine02_;
	// 1、3线上划分的数量
	int DividLine13_;
	// 是否已进行了网格划分
	bool IfDividFinished_;
	// 网格节点矩阵
	Node *NodeInElement_;
	// 单元矩阵
	Element_Surface_Quad *ElementInElement_;
};

#endif
