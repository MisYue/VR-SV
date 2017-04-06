/********************************************************************
Creating Date:	2016/04/26
 
File Ext:	h

Purpose:	�����������������ϵ�����ݽṹ

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "Bit-FirePlanningGlobal.h"
#pragma once
class BIT_FIREPLANNING_API Bit_RocketDataStructure
{
public:
	//���캯����ʼ��
	//id:�����ID�ţ�US����λ�ƣ�PitchingAngle:����������ǣ���������ϵ�£���YawAngle�������ƫ���ǣ���������ϵ�£���
	//WarheadStaticDisporaAngle:�����ս������̬��ɢ��;WarheadStaticAngleCentralLine:�����ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
	//RocketVelocity:������ٶ�;RocketCEP:�����CEP
	Bit_RocketDataStructure( int &id , Bit_UnitSystem &US , double &PitchingAngle , double &YawAngle , double &WarheadStaticDisporaAngle , double &WarheadStaticAngleCentralLine ,
		double &RocketVelocity , double &RocketCEP );
	~Bit_RocketDataStructure();
	//�������캯��
	Bit_RocketDataStructure( const Bit_RocketDataStructure &Bit_Rock );
	//�������=������
	Bit_RocketDataStructure &operator=( const Bit_RocketDataStructure &Bit_Rock );

	//���û����IDֵ
	void Set_RocketID( int &Rock_ID );
	//���û������λ��
	void Set_RocketUS( Bit_UnitSystem &Rock_US );
	//���û����������
	void Set_RocketPitchingAngle( double &Rock_PitchingAngle );
	//���û����ƫ����
	void Set_RocketYawAngle( double &Rock_YawAngle );
	//���û����ս������̬��ɢ��
	void Set_WarheadStaticDisporaAngle( double &Rock_WarheadStaticDisporaAngle );
	//���û����ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
	void Set_WarheadStaticAngleCentralLine( double &Rock_WarheadStaticAngleCentralLine );
	//���û�����ٶ�
	void Set_RocketVelocity( double &Rock_Velocity );
	//���û�����ٶ�
	void Set_RocketCEP( double &Rock_CEP );


	//�õ������ID
	int Get_RocketID( void )const;
	//�õ��������λ��
	Bit_UnitSystem Get_RocketUS( void )const;
	//�õ������������
	double Get_RocketPitchingAngle( void )const;
	//�õ������ƫ����
	double Get_RocketYawAngle( void )const;
	//�õ������ս������̬��ɢ��
	double Get_WarheadStaticDisporaAngle( void )const;
	//�õ������ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
	double Get_WarheadStaticAngleCentralLine( void )const;
	//�õ�������ٶ�
	double Get_RocketVelocity( void )const;
	//�õ������CEP
	double Get_RocketCEP( void )const;

private:
	Bit_UnitSystem US_;
	int id_;
	double PitchingAngle_;
	double YawAngle_;
	double WarheadStaticDisporaAngle_;
	double WarheadStaticAngleCentralLine_;
	double RocketVelocity_;
	double RocketCEP_;
};