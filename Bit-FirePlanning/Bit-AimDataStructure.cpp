#include "Bit-AimDataStructure.h"

//构造函数初始化
Bit_AimDataStructure::Bit_AimDataStructure( int &id , CoordinatesPosition &HitPosition , double &Long , double &Wide ,
	int& FristNode , int& FristElement , double& N_02 , double &N_13 , double &AimLat , double &AimLon , CoordinatesPosition &AimPoint )
{
	id_ = id;
	HitPosition_ = HitPosition;
	Long_ = Long;
	Wide_ = Wide;
	FristNode_ = FristNode;
	FristElement_ = FristElement;
	N_02_ = N_02;
	N_13_ = N_13;
	AimLat_ = AimLat;
	AimLon_ = AimLon;
	AimPoint_ = AimPoint;
}

Bit_AimDataStructure::~Bit_AimDataStructure()
{

}

//拷贝构造函数
Bit_AimDataStructure::Bit_AimDataStructure( const Bit_AimDataStructure &Bit_Aim )
{
	id_ = Bit_Aim.id_;
	US_ = Bit_Aim.US_;
	HitPosition_ = Bit_Aim.HitPosition_;
	Long_ = Bit_Aim.Long_;
	Wide_ = Bit_Aim.Wide_;
	FristNode_ = Bit_Aim.FristNode_;
	FristElement_ = Bit_Aim.FristElement_;
	N_02_ = Bit_Aim.N_02_;
	N_13_ = Bit_Aim.N_13_;
	AimLat_ = Bit_Aim.AimLat_;
	AimLon_ = Bit_Aim.AimLon_;
	AimPoint_ = Bit_Aim.AimPoint_;
}

//运算符“=”重载
Bit_AimDataStructure & Bit_AimDataStructure::operator=( const Bit_AimDataStructure &Bit_Aim )
{
	if ( this != & Bit_Aim )
	{
		id_ = Bit_Aim.id_;
		US_ = Bit_Aim.US_;
		HitPosition_ = Bit_Aim.HitPosition_;
		Long_ = Bit_Aim.Long_;
		Wide_ = Bit_Aim.Wide_;
		FristNode_ = Bit_Aim.FristNode_;
		FristElement_ = Bit_Aim.FristElement_;
		N_02_ = Bit_Aim.N_02_;
		N_13_ = Bit_Aim.N_13_;
		AimLat_ = Bit_Aim.AimLat_;
		AimLon_ = Bit_Aim.AimLon_;
		AimPoint_ = Bit_Aim.AimPoint_;
	}
	return *this;
}

//设置目标ID值
void Bit_AimDataStructure::Set_AimID( int &Aim_ID )
{
	id_ = Aim_ID;
}

//设置炸点在目标坐标系内坐标
void Bit_AimDataStructure::Set_HitPosition( CoordinatesPosition &HitPositionInAim )
{
	HitPosition_ = HitPositionInAim;
}

////设置目标区域中心点坐标
//void Bit_AimDataStructure::Set_AimCenterCP( CoordinatesPosition &AimCenterCPInAim )
//{
//	AimCenterCP_ = AimCenterCPInAim;
//}

////设置目标区域四个顶点坐标
//void Bit_AimDataStructure::Set_AimArea( CoordinatesPosition AimAreaInAim[4] )
//{
//	for( int i = 0 ; i < 4 ; i++ )
//	{
//		AimArea_[i] = AimAreaInAim[i];
//	}
//}


////设置四边形单元自动划分四边形网格
//void Bit_AimDataStructure::Set_AimQuad( QuadMeshingQuad &AimQuadInAim )
//{
//	AimQuad_ = AimQuadInAim;
//}

//设置划分产生的第一个节点号
void Bit_AimDataStructure::Set_FristNode( int &FristNodeInAim )
{
	FristNode_ = FristNodeInAim;
}

//设置划分产生的第一个单元号
void Bit_AimDataStructure::Set_FristElement( int &FristElementInAim )
{
	FristElement_ = FristElementInAim;
}

//设置在0号和2号线上划分单元大小
void Bit_AimDataStructure::Set_N_02( double &N_02InAim )
{
	N_02_ = N_02InAim;
}

//设置在0号和2号线上划分单元大小
void Bit_AimDataStructure::Set_N_13( double &N_13InAim )
{
	N_13_ = N_13InAim;
}

//设置目标中心点纬度
void Bit_AimDataStructure::Set_AimLat( double &AimLatInAim )
{
	AimLat_ = AimLatInAim;
}

//设置目标中心点经度
void Bit_AimDataStructure::Set_AimLon( double &AimLonInAim )
{
	AimLon_ = AimLonInAim;
}

void Bit_AimDataStructure::Set_AimPoint( CoordinatesPosition &AimPointInAim )
{
	AimPoint_ = AimPointInAim;
}





//得到目标ID
int Bit_AimDataStructure::Get_AimID( void ) const
{
	return id_;
}

//得到炸点在目标坐标系内坐标
CoordinatesPosition Bit_AimDataStructure::Get_HitPosition( void ) const
{
	return HitPosition_;
}

////得到目标区域中心点坐标
//CoordinatesPosition Bit_AimDataStructure::Get_AimCenterCP( void ) const
//{
//	return AimCenterCP_;
//}

////得到目标区域四个顶点坐标
//void Bit_AimDataStructure::Get_AimArea( CoordinatesPosition AimAreaPoint[4] ) const
//{
//	for( int i = 0 ; i < 4 ; i++ )
//	{
//		AimAreaPoint[i] = AimArea_[i];
//	}
//}

//得到目标区域四个顶点坐标
void Bit_AimDataStructure::Get_AimArea( CoordinatesPosition AimAreaPoint[4] ) const
{
	ComputeVertexCoordinate( Long_ , Wide_ , AimAreaPoint );
}

////得到四边形单元自动划分四边形网格
//QuadMeshingQuad Bit_AimDataStructure::Get_AimQuad( void ) const
//{
//	return AimQuad_;
//}

//得到划分产生的第一个节点号
int Bit_AimDataStructure::Get_FristNode( void ) const
{
	return FristNode_;
}

//得到划分产生的第一个单元号
int Bit_AimDataStructure::Get_FristElement( void ) const
{
	return FristElement_;
}

//得到在0号和2号线上划分单元大小
double Bit_AimDataStructure::Get_N_02( void ) const
{
	return N_02_;
}

//得到在1号和3号线上划分单元大小
double Bit_AimDataStructure::Get_N_13( void ) const
{
	return N_13_;
}

//得到目标中心点纬度
double Bit_AimDataStructure::Get_AimLat( void )const
{
	return AimLat_;
}

//得到目标中心点经度
double Bit_AimDataStructure::Get_AimLon( void ) const
{
	return AimLon_;
}

//得到瞄准点在目标坐标系内坐标
CoordinatesPosition Bit_AimDataStructure::Get_AimPoint( void )
{
	return AimPoint_;
}




//*****************************计算函数******************************//
//由目标区域长宽计算四个顶点坐标
void Bit_AimDataStructure::ComputeVertexCoordinate( double lon , double wid , CoordinatesPosition VC[4] )const
{
		VC[0] = CoordinatesPosition( -lon / 2 , -wid / 2 , 0 );
		VC[1] = CoordinatesPosition( lon / 2 , wid / 2 , 0 );
		VC[2] = CoordinatesPosition( -lon / 2 , wid / 2 , 0 );
		VC[3] = CoordinatesPosition( lon / 2 , -wid / 2 , 0 );
}






