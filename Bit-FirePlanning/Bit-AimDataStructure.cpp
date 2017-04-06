#include "Bit-AimDataStructure.h"

//���캯����ʼ��
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

//�������캯��
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

//�������=������
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

//����Ŀ��IDֵ
void Bit_AimDataStructure::Set_AimID( int &Aim_ID )
{
	id_ = Aim_ID;
}

//����ը����Ŀ������ϵ������
void Bit_AimDataStructure::Set_HitPosition( CoordinatesPosition &HitPositionInAim )
{
	HitPosition_ = HitPositionInAim;
}

////����Ŀ���������ĵ�����
//void Bit_AimDataStructure::Set_AimCenterCP( CoordinatesPosition &AimCenterCPInAim )
//{
//	AimCenterCP_ = AimCenterCPInAim;
//}

////����Ŀ�������ĸ���������
//void Bit_AimDataStructure::Set_AimArea( CoordinatesPosition AimAreaInAim[4] )
//{
//	for( int i = 0 ; i < 4 ; i++ )
//	{
//		AimArea_[i] = AimAreaInAim[i];
//	}
//}


////�����ı��ε�Ԫ�Զ������ı�������
//void Bit_AimDataStructure::Set_AimQuad( QuadMeshingQuad &AimQuadInAim )
//{
//	AimQuad_ = AimQuadInAim;
//}

//���û��ֲ����ĵ�һ���ڵ��
void Bit_AimDataStructure::Set_FristNode( int &FristNodeInAim )
{
	FristNode_ = FristNodeInAim;
}

//���û��ֲ����ĵ�һ����Ԫ��
void Bit_AimDataStructure::Set_FristElement( int &FristElementInAim )
{
	FristElement_ = FristElementInAim;
}

//������0�ź�2�����ϻ��ֵ�Ԫ��С
void Bit_AimDataStructure::Set_N_02( double &N_02InAim )
{
	N_02_ = N_02InAim;
}

//������0�ź�2�����ϻ��ֵ�Ԫ��С
void Bit_AimDataStructure::Set_N_13( double &N_13InAim )
{
	N_13_ = N_13InAim;
}

//����Ŀ�����ĵ�γ��
void Bit_AimDataStructure::Set_AimLat( double &AimLatInAim )
{
	AimLat_ = AimLatInAim;
}

//����Ŀ�����ĵ㾭��
void Bit_AimDataStructure::Set_AimLon( double &AimLonInAim )
{
	AimLon_ = AimLonInAim;
}

void Bit_AimDataStructure::Set_AimPoint( CoordinatesPosition &AimPointInAim )
{
	AimPoint_ = AimPointInAim;
}





//�õ�Ŀ��ID
int Bit_AimDataStructure::Get_AimID( void ) const
{
	return id_;
}

//�õ�ը����Ŀ������ϵ������
CoordinatesPosition Bit_AimDataStructure::Get_HitPosition( void ) const
{
	return HitPosition_;
}

////�õ�Ŀ���������ĵ�����
//CoordinatesPosition Bit_AimDataStructure::Get_AimCenterCP( void ) const
//{
//	return AimCenterCP_;
//}

////�õ�Ŀ�������ĸ���������
//void Bit_AimDataStructure::Get_AimArea( CoordinatesPosition AimAreaPoint[4] ) const
//{
//	for( int i = 0 ; i < 4 ; i++ )
//	{
//		AimAreaPoint[i] = AimArea_[i];
//	}
//}

//�õ�Ŀ�������ĸ���������
void Bit_AimDataStructure::Get_AimArea( CoordinatesPosition AimAreaPoint[4] ) const
{
	ComputeVertexCoordinate( Long_ , Wide_ , AimAreaPoint );
}

////�õ��ı��ε�Ԫ�Զ������ı�������
//QuadMeshingQuad Bit_AimDataStructure::Get_AimQuad( void ) const
//{
//	return AimQuad_;
//}

//�õ����ֲ����ĵ�һ���ڵ��
int Bit_AimDataStructure::Get_FristNode( void ) const
{
	return FristNode_;
}

//�õ����ֲ����ĵ�һ����Ԫ��
int Bit_AimDataStructure::Get_FristElement( void ) const
{
	return FristElement_;
}

//�õ���0�ź�2�����ϻ��ֵ�Ԫ��С
double Bit_AimDataStructure::Get_N_02( void ) const
{
	return N_02_;
}

//�õ���1�ź�3�����ϻ��ֵ�Ԫ��С
double Bit_AimDataStructure::Get_N_13( void ) const
{
	return N_13_;
}

//�õ�Ŀ�����ĵ�γ��
double Bit_AimDataStructure::Get_AimLat( void )const
{
	return AimLat_;
}

//�õ�Ŀ�����ĵ㾭��
double Bit_AimDataStructure::Get_AimLon( void ) const
{
	return AimLon_;
}

//�õ���׼����Ŀ������ϵ������
CoordinatesPosition Bit_AimDataStructure::Get_AimPoint( void )
{
	return AimPoint_;
}




//*****************************���㺯��******************************//
//��Ŀ�����򳤿�����ĸ���������
void Bit_AimDataStructure::ComputeVertexCoordinate( double lon , double wid , CoordinatesPosition VC[4] )const
{
		VC[0] = CoordinatesPosition( -lon / 2 , -wid / 2 , 0 );
		VC[1] = CoordinatesPosition( lon / 2 , wid / 2 , 0 );
		VC[2] = CoordinatesPosition( -lon / 2 , wid / 2 , 0 );
		VC[3] = CoordinatesPosition( lon / 2 , -wid / 2 , 0 );
}






