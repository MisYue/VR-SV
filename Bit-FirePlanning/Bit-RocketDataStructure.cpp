#include "Bit-RocketDataStructure.h"

//构造函数初始化
Bit_RocketDataStructure::Bit_RocketDataStructure( int &id , Bit_UnitSystem &US , double &PitchingAngle , double &YawAngle , double &WarheadStaticDisporaAngle , double &WarheadStaticAngleCentralLine ,
	double &RocketVelocity , double &RocketCEP )
{
	id_ = id;
	US_ = US;
	PitchingAngle_ = PitchingAngle;
	YawAngle_ = YawAngle;
	WarheadStaticDisporaAngle_ = WarheadStaticDisporaAngle;
	WarheadStaticAngleCentralLine_ = WarheadStaticAngleCentralLine;
	RocketVelocity_ = RocketVelocity;
	RocketCEP_ = RocketCEP;
}


Bit_RocketDataStructure::~Bit_RocketDataStructure()
{

}

//拷贝构造函数
Bit_RocketDataStructure::Bit_RocketDataStructure( const Bit_RocketDataStructure &Bit_Rock )
{
	id_ = Bit_Rock.id_;
	US_ = Bit_Rock.US_;
	PitchingAngle_ = Bit_Rock.PitchingAngle_;
	YawAngle_ = Bit_Rock.YawAngle_;
	WarheadStaticDisporaAngle_ = Bit_Rock.WarheadStaticDisporaAngle_;
	WarheadStaticAngleCentralLine_ = Bit_Rock.WarheadStaticAngleCentralLine_;
	RocketVelocity_ = Bit_Rock.RocketVelocity_;
	RocketCEP_ = Bit_Rock.RocketCEP_;
}

//运算符“=”重载
Bit_RocketDataStructure & Bit_RocketDataStructure::operator=( const Bit_RocketDataStructure &Bit_Rock )
{
	if ( this != & Bit_Rock )
	{
		id_ = Bit_Rock.id_;
		US_ = Bit_Rock.US_;
		PitchingAngle_ = Bit_Rock.PitchingAngle_;
		YawAngle_ = Bit_Rock.YawAngle_;
		WarheadStaticDisporaAngle_ = Bit_Rock.WarheadStaticDisporaAngle_;
		WarheadStaticAngleCentralLine_ = Bit_Rock.WarheadStaticAngleCentralLine_;
		RocketVelocity_ = Bit_Rock.RocketVelocity_;
		RocketCEP_ = Bit_Rock.RocketCEP_;
	}
	return *this;
}

//设置火箭弹ID值
void Bit_RocketDataStructure::Set_RocketID( int &Rock_ID )
{
	id_ = Rock_ID;
}

//设置火箭弹单位制
void Bit_RocketDataStructure::Set_RocketUS( Bit_UnitSystem &Rock_US )
{
	US_ = Rock_US;
}

//设置火箭弹俯仰角
void Bit_RocketDataStructure::Set_RocketPitchingAngle( double &Rock_PitchingAngle )
{
	PitchingAngle_ = Rock_PitchingAngle;
}

//设置火箭弹偏航角
void Bit_RocketDataStructure::Set_RocketYawAngle( double &Rock_YawAngle )
{
	YawAngle_ = Rock_YawAngle;
}

//设置火箭弹战斗部静态飞散角
void Bit_RocketDataStructure::Set_WarheadStaticDisporaAngle( double &Rock_WarheadStaticDisporaAngle )
{
	WarheadStaticDisporaAngle_ = Rock_WarheadStaticDisporaAngle;
}

//设置火箭弹战斗部静态飞散角分布中心线与弹体坐标系x轴夹角
void Bit_RocketDataStructure::Set_WarheadStaticAngleCentralLine( double &Rock_WarheadStaticAngleCentralLine )
{
	WarheadStaticAngleCentralLine_ = Rock_WarheadStaticAngleCentralLine;
}

//设置火箭弹速度
void Bit_RocketDataStructure::Set_RocketVelocity( double &Rock_Velocity )
{
	RocketVelocity_ = Rock_Velocity;
}

//设置火箭弹CEP
void Bit_RocketDataStructure::Set_RocketCEP( double &Rock_CEP )
{
	RocketCEP_ = Rock_CEP;
}


//得到火箭弹ID
int Bit_RocketDataStructure::Get_RocketID( void ) const
{
	return id_;
}
//得到火箭弹单位制
Bit_UnitSystem Bit_RocketDataStructure::Get_RocketUS( void ) const
{
	return US_;
}

//得到火箭弹俯仰角
double Bit_RocketDataStructure::Get_RocketPitchingAngle( void ) const
{
	return PitchingAngle_;
}

//得到火箭弹偏航角
double Bit_RocketDataStructure::Get_RocketYawAngle( void ) const
{
	return YawAngle_;
}

//得到火箭弹战斗部静态飞散角
double Bit_RocketDataStructure::Get_WarheadStaticDisporaAngle( void ) const
{
	return WarheadStaticDisporaAngle_;
}

//得到火箭弹战斗部静态飞散角分布中心线与弹体坐标系x轴夹角
double Bit_RocketDataStructure::Get_WarheadStaticAngleCentralLine( void ) const
{
	return WarheadStaticAngleCentralLine_;
}

//得到火箭弹速度
double Bit_RocketDataStructure::Get_RocketVelocity( void )const
{
	return RocketVelocity_;
}

//得到火箭弹CEP
double Bit_RocketDataStructure::Get_RocketCEP( void ) const
{
	return RocketCEP_;
}
