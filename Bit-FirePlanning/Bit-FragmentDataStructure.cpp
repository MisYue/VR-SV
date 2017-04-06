#include "Bit-FragmentDataStructure.h"


Bit_FragmentDataStructure::Bit_FragmentDataStructure()
{

}

//构造函数初始化
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

//拷贝构造函数
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

//运算符“=”重载
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

//设置破片ID值
void Bit_FragmentDataStructure::Set_FragmentID( int Frag_ID ) 
{
	id_ = Frag_ID;
}

//设置单位制
void Bit_FragmentDataStructure::Set_FragmentUS( Bit_UnitSystem &Frag_US )
{
	US_ = Frag_US;
}

//设置破片质量
void Bit_FragmentDataStructure::Set_Mass( double &Frag_Mass )
{
	Mass_ = Frag_Mass;
}

//设置破片静态飞散角
void Bit_FragmentDataStructure::Set_StaticDisporaAngle( double &Frag_StaticDisporaAngle )
{
	StaticDisporaAngle_ = Frag_StaticDisporaAngle;
}

//设置破片静态方向角
void Bit_FragmentDataStructure::Set_StaticDirectonalAngle( double &Frag_StaticDirectonalAngle )
{
	StaticDirectonalAngle_ = Frag_StaticDirectonalAngle;
}

//设置破片动态周向角
void Bit_FragmentDataStructure::Set_DynamicCircleAngle( double Frag_DynamicCircleAngle )
{
	DynamicCircleAngle_ = Frag_DynamicCircleAngle;
}

//设置破片动态方向角
void Bit_FragmentDataStructure::Set_DynamicDirectionalAngle( double &Frag_DynamicDirectionalAngle )
{
	DynamicDirectionalAngle_ = Frag_DynamicDirectionalAngle;
}

//设置破片飞行距离
void Bit_FragmentDataStructure::Set_FlyDistance( double &Frag_FlyDistance )
{
	FlyDistance_ = Frag_FlyDistance;
}

//设置破片初速
void Bit_FragmentDataStructure::Set_FragmentVelocity( double &Frag_FragmentVelocity )
{
	FragmentVelocity_ = Frag_FragmentVelocity;
}

//设置破片动态飞行速度
void Bit_FragmentDataStructure::Set_FragmentDynamicVelocity( double &Frag_FragmentDynamicVelocity )
{
	FragmentDynamicVelocity_ = Frag_FragmentDynamicVelocity;
}

//设置破片在弹体坐标系内坐标
void Bit_FragmentDataStructure::Set_FragmentPositionInRocketCoordinate( CoordinatesPosition &Frag_FragmentPositionInRocketCoordinate )
{
	FragmentPositionInRocketCoordinate_ = Frag_FragmentPositionInRocketCoordinate;
}

//设置破片剩余速度
void Bit_FragmentDataStructure::Set_FragmentResidualVelocity( double &Frag_FragmentResidualVelocity )
{
	FragmentResidualVelocity_ = Frag_FragmentResidualVelocity;
}



//得到破皮ID
int Bit_FragmentDataStructure::Get_FragmentID( void ) const
{
	return id_; 
}

//得到单位制
Bit_UnitSystem Bit_FragmentDataStructure::Get_FragmentUS( void ) const
{
	return US_;
}

//得到破片静态飞散角
double Bit_FragmentDataStructure::Get_StaticDisporaAngle( void ) const
{
	return StaticDisporaAngle_;
}

//得到破片静态方向角
double Bit_FragmentDataStructure::Get_StaticDirectonalAngle( void ) const
{
	return StaticDirectonalAngle_;
}

//得到破片动态周向角
double Bit_FragmentDataStructure::Get_DynamicCircleAngle( void ) 
{
	return DynamicCircleAngle_;
}

//得到破片动态方向角
double Bit_FragmentDataStructure::Get_DynamicDirectionalAngle( void ) const
{
	return DynamicDirectionalAngle_;
}

//得到破片飞行距离
double Bit_FragmentDataStructure::Get_FlyDistance( void ) const
{
	return FlyDistance_;
}

//得到破片初速
double Bit_FragmentDataStructure::Get_FragmentVelocity( void )const
{
	return FragmentVelocity_;
}

//得到破片动态飞行速度
double Bit_FragmentDataStructure::Get_FragmentDynamicVelocity( void )const
{
	return FragmentDynamicVelocity_;
}

//得到破片在弹体坐标系内坐标
CoordinatesPosition Bit_FragmentDataStructure::Get_FragmentPositionInRocketCoordinate( void ) const
{
	return FragmentPositionInRocketCoordinate_;
}

//得到破片质量
double Bit_FragmentDataStructure::Get_Mass( void ) const
{
	return Mass_;
}

//得到破片剩余速度
double Bit_FragmentDataStructure::Get_FragmentResidualVelocity( void ) const
{
	return FragmentResidualVelocity_;
}


