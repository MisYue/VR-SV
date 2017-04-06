/********************************************************************
created:	2016/01/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�������Դ���������

*********************************************************************/

#ifndef MATRIXANDLINEARALGEBRA_H__
#define MATRIXANDLINEARALGEBRA_H__

#include "MathCalculationSupport_Global.h"

//#pragma once
class MATHCALCULATIONSUPPORT_API MatrixAndLinearAlgebra
{
public:
	// ����յľ���
	MatrixAndLinearAlgebra(void);
	// �����ƶ������кͳ�ʼֵ�ľ���
	MatrixAndLinearAlgebra( int r , int c , double *Ma );
	// ���쿽�����캯��
	MatrixAndLinearAlgebra(const MatrixAndLinearAlgebra &cMatrix );
	// ���ع��캯����=��
	MatrixAndLinearAlgebra &operator=( const MatrixAndLinearAlgebra &cMatrix  );
	// ���ع��캯����+��
	MatrixAndLinearAlgebra operator+( const MatrixAndLinearAlgebra &cMatrix  )const;

	~MatrixAndLinearAlgebra(void);

	//������(������С��0�˳�����)
	inline void Set_Matrixrow(const int& M_r );
	//������

	//���ó�ʼֵ

private:
	// ������
	int Matrix_row;
	// ������
	int Matrix_column;
	// һά����ָ�� 
	double *Matrix_P;
};

#endif

