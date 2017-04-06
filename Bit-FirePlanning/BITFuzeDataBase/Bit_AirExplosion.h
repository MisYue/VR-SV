/********************************************************************
created:	2016/08/21
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ձ��������

*********************************************************************/

#include "Bit_FuzeDataBase_Global.h"
#include "BITUnitsSupport/Bit_UnitSystem.h"
#ifndef BITAIREXPLOSION_H__
#define BITAIREXPLOSION_H__

class BITFUZEDATABASE_API Bit_AirExplosion
{
public:
	// �պ���
	Bit_AirExplosion(void);
	// ��ʼ���캯��
	Bit_AirExplosion( const Bit_UnitSystem& US , const double& AirExplosionHE 
		, const double& AirExplosionHS );
	// �������캯��
	Bit_AirExplosion( const Bit_AirExplosion& cAE );
	// ���صȺ�
	Bit_AirExplosion& operator= (const Bit_AirExplosion& cAE );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_AirExplosion& cAE )const;
	// ���ء�!=���Ⱥ�
	bool operator != (const Bit_AirExplosion& cAE )const;

	~Bit_AirExplosion(void);

	// ���ó�ʼ��
	inline void Set_Initial( const Bit_UnitSystem& US 
		, const double& AirExplosionHE , const double& AirExplosionHS );
	// ת����λ
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//�õ��Ƿ���
	inline bool Get_USDefinition(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;

	// ��ը�߶�����
	inline double Get_AirExplosionHE(void)const;
	// ��ը�߶ȱ�׼��
	inline double Get_AirExplosionHS(void)const;

private:
	// ��λ��
	Bit_UnitSystem US_;
	// ��ը�߶�����
	double AirExplosionHE_;
	// ��ը�߶ȱ�׼��
	double AirExplosionHS_;
	//��λ�ƶ���
	bool USDefinition_;
};
#endif
