/********************************************************************
created:	2016/2/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���л�������

*********************************************************************/

#ifndef BITPOWERANALYSISBASE_H__
#define BITPOWERANALYSISBASE_H__
// ��̬�⵼��
//#include "WarheadPowerAnalysis_Global.h"

#include "WarheadDataBase\WarheadPowerAnalysisData.h"

//��������ܵ��û��Զ���
#include "USERD_ComputeGurenyEnergy.h"
//#include "MathCalculationSupport\UnitSystem.h"

class WARHEADPOWERANALYSIS_API Bit_PowerAnalysisBase
{
public:
	// �չ��캯��
	Bit_PowerAnalysisBase(void);
	// �ṹ���ʼ��
	Bit_PowerAnalysisBase( Bit_UnitSystem US );

	//***********************��ս������װҩ���ݽṹ��������****************************
	//���أ�ս��������װҩ�����������
	double ComputeMassRatioForChargeAndShell( const double& WholeMass, const double& ChargesMass, const double& ShellMass)const;
	//����ս����Բ����װҩ�Ϳ���������
	inline double ComputeMassRatioForChargeAndShellInClinder( const double& ChargeMassInClinder , const double &ShellMassInClinder )const;
	//����ս����װ��ϵ��
	inline double ComputeFillCoefficient( const double& WholeMass, const double& ChargeWholeMass )const;
	//���ڱ��ȵ�TNT��������(����TNT��ը��ըҩ����)
	inline double ComputeTNTNLOnQv(const double& ChargeMass , const double &ChargeQv , const double &TNTQV)const;
	//�������װҩ�൱����¶װҩ�ĵ�����ʽ1
	double ComputeChargeEquivalentMassWithShell_F1(const double& ChargeWithshell , const double& R_0 
		, const double& R_P0 , const double &aa , const double &bb , const double& PolytropicE , const double&WLC)const;
	//�˶�װҩ��ֹװҩת����ʽ1(ʹ�ù�������ע�ⵥλ�Ƶ�ͳһ)
	double ComputeMotionChargeEquivalentMass_F1( const double& ChargeMovie_Kg, const double& ChargeVelocity_MS, const double& ChargeQv_JKg )const;

	////////********��ս������װҩ���ݽṹ�����������******************
	// ս��������װҩ�����������
	double ComputeMassRatioForChargeAndShellOnWarD( const WarheadPowerAnalysisData &WarheadD)const;
	// ����ս����Բ����װҩ�Ϳ���������
	double ComputeMassRatioForChargeAndShellInClinderOnWarD( const WarheadPowerAnalysisData &WarheadD )const;
	// ����ս����װ��ϵ��
	double ComputeFillCoefficientOnWarD( const WarheadPowerAnalysisData &WarheadD )const;
	
	///////************����ʽ�������******************
	// ��������ܣ����빫ʽ�ţ�
	double ComputeGurneyEnergy( const int& Function_Number , const ChargeData& ChargeD )const;
	// �û��Զ����������ܣ����빫ʽ�ţ�
	double ComputeGurneyEnergy_USER( const int& Number , const ChargeData& ChargeD , USERD_ComputeGurenyEnergy &USERD_GE )const;
	// ����TNT���������빫ʽ�ţ�_�����ǣ����빫ʽ�ţ�
	double ComputeTNTEquivalentWithoutShell( const int& Function_Number , const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD )const;
	// ����װҩ��ը����Ķ෽ָ�������빫ʽ�ţ�
	double ComputeExplosionGasPolytropicExponent( const int& Function_Number , const ChargeData& ChargeD )const;
	// �������װҩ�ĵ�Ч���������빫ʽ�ţ�
	double ComputeChargeEquivalentMassWithShellOnWarD( const int& Function_Number , const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD , const int& PECompute_Num )const;

	///////////*******��������************************
	// ��������ܹ�ʽ1
	double GurenyEnergy_F1( const ChargeData& ChargeD )const;
	// ��������ܹ�ʽ2
	double GurenyEnergy_F2( const ChargeData& ChargeD )const;
	// ����TNT������ʽ1�������ǣ�
	double TNTEquivalentWithoutShell_F1( const WarheadPowerAnalysisData &WarheadData , const ChargeData& ChargeD )const;
	// ����෽ָ��(����ָ��)��ʽ1
	double ExplosionGasPolytropicExponent_F1( const ChargeData& ChargeD )const;
	// ����෽ָ��(����ָ��)��ʽ2
	double ExplosionGasPolytropicExponent_F2( const ChargeData& ChargeD )const;

	// �������װҩ�ĵ�Чװҩ������ʽ1
	double ChargeEquivalentMassWithShellOnWarD_F1( const WarheadPowerAnalysisData &WarheadData 
		, const ChargeData& ChargeD , const int& PECompute_Num )const;
	
	
	~Bit_PowerAnalysisBase(void);


private:
	// ��λϵ
	Bit_UnitSystem US_;
	// �����Ƿ��ʼ����λϵ��
	bool IfUS_;
};

#endif