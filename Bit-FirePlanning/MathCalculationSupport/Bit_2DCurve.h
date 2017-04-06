/********************************************************************
created:	2016/04/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	2ά���߶������ݽṹ

*********************************************************************/

#ifndef BIT2DCURVE_H__
#define BIT2DCURVE_H__

#include "MathCalculationSupport_Global.h"

class MATHCALCULATIONSUPPORT_API Bit_2DCurve
{
public:
	//�չ��캯��
	Bit_2DCurve(void);
	// �ṹ��ʼ��
	Bit_2DCurve( int n , double *XArray , double *YArray );
	// ���쿽�����캯��
	Bit_2DCurve(const Bit_2DCurve &c2DCurve );
	// ���ع��캯����=��  
	Bit_2DCurve& operator= (const Bit_2DCurve& c2DCurve );
	// ����"=="����ж�
	bool operator == (const Bit_2DCurve& c2DCurve )const;

	~Bit_2DCurve(void);

	//��ʼ������
	void Set_Initial(const int& n , const double XArray[], const double YArray[] );

	//�õ������
	inline int Get_PointNumber(void) const;
	//�õ�X����
	void Get_XArray( double XArray[] ) const;
	//�õ�Y����
	void Get_YArray( double YArray[] ) const;

private:
	//2ά�����ϵ�ĸ���
	int Number_;
	//X����
	double *XArray_;
	//Y����
	double *YArray_;
};

#endif