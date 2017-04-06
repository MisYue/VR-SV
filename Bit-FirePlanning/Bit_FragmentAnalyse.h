/********************************************************************
Creating Date:	2016/04/15
 
File Ext:	h

Purpose:	破片毁伤分析

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
	//构造函数初始化
	Bit_FragmentAnalyse( Bit_UnitSystem &US );
	~Bit_FragmentAnalyse();
	//拷贝构造函数
	Bit_FragmentAnalyse( const Bit_FragmentAnalyse &Bit_Frag );
	//运算符“=”重载
	Bit_FragmentAnalyse &operator=( const Bit_FragmentAnalyse &Bit_Frag );

	//正态分布抽样得到所有破片静态方向角
	//FragNum：破片数量；FDAResults[]：所有破片静态方向角数组；
	void FragmentDirectionalAngle( Bit_RocketDataStructure &RockDataStructure , int &FragNum , double FDAResults[] )const;
	//根据破片初速、火箭弹速度、每个破片静态方向角矢量合成破片动态飞行速度
	double FragmentRealVelocity( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure )const;
	//根据破片初速、火箭弹速度、破片动态飞行速度用余弦定理反求动态方向角
	double FragmentDynamicDirectionalAngle( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure )const;
	//根据炸点与破片飞行周向角、方向角计算破片在弹体坐标系内直角坐标（输入角度为弧度）
	//CircleAngle:周向角；DirectionalAngle：方向角；FragmentFlyDistance：破片飞行距离
	CoordinatesPosition ComputeFragmentCoordinateInBodyCoordinate( Bit_FragmentDataStructure &FragDataStructure )const;

	//判断空间直线与平面是否相交
	//M：直线上一点；VL:直线方向向量；P：平面上一点；VP：平面法向量
	bool JungleIfIntereForLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP )const;
	//空间直线与平面交点(两者在同一坐标系内)
	//M：直线上一点；VL:直线方向向量；P：平面上一点；VP：平面法向量
	CoordinatesPosition ComputePointBetweenLineAndPlane( CoordinatesPosition M , CoordinatesPosition VL , CoordinatesPosition N , CoordinatesPosition VP )const;
	
	//将目标区域划分网格
	//AimDataStructure:目标（含目标坐标系）数据结构；AimQMP：已划分网格的平面数据结构，用于存储划分网格后的目标区域信息
	void AreaDividing( Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &AimQMP );
	//计算破片飞行轨迹线（基于目标坐标系）
	Line ComputeFragmentFlyLine( Bit_FragmentDataStructure &FragDataStructure , Bit_RocketDataStructure &RockDataStructure , Bit_AimDataStructure &AimDataStructure )const;
	//判断破片与目标区域所在平面是否存在交点
	bool MeetingOrNot( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure )const;
	//计算破片飞行轨迹与目标区域交点（假设破片飞行距离无限远，在空气中无速度衰减）
	CoordinatesPosition ComputeMeetingPointWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure )const;
	//判断交点是否在目标范围内
	bool InOrNot( Line &FragmentLine , Bit_QuadMeshPlane &QMP )const;
	//破片与已划分网格的目标区域交汇
	//FragDataStructure：破片数据结构；RockDataStructure：火箭弹数据结构；AimDataStructure：目标（含目标坐标系）数据结构；AimQMP：已划分网格的平面数据结构，用于存储划分网格后的目标区域信息
	int FragmentMeetWithArea( Line &FragmentLine , Bit_AimDataStructure &AimDataStructure , Bit_QuadMeshPlane &QMP )const;

	//判断破片对目标区域网格是否毁伤
	bool WhetherFragmentDamageAimArea( double &FragmentDamageCriterion  , Bit_FragmentDataStructure &FragDataStructure );




private:
	Bit_UnitSystem US_;
	int id_;
};