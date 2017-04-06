/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Բ������ϵ�������

*********************************************************************/
#ifndef BITCYLINDERCOORDINATE_H__
#define BITCYLINDERCOORDINATE_H__

// ��̬�⵼��
#include "BITCoordinateSystemSupport_Global.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CylinderCoordinate
{
public:
	Bit_CylinderCoordinate(void);
	// ��ʼ�����캯��
	Bit_CylinderCoordinate( double Radius, double AngleR, double z );
	// �������캯��
	Bit_CylinderCoordinate( const Bit_CylinderCoordinate& cCCPositon);

	// ���صȺ�
	Bit_CylinderCoordinate& operator= (const Bit_CylinderCoordinate& cCCPositon );
	// ���ؼ���
	Bit_CylinderCoordinate operator- (const Bit_CylinderCoordinate& cCCPositon )const;
	// ���ؼӺ�
	Bit_CylinderCoordinate operator+ (const Bit_CylinderCoordinate& cCCPositon )const;
	// ���غ���ж�
	bool operator == (const Bit_CylinderCoordinate& cCCPositon )const;

	~Bit_CylinderCoordinate(void);

	// �Ƕ�ת����
	inline double AngleToRadian(const double& angle) const;
	// ����ת�Ƕ�
	inline double RadianToAngle(const double& radian) const;
	
	//�������в���
	inline void Set_Initial( const double& Radius , const double& AngleR ,const double& z);

	//���þ������ֵ
	inline void Set_Radius(const double& Radius );
	//���ýǶ�(����)ֵ
	inline void Set_AngleR(const double& AngleR );
	//���ø߶�zֵ
	inline void Set_z(const double& z );

	// �õ����еľ������ֵ
	inline double Get_Radius(void) const ;
	// �õ����еĽǶ�(����)ֵ
	inline double Get_AngleR(void) const ;
	// �õ����е�zֵ
	inline double Get_z(void) const;

private:
	double Radius_;
	double AngleR_;
	double z_;
};

#endif

