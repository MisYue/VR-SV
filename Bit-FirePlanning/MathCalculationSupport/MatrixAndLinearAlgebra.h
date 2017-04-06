/********************************************************************
created:	2016/01/30
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	矩阵及线性代数计算类

*********************************************************************/

#ifndef MATRIXANDLINEARALGEBRA_H__
#define MATRIXANDLINEARALGEBRA_H__

#include "MathCalculationSupport_Global.h"

//#pragma once
class MATHCALCULATIONSUPPORT_API MatrixAndLinearAlgebra
{
public:
	// 构造空的矩阵
	MatrixAndLinearAlgebra(void);
	// 构造制定行列列和初始值的矩阵
	MatrixAndLinearAlgebra( int r , int c , double *Ma );
	// 构造拷贝构造函数
	MatrixAndLinearAlgebra(const MatrixAndLinearAlgebra &cMatrix );
	// 重载构造函数“=”
	MatrixAndLinearAlgebra &operator=( const MatrixAndLinearAlgebra &cMatrix  );
	// 重载构造函数“+”
	MatrixAndLinearAlgebra operator+( const MatrixAndLinearAlgebra &cMatrix  )const;

	~MatrixAndLinearAlgebra(void);

	//设置行(输入数小于0退出程序)
	inline void Set_Matrixrow(const int& M_r );
	//设置列

	//设置初始值

private:
	// 矩阵行
	int Matrix_row;
	// 矩阵列
	int Matrix_column;
	// 一维数组指针 
	double *Matrix_P;
};

#endif

