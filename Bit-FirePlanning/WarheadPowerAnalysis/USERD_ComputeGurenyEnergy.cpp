#include "USERD_ComputeGurenyEnergy.h"


USERD_ComputeGurenyEnergy::USERD_ComputeGurenyEnergy(void)
{
	US_ = Bit_UnitSystem( 1 , 1, 1 );
	GurneyEnergy_ = 0;
	IfUS_ = false;
}
//初始化定义
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
////设置自定义格尼能的单位制
inline void USERD_ComputeGurenyEnergy::Set_US( const Bit_UnitSystem& US )
{
	US_ = US;
	IfUS_ = true;
}

// 得到单位制度是否定义
inline bool USERD_ComputeGurenyEnergy::Get_USIfDefinition( void ) const
{
	return IfUS_;
}
// 得到单位制
inline Bit_UnitSystem USERD_ComputeGurenyEnergy::Get_US( void ) const
{
	if( IfUS_ != true )
		exit(0);
	return US_;
}

//设置自定义格尼能
inline void USERD_ComputeGurenyEnergy::Set_GurneyEnergy( const double& GurneyEnergy )
{
	if( IfUS_ != true )
		exit(0);
	GurneyEnergy_ = GurneyEnergy * US_.Get_VelocityCoefficient();
}

// 设置自定义格尼能的单位制
inline void USERD_ComputeGurenyEnergy::Set_GurneyEnergyAndUS( const Bit_UnitSystem& US , const double& GurneyEnergy )
{
	US_ = US;
	IfUS_ = true;
	GurneyEnergy_ = GurneyEnergy * US_.Get_VelocityCoefficient();
}

// 得到用户自定义格尼能
inline double USERD_ComputeGurenyEnergy::Get_GurneyEnergy( void ) const
{
	if( IfUS_ != true )
		exit(0);
	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}
//自定义公式-1（无charge参数）
double USERD_ComputeGurenyEnergy::Get_GurneyEnergyOnUSER_NoCharge( void )
{
	//1.定义计算的单位制并进行设置
	Bit_UnitSystem US(1 ,2 ,1 );
	//设置单位制度(用户不用操作)
	Set_US( US );
	//2. 定义在该单位制下的相关变量并进行赋值
	// 定义该单位制度下的爆速
	double ExplosiveVelocity = 7.0;
	//3.写计算式，通过计算得到在该单位制下的计算值
	// 通过计算获得定义单位制的结果
	GurneyEnergy_ = 0.52 + 0.25 * ExplosiveVelocity ;
	
	//4.将计算值转化为mm-g-us单位制（用户不用操作）
	// 计算出结果并转化成mm-g-us单位制
	GurneyEnergy_ = GurneyEnergy_ * US_.Get_VelocityCoefficient();
	// 输出此类当前单位值的结果用户不用操作）
	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}
//自定义公式_2(带Charge)
double USERD_ComputeGurenyEnergy::Get_GurneyEnergyOnUSER_WithCharge( const ChargeData& ChargeD ) const
{
	if( IfUS_ != true )
		exit(0);
	
	// 用户自定义公式(计算出结果为mm-g-us单位制)

	
	

	return GurneyEnergy_ / US_.Get_VelocityCoefficient();
}




