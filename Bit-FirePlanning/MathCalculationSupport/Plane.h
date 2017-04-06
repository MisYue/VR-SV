/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�涨�弰��ؼ��㺯��

*********************************************************************/

#ifndef PLANE_H__
#define PLANE_H__

//����������
//#include "CoordinatesPosition.h"
//���弸�οռ���
#include "SpaceGeometry.h"
//����ڵ���
#include "Node.h"
//����ߵ����ݼ�����
//#include "AdvancedMath.h"

//#pragma once
class MATHCALCULATIONSUPPORT_API Plane
{
public:
	// �������
	Plane(void);
	// �����ʼ��ƽ�棨1���ڵ㣩
	Plane( double Thickness , CoordinatesPosition Vec , Node NodeInSurface );
	// �����ʼ��ƽ�棨1������㣩
	Plane( double Thickness , CoordinatesPosition Vec , CoordinatesPosition Point);
	// ��������㹹��һ��ƽ��
	Plane( double Thickness , CoordinatesPosition P1 , CoordinatesPosition P2, CoordinatesPosition P3 );
	// ���������ڵ㹹��һ��ƽ��
	Plane( double Thickness , int Node_Num , Node *N ); 

	// �������캯��
	Plane(const Plane &cPlane );
	// ���ع��캯����=��
	Plane &operator=( const Plane &cPlane  );
	// ���ع��캯����==��
	bool operator == (const Plane&cPlane )const;

	~Plane(void);

	//�������еĺ��ֵ
	inline void Set_Thickness(const double& Thickness );
	////������ķ�����
	//inline void Set_NormalVector(const CoordinatesPosition& nV );
	//////�������������Ľڵ�������ڵ�(����һ���ڵ�)
	//inline void Set_Node( const int& NodeNumber , const Node N[] );
	
	////�õ���ĺ��ֵ
	inline double Get_Thickness()const;
	////�õ���ķ�����ֵ
	inline CoordinatesPosition Get_NormalVector()const;
	//�õ����������Ľڵ�
	inline void Get_Node( int * NodeNumber , Node N[] )const;

	// �淨������YZ��н�(�������ֵ)����Y����ת��
	inline double AngleNormalVectorAndYZPlane( )const;
	// �淨������XZ��н�(�������ֵ)����Z����ת��
	inline double AngleNormalVectorAndXZPlane( )const;

private:
	// ����
	double Thickness_; 
	// ��ķ�����
	CoordinatesPosition Vec_;
	// ���������Ľڵ������������һ����
	int Node_Num_;
	// ���������Ľڵ�
	Node *NodeInPlane_;
};
#endif
