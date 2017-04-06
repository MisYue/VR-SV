/********************************************************************
Creating Date:	2016/04/26
 
File Ext:	h

Purpose:	目标（含目标坐标系）数据结构

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
	//构造函数初始化
	//id:目标ID号；HitPosition:炸点在目标坐标系内坐标；AimCenterCP:目标区域中心点坐标；Long:目标区域长度；Wide：目标区域宽度；
	//FristNode：划分产生的第一个节点号；FristElement：划分产生的第一个单元号；
	//N_02：在0号和2号线上划分单元大小(默认长度方向为0号和2号线)；N_13：在1号和3号线上划分单元大小(默认宽度方向为1号和3号线)；
	//AimLat:目标中心点纬度；AimLon：目标中心点经度;AimPoint:瞄准点在目标坐标系内坐标（不考虑CEP，界面输入）
	Bit_AimDataStructure( int &id , CoordinatesPosition &HitPosition , double &Long , double &Wide,
	 int& FristNode , int& FristElement , double& N_02 , double &N_13 , double &AimLat , double &AimLon , CoordinatesPosition &AimPoint );
	~Bit_AimDataStructure();
	//拷贝构造函数
	Bit_AimDataStructure( const Bit_AimDataStructure &Bit_Aim );
	//运算符“=”重载
	Bit_AimDataStructure &operator=( const Bit_AimDataStructure &Bit_Aim );

	//设置目标ID值
	void Set_AimID( int &Aim_ID );
	//设置炸点在目标坐标系内坐标
	void Set_HitPosition( CoordinatesPosition &HitPositionInAim );
	////设置目标区域中心点坐标
	//void Set_AimCenterCP( CoordinatesPosition &AimCenterCPInAim );
	////设置目标区域四个顶点坐标
	//void Set_AimArea( CoordinatesPosition AimAreaInAim[4] );
	//设置划分产生的第一个节点号
	void Set_FristNode( int &FristNodeInAim );
	//设置划分产生的第一个单元号
	void Set_FristElement( int &FristElementInAim );
	//设置在0号和2号线上划分单元大小
	void Set_N_02( double &N_02InAim );
	//设置在1号和3号线上划分单元大小
	void Set_N_13( double &N_13InAim );
	//设置目标中心点纬度
	void Set_AimLat( double &AimLatInAim );
	//设置目标中心点经度
	void Set_AimLon( double &AimLonInAim );
	//设置瞄准点在目标坐标系内坐标
	void Set_AimPoint( CoordinatesPosition &AimPointInAim );


	//得到目标ID
	int Get_AimID( void )const;
	//得到炸点在目标坐标系内坐标
	CoordinatesPosition Get_HitPosition( void )const;
	////得到目标区域中心点坐标
	//CoordinatesPosition Get_AimCenterCP( void )const;
	////得到目标区域四个顶点坐标
	//void Get_AimArea( CoordinatesPosition AimAreaPoint[4] )const;
	//得到目标区域四个顶点坐标
	void Get_AimArea( CoordinatesPosition AimAreaPoint[4] )const;
	//得到划分产生的第一个节点号
	int Get_FristNode( void )const;
	//得到划分产生的第一个单元号
	int Get_FristElement( void )const;
	//得到在0号和2号线上划分单元大小
	double Get_N_02( void )const;
	//得到在1号和3号线上划分单元大小
	double Get_N_13( void )const;
	//得到目标中心点纬度
	double Get_AimLat( void )const;
	//得到目标中心点经度
	double Get_AimLon( void )const;
	//得到瞄准点在目标坐标系内坐标
	CoordinatesPosition Get_AimPoint( void );


	//*****************************计算函数******************************//
	//由目标区域长宽计算四个顶点坐标
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