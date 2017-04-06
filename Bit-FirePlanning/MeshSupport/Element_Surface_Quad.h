//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ı����浥Ԫ����ؼ���

*********************************************************************/

#ifndef ELEMENT_SURFACE_QUAD_H__
#define ELEMENT_SURFACE_QUAD_H__

#include "MeshSupport_Global.h"
// �涨��
#include "MathCalculationSupport/Plane.h"

#include "MathCalculationSupport/Line.h"

class MESHSUPPORT_API Element_Surface_Quad
{
public:
	// ����պ���
	Element_Surface_Quad(void);
	// �����ʼ����Ԫ
	Element_Surface_Quad( int Id , int PartId , Node N[4] , double Thickness );
	// �������캯��
	Element_Surface_Quad( const Element_Surface_Quad& cElement_Quad);
	// ���ء�=��
	Element_Surface_Quad& operator= (const Element_Surface_Quad& cElement_Quad );
	// ���ء�==��
	bool operator == (const Element_Surface_Quad& cElement_Quad )const;
	// ��������
	~Element_Surface_Quad(void);
	
	//***************�����ı��ε�Ԫ�ṹ�е�˽�б���**************
	//����Idֵ
	inline void Set_Id(const int& Id );
	//����PartIdֵ
	inline void Set_PartId(const int& PartId );
	//���õ�Ԫ���
	inline void Set_Thickness(const int& Thickness );
	//�����ĸ��ڵ������(ֻ��ͨ����ʼ��������)
	/*inline void Set_Node( const Node N[4] );*/

	//***************�õ��ı��ε�Ԫ�ṹ�е�˽�б���**************
	//�õ�Id
	inline int Get_id( void ) const;
	//�õ�PartIdֵ
	inline int Get_Partid( void ) const;
	//�õ���Ԫ���
	inline double Get_Thickness( void ) const;
	//�õ�4���ڵ�
	void Get_Node( Node N[4] )const;
	//�õ�N[0],��1���ڵ�
	inline Node Get_Node_0( void )const; 
	//�õ�N[1],��2���ڵ�
	inline Node Get_Node_1( void )const; 
	//�õ�N[2],��3���ڵ�
	inline Node Get_Node_2( void )const; 
	//�õ�N[3],��4���ڵ�
	inline Node Get_Node_3( void )const; 
	//�õ��Ƿ����
	inline bool Get_IfPorduct(void)const;

	//�õ���׼������(��ǰ3�����)
	inline CoordinatesPosition Get_StandardizationVector(void)const;

	//�õ���Ԫ��׼ƽ�淽��ϵ��A(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_A_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��B(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_B_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��C(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_C_OnN0(void)const;
	//�õ���Ԫ��׼ƽ�淽��ϵ��D(���ڵ�0)
	inline double Get_PlaneFunctionCoefficient_D_OnN0(void)const;
	//�õ���Ԫ�ĸ��ڵ������Xֵ����
	inline void Get_XArrayInNode( double XInN[4])const;
	//�õ���Ԫ�ĸ��ڵ������Yֵ����
	inline void Get_YArrayInNode( double YInN[4])const;
	//�õ���Ԫ�ĸ��ڵ������Zֵ����
	inline void Get_ZArrayInNode( double ZInN[4])const;
	//�õ���Ԫ�����нڵ�X�����ֵ
	double Get_X_Max(void)const;
	//�õ���Ԫ�����нڵ�X����Сֵ
	double Get_X_Min(void)const;
	//�õ���Ԫ�����нڵ�Y�����ֵ
	double Get_Y_Max(void)const;
	//�õ���Ԫ�����нڵ�Y����Сֵ
	double Get_Y_Min(void)const;
	//�õ���Ԫ�����нڵ�Z�����ֵ
	double Get_Z_Max(void)const;
	//�õ���Ԫ�����нڵ�Z����Сֵ
	double Get_Z_Min(void)const;

	//�ж�һ�����Ƿ��ڵ�Ԫ��ƽ����
	bool JudgePointIfInPlaneOnE(const CoordinatesPosition& P)const;
	//�ж�һ��ֱ�ߣ������ߣ��Ƿ��ڵ�Ԫ��ƽ����
	bool JudgeLineIfInPlaneOnE(const Line& L)const;
	//�ж�һ�����Ƿ���ĸ��ڵ�������һ�����
	bool JudgeIfIn4Nodes( const CoordinatesPosition& P)const;
	//�ж�һ��ֱ�ߣ������ߣ��Ƿ��뵥Ԫ��ƽ��ƽ��
	bool JudgeIfParallelWithLine( const Line& L )const;
	//�ж�ֱ���Ƿ��뵥Ԫ���ڵ�ƽ���ཻ
	bool JudgeIfIntersectWithLine( const Line& L )const;

	// ��ȷ���ཻ����¼���ֱ���뵥Ԫƽ����ཻ��
	CoordinatesPosition ComputeIntersectPOnLineAndEPlane( const Line& L )const;
	// ��ȷ���ཻ������ж�ֱ���뵥Ԫƽ��Ľ����Ƿ��ǵ�Ԫ��
	bool JudgeIfInElementForIntersectPOnLine( const Line& L )const;
	// ��ȷ���ཻ�ҵ��ڵ�Ԫ�ڵ�����¼���ֱ���뵥Ԫ�Ľ���
	CoordinatesPosition ComputeIntersectPOnLineAndElement( const Line& L )const;

	//�ж�һ�������Ƿ��뵥Ԫ���ڵ�ƽ���ཻ
	bool JudgeIfIntersectWithRLine( const Line& L )const;

	//�жϲ������߻�������ƽ����ཻ��
	bool ComputeIntersectPOnL_RLAndEPlane( const Line& L 
		, CoordinatesPosition *IntersectP )const;

	

private:
	// ID��
	int Id_;
	// ������PartId
	int PartId_;
	// �ĸ��ڵ������
	Node N_[4];
	// ƽ����
	double Thickness_;
	// �ĸ��ڵ�ĵ�Ԫ�Ƿ�����
	bool IfPorduct_;
};

#endif
