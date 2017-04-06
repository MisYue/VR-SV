#include "USERD_ComputeGurenyEnergy.h"


USERD_ComputeGurenyEnergy::USERD_ComputeGurenyEnergy(void)
{
	US_ = Bit_UnitSystem( 1 , 1, 1 );
	GurneyEnergy_ = 0;
	IfUS_ = false;
}
//��ʼ������
USERD_ComputeGurenyEnergy::USERD_ComputeGurenyEnergy( Bit_UnitSystem US , double GurneyEnergy )
{
	US_ = US;
	IfUS_ = true;
	GurneyEnergy_ = GurneyEnergy * US_.Get_VelocityCoefficient();
}


USERD_ComputeGurenyEnergy::~USERD_ComputeGurenyEnergy(void)
{
	IfUS_ = false;
}
////�����Զ�������ܵĵ�λ��
inline void USERD_ComputeGurenyEnergy::Set_US( const Bit_UnitSystem& US )
{
	US_ = US;
	IfUS_ = true;
}

// �õ���λ�ƶ��Ƿ���
inline bool USERD_ComputeGurenyEnergy::Get_USIfDefinition( void ) const
{
	return IfUS_;
}
// �õ���λ��
inline Bit_UnitSystem USERD_ComputeGurenyEnergy::Get_US( void ) const
{
	if( IfUS_ != true )
		exit(0);
	return US_;
}

//�����Զ��������
inline void USERD_ComputeGurenyEnergy::Set_GurneyEnergy( const double& GurneyEnergy )
{
	if( IfUS_ != true )
		exit(0);
	GurneyEnergy_ = GurneyEnergy * US_.Get_VelocityCoefficient();
}

// �����Զ�������ܵĵ�λ��
inline void USERD_ComputeGurenyEnergy::Set_GurneyEnergyAndUS( const Bit_UnitSystem& US , const double& GurneyEnergy )
{
	US_ = US;
	IfUS_ = true;
	GurneyEnergy_ = GurneyEnergy * US_.Get_VelocityCoefficient();
}

// �õ��û��Զ��������
inline double USERD_ComputeGurenyEnergy::Get_GurneyEnergy( void ) const
{
	if( IfUS_ != true )
		exit(0);
	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}
//�Զ��幫ʽ-1����charge������
double USERD_ComputeGurenyEnergy::Get_GurneyEnergyOnUSER_NoCharge( void )
{
	//1.�������ĵ�λ�Ʋ���������
	Bit_UnitSystem US(1 ,2 ,1 );
	//���õ�λ�ƶ�(�û����ò���)
	Set_US( US );
	//2. �����ڸõ�λ���µ���ر��������и�ֵ
	// ����õ�λ�ƶ��µı���
	double ExplosiveVelocity = 7.0;
	//3.д����ʽ��ͨ������õ��ڸõ�λ���µļ���ֵ
	// ͨ�������ö��嵥λ�ƵĽ��
	GurneyEnergy_ = 0.52 + 0.25 * ExplosiveVelocity ;
	
	//4.������ֵת��Ϊmm-g-us��λ�ƣ��û����ò�����
	// ����������ת����mm-g-us��λ��
	GurneyEnergy_ = GurneyEnergy_ * US_.Get_VelocityCoefficient();
	// ������൱ǰ��λֵ�Ľ���û����ò�����
	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}
//�Զ��幫ʽ_2(��Charge)
double USERD_ComputeGurenyEnergy::Get_GurneyEnergyOnUSER_WithCharge( const ChargeData& ChargeD ) const
{
	if( IfUS_ != true )
		exit(0);
	
	// �û��Զ��幫ʽ(��������Ϊmm-g-us��λ��)

	
	

	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}




