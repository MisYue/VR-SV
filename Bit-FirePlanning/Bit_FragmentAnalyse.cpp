#include "Bit_FragmentAnalyse.h"

//构造函数初始化
Bit_FragmentAnalyse::Bit_FragmentAnalyse( Bit_UnitSystem &US )
{
	US_ = US;
}

//拷贝构造函数
Bit_FragmentAnalyse::Bit_FragmentAnalyse( const Bit_FragmentAnalyse &Bit_Frag )
{
	id_ = Bit_Frag.id_;
	US_ = Bit_Frag.US_;
}

//运算符“=”重载
Bit_FragmentAnalyse & Bit_FragmentAnalyse::operator=( const Bit_FragmentAnalyse &Bit_Frag )
{
	if ( this != & Bit_Frag )
	{
		id_ = Bit_Frag.id_;
		US_ = Bit_Frag.US_;
	}
	return *this;
}


Bit_FragmentAnalyse::~Bit_FragmentAnalyse()
{

}

//正态分布抽样得到所有破片方向角
void Bit_FragmentAnalyse::FragmentDirectionalAngle(  Bit_RocketDataStructure &RockDataStructure , int &FragNum , double FDAResults[] )const
{
	//求战斗部静态飞散角上边界与弹体坐标系x轴夹角，用于正态分布抽样
	double WarheadStaticAngle_Up = RockDataStructure.Get_WarheadStaticAngleCentralLine() - 0.5 * RockDataStructure.Get_WarheadStaticDisporaAngle();
	//产生一维正态分布随机数
	ProbabilityAndRandom *ThePAR = new ProbabilityAndRandom();
	  //设置产生随机数所需基础数据
	int StandardNormalDistribution_Base = 48;
	double StandardNormalDistribution_Random = 0;
	//double StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
	//设置标准差
	double GaussianStandardDeviation = RockDataStructure.Get_WarheadStaticDisporaAngle() / 6;
	//抽样得到每枚破片静态方向角
	//double StaticDA = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
	for ( int i = 0 ; i < FragNum ; i++ )
	{
		StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
		FDAResults[i] = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
		//判断角度是否大于0，否则重新抽样计算
		for( int j = 0 ; j < 100 ; j++ )
		{
			if ( FDAResults[i] > 0 )
			{
				break;
			}
			else
			{
				//重新抽样计算
				StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
				FDAResults[i] = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
			}
		}
	}
}

//根据破片初速、火箭弹速度、每个破片静态方向角矢量合成破片实际速度
double Bit_FragmentAnalyse::FragmentRealVelocity( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure ) const
{
	//破片初速（单位制转化至最基本单位计算）
	double FragmentStratVelocity = FragDataStructure.Get_FragmentVelocity()
		* FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient();
	//火箭弹速度（单位制转化至最基本单位计算）
	double RocketStartVelocity = RockDataStructure.Get_RocketVelocity()
		* RockDataStructure.Get_RocketUS().Get_LengthCoefficient() / RockDataStructure.Get_RocketUS().Get_TimeCoefficient();
	return ( sqrt( FragmentStratVelocity * FragmentStratVelocity + RocketStartVelocity * RocketStartVelocity - 
		2 * FragmentStratVelocity * RocketStartVelocity * cos( pi - FragDataStructure.Get_StaticDirectonalAngle() ) )
		/ US_.Get_LengthCoefficient() * US_.Get_TimeCoefficient() );
}

//根据破片初速、火箭弹速度、破片动态飞行速度用余弦定理反求动态方向角
double Bit_FragmentAnalyse::FragmentDynamicDirectionalAngle( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure ) const
{
	AdvancedMath *TheAdvancedMath = new AdvancedMath();
	//余弦定理反求破片动态方向角（用于计算破片在弹体坐标系内位置）
	double FragmentDynamicDirectionalA = TheAdvancedMath->ComputeFaceSideAngle( 
		RockDataStructure.Get_RocketVelocity() * RockDataStructure.Get_RocketUS().Get_LengthCoefficient() / RockDataStructure.Get_RocketUS().Get_TimeCoefficient() ,
		FragDataStructure.Get_FragmentDynamicVelocity() * FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient(),
		FragDataStructure.Get_FragmentVelocity() * FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient() );
	delete TheAdvancedMath;
	return FragmentDynamicDirectionalA;
}

//根据炸点与破片飞行周向角、方向角计算破片在弹体坐标系内直角坐标
CoordinatesPosition Bit_FragmentAnalyse::ComputeFragmentCoordinateInBodyCoordinate( Bit_FragmentDataStructure &FragDataStructure )const
{
	CoordinatesPosition Frag_CoordinatesPosition = CoordinatesPosition( FragDataStructure.Get_FlyDistance() * cos( FragDataStructure.Get_DynamicDirectionalAngle() ) , 
		FragDataStructure.Get_FlyDistance() * sin( FragDataStructure.Get_DynamicDirectionalAngle() ) * cos( FragDataStructure.Get_DynamicCircleAngle() ) , 
		FragDataStructure.Get_FlyDistance() * sin( FragDataStructure.Get_DynamicDirectionalAngle() ) * sin( FragDataStructure.Get_DynamicCircleAngle() ) );
	return Frag_CoordinatesPosition;
}

//判断空间直线与平面是否相交
//M：直线上一点；VL:直线方向向量；N：平面上一点；VP：平面法向量
bool Bit_FragmentAnalyse::JungleIfIntereForLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP ) const
{
	double m1 = M.Get_x() , m2 = M.Get_y() , m3 = M.Get_z();
	double v1 = VL.Get_x() , v2 = VL.Get_y() , v3 = VL.Get_z();
	double n1 = N.Get_x() , n2 = N.Get_y() , n3 = N.Get_z();
	double vp1 = VP.Get_x() , vp2 = VP.Get_y() , vp3 = VP.Get_z();
	double TOrF = vp1 * v1 + vp2 * v2 + vp3 * v3;
	if ( abs( TOrF ) < 0.0000000001 )
	{
		return false;
	} 
	else
	{
		return true;
	}
}

//空间直线与平面交点
//M：直线上一点；VL:直线方向向量；P：平面上一点；VP：平面法向量
CoordinatesPosition Bit_FragmentAnalyse::ComputePointBetweenLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP ) const
{
	double m1 = M.Get_x() , m2 = M.Get_y() , m3 = M.Get_z();
	double v1 = VL.Get_x() , v2 = VL.Get_y() , v3 = VL.Get_z();
	double n1 = N.Get_x() , n2 = N.Get_y() , n3 = N.Get_z();
	double vp1 = VP.Get_x() , vp2 = VP.Get_y() , vp3 = VP.Get_z();
	double TOrF = vp1 * v1 + vp2 * v2 + vp3 * v3;
	CoordinatesPosition ComputeResult = CoordinatesPosition();
	if ( JungleIfIntereForLineAndPlane( M , VL , N , VP ) )
	{
		double t = ( ( n1 - m1 ) * vp1 + ( n2 - m2 ) *vp2 + ( n3 - m3 ) *vp3 ) / TOrF;
		ComputeResult.Set_x( m1 + v1 * t );
		ComputeResult.Set_y( m2 + v2 * t );
		ComputeResult.Set_z( m3 + v3 * t );
		return ComputeResult;
	} 
	else
	{
		exit( 0 );
	}
}

//将目标区域划分网格
void Bit_FragmentAnalyse::AreaDividing( Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &AimQMP )
{
	//得到目标区域四个顶点坐标
	CoordinatesPosition *AimAreaForDevide = new CoordinatesPosition[4]();
	AimDataStructure.Get_AimArea( AimAreaForDevide );
	Node *Aim_N = new Node[4]();
	for( int i = 0 ; i < 4 ; i++ )
	{
		Aim_N[i] = Node( i ,AimAreaForDevide[i] );
	}
	Element_Surface_Quad Aim_Initial( 0 , 0 , Aim_N , 0 );
	QuadMeshingQuad Aim_QMQ_Store( Aim_Initial , 0 );
	//划分网格
	//计算第0号线段长度
	double LengthofNum0 = AimAreaForDevide[0].Distance( AimAreaForDevide[3]);
	int N_N02 = LengthofNum0 / AimDataStructure.Get_N_02();
	//计算第1号线段长度
	double LengthofNum1 = AimAreaForDevide[1].Distance( AimAreaForDevide[3]);
	int N_N13 = LengthofNum1 / AimDataStructure.Get_N_13();
	Aim_QMQ_Store.MeshQuad( AimDataStructure.Get_FristNode() , AimDataStructure.Get_FristElement() , N_N02 , N_N13 );
	//获得划分网格后整个单元上的单元数量和每个单元，用Get_ElementInElement函数
	int ElementNumberInAim = Aim_QMQ_Store.Get_ElementNumber();
	Element_Surface_Quad *GetElementSQ = new Element_Surface_Quad[ ElementNumberInAim ]();
	Aim_QMQ_Store.Get_ElementInElement( &ElementNumberInAim , GetElementSQ );
	AimQMP.Set_Initial( ElementNumberInAim , GetElementSQ );
	delete []Aim_N;
	delete []AimAreaForDevide;
	delete []GetElementSQ;
}

//计算破片飞行轨迹线（基于目标坐标系）
Line Bit_FragmentAnalyse::ComputeFragmentFlyLine( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure , Bit_AimDataStructure &AimDataStructure ) const
{
	//破片在弹体坐标系内位置
	CoordinatesPosition FIR = FragDataStructure.Get_FragmentPositionInRocketCoordinate();
	//将破片在弹体坐标系中的坐标转化至目标坐标系
	CoordinatesPosition *TheCoor = new CoordinatesPosition();
	CoordinatesPosition *AngleRadian = new CoordinatesPosition();
	CoordinatesPosition FragmentPositionInAimCoordinates = TheCoor->ComputeCoordinateInTargetFromAmmunition( AngleRadian->RadianToAngle( RockDataStructure.Get_RocketPitchingAngle() ) , AngleRadian->RadianToAngle( RockDataStructure.Get_RocketYawAngle() )  ,
		FragDataStructure.Get_FragmentPositionInRocketCoordinate() , AimDataStructure.Get_HitPosition() );
	delete TheCoor;
	delete AngleRadian;
	//破片飞行轨迹线方向向量
	double xx = FragmentPositionInAimCoordinates.Get_x() - AimDataStructure.Get_HitPosition().Get_x();
	double yy = FragmentPositionInAimCoordinates.Get_y() - AimDataStructure.Get_HitPosition().Get_y();
	double zz = FragmentPositionInAimCoordinates.Get_z() - AimDataStructure.Get_HitPosition().Get_z();
	CoordinatesPosition DrictionVector = CoordinatesPosition ( xx , yy , zz );
	//破片飞行轨迹线
	Node FragmentNode = Node( 1 , AimDataStructure.Get_HitPosition() );
	Line FragmentLine = Line( 1 , DrictionVector , FragmentNode );
	return FragmentLine;
}

//判断破片与目标区域所在平面是否存在交点
bool Bit_FragmentAnalyse::MeetingOrNot( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure ) const
{
	//目标区域初始单元
	//得到目标区域四个顶点坐标
	CoordinatesPosition *AimAreaForDevide = new CoordinatesPosition[4]();
	AimDataStructure.Get_AimArea( AimAreaForDevide );
	Node *Aim_N = new Node[4]();
	for( int i = 0 ; i < 4 ; i++ )
	{
		Aim_N[i] = Node( i ,AimAreaForDevide[i] );
	}
	Element_Surface_Quad AimESQ( 0 , 0 , Aim_N , 0 );
	bool MON = AimESQ.JudgeIfIntersectWithRLine( FragmentLine );
	delete []Aim_N;
	delete []AimAreaForDevide;
	return MON;
}

//计算破片飞行轨迹与目标区域交点（假设破片飞行距离无限远，在空气中无速度衰减）
CoordinatesPosition Bit_FragmentAnalyse::ComputeMeetingPointWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure ) const
{
	//目标区域初始单元
	//得到目标区域四个顶点坐标
	CoordinatesPosition *AimAreaForDevide = new CoordinatesPosition[4]();
	AimDataStructure.Get_AimArea( AimAreaForDevide );
	Node *Aim_N = new Node[4]();
	for( int i = 0 ; i < 4 ; i++ )
	{
		Aim_N[i] = Node( i ,AimAreaForDevide[i] );
	}
	Element_Surface_Quad AimESQ( 0 , 0 , Aim_N , 0 );
	delete []Aim_N;
	delete []AimAreaForDevide;
	//求破片飞行轨迹线与目标平面交点
	CoordinatesPosition IntersectPoint = CoordinatesPosition( -1000000 , -1000000 , -1000000 );
	bool MON = AimESQ.ComputeIntersectPOnL_RLAndEPlane( FragmentLine , &IntersectPoint );
	return IntersectPoint;
}

//判断交点是否在目标范围内
bool Bit_FragmentAnalyse::InOrNot( Line &FragmentLine , Bit_QuadMeshPlane &QMP ) const
{
	int ElementNumber = QMP.Get_ElementNumber();
	Element_Surface_Quad *Aim_Element = new Element_Surface_Quad[ ElementNumber ]();
	QMP.Get_ElementInPlane( Aim_Element );
	//定义交点是否在区域单元内判断变量
	bool WhetherIn = false;
	for( int i = 0 ; i < ElementNumber ; i++ )
	{
		WhetherIn = Aim_Element[i].JudgeIfInElementForIntersectPOnLine( FragmentLine );
		if ( WhetherIn == true )
		{
			break;
		}
	}
	delete []Aim_Element;
	return WhetherIn;
}

//破片与已划分网格的目标区域交汇
int Bit_FragmentAnalyse::FragmentMeetWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &QMP ) const
{
	CoordinatesPosition IntersectPoint = ComputeMeetingPointWithArea( FragmentLine , AimDataStructure );
	//判断交点在区域内哪个单元里
	int IntersectID = -1;
	int ElementNumber = QMP.Get_ElementNumber();
	Element_Surface_Quad *Aim_Element = new Element_Surface_Quad[ElementNumber]();
	QMP.Get_ElementInPlane( Aim_Element );
	for( int i = 0 ; i < ElementNumber ; i++ )
	{
		if ( Aim_Element[i].JudgeIfInElementForIntersectPOnLine( FragmentLine ) == true )
		{
			IntersectID = Aim_Element[i].Get_id();
		} 
	}
	delete []Aim_Element;
	return IntersectID;
}


//判断破片对目标区域网格是否毁伤
bool Bit_FragmentAnalyse::WhetherFragmentDamageAimArea( double &FragmentDamageCriterion , Bit_FragmentDataStructure &FragDataStructure )
{
	//计算破片命中目标区域动能
	double FragmentKineticEnergy = 0.5 * ( FragDataStructure.Get_Mass() * FragDataStructure.Get_FragmentUS().Get_MassCoefficient() / 1000 ) * FragDataStructure.Get_FragmentResidualVelocity() * FragDataStructure.Get_FragmentResidualVelocity();
	//判断破片对目标区域网格是否毁伤
	if ( FragmentKineticEnergy > FragmentDamageCriterion || abs( FragmentKineticEnergy - FragmentDamageCriterion ) < 0.000000000001 )
	{
		return true;
	} 
	else
	{
		return false;
	}
}