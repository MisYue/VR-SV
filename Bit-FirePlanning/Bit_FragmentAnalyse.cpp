#include "Bit_FragmentAnalyse.h"

//���캯����ʼ��
Bit_FragmentAnalyse::Bit_FragmentAnalyse( Bit_UnitSystem &US )
{
	US_ = US;
}

//�������캯��
Bit_FragmentAnalyse::Bit_FragmentAnalyse( const Bit_FragmentAnalyse &Bit_Frag )
{
	id_ = Bit_Frag.id_;
	US_ = Bit_Frag.US_;
}

//�������=������
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

//��̬�ֲ������õ�������Ƭ�����
void Bit_FragmentAnalyse::FragmentDirectionalAngle(  Bit_RocketDataStructure &RockDataStructure , int &FragNum , double FDAResults[] )const
{
	//��ս������̬��ɢ���ϱ߽��뵯������ϵx��нǣ�������̬�ֲ�����
	double WarheadStaticAngle_Up = RockDataStructure.Get_WarheadStaticAngleCentralLine() - 0.5 * RockDataStructure.Get_WarheadStaticDisporaAngle();
	//����һά��̬�ֲ������
	ProbabilityAndRandom *ThePAR = new ProbabilityAndRandom();
	  //���ò�������������������
	int StandardNormalDistribution_Base = 48;
	double StandardNormalDistribution_Random = 0;
	//double StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
	//���ñ�׼��
	double GaussianStandardDeviation = RockDataStructure.Get_WarheadStaticDisporaAngle() / 6;
	//�����õ�ÿö��Ƭ��̬�����
	//double StaticDA = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
	for ( int i = 0 ; i < FragNum ; i++ )
	{
		StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
		FDAResults[i] = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
		//�жϽǶ��Ƿ����0���������³�������
		for( int j = 0 ; j < 100 ; j++ )
		{
			if ( FDAResults[i] > 0 )
			{
				break;
			}
			else
			{
				//���³�������
				StandardNormalDistribution_Random = ThePAR->Get1DStandardNormalDistributionRandom( StandardNormalDistribution_Base );
				FDAResults[i] = RockDataStructure.Get_WarheadStaticAngleCentralLine() + StandardNormalDistribution_Random * GaussianStandardDeviation;
			}
		}
	}
}

//������Ƭ���١�������ٶȡ�ÿ����Ƭ��̬�����ʸ���ϳ���Ƭʵ���ٶ�
double Bit_FragmentAnalyse::FragmentRealVelocity( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure ) const
{
	//��Ƭ���٣���λ��ת�����������λ���㣩
	double FragmentStratVelocity = FragDataStructure.Get_FragmentVelocity()
		* FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient();
	//������ٶȣ���λ��ת�����������λ���㣩
	double RocketStartVelocity = RockDataStructure.Get_RocketVelocity()
		* RockDataStructure.Get_RocketUS().Get_LengthCoefficient() / RockDataStructure.Get_RocketUS().Get_TimeCoefficient();
	return ( sqrt( FragmentStratVelocity * FragmentStratVelocity + RocketStartVelocity * RocketStartVelocity - 
		2 * FragmentStratVelocity * RocketStartVelocity * cos( pi - FragDataStructure.Get_StaticDirectonalAngle() ) )
		/ US_.Get_LengthCoefficient() * US_.Get_TimeCoefficient() );
}

//������Ƭ���١�������ٶȡ���Ƭ��̬�����ٶ������Ҷ�����̬�����
double Bit_FragmentAnalyse::FragmentDynamicDirectionalAngle( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure ) const
{
	AdvancedMath *TheAdvancedMath = new AdvancedMath();
	//���Ҷ�������Ƭ��̬����ǣ����ڼ�����Ƭ�ڵ�������ϵ��λ�ã�
	double FragmentDynamicDirectionalA = TheAdvancedMath->ComputeFaceSideAngle( 
		RockDataStructure.Get_RocketVelocity() * RockDataStructure.Get_RocketUS().Get_LengthCoefficient() / RockDataStructure.Get_RocketUS().Get_TimeCoefficient() ,
		FragDataStructure.Get_FragmentDynamicVelocity() * FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient(),
		FragDataStructure.Get_FragmentVelocity() * FragDataStructure.Get_FragmentUS().Get_LengthCoefficient() / FragDataStructure.Get_FragmentUS().Get_TimeCoefficient() );
	delete TheAdvancedMath;
	return FragmentDynamicDirectionalA;
}

//����ը������Ƭ��������ǡ�����Ǽ�����Ƭ�ڵ�������ϵ��ֱ������
CoordinatesPosition Bit_FragmentAnalyse::ComputeFragmentCoordinateInBodyCoordinate( Bit_FragmentDataStructure &FragDataStructure )const
{
	CoordinatesPosition Frag_CoordinatesPosition = CoordinatesPosition( FragDataStructure.Get_FlyDistance() * cos( FragDataStructure.Get_DynamicDirectionalAngle() ) , 
		FragDataStructure.Get_FlyDistance() * sin( FragDataStructure.Get_DynamicDirectionalAngle() ) * cos( FragDataStructure.Get_DynamicCircleAngle() ) , 
		FragDataStructure.Get_FlyDistance() * sin( FragDataStructure.Get_DynamicDirectionalAngle() ) * sin( FragDataStructure.Get_DynamicCircleAngle() ) );
	return Frag_CoordinatesPosition;
}

//�жϿռ�ֱ����ƽ���Ƿ��ཻ
//M��ֱ����һ�㣻VL:ֱ�߷���������N��ƽ����һ�㣻VP��ƽ�淨����
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

//�ռ�ֱ����ƽ�潻��
//M��ֱ����һ�㣻VL:ֱ�߷���������P��ƽ����һ�㣻VP��ƽ�淨����
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

//��Ŀ�����򻮷�����
void Bit_FragmentAnalyse::AreaDividing( Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &AimQMP )
{
	//�õ�Ŀ�������ĸ���������
	CoordinatesPosition *AimAreaForDevide = new CoordinatesPosition[4]();
	AimDataStructure.Get_AimArea( AimAreaForDevide );
	Node *Aim_N = new Node[4]();
	for( int i = 0 ; i < 4 ; i++ )
	{
		Aim_N[i] = Node( i ,AimAreaForDevide[i] );
	}
	Element_Surface_Quad Aim_Initial( 0 , 0 , Aim_N , 0 );
	QuadMeshingQuad Aim_QMQ_Store( Aim_Initial , 0 );
	//��������
	//�����0���߶γ���
	double LengthofNum0 = AimAreaForDevide[0].Distance( AimAreaForDevide[3]);
	int N_N02 = LengthofNum0 / AimDataStructure.Get_N_02();
	//�����1���߶γ���
	double LengthofNum1 = AimAreaForDevide[1].Distance( AimAreaForDevide[3]);
	int N_N13 = LengthofNum1 / AimDataStructure.Get_N_13();
	Aim_QMQ_Store.MeshQuad( AimDataStructure.Get_FristNode() , AimDataStructure.Get_FristElement() , N_N02 , N_N13 );
	//��û��������������Ԫ�ϵĵ�Ԫ������ÿ����Ԫ����Get_ElementInElement����
	int ElementNumberInAim = Aim_QMQ_Store.Get_ElementNumber();
	Element_Surface_Quad *GetElementSQ = new Element_Surface_Quad[ ElementNumberInAim ]();
	Aim_QMQ_Store.Get_ElementInElement( &ElementNumberInAim , GetElementSQ );
	AimQMP.Set_Initial( ElementNumberInAim , GetElementSQ );
	delete []Aim_N;
	delete []AimAreaForDevide;
	delete []GetElementSQ;
}

//������Ƭ���й켣�ߣ�����Ŀ������ϵ��
Line Bit_FragmentAnalyse::ComputeFragmentFlyLine( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure , Bit_AimDataStructure &AimDataStructure ) const
{
	//��Ƭ�ڵ�������ϵ��λ��
	CoordinatesPosition FIR = FragDataStructure.Get_FragmentPositionInRocketCoordinate();
	//����Ƭ�ڵ�������ϵ�е�����ת����Ŀ������ϵ
	CoordinatesPosition *TheCoor = new CoordinatesPosition();
	CoordinatesPosition *AngleRadian = new CoordinatesPosition();
	CoordinatesPosition FragmentPositionInAimCoordinates = TheCoor->ComputeCoordinateInTargetFromAmmunition( AngleRadian->RadianToAngle( RockDataStructure.Get_RocketPitchingAngle() ) , AngleRadian->RadianToAngle( RockDataStructure.Get_RocketYawAngle() )  ,
		FragDataStructure.Get_FragmentPositionInRocketCoordinate() , AimDataStructure.Get_HitPosition() );
	delete TheCoor;
	delete AngleRadian;
	//��Ƭ���й켣�߷�������
	double xx = FragmentPositionInAimCoordinates.Get_x() - AimDataStructure.Get_HitPosition().Get_x();
	double yy = FragmentPositionInAimCoordinates.Get_y() - AimDataStructure.Get_HitPosition().Get_y();
	double zz = FragmentPositionInAimCoordinates.Get_z() - AimDataStructure.Get_HitPosition().Get_z();
	CoordinatesPosition DrictionVector = CoordinatesPosition ( xx , yy , zz );
	//��Ƭ���й켣��
	Node FragmentNode = Node( 1 , AimDataStructure.Get_HitPosition() );
	Line FragmentLine = Line( 1 , DrictionVector , FragmentNode );
	return FragmentLine;
}

//�ж���Ƭ��Ŀ����������ƽ���Ƿ���ڽ���
bool Bit_FragmentAnalyse::MeetingOrNot( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure ) const
{
	//Ŀ�������ʼ��Ԫ
	//�õ�Ŀ�������ĸ���������
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

//������Ƭ���й켣��Ŀ�����򽻵㣨������Ƭ���о�������Զ���ڿ��������ٶ�˥����
CoordinatesPosition Bit_FragmentAnalyse::ComputeMeetingPointWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure ) const
{
	//Ŀ�������ʼ��Ԫ
	//�õ�Ŀ�������ĸ���������
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
	//����Ƭ���й켣����Ŀ��ƽ�潻��
	CoordinatesPosition IntersectPoint = CoordinatesPosition( -1000000 , -1000000 , -1000000 );
	bool MON = AimESQ.ComputeIntersectPOnL_RLAndEPlane( FragmentLine , &IntersectPoint );
	return IntersectPoint;
}

//�жϽ����Ƿ���Ŀ�귶Χ��
bool Bit_FragmentAnalyse::InOrNot( Line &FragmentLine , Bit_QuadMeshPlane &QMP ) const
{
	int ElementNumber = QMP.Get_ElementNumber();
	Element_Surface_Quad *Aim_Element = new Element_Surface_Quad[ ElementNumber ]();
	QMP.Get_ElementInPlane( Aim_Element );
	//���彻���Ƿ�������Ԫ���жϱ���
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

//��Ƭ���ѻ��������Ŀ�����򽻻�
int Bit_FragmentAnalyse::FragmentMeetWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &QMP ) const
{
	CoordinatesPosition IntersectPoint = ComputeMeetingPointWithArea( FragmentLine , AimDataStructure );
	//�жϽ������������ĸ���Ԫ��
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


//�ж���Ƭ��Ŀ�����������Ƿ����
bool Bit_FragmentAnalyse::WhetherFragmentDamageAimArea( double &FragmentDamageCriterion , Bit_FragmentDataStructure &FragDataStructure )
{
	//������Ƭ����Ŀ��������
	double FragmentKineticEnergy = 0.5 * ( FragDataStructure.Get_Mass() * FragDataStructure.Get_FragmentUS().Get_MassCoefficient() / 1000 ) * FragDataStructure.Get_FragmentResidualVelocity() * FragDataStructure.Get_FragmentResidualVelocity();
	//�ж���Ƭ��Ŀ�����������Ƿ����
	if ( FragmentKineticEnergy > FragmentDamageCriterion || abs( FragmentKineticEnergy - FragmentDamageCriterion ) < 0.000000000001 )
	{
		return true;
	} 
	else
	{
		return false;
	}
}