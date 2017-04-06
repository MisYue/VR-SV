#include "Bit_RocketAnalyse.h"



//空构造函数
Bit_RocketAnalyse::Bit_RocketAnalyse()
{

}

//构造函数初始化
Bit_RocketAnalyse::Bit_RocketAnalyse( Bit_UnitSystem &US )
{
	US_ = US;
}

//析构函数
Bit_RocketAnalyse::~Bit_RocketAnalyse()
{

}

//拷贝构造函数
Bit_RocketAnalyse::Bit_RocketAnalyse( const Bit_RocketAnalyse &Bit_Rock )
{
	US_ = Bit_Rock.US_;
}


//运算符“=”重载
Bit_RocketAnalyse & Bit_RocketAnalyse::operator=( const Bit_RocketAnalyse &Bit_Rock )
{
	if ( this != &Bit_Rock )
	{
		US_ = Bit_Rock.US_;
	}
	return *this;
}

//计算破片初速（Gurney公式）
// 《终点效应学》-王树山-国防工业出版社 P78
double Bit_RocketAnalyse::ComputeFragmentVelocityViaGurney( WarheadPowerAnalysisData &WarheadData , ChargeData &ChargeD , Bit_UnitSystem &USForVelocity ) const
{
	//计算爆炸载荷系数
	double ExplosiveLoadCoefficient = WarheadData.Get_ChargeMassClylinder() / WarheadData.Get_ShellMassClylinder();
	//计算装药格尼比能
	Bit_PowerAnalysisBase *TheBit_PowerAnalysisBase = new Bit_PowerAnalysisBase( USForVelocity );
	double ChargeGurneyEnergy = TheBit_PowerAnalysisBase->ComputeGurneyEnergy( 1 , ChargeD );
	delete TheBit_PowerAnalysisBase;
	return ChargeGurneyEnergy * sqrt( ExplosiveLoadCoefficient / ( 1 + 0.5 * ExplosiveLoadCoefficient ) );
}

//速度衰减后破片剩余速度(FragmentVelocity:破片初速；FlyDistance：破片飞行距离；AttenuationCoefficient：速度衰减系数)-cm/s
// 《终点效应学》-王树山-国防工业出版社 P87
double Bit_RocketAnalyse::ComputeFragmentVelocityAttenuation( double &FragmentVelocity , double &FlyDistance , double &AttenuationCoefficient ) const
{
	return FragmentVelocity * exp( - AttenuationCoefficient * FlyDistance );
}

//速度衰减系数(ResistanceCoefficient：气动阻力系数；LocalAirDencity：当地空气密度；FragmentFrontalArea：破片展现面积；FragmentMass：破片质量)-1/m
// 《终点效应学》-王树山-国防工业出版社 P88
double Bit_RocketAnalyse::ComputeVelocityAttenuationCoefficient( double &ResistanceCoefficient , double &LocalAirDencity , double &FragmentFrontalArea , double &FragmentMass , Bit_UnitSystem &US )const
{
	return ResistanceCoefficient * LocalAirDencity * FragmentFrontalArea / 2 / ( FragmentMass * US.Get_MassCoefficient() / 1000 );
}

//当地空气密度(AboveSeaLevel：海拔高度)-kg/m^3
// 《终点效应学》-王树山-国防工业出版社 P90
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

//破片展现面积(ShapeCoefficient:形状系数；FragmentMass：破片质量)
// 《终点效应学》-王树山-国防工业出版社 P90
double Bit_RocketAnalyse::ComputeFragmentFrontalArea( double &ShapeCoefficient , double &FragmentMass , Bit_UnitSystem &US ) const
{
	return ShapeCoefficient * pow( FragmentMass * US.Get_MassCoefficient() / 1000 , 2.0 / 3.0 );
}




//********************计算带CEP的火箭弹在目标平面上瞄准点******************//
//计算瞄准点在目标坐标系内位置（考虑CEP）
//AimPointWithoutCEP：瞄准点在目标坐标系内坐标（未带CEP）；
CoordinatesPosition Bit_RocketAnalyse::AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure ) const
{
	//由CEP计算标准偏差
	double stdev = RockDataStructure.Get_RocketCEP() / 1.1774;
	//计算制导平面上的瞄准点
	HAE_HitPointAnalysis *HPA = new HAE_HitPointAnalysis();
	CoordinatesPosition APInGuidePlane = HPA->ComputeAimPositionOnGuide( AimPointWithoutCEP , RockDataStructure.Get_RocketYawAngle() , RockDataStructure.Get_RocketPitchingAngle() );
	//抽样得到制导平面上瞄准点（带CEP）
	CoordinatesPosition APGPWithCEP = CoordinatesPosition( 0 , 0 , 0 );
	ProbabilityAndRandom *PARInRock = new ProbabilityAndRandom();
	//存放0-1随机数数组
	double Randomof01[4] = { 0 };
	bool Generate = PARInRock->SampleOnSampleNumber( 4 , Randomof01 );
	//二维正态分布随机数cos
	double Randomcos = PARInRock->Get2DStandardNormalDistributionRandom_cos( Randomof01[0] , Randomof01[1] );
	//二维正态分布随机数sin
	double Randomsin = PARInRock->Get2DStandardNormalDistributionRandom_sin( Randomof01[2] , Randomof01[3] );
	//计算带CEP瞄准点(制导平面)
	APGPWithCEP.Set_z( APInGuidePlane.Get_z() );
	APGPWithCEP.Set_x( APInGuidePlane.Get_x() + Randomcos * stdev );
	APGPWithCEP.Set_y( APInGuidePlane.Get_y() + Randomsin * stdev );
	//制导平面上带CEP瞄准点转到目标坐标系内
	APGPWithCEP.RotateAngleByYAxis( -RockDataStructure.Get_RocketPitchingAngle() );
	APGPWithCEP.RotateAngleByZAxis( -RockDataStructure.Get_RocketYawAngle() );
	delete PARInRock;
	delete HPA;
	return APGPWithCEP;
}



////计算瞄准点在目标坐标系内位置（考虑CEP，NRotate）
////AimPointWithoutCEP：瞄准点在目标坐标系内坐标（未带CEP）；
//CoordinatesPosition Bit_RocketAnalyse::AimPointInAim( CoordinatesPosition &AimPointWithoutCEP , Bit_RocketDataStructure &RockDataStructure ) const
//{
//	//由CEP计算标准偏差
//	double stdev = RockDataStructure.Get_RocketCEP() / 1.1774;
//	//考虑CEP后瞄准点坐标
//	CoordinatesPosition APGPWithCEP = CoordinatesPosition( 0 , 0 , 0 );
//	//随机抽样
//	ProbabilityAndRandom *PARInRock = new ProbabilityAndRandom();
//	//存放0-1随机数数组
//	double Randomof01[4] = { 0 };
//	bool Generate = PARInRock->SampleOnSampleNumber( 4 , Randomof01 );
//	//二维正态分布随机数cos
//	double Randomcos = PARInRock->Get2DStandardNormalDistributionRandom_cos( Randomof01[0] , Randomof01[1] );
//	//二维正态分布随机数sin
//	double Randomsin = PARInRock->Get2DStandardNormalDistributionRandom_sin( Randomof01[2] , Randomof01[3] );
//	//计算带CEP瞄准点(制导平面)
//	APGPWithCEP.Set_z( AimPointWithoutCEP.Get_z() );
//	APGPWithCEP.Set_x( AimPointWithoutCEP.Get_x() + Randomcos * stdev );
//	APGPWithCEP.Set_y( AimPointWithoutCEP.Get_y() + Randomsin * stdev );
//	delete PARInRock;
//	return APGPWithCEP;
//}


//抽样计算得到炸点坐标
//AimPointWithCEP：瞄准点（带CEP）在目标坐标系位置；BurstHighE：引信炸高期望；BurstHighD：引信炸高方差
CoordinatesPosition Bit_RocketAnalyse::BurstPoint( CoordinatesPosition &AimPointWithCEP , double &BurstHighE , double &BurstHighD , Bit_RocketDataStructure &RockDataStructure ) const
{
	//炸点坐标，用于返回
	CoordinatesPosition BP = CoordinatesPosition ( 0 , 0 , 0 );
	//正态分布随机数计算炸高
	ProbabilityAndRandom *PA = new ProbabilityAndRandom();
	//正态分布随机数抽样计算炸高
	double RanStd = PA->Get1DStandardNormalDistributionRandom(48);
	double BurstHigh = BurstHighE + RanStd * BurstHighD;
	//计算炸点坐标
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
