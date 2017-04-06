/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	����ϵ����

*********************************************************************/

#ifndef COORDINATESYSTEM_H__
#define COORDINATESYSTEM_H__

#include "BITCoordinateSystemSupport_Global.h"
// �������
#include "MathCalculationSupport/CoordinatesPosition.h"
// �ռ���
#include "MathCalculationSupport/SpaceGeometry.h"

class BITCOORDINATESYSTEMSUPPORT_API CoordinateSystem
{
public:
	// ����յ�����ϵ
	CoordinateSystem(void);
	// ��������ϵ(��ԭ�㡢����һ������һ)
	CoordinateSystem( int n , CoordinatesPosition OriginalPoint 
		, CoordinatesPosition One_AixV , CoordinatesPosition Two_AixV );
	// �������캯��
	CoordinateSystem( const CoordinateSystem &cCS );
	// ����"="�Ⱥ�
	CoordinateSystem& operator= (const CoordinateSystem& cCS );
	// ����"=="����ж�
	bool operator == (const CoordinateSystem& cCS )const;

	~CoordinateSystem(void);
	
	// ��ʼ������
	void Set_Initial( const int& n , const CoordinatesPosition& OriginalPoint 
		, const CoordinatesPosition& One_AixV , const CoordinatesPosition& Two_AixV );

	// �õ�ԭ��
	inline CoordinatesPosition Get_OriginalPoint(void) const ;
	// �õ�X������
	inline CoordinatesPosition Get_XAixVector(void) const ;
	// �õ�Y������
	inline CoordinatesPosition Get_YAixVector(void) const ;
	// �õ�Z������
	inline CoordinatesPosition Get_ZAixVector(void) const ;

	//���ݸ���B����ϵ��A����ϵ�е�λ�ü���A����ϵ�еĵ���B����ϵ�е������
	CoordinatesPosition TransformCoordinateFromCSAToCSB( const CoordinatesPosition& BCS_OriginInACS 
		, const CoordinatesPosition& BCS_ZAxisVecInACS , const CoordinatesPosition& BCS_XAxisVecInACS 
		, const CoordinatesPosition& PointInACS) const ;

private:
	// ����ԭ��
	CoordinatesPosition OriginalPoint_;
	// X������
	CoordinatesPosition X_AixVector_;
	// Y������
	CoordinatesPosition Y_AixVector_;
	// Z������
	CoordinatesPosition Z_AixVector_;
};
#endif