/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�û��Զ���ĸ����ܼ���

*********************************************************************/

#ifndef USERDCOMPUTEGURENYENERGY_H__
#define USERDCOMPUTEGURENYENERGY_H__

#include "WarheadPowerAnalysis_Global.h"

#include "MaterialDataBase\ChargeData.h"

class WARHEADPOWERANALYSIS_API USERD_ComputeGurenyEnergy
{
public:
	// �չ��캯��
	USERD_ComputeGurenyEnergy(void);
	//��ʼ������
	USERD_ComputeGurenyEnergy( Bit_UnitSystem US , double GurneyEnergy );

	~USERD_ComputeGurenyEnergy(void);

	//�����Զ�������ܵĵ�λ��
	inline void Set_US( const Bit_UnitSystem& US );
	// �õ���λ�ƶ��Ƿ���
	inline bool Get_USIfDefinition(void)const;
	// �õ���λ��
	inline Bit_UnitSystem Get_US(void)const;

	////�����Զ��������
	inline void Set_GurneyEnergy(const double& GurneyEnergy);
	// �����Զ�������ܵĵ�λ��
	inline void Set_GurneyEnergyAndUS( const Bit_UnitSystem& US , const double& GurneyEnergy );


	//�õ��Զ��������
	inline double Get_GurneyEnergy(void)const;
	//�Զ��幫ʽ_1(����Charge)
	inline double Get_GurneyEnergyOnUSER_NoCharge( void );
	//�Զ��幫ʽ_2(����Charge)
	inline double Get_GurneyEnergyOnUSER_WithCharge( const ChargeData& ChargeD )const;

private:
	// ��λϵ
	Bit_UnitSystem US_;
	// ������
	double GurneyEnergy_;
	// �Ƿ������˵�λ��
	bool IfUS_;
};

#endif