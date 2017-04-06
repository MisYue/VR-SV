/********************************************************************
created:	2016/8/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��ҩ�ն�����

*********************************************************************/

#ifndef BITTERMINALDATA_H__
#define BITTERMINALDATA_H__

#include "BITProjectileDataBase/Bit_ProjectileDataBase_Global.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"

class BITPROJECTILEDATABASE_API Bit_TerminalData
{
public:
	// �պ���
	Bit_TerminalData(void);
	// ���캯��
	Bit_TerminalData( Bit_UnitSystem US , double TerminalV , double CEP );
	// �������캯��
	Bit_TerminalData( const Bit_TerminalData& cTD );
	// ���صȺ�
	Bit_TerminalData& operator= (const Bit_TerminalData& cTD );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_TerminalData& cTD )const;
	// ���ء�!=���Ⱥ�
	bool operator != (const Bit_TerminalData& cTD )const;

	~Bit_TerminalData(void);

	// ���ó�ʼ��
	inline void Set_Initial( const Bit_UnitSystem& US , const double& TerminalV , const double& CEP );
	// ת����λ
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//�õ��Ƿ���
	inline bool Get_USDefinition(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ��ն��ٶ�
	inline double Get_TerminalV(void)const;
	// �õ�CEP
	inline double Get_CEP(void)const;

private:
	// ��λ��
	Bit_UnitSystem US_;
	// �ն��ٶ�
	double TerminalV_;
	// CEP
	double CEP_;
	//��λ�ƶ���
	bool USDefinition_;
};
#endif
