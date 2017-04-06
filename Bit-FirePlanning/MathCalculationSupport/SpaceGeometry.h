/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���пռ伸����ؼ���

*********************************************************************/

//#pragma once
#include "MathCalculationSupport_Global.h"
////������
//#include "CoordinatesPosition.h"
////�ڵ���
#include "Node.h"
////�ߵ���ѧ��
#include "AdvancedMath.h"
//
//#include "Surface.h"

#ifndef SPACEGEOMETRY_H__
#define SPACEGEOMETRY_H__
//#define pi 3.14159265358979323846			//����Piֵ = 3.1415926

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API SpaceGeometry
{
public:
	SpaceGeometry(void);
	~SpaceGeometry(void);

	//************�ռ��ά�߶μ���***************
	//1.���������ߵķ������ռ��������ߵ���Ǽнǣ��������
	double AcuteAngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	// ���������ߵķ������ռ��������ߵļнǣ��������
    double AngleInTwoLine( const double& lineone_i , const double& lineone_j , 
		const double& lineone_k , const double& linetwo_i , const double& linetwo_j , const double& linetwo_k ) const;
	//����������������������Ǽнǣ��������
	inline double AcuteAngleInTwoVetor( const CoordinatesPosition &V1 , const CoordinatesPosition &V2) const;
    //��������������������нǣ��������
	inline double AngleInTwoVetor( const CoordinatesPosition &V1 , const CoordinatesPosition &V2) const;

	//2.�ж�һ�����ϵ���������һ�����Ƿ���������֮��
	bool JudgePointSiteBetweenTwoPoint( const CoordinatesPosition& JudgePoint ,
		const CoordinatesPosition& FristPoint, const CoordinatesPosition& SecondPoint) const;

	// �жϿռ�����ֱ���Ƿ��ཻ
	bool JudgeIfIntereFor2Lines( const CoordinatesPosition &Ponint_one ,const CoordinatesPosition &Ponint_two
		, const CoordinatesPosition &Vector_one , const CoordinatesPosition &Vector_two )const;

	//3.����ռ�����ֱ�ߵĽ��㣨ֱ����һ�����ֱ�������ķ�ʽ������
	bool  ComputeIntersectionPointToTwoLine(const CoordinatesPosition &Ponint_one 
		,const CoordinatesPosition &Ponint_two, const CoordinatesPosition &Vector_one 
		, const CoordinatesPosition &Vector_two , CoordinatesPosition *InterePoint ) const;
	//4.�ɿռ���1���㡢�������̷������ͽؾ������һ��
	CoordinatesPosition GetAnotherPoint(const CoordinatesPosition& p1  
		, const double& aa , const double &bb , const double& cc , const double& dis) const;
	//5.�ж��������Ƿ���һ��ֱ����
	bool JudgeIfLineFor3Points( const CoordinatesPosition &P1 , const CoordinatesPosition &P2 , const CoordinatesPosition &P3 ) const;
	// �ж�һ������һ����������
	bool JudgeIfPointInTriangle( const CoordinatesPosition &JP , const CoordinatesPosition &P1 
		, const CoordinatesPosition &P2 , const CoordinatesPosition &P3  )const;
	// �ж��ĸ�����ɵ��ı����Ƿ���͹�ı���
	bool JudgeIfConvexQuadOn4Points( const CoordinatesPosition P[4] )const;
	
	// �ж�4�������Ƿ���3���㹲�ߵ�(��������)
	bool JudgeIf3PointsIn1LineFor4Points( const CoordinatesPosition P[4])const;
	// �ж�4�������Ƿ���3���㹲�ߵ�(4������)
	bool JudgeIf3PointsIn1LineFor4Points( const CoordinatesPosition& P0 ,const CoordinatesPosition& P1
		, const CoordinatesPosition& P2 ,const CoordinatesPosition& P3)const;

	//***********************�ռ���������***************
	// ������λ������
	inline CoordinatesPosition VectorStandardization( const CoordinatesPosition &V )const;
	//6.�������������Ĳ��
	inline CoordinatesPosition ComputeCrossProducts( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;
	//7. ���������������ĵ��
	inline double ComputeDotProducts( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;
	//���������������㷨���������ط�����
	inline CoordinatesPosition NormalVectorOn2Vectors( const CoordinatesPosition &V1 , const CoordinatesPosition &V2 )const;

	//8.ͨ�����������ƽ��ķ�����VV�����ط�����
	CoordinatesPosition NormalVectorOn3points( const CoordinatesPosition &P1 , const CoordinatesPosition &P2 , const CoordinatesPosition &P3 ) const;
	//9. ͨ��������������ƽ��ķ�����VV�����ط�����
	CoordinatesPosition NormalVectorOnNpoints( int &n , const CoordinatesPosition Num[] )const;
	//10.�жϿռ��ĵ��Ƿ��棬���淵��true�������淵��flase
	bool JudgeIfCoplanarityFor4Points( const CoordinatesPosition& P1 , const CoordinatesPosition& P2
		, const CoordinatesPosition& P3 , const CoordinatesPosition& P4)const;
    //11. �жϴ��ڵ���3�����Ƿ��棬���淵��true�������淵��flase
    bool JudgeIfCoplanarityForNPoints( const int& n , const CoordinatesPosition Num[] )const;
	//12. �ж�3�������Ͻڵ㣨Node���Ƿ���һ��ƽ���ϣ�n<3�˳�����
	bool JudgeIfCoplanarityForNNodes( const int& n , const Node Nu[] )const;
	
	//******************���νṹ�������*******************
	//13.����Բ̨����������ڼ�����������
	//R����Բ�뾶��r��СԲ�뾶��H����
	inline double ComputeFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//14.�����Բ̨����������ڼ�����������
	//R����Բ�뾶��r��СԲ�뾶��H����
	inline double ComputeHalfFrustumOfAConeVolume( const double& R , const double& r , const double& H ) const;
	//15.����Բ�������������ڼ�����������
	//Diameter��Բֱ����Height����
	inline double ComputeCylinderVolume( const double& Diameter , const double& Height ) const;
	//16.�����Բ�������������ڼ�����������
	//Diameter��Բֱ����Height����
	inline double ComputeHalfCylinderVolume( const double& Diameter , const double& Height ) const;
	//17.����Բ׶�����������ڼ�����������
	//Radius����Բ�뾶��Height����
	inline double ComputeConeVolume( const double& Radius , const double& Height ) const;
	//18.�����Բ׶�����������ڼ�����������
	//Radius����Բ�뾶��Height����
	inline double ComputeHalfConeVolume( const double& Radius , const double& Height )const;
	//19.����������������ڼ�����������
	inline double ComputeSphereVolume( const double& Diameter )const;
	//20.���㳤�������������ڼ�����������
	inline double ComputeCuboidVolume( const double& XLength , const double& YLength , const double& ZLength )const;

	///******************�������������*******************
	//21.�������(�����������ܶ�)
	//Mass��������g��Density���ܶȣ�g/cm^3
	inline double ComputeVolumeOnMassAndDensity( const double& Mass , const double& Density )const;

	//******************��������㼸��������*******************
	//22.�������������뾶
	inline double ComputeSphereRadiusOnVolume( const double& Volume )const;

};
#endif
//}

