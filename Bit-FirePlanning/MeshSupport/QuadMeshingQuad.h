//#pragma once

/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ı����浥Ԫ�Զ������ı����浥Ԫ

*********************************************************************/

#ifndef QUADMESHINGQUAD_H__
#define QUADMESHINGQUAD_H__

#include "MeshSupport_Global.h"
//�����嵥Ԫ
#include "Element_Surface_Quad.h"
//����ϵ����
#include "BITCoordinateSystemSupport\CoordinateSystem.h"
//��
#include "MathCalculationSupport\Line.h"
//�߶�
#include "MathCalculationSupport\Segment.h"

class MESHSUPPORT_API QuadMeshingQuad
{
public:
	QuadMeshingQuad(void);
	// �����ʼ����Ԫ
	QuadMeshingQuad( Element_Surface_Quad EQ , int LineId );
	// �������캯��
	QuadMeshingQuad( const QuadMeshingQuad & cQMQ);
	// ����"="�Ⱥ�
	QuadMeshingQuad& operator= (const QuadMeshingQuad& cQMQ );
	// ����"=="�Ⱥ�
	bool operator == (const QuadMeshingQuad& cQMQ )const;

	~QuadMeshingQuad(void);

	// ��ó�ʼ�ı��ε�Ԫ
	inline Element_Surface_Quad Get_InQuadElement(void) const;
	// ��õ�Ԫ����ϵ
	inline CoordinateSystem Get_CSInElement(void) const;
	// ��õ�Ԫ�ϵ���
	inline void Get_LineInElement( Line LineInE[4] ) const;
	// �����0��2�ϻ������������
	inline int Get_DividNInLine02( void )const;
	// �����1��3�ϻ������������
	inline int Get_DividNInLine13( void )const;
	// ��������Ƿ��ѽ��л���
	inline bool Get_IfDivid(void)const;
	// ��õ�Ԫ�ϵĽڵ���
	inline int Get_NodeNumber(void)const;
	// ��õ�Ԫ�ϵĵ�Ԫ��
	inline int Get_ElementNumber(void)const;
	// ��õ�Ԫ�Ͻڵ�
	void Get_NodeInElement( int * NodeNumber , Node N[] )const;
	// ��õ�Ԫ�ϵ�Ԫ
	void Get_ElementInElement( int * ElementNumber , Element_Surface_Quad E[] )const;
	//�����ı������񻮷֣��õ���Ԫ���ڵ�Ԫ����ϵ�е����꣩
	void MeshQuad( const int& FristNum_Node, const int& FristNum_Element 
		, const int& N_L02 , const int &N_L13);

private:
	// ��ʼ�ı��ε�Ԫ
	Element_Surface_Quad Element_Quad_;
	// ��Ԫ����ϵ
	CoordinateSystem CS_E_;
	// ���嵥Ԫ�ϵ���
	Line LineInElement_[4];
	// 0��2���ϻ��ֵ�����
	int DividLine02_;
	// 1��3���ϻ��ֵ�����
	int DividLine13_;
	// �Ƿ��ѽ��������񻮷�
	bool IfDividFinished_;
	// ����ڵ����
	Node *NodeInElement_;
	// ��Ԫ����
	Element_Surface_Quad *ElementInElement_;
};

#endif
