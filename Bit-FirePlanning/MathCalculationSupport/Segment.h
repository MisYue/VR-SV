//#pragma once
/********************************************************************
created:	2016/02/09
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�߶ζ��弰��ؼ��㺯��

*********************************************************************/

#ifndef SEGMENT_H__
#define SEGMENT_H__

//#include "MathCalculationSupport_Global.h"
// �������
#include "SpaceGeometry.h"

class MATHCALCULATIONSUPPORT_API Segment
{
public:
	Segment(void);
	// �����ʼ���߶Σ���������㣨��㡢�յ㣩��
	Segment( CoordinatesPosition Point_1 , CoordinatesPosition Point_2 );

	// �������캯��
	Segment( const Segment &cSeg );
	// ���ء�=��
	Segment &operator=( const Segment &cSeg );

	~Segment(void);
	

    // �õ���һ����
	inline CoordinatesPosition Get_FristPoint(void) const;
	// �õ��ڶ�����
	inline CoordinatesPosition Get_SecondPoint(void) const;
	// �õ���λ����
    inline CoordinatesPosition Get_SVector(void) const;
	////�ж�һ�����Ƿ����߶���
	bool JudgePointIfInSegment( const CoordinatesPosition &Point)const;
	////�ж������߶��Ƿ��н���
	/*bool JudgeIfInterFor2Segments( const Segment &Seg_1 ,  const Segment &Seg_2 ) const;*/
	//// ���������߶εĽ�������(�����������߶��Ƿ���һ��ƽ���ϵļ�顢���������߶α�Ȼ�ཻ�н���)
	CoordinatesPosition ComputePointBetween2Segments_NoCheck( const Segment& S1 , const Segment& S2 )const;

private:
	// ��һ����
	CoordinatesPosition Point_Frist_;
	// �ڶ�����
	CoordinatesPosition Point_Sencod_;
	// ��׼������
	CoordinatesPosition SVer_;
};

#endif

