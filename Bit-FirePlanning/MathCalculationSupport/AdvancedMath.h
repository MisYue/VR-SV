/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��math.h�����Ͻ��и���һ�����ѧ����

*********************************************************************/

// #include <cstdlib>
// #include <time.h>
// #include <math.h>

// #pragma once
#ifndef ADVANCEDMATH_H__
#define ADVANCEDMATH_H__

#include "MathCalculationSupport_Global.h"
// �������
#include "CoordinatesPosition.h"

//namespace BIT
//{
class MATHCALCULATIONSUPPORT_API AdvancedMath
{
public:
	AdvancedMath(void);
	~AdvancedMath(void);

	// �Ƕ�ת����
	inline double AngleToRadian(const double& angle) const;
	// ����ת�Ƕ�
	inline double RadianToAngle(const double& radian) const;
	// ���ֵ
	double LinearInterpolation(const double& xx, const double x_table[], const double y_table[], const int&jj)const;
	//����Delta(�¶���)
	inline double ComputeDelta(const double& aa , const double& bb , const double& cc)const;
	// ���һԪ���η���( a * x^2 + b * x + c = 0)
	double function_1yuan2ci(const double& aa, const double& bb, const double& cc, const double& x_min, const double& x_max)const;
	// ��һԪ���η��̽ϴ��( a * x^2 + b * x + c = 0)
	double function_1yuan2ci_Max(const double& aa, const double& bb, const double& cc)const ;
	// ��һԪ���η��̽�С��( a * x^2 + b * x + c = 0)
	double function_1yuan2ci_Min(const double& aa, const double& bb, const double& cc)const ;

	//==========[���� �޸� 2015-7-8]==========
	// ����Ԫ���η���( a * x^2 + b * y^2 + c * x * y + d * x + e * y + f = 0)
	double function_2yuan2ci(const double& aa, const  double& bb, const double& cc, const double& dd, const double& ee,
		const double& ff, const double& y_min, const double& y_max, const double& xx)const ;
	// ��Ԫ���η�����( a * x^2 + b * y^2 + c * x * y + d * x + e * y + f = 0) 
	/*double function2yuan2ci_differential(const double& aa, const double& bb, const double& cc, const double& dd, const double& ee,
		const double& ff, const double& y_min, const double& y_max, const double& xx)const ;*/

	//==========[���� ����ģ�庯���Ϻ� 2015-7-8]==========
	// ��������֮��
	inline int TheDefferenceofTwoIntegers(const int& n_max, const int& n_min)const ;
	// ����������֮��
	inline double TheDefferenceofTwoFloatNumber(const double& n_max ,const double& n_min)const ;

	// ���������еĽ�С��
	inline double CompareForMin(const double& aa , const double& bb)const ;
	// ���������еĽϴ���
	inline double CompareForMax(const double& aa , const double& bb)const ;
	// ��һ��(int)���е���С������
	int ComputeMinValueInArrayOnInt(const int& n, const int array[])const;
	// ��һ��(int)���е����������
	int ComputeMaxValueInArrayOnInt(const int& n, const int array[])const;
	// ��һ��(double)���е���С������
	double ComputeMinValueInArrayOnDouble(const int& n, const double array[])const ;
	// ����һ��(double)���е����ֵ
	double ComputeMaxValueInArrayOnDouble(const int& n, const double array[] )const ;
	// ����һ��������������ֵ�Ĳ�(��ֵ)
	double ComputeMaxTwoValueDiffereconst (int& n, const double array[] )const ;
	// ����һ��������С������ֵ�Ĳ��ֵ��
	double ComputeMinTwoValueDiffereconst (int& n, const double array[] )const ;

	// ȥ�������е�ĳ�������γ�һ���µ�����
	int DeleteValueInArray(const int&old_n , const double &value , const double old_array[], double new_array[] )const;

	// ����ĳһ������һ����������
	int ComputeSNInArray( const int& n, const double array[] , const double & value )const ;

	//ȥ���ظ�����㷵���µ����������
	void NewArrayPointDistinct( const int&Old_n , const CoordinatesPosition Old_P[], int *New_n , CoordinatesPosition New_P[] ) const;

	// ����Ƕ����¼��ġ��롱��1-(1-P1)(1-P2)...������
	double TheAndComputation(const int& n, const double single_p[] )const ;

	// �������Ҷ���֪�������߼���Ƕȣ�
	//IncludedAngleSideOneLength���нǱ�1���ȣ�
	//IncludedAngleSideTwoLength���нǱ�2���ȣ�
	//IncludedAngleFaceSideLength���нǶԱ߳���
	double ComputeFaceSideAngle(const double& angle_side_one_length ,
		const double& angle_side_another_length , const double& face_side_length )const ;

	// ����׼ֵ��Χֵ����Ϊ��׼ֵ
	double ComputeSimilarStandardValue( const double& similar_value ,
		const double& input_value , const double& tolerance_value )const ;
	// ����ĳֵ��С��1e-12����Ϊĳֵ
	inline double ApproximateValueForBiggerLittle( const double& Value , const double& Input_value )const;
	// С��ĳֵ��С��1e-12����Ϊĳֵ
	inline double ApproximateValueForSmallerLittle( const double& Value , const double& Input_value )const;

	// ��̬������㳤��
	inline int ComputeIntArrayLenth_Static(const int Arry[] )const;

	// ��̬�������int�����鳤��
	inline int ComputeIntArrayLenth_Dynamic( const int *N )const;
	// ��̬�������double�����鳤��
	inline int ComputeDoubleArrayLenth_Dynamic( const double *N )const;

	// *************��ʽ����㷨***********
	//ʵ�ֶ� y = ax ��ʽ�����Ĳ���a���й���,������С���˷�
	double FitAFor_Ax (const int& n , const double dx[], const double dy[] )const;

	//**************������ϼ���*************
	// ����n�Ľ׳�
	int ComputeFactorialForN( const int& n)const;
};
//}

#endif