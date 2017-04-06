/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	节点定义及相关计算函数

*********************************************************************/
//#pragma once
#ifndef NODE_H__
#define NODE_H__

#include "MathCalculationSupport_Global.h"

//定义坐标类
#include "CoordinatesPosition.h"
//定义高等数学类
//#include "AdvancedMath.h"
//定义几何空间类
//#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Node
{
public:
	// 构造空节点
	Node(void);
	// 构造初始化节点（ID+XYZ坐标
	Node( int id , double x , double y , double z );
	// 构造初始化节点（ID+coordinates坐标）
	Node( int id , CoordinatesPosition& Position );//
	// 拷贝构造函数
	Node( const Node &cN );

	// 重载“=”
	Node& operator = ( const Node& cN );
	// 重载“==”
	bool operator == ( const Node& cN )const;

	virtual ~Node(void);

	//设置节点中的id值
	inline void Set_id(const int& idid );
	//设置x值
	inline void Set_x(const double& xx );
	//设置y值
	inline void Set_y(const double& yy );
	//设置z值
	inline void Set_z(const double& zz );
	//设置节点坐标
	inline void Set_NodeCoordinate( const CoordinatesPosition& N_Position );
	//设置节点
	inline void Set_Node( const int&id , const CoordinatesPosition& N_Position );

	// 得到节点中的id值
	inline int Get_id(void)const;
	// 得到节点中的x值
	inline double Get_x(void)const;
	// 得到节点中的y值
	inline double Get_y(void)const;
	// 得到节点中的z值
	inline double Get_z(void)const;
	//得到节点坐标
	inline CoordinatesPosition Get_NodeCoordinates(void)const;

	///////********节点预处理***************
	//判断两个节点是否坐标点相同
	inline bool JudgeIfSamePointIn2Nodes( const Node& N1 , const Node& N2 )const;
	//判断多个节点中是否有坐标点相同的
	bool JudgeIfSamePointInNNodes( const int& Num , const Node N[])const;
	//节点号重复的话合并节点，形成新的节点
	void MergeIdRepetitionNodes( const int &Num_Old , const Node N_Old[] , int *Num_new , Node N_new[] )const;

	//设置节点组

	//读入keyword节点文件
	void ReadKeyWordNodeFile( ); //相对输入文件名

private:
	int id_;             // 节点号定义
	double x_;           // 节点坐标X
	double y_;           // 节点坐标Y
	double z_;           // 节点坐标Z

};
#endif

