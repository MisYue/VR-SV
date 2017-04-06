/********************************************************************
Creating Date:	2016/04/25
 
File Ext:	h

Purpose:	������Ƭ�������ݽṹ

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "MathCalculationSupport/ProbabilityAndRandom.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "MathCalculationSupport/Line.h"
#include "MeshSupport/QuadMeshingQuad.h"
#include "Bit-FirePlanningGlobal.h"
#pragma once

class BIT_FIREPLANNING_API Bit_FragmentDataStructure
{
public:
	//�չ��캯��
	Bit_FragmentDataStructure();
	//���캯����ʼ��
	//id:��ƬID�ţ�US����λ�ƣ�StaticDisporaAngle����Ƭ��̬��ɢ�ǣ�StaticDirectonalAngle����Ƭ��̬����ǣ�
	//DynamicCircleAngle:��Ƭ��̬����ǣ�DynamicDirectionalAngle:��Ƭ��̬����ǣ�FlyDistance����Ƭ���о���;
	//FragmentVelocity:��Ƭ���٣�FragmentDynamicVelocity:ÿ����Ƭ��̬��ɢ�ٶȣ���Ƭʵ���ٶȣ���FragmentPositionInRocketCoordinate:��Ƭ�ڵ�������ϵ������
	Bit_FragmentDataStructure( int &id , Bit_UnitSystem &US , double &Mass , double &StaticDisporaAngle , double &StaticDirectonalAngle ,
		double &DynamicCircleAngle , double &DynamicDirectionalAngle , double &FlyDistance , double &FragmentVelocity , double &FragmentDynamicVelocity ,
		CoordinatesPosition &FragmentPositionInRocketCoordinate , double &FragmentResidualVelocity );
	~Bit_FragmentDataStructure();
	//�������캯��
	Bit_FragmentDataStructure( const Bit_FragmentDataStructure &Bit_Frag );
	//�������=������
	Bit_FragmentDataStructure &operator=( const Bit_FragmentDataStructure &Bit_Frag );

	//������ƬIDֵ
	void Set_FragmentID( int Frag_ID );
	//���õ�λ��
	void Set_FragmentUS( Bit_UnitSystem &Frag_US );
	//������Ƭ����
	void Set_Mass( double &Frag_Mass );
	//������Ƭ��̬��ɢ��
	void Set_StaticDisporaAngle( double &Frag_StaticDisporaAngle );
	//������Ƭ��̬�����
	void Set_StaticDirectonalAngle( double &Frag_StaticDirectonalAngle );
	//������Ƭ��̬�����
	void Set_DynamicCircleAngle( double Frag_DynamicCircleAngle );
	//������Ƭ��̬�����
	void Set_DynamicDirectionalAngle( double &Frag_DynamicDirectionalAngle );
	//������Ƭ���о���
	void Set_FlyDistance( double &Frag_FlyDistance );
	//������Ƭ����
	void Set_FragmentVelocity( double &Frag_FragmentVelocity );
	//������Ƭ��̬�����ٶ�
	void Set_FragmentDynamicVelocity( double &Frag_FragmentDynamicVelocity );
	//������Ƭ�ڵ�������ϵ������
	void Set_FragmentPositionInRocketCoordinate( CoordinatesPosition &Frag_FragmentPositionInRocketCoordinate );
	//������Ƭʣ���ٶ�
	void Set_FragmentResidualVelocity( double &Frag_FragmentResidualVelocity );


	//�õ���ƬID
	int Get_FragmentID( void )const;
	//�õ���λ��
	Bit_UnitSystem Get_FragmentUS( void )const;
	//�õ���Ƭ����
	double Get_Mass( void )const;
	//�õ���Ƭ��̬��ɢ��
	double Get_StaticDisporaAngle( void )const;
	//�õ���Ƭ��̬�����
	double Get_StaticDirectonalAngle( void )const;
	//�õ���Ƭ��̬�����
	double Get_DynamicCircleAngle( void );
	//�õ���Ƭ��̬�����
	double Get_DynamicDirectionalAngle( void )const;
	//�õ���Ƭ���о���
	double Get_FlyDistance( void )const;
	//�õ���Ƭ����
	double Get_FragmentVelocity( void )const;
	//�õ���Ƭ��̬�����ٶ�
	double Get_FragmentDynamicVelocity( void )const;
	//�õ���Ƭ�ڵ�������ϵ������
	CoordinatesPosition Get_FragmentPositionInRocketCoordinate( void )const;
	//�õ���Ƭʣ���ٶ�
	double Get_FragmentResidualVelocity( void )const;


private:
	Bit_UnitSystem US_;
	int id_;
	double Mass_;
	double StaticDisporaAngle_ ;
	double StaticDirectonalAngle_;
	double FlyDistance_;
	double DynamicCircleAngle_;
	double DynamicDirectionalAngle_;
	CoordinatesPosition FragmentPositionInRocketCoordinate_;
	double FragmentVelocity_;
	double FragmentDynamicVelocity_;
	//CoordinatesPosition FragmentPositionInAimCoordinate_;
	double FragmentResidualVelocity_;
};