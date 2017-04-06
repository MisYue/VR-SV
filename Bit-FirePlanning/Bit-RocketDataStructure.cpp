#include "Bit-RocketDataStructure.h"

//���캯����ʼ��
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

//�������캯��
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

//�������=������
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

//���û����IDֵ
void Bit_RocketDataStructure::Set_RocketID( int &Rock_ID )
{
	id_ = Rock_ID;
}

//���û������λ��
void Bit_RocketDataStructure::Set_RocketUS( Bit_UnitSystem &Rock_US )
{
	US_ = Rock_US;
}

//���û����������
void Bit_RocketDataStructure::Set_RocketPitchingAngle( double &Rock_PitchingAngle )
{
	PitchingAngle_ = Rock_PitchingAngle;
}

//���û����ƫ����
void Bit_RocketDataStructure::Set_RocketYawAngle( double &Rock_YawAngle )
{
	YawAngle_ = Rock_YawAngle;
}

//���û����ս������̬��ɢ��
void Bit_RocketDataStructure::Set_WarheadStaticDisporaAngle( double &Rock_WarheadStaticDisporaAngle )
{
	WarheadStaticDisporaAngle_ = Rock_WarheadStaticDisporaAngle;
}

//���û����ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
void Bit_RocketDataStructure::Set_WarheadStaticAngleCentralLine( double &Rock_WarheadStaticAngleCentralLine )
{
	WarheadStaticAngleCentralLine_ = Rock_WarheadStaticAngleCentralLine;
}

//���û�����ٶ�
void Bit_RocketDataStructure::Set_RocketVelocity( double &Rock_Velocity )
{
	RocketVelocity_ = Rock_Velocity;
}

//���û����CEP
void Bit_RocketDataStructure::Set_RocketCEP( double &Rock_CEP )
{
	RocketCEP_ = Rock_CEP;
}


//�õ������ID
int Bit_RocketDataStructure::Get_RocketID( void ) const
{
	return id_;
}
//�õ��������λ��
Bit_UnitSystem Bit_RocketDataStructure::Get_RocketUS( void ) const
{
	return US_;
}

//�õ������������
double Bit_RocketDataStructure::Get_RocketPitchingAngle( void ) const
{
	return PitchingAngle_;
}

//�õ������ƫ����
double Bit_RocketDataStructure::Get_RocketYawAngle( void ) const
{
	return YawAngle_;
}

//�õ������ս������̬��ɢ��
double Bit_RocketDataStructure::Get_WarheadStaticDisporaAngle( void ) const
{
	return WarheadStaticDisporaAngle_;
}

//�õ������ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
double Bit_RocketDataStructure::Get_WarheadStaticAngleCentralLine( void ) const
{
	return WarheadStaticAngleCentralLine_;
}

//�õ�������ٶ�
double Bit_RocketDataStructure::Get_RocketVelocity( void )const
{
	return RocketVelocity_;
}

//�õ������CEP
double Bit_RocketDataStructure::Get_RocketCEP( void ) const
{
	return RocketCEP_;
}
