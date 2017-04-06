/********************************************************************
Creating Date:	2016/05/06
 
File Ext:	h

Purpose:	�����ս������������

*********************************************************************/


#include "WarheadDataBase/WarheadPowerAnalysisData.h"
#include "WarheadPowerAnalysis/Bit_PowerAnalysisBase.h"
#include "MaterialDataBase/ChargeData.h"
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "HitAndExplosionPointAnalysis/HAE_HitPointAnalysis.h"
#include "MathCalculationSupport/ProbabilityAndRandom.h"
#include "Bit-RocketDataStructure.h"
#include "Bit-FirePlanningGlobal.h"
class BIT_FIREPLANNING_API Bit_RocketAnalyse
{
public:

	//�չ��캯��
	Bit_RocketAnalyse();
	//���캯����ʼ��
	Bit_RocketAnalyse( Bit_UnitSystem &US );
	~Bit_RocketAnalyse();
	//�������캯��
	Bit_RocketAnalyse( const Bit_RocketAnalyse &Bit_Rock );
	//�������=������
	Bit_RocketAnalyse &operator=( const Bit_RocketAnalyse &Bit_Rock );

	//������Ƭ���٣�Gurney��ʽ��
	//USForVelocity:���㵥λ��
	double ComputeFragmentVelocityViaGurney( WarheadPowerAnalysisData &WarheadData , ChargeData &ChargeD , Bit_UnitSystem &USForVelocity )const;
	//�ٶ�˥������Ƭʣ���ٶ�(FragmentVelocity:��Ƭ���٣�FlyDistance����Ƭ���о��룻AttenuationCoefficient���ٶ�˥��ϵ��)
	double ComputeFragmentVelocityAttenuation( double &FragmentVelocity , double &FlyDistance , double &AttenuationCoefficient )const;
	//�ٶ�˥��ϵ��(ResistanceCoefficient����������ϵ����LocalAirDencity�����ؿ����ܶȣ�FragmentFrontalArea����Ƭչ�������FragmentMass����Ƭ����)
	double ComputeVelocityAttenuationCoefficient( double &ResistanceCoefficient , double &LocalAirDencity , double &FragmentFrontalArea , double &FragmentMass , Bit_UnitSystem &US )const;
	//���ؿ����ܶ�(AboveSeaLevel�����θ߶�)
	double ComputeLocalAirDensity( double &AboveSeaLevel , Bit_UnitSystem &US )const;
	//��Ƭչ�����(ShapeCoefficient:��״ϵ����FragmentMass����Ƭ����)
	double ComputeFragmentFrontalArea( double &ShapeCoefficient , double &FragmentMass , Bit_UnitSystem &US )const;


	//********************�����CEP�Ļ������Ŀ��ƽ������׼��******************//
	//������׼����Ŀ������ϵ��λ�ã�����CEP��
	//AimPointWithoutCEP����׼����Ŀ������ϵ�����꣨δ��CEP����CEP�������CEP��PitchingAngle������������ǣ�YawAngle�������ƫ����
	CoordinatesPosition AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure )const;
	////������׼����Ŀ������ϵ��λ�ã�����CEP��NRotate��
	////AimPointWithoutCEP����׼����Ŀ������ϵ�����꣨δ��CEP����CEP�������CEP��PitchingAngle������������ǣ�YawAngle�������ƫ����
	//CoordinatesPosition AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure )const;
	//��������õ�ը������
	//AimPointWithCEP����׼�㣨��CEP����Ŀ������ϵλ�ã�BurstHighE������ը��������BurstHighD������ը�߷���
	CoordinatesPosition BurstPoint( CoordinatesPosition &AimPointWithCEP , double &BurstHighE , double &BurstHighD , Bit_RocketDataStructure &RockDataStructure )const;

	

private:
	Bit_UnitSystem US_;

};