/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ڵ㶨�弰��ؼ��㺯��

*********************************************************************/
//#pragma once
#ifndef NODE_H__
#define NODE_H__

#include "MathCalculationSupport_Global.h"

//����������
#include "CoordinatesPosition.h"
//����ߵ���ѧ��
//#include "AdvancedMath.h"
//���弸�οռ���
//#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Node
{
public:
	// ����սڵ�
	Node(void);
	// �����ʼ���ڵ㣨ID+XYZ����
	Node( int id , double x , double y , double z );
	// �����ʼ���ڵ㣨ID+coordinates���꣩
	Node( int id , CoordinatesPosition& Position );//
	// �������캯��
	Node( const Node &cN );

	// ���ء�=��
	Node& operator = ( const Node& cN );
	// ���ء�==��
	bool operator == ( const Node& cN )const;

	virtual ~Node(void);

	//���ýڵ��е�idֵ
	inline void Set_id(const int& idid );
	//����xֵ
	inline void Set_x(const double& xx );
	//����yֵ
	inline void Set_y(const double& yy );
	//����zֵ
	inline void Set_z(const double& zz );
	//���ýڵ�����
	inline void Set_NodeCoordinate( const CoordinatesPosition& N_Position );
	//���ýڵ�
	inline void Set_Node( const int&id , const CoordinatesPosition& N_Position );

	// �õ��ڵ��е�idֵ
	inline int Get_id(void)const;
	// �õ��ڵ��е�xֵ
	inline double Get_x(void)const;
	// �õ��ڵ��е�yֵ
	inline double Get_y(void)const;
	// �õ��ڵ��е�zֵ
	inline double Get_z(void)const;
	//�õ��ڵ�����
	inline CoordinatesPosition Get_NodeCoordinates(void)const;

	///////********�ڵ�Ԥ����***************
	//�ж������ڵ��Ƿ��������ͬ
	inline bool JudgeIfSamePointIn2Nodes( const Node& N1 , const Node& N2 )const;
	//�ж϶���ڵ����Ƿ����������ͬ��
	bool JudgeIfSamePointInNNodes( const int& Num , const Node N[])const;
	//�ڵ���ظ��Ļ��ϲ��ڵ㣬�γ��µĽڵ�
	void MergeIdRepetitionNodes( const int &Num_Old , const Node N_Old[] , int *Num_new , Node N_new[] )const;

	//���ýڵ���

	//����keyword�ڵ��ļ�
	void ReadKeyWordNodeFile( ); //��������ļ���

private:
	int id_;             // �ڵ�Ŷ���
	double x_;           // �ڵ�����X
	double y_;           // �ڵ�����Y
	double z_;           // �ڵ�����Z

};
#endif

