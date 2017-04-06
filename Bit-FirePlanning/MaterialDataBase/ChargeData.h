//#pragma once
/********************************************************************
created:	2016/02/24
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ϊװҩ���ݿ��ṩ���ݽṹ

*********************************************************************/

#ifndef CHARGEDATA_H__
#define CHARGEDATA_H__

#include "MaterialDataBase/MaterialDataBase_Global.h"
//��λ�ƶ�
#include "BITUnitsSupport/Bit_UnitSystem.h"

class MATERIALDATABASE_API ChargeData
{
public:
	// �չ��캯��
	ChargeData(void);
	// �ṹ���ʼ��
	ChargeData( int Charge_Id , Bit_UnitSystem US , double Density
		, double ExplosionVelocity , double ExplosionHeat , double ExplosinPressure );
	
	// �������캯��
	ChargeData( const ChargeData& cCharData );
	// ���صȺ�
	ChargeData& operator= (const ChargeData& cCharData );
	// ����"=="��Ⱥ�
	bool operator == (const ChargeData& cCharData )const;
	// ����
	~ChargeData(void);

	// **********��������ת�����µĵ�λ����***********//
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );
	// ����ת�����ȵ�λ
	inline void TransitionLength( const int& Length );
	// ����ת��ʱ�䵥λ
	inline void TransitionTime( const int& Time );
	// ����ת��������λ
	inline void TransitionMass( const int& Mass );
	// ת����λ�����
	//ChargeData TransitionUS_Input( const Bit_UnitSystem& NewUS );

	//*************88

	//��ʼ������
	void Set_Initial( const int& Charge_Id , const Bit_UnitSystem& US 
		, const double& Density , const double& ExplosionVelocity 
		, const double& ExplosionHeat , const double& ExplosinPressure );

	//�õ��Ƿ���
	inline bool Get_IfDefinition(void)const;
	//�õ�װҩId
	inline int Get_ChargeId(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ�װҩ�ܶȣ������뵥λ��һ�£�
	inline double Get_Density(void)const;
	// �õ�װҩ���٣������뵥λ��һ�£�
	inline double Get_ExplosionVelocity(void)const;
	// �õ�װҩ���ȣ������뵥λ��һ�£�
	inline double Get_ExplosionHeat(void)const;
	// �õ�װҩ��ѹ�������뵥λ��һ�£�
	inline double Get_ExplosinPressure(void)const;

	// �õ�װҩ�ܶȣ�mm-g-us��λϵ�����
	inline double Get_DensityForC(void)const;
	// �õ�װҩ���٣�mm-g-us��λϵ�����
	inline double Get_ExplosionVelocityForC(void)const;
	// �õ�װҩ���ȣ�mm-g-us��λϵ�����
	inline double Get_ExplosionHeatForC(void)const;
	// �õ�װҩ��ѹ��mm-g-us��λϵ�����
	inline double Get_ExplosinPressureForC(void)const;

	//ͨ��id�ŷ��ص�λϵ�������뵥λ��һ�£�
	Bit_UnitSystem Get_USOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ�ܶȣ������뵥λ��һ�£�
	inline double Get_DensityOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ���٣������뵥λ��һ�£�
	inline double Get_ExplosionVelocityOnId( const int& id )const;
	//ͨ��id�ŷ���װҩ���ȣ������뵥λ��һ�£�
	inline double Get_ExplosionHeatOnId( const int& id )const;
	//ͨ��id��װҩ��ѹ�������뵥λ��һ�£�
	inline double Get_ExplosinPressureOnId( const int& id )const;
	

private:
	// װҩ�ţ�Ψһʶ�����
	int Charge_Id_;
	// ��λϵ
	Bit_UnitSystem US_;
	// װҩ�ܶ�
	double Density_;
	// װҩ����
	double ExplosionVelocity_;
	// װҩ����
	double ExplosionHeat_;
	// װҩ��ѹ
	double ExplosinPressure_;
	// �Ƿ���
	bool IfDefinition_;
};
#endif
