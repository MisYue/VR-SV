#include "Bit-FragmentDataStructure.h"


Bit_FragmentDataStructure::Bit_FragmentDataStructure()
{

}

//���캯����ʼ��
Bit_FragmentDataStructure::Bit_FragmentDataStructure( int &id , Bit_UnitSystem &US , double &Mass , double &StaticDisporaAngle , double &StaticDirectonalAngle , 
	double &DynamicCircleAngle , double &DynamicDirectionalAngle , double &FlyDistance , double &FragmentVelocity , double &FragmentDynamicVelocity ,
	CoordinatesPosition &FragmentPositionInRocketCoordinate , double &FragmentResidualVelocity )
{
	id_ = id;
	US_ = US;
	Mass_ = Mass;
	StaticDisporaAngle_ = StaticDisporaAngle;
	StaticDirectonalAngle_ = StaticDirectonalAngle;
	FlyDistance_ = FlyDistance;
	DynamicCircleAngle_ = DynamicCircleAngle;
	DynamicDirectionalAngle_ = DynamicDirectionalAngle;
	FragmentPositionInRocketCoordinate_ = FragmentPositionInRocketCoordinate;
	FragmentVelocity_ = FragmentVelocity;
	FragmentDynamicVelocity_ = FragmentDynamicVelocity;
	FragmentResidualVelocity_ = FragmentResidualVelocity;
}

//�������캯��
Bit_FragmentDataStructure::Bit_FragmentDataStructure( const Bit_FragmentDataStructure &Bit_Frag )
{
	id_ = Bit_Frag.id_;
	US_ = Bit_Frag.US_;
	Mass_ = Bit_Frag.Mass_;
	StaticDisporaAngle_ = Bit_Frag.StaticDisporaAngle_;
	StaticDirectonalAngle_ = Bit_Frag.StaticDirectonalAngle_;
	FlyDistance_ = Bit_Frag.FlyDistance_;
	DynamicCircleAngle_ = Bit_Frag.DynamicCircleAngle_;
	DynamicDirectionalAngle_ = Bit_Frag.DynamicDirectionalAngle_;
	FragmentPositionInRocketCoordinate_ = Bit_Frag.FragmentPositionInRocketCoordinate_;
	FragmentVelocity_ = Bit_Frag.FragmentVelocity_;
	FragmentDynamicVelocity_ = Bit_Frag.FragmentDynamicVelocity_;
	FragmentResidualVelocity_ = Bit_Frag.FragmentResidualVelocity_;
}

//�������=������
Bit_FragmentDataStructure & Bit_FragmentDataStructure::operator=( const Bit_FragmentDataStructure &Bit_Frag )
{
	if ( this != & Bit_Frag )
	{
	    id_ = Bit_Frag.id_;
		US_ = Bit_Frag.US_;
		Mass_ = Bit_Frag.Mass_;
		StaticDisporaAngle_ = Bit_Frag.StaticDisporaAngle_;
		StaticDirectonalAngle_ = Bit_Frag.StaticDirectonalAngle_;
		FlyDistance_ = Bit_Frag.FlyDistance_;
		DynamicCircleAngle_ = Bit_Frag.DynamicCircleAngle_;
		DynamicDirectionalAngle_ = Bit_Frag.DynamicDirectionalAngle_;
		FragmentPositionInRocketCoordinate_ = Bit_Frag.FragmentPositionInRocketCoordinate_;
		FragmentVelocity_ = Bit_Frag.FragmentVelocity_;
		FragmentDynamicVelocity_ = Bit_Frag.FragmentDynamicVelocity_;
		FragmentResidualVelocity_ = Bit_Frag.FragmentResidualVelocity_;
	}
	return *this;
}


Bit_FragmentDataStructure::~Bit_FragmentDataStructure()
{

}

//������ƬIDֵ
void Bit_FragmentDataStructure::Set_FragmentID( int Frag_ID ) 
{
	id_ = Frag_ID;
}

//���õ�λ��
void Bit_FragmentDataStructure::Set_FragmentUS( Bit_UnitSystem &Frag_US )
{
	US_ = Frag_US;
}

//������Ƭ����
void Bit_FragmentDataStructure::Set_Mass( double &Frag_Mass )
{
	Mass_ = Frag_Mass;
}

//������Ƭ��̬��ɢ��
void Bit_FragmentDataStructure::Set_StaticDisporaAngle( double &Frag_StaticDisporaAngle )
{
	StaticDisporaAngle_ = Frag_StaticDisporaAngle;
}

//������Ƭ��̬�����
void Bit_FragmentDataStructure::Set_StaticDirectonalAngle( double &Frag_StaticDirectonalAngle )
{
	StaticDirectonalAngle_ = Frag_StaticDirectonalAngle;
}

//������Ƭ��̬�����
void Bit_FragmentDataStructure::Set_DynamicCircleAngle( double Frag_DynamicCircleAngle )
{
	DynamicCircleAngle_ = Frag_DynamicCircleAngle;
}

//������Ƭ��̬�����
void Bit_FragmentDataStructure::Set_DynamicDirectionalAngle( double &Frag_DynamicDirectionalAngle )
{
	DynamicDirectionalAngle_ = Frag_DynamicDirectionalAngle;
}

//������Ƭ���о���
void Bit_FragmentDataStructure::Set_FlyDistance( double &Frag_FlyDistance )
{
	FlyDistance_ = Frag_FlyDistance;
}

//������Ƭ����
void Bit_FragmentDataStructure::Set_FragmentVelocity( double &Frag_FragmentVelocity )
{
	FragmentVelocity_ = Frag_FragmentVelocity;
}

//������Ƭ��̬�����ٶ�
void Bit_FragmentDataStructure::Set_FragmentDynamicVelocity( double &Frag_FragmentDynamicVelocity )
{
	FragmentDynamicVelocity_ = Frag_FragmentDynamicVelocity;
}

//������Ƭ�ڵ�������ϵ������
void Bit_FragmentDataStructure::Set_FragmentPositionInRocketCoordinate( CoordinatesPosition &Frag_FragmentPositionInRocketCoordinate )
{
	FragmentPositionInRocketCoordinate_ = Frag_FragmentPositionInRocketCoordinate;
}

//������Ƭʣ���ٶ�
void Bit_FragmentDataStructure::Set_FragmentResidualVelocity( double &Frag_FragmentResidualVelocity )
{
	FragmentResidualVelocity_ = Frag_FragmentResidualVelocity;
}



//�õ���ƤID
int Bit_FragmentDataStructure::Get_FragmentID( void ) const
{
	return id_; 
}

//�õ���λ��
Bit_UnitSystem Bit_FragmentDataStructure::Get_FragmentUS( void ) const
{
	return US_;
}

//�õ���Ƭ��̬��ɢ��
double Bit_FragmentDataStructure::Get_StaticDisporaAngle( void ) const
{
	return StaticDisporaAngle_;
}

//�õ���Ƭ��̬�����
double Bit_FragmentDataStructure::Get_StaticDirectonalAngle( void ) const
{
	return StaticDirectonalAngle_;
}

//�õ���Ƭ��̬�����
double Bit_FragmentDataStructure::Get_DynamicCircleAngle( void ) 
{
	return DynamicCircleAngle_;
}

//�õ���Ƭ��̬�����
double Bit_FragmentDataStructure::Get_DynamicDirectionalAngle( void ) const
{
	return DynamicDirectionalAngle_;
}

//�õ���Ƭ���о���
double Bit_FragmentDataStructure::Get_FlyDistance( void ) const
{
	return FlyDistance_;
}

//�õ���Ƭ����
double Bit_FragmentDataStructure::Get_FragmentVelocity( void )const
{
	return FragmentVelocity_;
}

//�õ���Ƭ��̬�����ٶ�
double Bit_FragmentDataStructure::Get_FragmentDynamicVelocity( void )const
{
	return FragmentDynamicVelocity_;
}

//�õ���Ƭ�ڵ�������ϵ������
CoordinatesPosition Bit_FragmentDataStructure::Get_FragmentPositionInRocketCoordinate( void ) const
{
	return FragmentPositionInRocketCoordinate_;
}

//�õ���Ƭ����
double Bit_FragmentDataStructure::Get_Mass( void ) const
{
	return Mass_;
}

//�õ���Ƭʣ���ٶ�
double Bit_FragmentDataStructure::Get_FragmentResidualVelocity( void ) const
{
	return FragmentResidualVelocity_;
}


