//
/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��������ϵ�Ķ���

*********************************************************************/

#ifndef BITCYLINDERCOSYSTEM_H__
#define BITCYLINDERCOSYSTEM_H__


// ��̬�⵼��
#include "BITCoordinateSystemSupport_Global.h"
// ֱ����������ϵ��
#include "CoordinateSystem.h"
// ��������
//#include "Bit_CylinderCoordinate.h"

//#include "MathCalculationSupport/SpaceGeometry.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CylinderCoSystem
{
public:
	// �չ��캯��
	Bit_CylinderCoSystem(void);
	// ��ʼ���캯��
	Bit_CylinderCoSystem( CoordinatesPosition OriginalPoint 
		, CoordinatesPosition Polar_Vector , CoordinatesPosition Z_Vector );

	// �������캯��
	Bit_CylinderCoSystem( const Bit_CylinderCoSystem &cCCS );
	// ����"="�Ⱥ�
	Bit_CylinderCoSystem& operator= (const Bit_CylinderCoSystem& cCCS );
	// ����"=="����ж�
	bool operator == (const Bit_CylinderCoSystem& cCCS )const;

	~Bit_CylinderCoSystem(void);

	// ��ʼ������
	void Set_Initial( const CoordinatesPosition& OriginalPoint 
		, const CoordinatesPosition& Polar_Vector ,const CoordinatesPosition& Z_Vector);
	
	//�ռ�����ϵת������������ϵ
	void TransformFromCSToCCS( const int &XorY , const CoordinateSystem &CP_CS );
	//�ռ�����ϵ(ָ��)ת������������ϵ
	void TransformFromCS_PToCCS( const int &XorY , const CoordinateSystem *CP_CS );
	
	// �õ�ԭ��
	inline CoordinatesPosition Get_OriginalPoint(void) const ;
	// �õ���������
	inline CoordinatesPosition Get_PolarAixVector(void) const ;
	// �õ�Z������
	inline CoordinatesPosition Get_ZAixVector(void) const;
	

private:
	// ����ԭ��
	CoordinatesPosition OriginalPoint_;
	// ��������
	CoordinatesPosition Polar_AixVector_;
	// Z������
	CoordinatesPosition Z_AixVector_;
};

#endif

