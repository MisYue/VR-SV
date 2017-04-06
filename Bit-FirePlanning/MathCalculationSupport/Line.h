/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Wangxiao Xuyuxin

purpose:	�߶��弰��ؼ��㺯��

*********************************************************************/
//#include "CoordinatesPosition.h"
#ifndef LINE_H__
#define LINE_H__

#include "Node.h"
#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Line
{
public:
	//������߶�
	Line(void);
	// �����ĳһ�ڵ�����(1���ڵ��1��������-(��)
	Line( int id , CoordinatesPosition DirectionVector ,Node N );
	// �����ĳһλ�õ�����(1��������һ��������-(��)
	Line(int id , CoordinatesPosition DirectionVector ,CoordinatesPosition Point );
	// �����ʼ��ֱ�ߣ�ID+��������㣨��㡢�յ㣩��
	Line(int id , CoordinatesPosition Point[2] );
	//�����ʼ��ֱ�ߣ�ID+�����ڵ㣩
	Line( int id , Node N1 , Node N2 );

	//�������캯��
	Line( const Line &cL );

	// ���ء�=��
	Line &operator=( const Line &cL );
	// ���ء�==��
	bool operator==( const Line &cL )const;

	~Line(void);

	//�����ߵ�idֵ
	inline void Set_id(const int &id );
	

	// �õ��ߵ�IDֵ
	inline int Get_id( void ) const;
	// �õ��ߵķ�������
	inline CoordinatesPosition Get_Vector( void ) const;
	//�õ������������ڵ�Ľڵ���
	inline int Get_NodeNumber( void )const;
	//�õ����������Ľڵ�
	inline void Get_Node( int * NodeNumber , Node N[] )const;
	//�õ����������ĵ�һ���ڵ�
	inline Node Get_FristNode( void )const;
	//�õ����������ĵڶ����ڵ�
	inline Node Get_SecondNode( void )const;
	//ͨ��id�ŷ��ص�һ���ڵ�
	inline Node Get_FristNodeOnId( const int& id )const;
	//ͨ��id�ŷ��صڶ����ڵ�
	inline Node Get_SecondNodeOnId( const int& id )const;

	//�������ϵ�һ���ڵ㵽�ڶ����ڵ�ľ��루ֻ���������ڵ㣩
	inline double LengthOfLineS()const;
	//�������߶����ľ�����������
	inline CoordinatesPosition PointFromFristNodeOnDis( const double &dis )const; 
	
	// �жϵ��Ƿ�������
	bool JudgePointIfInLine( const CoordinatesPosition& P )const;

private:
	//�����
	int id_;
	//�ߵķ�������
	CoordinatesPosition Vec_;
	//�������Ľڵ������������һ����
	int Node_Num_;
	//���������Ľڵ�
	Node *NodeInLine_;
};

#endif

