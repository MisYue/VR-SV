/********************************************************************
created:	2016/6/2
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	���е�������ϵ�ϵ���Ƭ������
include:	
*********************************************************************/

#ifndef BITFRAGMENTFIELDPCSANALYSIS_H__
#define BITFRAGMENTFIELDPCSANALYSIS_H__
// ��̬�⵼��
#include "WarheadPowerAnalysis_Global.h"
// ��Ƭ���ݿ�
#include "WarheadDataBase/Bit_SFragVPData_P.h"

class WARHEADPOWERANALYSIS_API Bit_FragmentFieldPCSAnalysis
{
public:
	Bit_FragmentFieldPCSAnalysis(void);
	~Bit_FragmentFieldPCSAnalysis(void);
	
	// �������г�ʼֵ������n����Ƭ���ݵĴ洢�ռ䣩
	void Set_Initial( const int& Number_Frg );
	
	// ���õ�i��<N������Ƭ�ĳ���
	void Set_SFInitV( const int& Number , const double& SFInitV);

	// �õ���i��<N������Ƭ���ٶ�
	inline double Get_SFInitV(const int& Number)const;

private:
	// ��Ƭ��Ŀ
	int Number_Frg_;
	Bit_SFragVPData_P *SFD_;
	// �Ƿ�����˳�ʼ������
	bool IfInitialFinished_;

};
#endif
