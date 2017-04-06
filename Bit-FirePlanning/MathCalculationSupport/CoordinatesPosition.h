/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���궨�弰ת������

*********************************************************************/

#ifndef COORDINATESPOSITION_H__
#define COORDINATESPOSITION_H__

#include "MathCalculationSupport/MathCalculationSupport_Global.h"

// ����㺯��
//#include <iostream>
//#include <math.h>
//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API CoordinatesPosition
{
public:
	// ����յ�����
	CoordinatesPosition(void);
	// �����ʼֵ����
	CoordinatesPosition( double x, double y, double z );
	// ���쿽�����캯��
	CoordinatesPosition( const CoordinatesPosition& cPositon);

	// ���صȺ�
	CoordinatesPosition& operator= (const CoordinatesPosition& cPositon );
	// ���ؼ���
	CoordinatesPosition operator- (const CoordinatesPosition& cPositon )const;
	// ���ؼӺ�
	CoordinatesPosition operator+ (const CoordinatesPosition& cPositon )const;
	// ���أ��㣩�˺ţ�ÿ�������
	CoordinatesPosition operator* (const CoordinatesPosition& cPositon )const;

	// ���غ���ж�
	bool operator == (const CoordinatesPosition& cPositon )const;

	~CoordinatesPosition(void);

	// �Ƕ�ת����
	inline double AngleToRadian(const double& angle) const;
	// ����ת�Ƕ�
	inline double RadianToAngle(const double& radian) const;

	//����xֵ
	inline void Set_x(const double& xx );
	//����yֵ
	inline void Set_y(const double& yy );
	//����zֵ
	inline void Set_z(const double& zz );

	// �õ����е�xֵ
	inline double Get_x(void) const ;
	// �õ����е�yֵ
	inline double Get_y(void) const ;
	// �õ����е�zֵ
	inline double Get_z(void) const ;

	// �������������ľ���
	inline double Distance(const CoordinatesPosition& p2) const;
	// ���㵽ԭ��ľ���
	inline double DistanceOriginPosition(void) const;
	// �����XZƽ��ļнǣ����Ϊ���ȣ�
	inline double AngleWithXZPlane(void) const;
	// �����XYƽ��ļнǣ����Ϊ���ȣ�
	inline double AngleWithXYPlane(void) const;
	// �����YZƽ��ļнǣ����Ϊ���ȣ�
	inline double AngleWithYZPlane(void) const;
	// ��-ԭ��������X��ļнǣ����Ϊ���ȣ�
	inline double AngleWithXAxis(void) const;
	// ��-ԭ��������Y��ļнǣ����Ϊ���ȣ�
	inline double AngleWithYAxis(void) const;
	// ��-ԭ��������Z��ļнǣ����Ϊ���ȣ�
	inline double AngleWithZAxis(void) const;
	// ��ά������ƽ��
	inline void CoordinatesAfterTranslation(const double& dx, const double& dy, const double& dz);
	// ��ά������X����ת������Ϊ�Ƕ�ֵ��
	void RotateAngleByXAxis(const double& angle );
	// ��ά������Y����ת������Ϊ�Ƕ�ֵ��
	void RotateAngleByYAxis(const  double& angle );
	// ��ά������Z����ת������Ϊ�Ƕ�ֵ��
	void RotateAngleByZAxis(const  double& angle );
	// ��ά������X����ת������Ϊ����ֵ��
	void RotateRadianByXAxis(const double& radian );
	// ��ά������Y����ת������Ϊ����ֵ��
	void RotateRadianByYAxis(const  double& radian );
	// ��ά������Z����ת������Ϊ����ֵ��
	void RotateRadianByZAxis(const  double& radian );
	//��ռ�������������X��н�
	double IncludedAngleOfXAxis(const CoordinatesPosition& p2) const;
	//��ռ�������������Y��н�
	double IncludedAngleOfYAxis(const CoordinatesPosition& p2) const;
	//��ռ���������Z��н�
	double IncludedAngleOfZAxis(const CoordinatesPosition& p2) const;

	//���ݵ�����������ľ��Ⱥ�γ�ȼ�������֮��ľ��룻
	double DistanceFromLongitudeAndLatitude( const double &lon_a , const double &lat_a ,
		const double &lon_b , const double &lat_b ) const;

	//����A��B������ľ��Ⱥ�γ�ȼ���B�����A��ķ�λ�Ƕȣ�
	double AzimuthFromLongitudeAndLatitude( const double &longaixs , const double &shortaixs ,
		 const double &lon_a , const double &lat_a , const double &lon_b , const double &lat_b )const ;


	////************�����໥ת������***********************
	//


	//��������ϵ��(��ֹ)Ŀ������ϵת������
	//A_PitchingAngle�����������ǣ���ֹĿ��/�������ϵ������
	//A_YawAngle������ƫ���ǣ���ֹĿ��/�������ϵ����
	//CoordinateInAmmunition���ڵ��������еĵ�
	//WarheadCenterPosition��ս����������Ŀ������ϵ�е�����ֵ
	CoordinatesPosition ComputeCoordinateInTargetFromAmmunition( 
		const double &A_PitchingAngle , const double &A_YawAngle, 
		const CoordinatesPosition &CoordinateInAmmunition ,
		const CoordinatesPosition &WarheadCenterPosition ) const;

private:
	double x_;
	double y_;
	double z_;
};
//}

#endif