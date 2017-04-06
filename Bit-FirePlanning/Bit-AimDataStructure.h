/********************************************************************
Creating Date:	2016/04/26
 
File Ext:	h

Purpose:	Ŀ�꣨��Ŀ������ϵ�����ݽṹ

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "MeshSupport/QuadMeshingQuad.h"
#include "MeshSupport/Bit_QuadMeshPlane.h"
#include "MathCalculationSupport/Node.h"
#include "Bit-FirePlanningGlobal.h"

class BIT_FIREPLANNING_API Bit_AimDataStructure
{
public:
	//���캯����ʼ��
	//id:Ŀ��ID�ţ�HitPosition:ը����Ŀ������ϵ�����ꣻAimCenterCP:Ŀ���������ĵ����ꣻLong:Ŀ�����򳤶ȣ�Wide��Ŀ�������ȣ�
	//FristNode�����ֲ����ĵ�һ���ڵ�ţ�FristElement�����ֲ����ĵ�һ����Ԫ�ţ�
	//N_02����0�ź�2�����ϻ��ֵ�Ԫ��С(Ĭ�ϳ��ȷ���Ϊ0�ź�2����)��N_13����1�ź�3�����ϻ��ֵ�Ԫ��С(Ĭ�Ͽ�ȷ���Ϊ1�ź�3����)��
	//AimLat:Ŀ�����ĵ�γ�ȣ�AimLon��Ŀ�����ĵ㾭��;AimPoint:��׼����Ŀ������ϵ�����꣨������CEP���������룩
	Bit_AimDataStructure( int &id , CoordinatesPosition &HitPosition , double &Long , double &Wide,
	 int& FristNode , int& FristElement , double& N_02 , double &N_13 , double &AimLat , double &AimLon , CoordinatesPosition &AimPoint );
	~Bit_AimDataStructure();
	//�������캯��
	Bit_AimDataStructure( const Bit_AimDataStructure &Bit_Aim );
	//�������=������
	Bit_AimDataStructure &operator=( const Bit_AimDataStructure &Bit_Aim );

	//����Ŀ��IDֵ
	void Set_AimID( int &Aim_ID );
	//����ը����Ŀ������ϵ������
	void Set_HitPosition( CoordinatesPosition &HitPositionInAim );
	////����Ŀ���������ĵ�����
	//void Set_AimCenterCP( CoordinatesPosition &AimCenterCPInAim );
	////����Ŀ�������ĸ���������
	//void Set_AimArea( CoordinatesPosition AimAreaInAim[4] );
	//���û��ֲ����ĵ�һ���ڵ��
	void Set_FristNode( int &FristNodeInAim );
	//���û��ֲ����ĵ�һ����Ԫ��
	void Set_FristElement( int &FristElementInAim );
	//������0�ź�2�����ϻ��ֵ�Ԫ��С
	void Set_N_02( double &N_02InAim );
	//������1�ź�3�����ϻ��ֵ�Ԫ��С
	void Set_N_13( double &N_13InAim );
	//����Ŀ�����ĵ�γ��
	void Set_AimLat( double &AimLatInAim );
	//����Ŀ�����ĵ㾭��
	void Set_AimLon( double &AimLonInAim );
	//������׼����Ŀ������ϵ������
	void Set_AimPoint( CoordinatesPosition &AimPointInAim );


	//�õ�Ŀ��ID
	int Get_AimID( void )const;
	//�õ�ը����Ŀ������ϵ������
	CoordinatesPosition Get_HitPosition( void )const;
	////�õ�Ŀ���������ĵ�����
	//CoordinatesPosition Get_AimCenterCP( void )const;
	////�õ�Ŀ�������ĸ���������
	//void Get_AimArea( CoordinatesPosition AimAreaPoint[4] )const;
	//�õ�Ŀ�������ĸ���������
	void Get_AimArea( CoordinatesPosition AimAreaPoint[4] )const;
	//�õ����ֲ����ĵ�һ���ڵ��
	int Get_FristNode( void )const;
	//�õ����ֲ����ĵ�һ����Ԫ��
	int Get_FristElement( void )const;
	//�õ���0�ź�2�����ϻ��ֵ�Ԫ��С
	double Get_N_02( void )const;
	//�õ���1�ź�3�����ϻ��ֵ�Ԫ��С
	double Get_N_13( void )const;
	//�õ�Ŀ�����ĵ�γ��
	double Get_AimLat( void )const;
	//�õ�Ŀ�����ĵ㾭��
	double Get_AimLon( void )const;
	//�õ���׼����Ŀ������ϵ������
	CoordinatesPosition Get_AimPoint( void );


	//*****************************���㺯��******************************//
	//��Ŀ�����򳤿�����ĸ���������
	void ComputeVertexCoordinate( double lon , double wid , CoordinatesPosition VC[4] )const;




private:
	Bit_UnitSystem US_;
	int id_;
	CoordinatesPosition HitPosition_;
	//CoordinatesPosition AimCenterCP_;
	double Long_;
	double Wide_;
	//CoordinatesPosition AimArea_[4];
	int FristNode_;
	int FristElement_;
	double N_02_;
	double N_13_;
	double AimLat_;
	double AimLon_;
	CoordinatesPosition AimPoint_;
};