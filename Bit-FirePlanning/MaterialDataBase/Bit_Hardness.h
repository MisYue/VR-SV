// #pragma once
/********************************************************************
created:	2016/06/04
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ӳ�����ݽṹ

*********************************************************************/

#ifndef BITHARDNESS_H__
#define BITHARDNESS_H__

// ��̬��
#include "MaterialDataBase_Global.h"


class MATERIALDATABASE_API Bit_Hardness
{
public:
	// �պ���
	Bit_Hardness(void);
	// ���캯����ʼ��
	Bit_Hardness( int HardType , double HardValue );
	// �������캯��
	Bit_Hardness( const Bit_Hardness& cH );
	// ���ء�=��
	Bit_Hardness& operator= (const Bit_Hardness& cH );
	// ���ء�==��
	bool operator == (const Bit_Hardness& cH )const;
	// ����
	~Bit_Hardness(void);
	//��ʼ������
	void Set_Initial( const int & HardType , const double & HardValue);
	//�õ�Ӳ������
	inline int Get_HardType(void)const;
	//�õ�Ӳ��ֵ
	inline double Get_HardValue(void)const;

private:
	int HardType_;
	double HardValue_;
};

#endif