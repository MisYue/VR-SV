/********************************************************************
Creating Date:	2016/04/15
 
File Ext:	h

Purpose:	��Ƭ���˷���

*********************************************************************/



#include <math.h>
#include "MathCalculationSupport/CoordinatesPosition.h"
#include "MathCalculationSupport/ProbabilityAndRandom.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#include "MathCalculationSupport/AdvancedMath.h"
#include "MathCalculationSupport/Line.h"
#include "MeshSupport/QuadMeshingQuad.h"
#include "Bit-FragmentDataStructure.h"
#include "Bit-RocketDataStructure.h"
#include "Bit-AimDataStructure.h"
#include "MeshSupport/Bit_QuadMeshPlane.h"
#include "Bit-FirePlanningGlobal.h"
//#define pi 3.1415926535897932384626433832795
class BIT_FIREPLANNING_API Bit_FragmentAnalyse
{
public:
	//���캯����ʼ��
	Bit_FragmentAnalyse( Bit_UnitSystem &US );
	~Bit_FragmentAnalyse();
	//�������캯��
	Bit_FragmentAnalyse( const Bit_FragmentAnalyse &Bit_Frag );
	//�������=������
	Bit_FragmentAnalyse &operator=( const Bit_FragmentAnalyse &Bit_Frag );

	//��̬�ֲ������õ�������Ƭ��̬�����
	//FragNum����Ƭ������FDAResults[]��������Ƭ��̬��������飻
	void FragmentDirectionalAngle( Bit_RocketDataStructure &RockDataStructure , int &FragNum , double FDAResults[] )const;
	//������Ƭ���١�������ٶȡ�ÿ����Ƭ��̬�����ʸ���ϳ���Ƭ��̬�����ٶ�
	double FragmentRealVelocity( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure )const;
	//������Ƭ���١�������ٶȡ���Ƭ��̬�����ٶ������Ҷ�����̬�����
	double FragmentDynamicDirectionalAngle( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure )const;
	//����ը������Ƭ��������ǡ�����Ǽ�����Ƭ�ڵ�������ϵ��ֱ�����꣨����Ƕ�Ϊ���ȣ�
	//CircleAngle:����ǣ�DirectionalAngle������ǣ�FragmentFlyDistance����Ƭ���о���
	CoordinatesPosition ComputeFragmentCoordinateInBodyCoordinate( Bit_FragmentDataStructure &FragDataStructure )const;

	//�жϿռ�ֱ����ƽ���Ƿ��ཻ
	//M��ֱ����һ�㣻VL:ֱ�߷���������P��ƽ����һ�㣻VP��ƽ�淨����
	bool JungleIfIntereForLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP )const;
	//�ռ�ֱ����ƽ�潻��(������ͬһ����ϵ��)
	//M��ֱ����һ�㣻VL:ֱ�߷���������P��ƽ����һ�㣻VP��ƽ�淨����
	CoordinatesPosition ComputePointBetweenLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP )const;
	
	//��Ŀ�����򻮷�����
	//AimDataStructure:Ŀ�꣨��Ŀ������ϵ�����ݽṹ��AimQMP���ѻ��������ƽ�����ݽṹ�����ڴ洢����������Ŀ��������Ϣ
	void AreaDividing( Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &AimQMP );
	//������Ƭ���й켣�ߣ�����Ŀ������ϵ��
	Line ComputeFragmentFlyLine( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure , Bit_AimDataStructure &AimDataStructure )const;
	//�ж���Ƭ��Ŀ����������ƽ���Ƿ���ڽ���
	bool MeetingOrNot( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure )const;
	//������Ƭ���й켣��Ŀ�����򽻵㣨������Ƭ���о�������Զ���ڿ��������ٶ�˥����
	CoordinatesPosition ComputeMeetingPointWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure )const;
	//�жϽ����Ƿ���Ŀ�귶Χ��
	bool InOrNot( Line &FragmentLine , Bit_QuadMeshPlane &QMP )const;
	//��Ƭ���ѻ��������Ŀ�����򽻻�
	//FragDataStructure����Ƭ���ݽṹ��RockDataStructure����������ݽṹ��AimDataStructure��Ŀ�꣨��Ŀ������ϵ�����ݽṹ��AimQMP���ѻ��������ƽ�����ݽṹ�����ڴ洢����������Ŀ��������Ϣ
	int FragmentMeetWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &QMP )const;

	//�ж���Ƭ��Ŀ�����������Ƿ����
	bool WhetherFragmentDamageAimArea( double &FragmentDamageCriterion  , Bit_FragmentDataStructure &FragDataStructure );




private:
	Bit_UnitSystem US_;
	int id_;
};