// #pragma once
/********************************************************************
created:	2016/06/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	硬度数据结构

*********************************************************************/

#ifndef BITHARDNESS_H__
#define BITHARDNESS_H__

// 动态库
#include "MaterialDataBase_Global.h"


class MATERIALDATABASE_API Bit_Hardness
{
public:
	// 空函数
	Bit_Hardness(void);
	// 构造函数初始化
	Bit_Hardness( int HardType , double HardValue );
	// 拷贝构造函数
	Bit_Hardness( const Bit_Hardness& cH );
	// 重载“=”
	Bit_Hardness& operator= (const Bit_Hardness& cH );
	// 重载“==”
	bool operator == (const Bit_Hardness& cH )const;
	// 析构
	~Bit_Hardness(void);
	//初始化设置
	void Set_Initial( const int & HardType , const double & HardValue);
	//得到硬度类型
	inline int Get_HardType(void)const;
	//得到硬度值
	inline double Get_HardValue(void)const;

private:
	int HardType_;
	double HardValue_;
};

#endif