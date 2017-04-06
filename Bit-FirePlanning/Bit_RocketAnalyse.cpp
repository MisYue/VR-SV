#include "Bit_RocketAnalyse.h"



//�չ��캯��
Bit_RocketAnalyse::Bit_RocketAnalyse()
{

}

//���캯����ʼ��
Bit_RocketAnalyse::Bit_RocketAnalyse( Bit_UnitSystem &US )
{
	US_ = US;
}

//��������
Bit_RocketAnalyse::~Bit_RocketAnalyse()
{

}

//�������캯��
Bit_RocketAnalyse::Bit_RocketAnalyse( const Bit_RocketAnalyse &Bit_Rock )
{
	US_ = Bit_Rock.US_;
}


//�������=������
Bit_RocketAnalyse & Bit_RocketAnalyse::operator=( const Bit_RocketAnalyse &Bit_Rock )
{
	if ( this != &Bit_Rock )
	{
		US_ = Bit_Rock.US_;
	}
	return *this;
}

//������Ƭ���٣�Gurney��ʽ��
// ���յ�ЧӦѧ��-����ɽ-������ҵ������ P78
double Bit_RocketAnalyse::ComputeFragmentVelocityViaGurney( WarheadPowerAnalysisData &WarheadData , ChargeData &ChargeD , Bit_UnitSystem &USForVelocity ) const
{
	//���㱬ը�غ�ϵ��
	double ExplosiveLoadCoefficient = WarheadData.Get_ChargeMassClylinder() / WarheadData.Get_ShellMassClylinder();
	//����װҩ�������
	Bit_PowerAnalysisBase *TheBit_PowerAnalysisBase = new Bit_PowerAnalysisBase( USForVelocity );
	double ChargeGurneyEnergy = TheBit_PowerAnalysisBase->ComputeGurneyEnergy( 1 , ChargeD );
	delete TheBit_PowerAnalysisBase;
	return ChargeGurneyEnergy * sqrt( ExplosiveLoadCoefficient / ( 1 + 0.5 * ExplosiveLoadCoefficient ) );
}

//�ٶ�˥������Ƭʣ���ٶ�(FragmentVelocity:��Ƭ���٣�FlyDistance����Ƭ���о��룻AttenuationCoefficient���ٶ�˥��ϵ��)-cm/s
// ���յ�ЧӦѧ��-����ɽ-������ҵ������ P87
double Bit_RocketAnalyse::ComputeFragmentVelocityAttenuation( double &FragmentVelocity , double &FlyDistance , double &AttenuationCoefficient ) const
{
	return FragmentVelocity * exp( - AttenuationCoefficient * FlyDistance );
}

//�ٶ�˥��ϵ��(ResistanceCoefficient����������ϵ����LocalAirDencity�����ؿ����ܶȣ�FragmentFrontalArea����Ƭչ�������FragmentMass����Ƭ����)-1/m
// ���յ�ЧӦѧ��-����ɽ-������ҵ������ P88
double Bit_RocketAnalyse::ComputeVelocityAttenuationCoefficient( double &ResistanceCoefficient , double &LocalAirDencity , double &FragmentFrontalArea , double &FragmentMass , Bit_UnitSystem &US )const
{
	return ResistanceCoefficient * LocalAirDencity * FragmentFrontalArea / 2 / ( FragmentMass * US.Get_MassCoefficient() / 1000 );
}

//���ؿ����ܶ�(AboveSeaLevel�����θ߶�)-kg/m^3
// ���յ�ЧӦѧ��-����ɽ-������ҵ������ P90
double Bit_RocketAnalyse::ComputeLocalAirDensity( double &AboveSeaLevel , Bit_UnitSystem &US ) const
{
	if ( AboveSeaLevel * US.Get_LengthCoefficient() / 1000000 < 11 || abs( AboveSeaLevel  * US.Get_LengthCoefficient() / 1000000 - 11 ) < 0.00000000001 )
	{
		return 1.226 * pow( (1 - AboveSeaLevel * US.Get_LengthCoefficient() / 1000000 / 44.308) , 4.2258 );
	} 
	else
	{
		return 1.226 * 0.279 * exp( -( AboveSeaLevel * US.Get_LengthCoefficient() / 1000000 - 11 ) / 6.318 );
	}
}

//��Ƭչ�����(ShapeCoefficient:��״ϵ����FragmentMass����Ƭ����)
// ���յ�ЧӦѧ��-����ɽ-������ҵ������ P90
double Bit_RocketAnalyse::ComputeFragmentFrontalArea( double &ShapeCoefficient , double &FragmentMass , Bit_UnitSystem &US ) const
{
	return ShapeCoefficient * pow( FragmentMass * US.Get_MassCoefficient() / 1000 , 2.0 / 3.0 );
}




//********************�����CEP�Ļ������Ŀ��ƽ������׼��******************//
//������׼����Ŀ������ϵ��λ�ã�����CEP��
//AimPointWithoutCEP����׼����Ŀ������ϵ�����꣨δ��CEP����
CoordinatesPosition Bit_RocketAnalyse::AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure ) const
{
	//��CEP�����׼ƫ��
	double stdev = RockDataStructure.Get_RocketCEP() / 1.1774;
	//�����Ƶ�ƽ���ϵ���׼��
	HAE_HitPointAnalysis *HPA = new HAE_HitPointAnalysis();
	CoordinatesPosition APInGuidePlane = HPA->ComputeAimPositionOnGuide( AimPointWithoutCEP , RockDataStructure.Get_RocketYawAngle() , RockDataStructure.Get_RocketPitchingAngle() );
	//�����õ��Ƶ�ƽ������׼�㣨��CEP��
	CoordinatesPosition APGPWithCEP = CoordinatesPosition( 0 , 0 , 0 );
	ProbabilityAndRandom *PARInRock = new ProbabilityAndRandom();
	//���0-1���������
	double Randomof01[4] = { 0 };
	bool Generate = PARInRock->SampleOnSampleNumber( 4 , Randomof01 );
	//��ά��̬�ֲ������cos
	double Randomcos = PARInRock->Get2DStandardNormalDistributionRandom_cos( Randomof01[0] , Randomof01[1] );
	//��ά��̬�ֲ������sin
	double Randomsin = PARInRock->Get2DStandardNormalDistributionRandom_sin( Randomof01[2] , Randomof01[3] );
	//�����CEP��׼��(�Ƶ�ƽ��)
	APGPWithCEP.Set_z( APInGuidePlane.Get_z() );
	APGPWithCEP.Set_x( APInGuidePlane.Get_x() + Randomcos * stdev );
	APGPWithCEP.Set_y( APInGuidePlane.Get_y() + Randomsin * stdev );
	//�Ƶ�ƽ���ϴ�CEP��׼��ת��Ŀ������ϵ��
	APGPWithCEP.RotateAngleByYAxis( -RockDataStructure.Get_RocketPitchingAngle() );
	APGPWithCEP.RotateAngleByZAxis( -RockDataStructure.Get_RocketYawAngle() );
	delete PARInRock;
	delete HPA;
	return APGPWithCEP;
}



////������׼����Ŀ������ϵ��λ�ã�����CEP��NRotate��
////AimPointWithoutCEP����׼����Ŀ������ϵ�����꣨δ��CEP����
//CoordinatesPosition Bit_RocketAnalyse::AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure ) const
//{
//	//��CEP�����׼ƫ��
//	double stdev = RockDataStructure.Get_RocketCEP() / 1.1774;
//	//����CEP����׼������
//	CoordinatesPosition APGPWithCEP = CoordinatesPosition( 0 , 0 , 0 );
//	//�������
//	ProbabilityAndRandom *PARInRock = new ProbabilityAndRandom();
//	//���0-1���������
//	double Randomof01[4] = { 0 };
//	bool Generate = PARInRock->SampleOnSampleNumber( 4 , Randomof01 );
//	//��ά��̬�ֲ������cos
//	double Randomcos = PARInRock->Get2DStandardNormalDistributionRandom_cos( Randomof01[0] , Randomof01[1] );
//	//��ά��̬�ֲ������sin
//	double Randomsin = PARInRock->Get2DStandardNormalDistributionRandom_sin( Randomof01[2] , Randomof01[3] );
//	//�����CEP��׼��(�Ƶ�ƽ��)
//	APGPWithCEP.Set_z( AimPointWithoutCEP.Get_z() );
//	APGPWithCEP.Set_x( AimPointWithoutCEP.Get_x() + Randomcos * stdev );
//	APGPWithCEP.Set_y( AimPointWithoutCEP.Get_y() + Randomsin * stdev );
//	delete PARInRock;
//	return APGPWithCEP;
//}


//��������õ�ը������
//AimPointWithCEP����׼�㣨��CEP����Ŀ������ϵλ�ã�BurstHighE������ը��������BurstHighD������ը�߷���
CoordinatesPosition Bit_RocketAnalyse::BurstPoint( CoordinatesPosition &AimPointWithCEP , double &BurstHighE , double &BurstHighD , Bit_RocketDataStructure &RockDataStructure ) const
{
	//ը�����꣬���ڷ���
	CoordinatesPosition BP = CoordinatesPosition ( 0 , 0 , 0 );
	//��̬�ֲ����������ը��
	ProbabilityAndRandom *PA = new ProbabilityAndRandom();
	//��̬�ֲ��������������ը��
	double RanStd = PA->Get1DStandardNormalDistributionRandom(48);
	double BurstHigh = BurstHighE + RanStd * BurstHighD;
	//����ը������
	if ( abs(RockDataStructure.Get_RocketPitchingAngle()) < 0.00000001 || abs( RockDataStructure.Get_RocketPitchingAngle() - pi / 2 ) < 0.00000001 )
	{
		BP.Set_x( AimPointWithCEP.Get_x() );
		BP.Set_y( AimPointWithCEP.Get_y() );
		BP.Set_z( BurstHigh );
	} 
	else
	{
		BP.Set_x( AimPointWithCEP.Get_x() + BurstHigh / tan( RockDataStructure.Get_RocketPitchingAngle() ) * cos( RockDataStructure.Get_RocketYawAngle() ));
		BP.Set_y( AimPointWithCEP.Get_y() + BurstHigh / tan( RockDataStructure.Get_RocketPitchingAngle() ) * sin( RockDataStructure.Get_RocketYawAngle() ));
		BP.Set_z( BurstHigh );
	}
	return BP;
}
