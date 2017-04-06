/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Wangxiao Xuyuxin

purpose:	线定义及相关计算函数

*********************************************************************/
//#include "CoordinatesPosition.h"
#ifndef LINE_H__
#define LINE_H__

#include "Node.h"
#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Line
{
public:
	//构造空线段
	Line(void);
	// 构造过某一节点射线(1个节点和1个向量）-(徐)
	Line( int id , CoordinatesPosition DirectionVector ,Node N );
	// 构造过某一位置点射线(1个坐标点和一个向量）-(徐)
	Line(int id , CoordinatesPosition DirectionVector ,CoordinatesPosition Point );
	// 构造初始化直线（ID+两个坐标点（起点、终点））
	Line(int id , CoordinatesPosition Point[2] );
	//构造初始化直线（ID+两个节点）
	Line( int id , Node N1 , Node N2 );

	//拷贝构造函数
	Line( const Line &cL );

	// 重载“=”
	Line &operator=( const Line &cL );
	// 重载“==”
	bool operator==( const Line &cL )const;

	~Line(void);

	//设置线的id值
	inline void Set_id(const int &id );
	

	// 得到线的ID值
	inline int Get_id( void ) const;
	// 得到线的方向向量
	inline CoordinatesPosition Get_Vector( void ) const;
	//得到线中所包含节点的节点数
	inline int Get_NodeNumber( void )const;
	//得到线所包含的节点
	inline void Get_Node( int * NodeNumber , Node N[] )const;
	//得到线所包含的第一个节点
	inline Node Get_FristNode( void )const;
	//得到线所包含的第二个节点
	inline Node Get_SecondNode( void )const;
	//通过id号返回第一个节点
	inline Node Get_FristNodeOnId( const int& id )const;
	//通过id号返回第二个节点
	inline Node Get_SecondNodeOnId( const int& id )const;

	//计算线上第一个节点到第二个节点的距离（只适用两个节点）
	inline double LengthOfLineS()const;
	//根据离线段起点的距离计算坐标点
	inline CoordinatesPosition PointFromFristNodeOnDis( const double &dis )const; 
	
	// 判断点是否在线上
	bool JudgePointIfInLine( const CoordinatesPosition& P )const;

private:
	//线序号
	int id_;
	//线的方向向量
	CoordinatesPosition Vec_;
	//线所含的节点个数（至少有一个）
	int Node_Num_;
	//线所包含的节点
	Node *NodeInLine_;
};

#endif

