// #pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ѻ��������ƽ��

*********************************************************************/

#include "MeshSupport_Global.h"

////����λ�Ƶ�����ϵ
//#include "MathCalculationSupport/Bit_CSWithExpAndUS.h"
//��Ԫ����
#include "Element_Surface_Quad.h"
//�ռ伸��
#include "MathCalculationSupport/SpaceGeometry.h"

#ifndef BITQUADMESHPLANE_H__
#define BITQUADMESHPLANE_H__

class MESHSUPPORT_API Bit_QuadMeshPlane
{
public:
	// �չ��캯��
	Bit_QuadMeshPlane(void);
	// ��ʼ�����캯��
	Bit_QuadMeshPlane( int Element_N , Element_Surface_Quad ElementInPlane[] );
	// �������캯��
	Bit_QuadMeshPlane( const Bit_QuadMeshPlane & cQMP);
	// ����"="�Ⱥ�
	Bit_QuadMeshPlane& operator= (const Bit_QuadMeshPlane& cQMP );
	// ����"=="�Ⱥ�
	bool operator == (const Bit_QuadMeshPlane& cQMP )const;

	~Bit_QuadMeshPlane(void);

	// ���ó�ʼ����
	void Set_Initial( const int& Element_N , const Element_Surface_Quad ElementInPlane[]);
	// �õ�ƽ���ϵĵ�Ԫ��
	inline int Get_ElementNumber(void)const;
	// �õ�ƽ���ϵĵ�Ԫ
	void Get_ElementInPlane( Element_Surface_Quad E[] )const;
	// �õ�ƽ�������е�Ԫ�ĵ�Ԫ��
	void Get_ElementIdInPlane( int EId[] );
	// ���ݵ�Ԫ�ŵõ�ƽ���ϵĵ�Ԫ
	Element_Surface_Quad Get_ElementOnEId( const int& EId)const;
	// �õ�ƽ���ϵ�n����Ԫ(n��0��ʼ)
	Element_Surface_Quad Get_ElementOnN( const int& N)const;
private:
	//ƽ���ϵĵ�Ԫ��
	int Element_N_;
	//ƽ���ϵĵ�Ԫ
	Element_Surface_Quad *ElementInPlane_;
	// �Ƿ���
	bool IfDefinition_;
};
#endif
