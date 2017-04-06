//#pragma once
/********************************************************************
created:	2016/06/22
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��Ƭ��������

*********************************************************************/

#ifndef BITFRAGMENTBASEDAtA_H__
#define BITFRAGMENTBASEDAtA_H__

// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
// ��������
#include "MaterialDataBase/Bit_MetalData.h"
// ս�������ݶ�̬��
#include "WarheadDataBase_Global.h"

class WARHEADDATABASE_API Bit_FragmentBaseData
{
public:
	//�պ���
	Bit_FragmentBaseData(void);
	// �������캯��
	Bit_FragmentBaseData( const Bit_FragmentBaseData& cFBD );
	// ���صȺ�
	Bit_FragmentBaseData& operator= (const Bit_FragmentBaseData& cFBD );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_FragmentBaseData& cFBD )const;

	~Bit_FragmentBaseData(void);

	//������ʼ������
	void Set_Initial( const Bit_UnitSystem& US , const int& FragmentShape 
		, const Bit_MetalData *FragMaterial , const double& VRCoefficient
		, const bool &USDefinition, const double & Mass );

private:
	//��λ��
	Bit_UnitSystem US_;
	//��Ƭ��״
	int FragmentShape_;
	//����������Ƭ����
	Bit_MetalData *FragMaterial_;
	//��Ƭ���ٶ�˥��(Velocity Reduction)ϵ��
	double VRCoefficient_;
	//��λ�ƶ���
	bool USDefinition_;
	//��Ƭ����
	double Mass_;
};
#endif
