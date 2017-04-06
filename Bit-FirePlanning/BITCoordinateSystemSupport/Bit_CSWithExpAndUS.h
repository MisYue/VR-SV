/********************************************************************
created:	2015/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��˵���͵�λ�Ƶ�ֱ������ϵ����

*********************************************************************/

#ifndef BITCSWITHEXPANDUS_H__
#define BITCSWITHEXPANDUS_H__

// ��̬�⵼��
#include "BITCoordinateSystemSupport_Global.h"
// ����ϵ
#include "BITUnitsSupport\Bit_UnitSystem.h"
// ����ϵ����
#include "Bit_CSWithExplain.h"


class BITCOORDINATESYSTEMSUPPORT_API Bit_CSWithExpAndUS
{
public:
	// ��
	Bit_CSWithExpAndUS(void);
	// ��ʼ������1
	Bit_CSWithExpAndUS( Bit_CSWithExplain RCSExplain , Bit_UnitSystem US );
	// �����ʼ������2
	Bit_CSWithExpAndUS( int CSId , string Name , CoordinateSystem CS , string Explain , Bit_UnitSystem US );

	// �������캯��
	Bit_CSWithExpAndUS( const Bit_CSWithExpAndUS& cCSExplainUS);
	// ����"="��
	Bit_CSWithExpAndUS& operator= (const Bit_CSWithExpAndUS& cCSExplainUS );
	// ����"=="��
	bool operator == (const Bit_CSWithExpAndUS& cCSExplainUS )const;


	~Bit_CSWithExpAndUS(void);

	//���ó�ʼ����
	void Set_Initial( const int& CSId , const string& Name , const CoordinateSystem& CS , 
		const string& Explain , const Bit_UnitSystem& US );
	//���õ�λ�ƶ�
	inline void Set_US(const Bit_UnitSystem& US );
	//��������ϵ���
	inline void Set_CSId( const int& CSId );

	//�õ���������ֱ������ϵ
	inline Bit_CSWithExplain Get_RCSExplain(void) const;
	//�õ�����ϵ���
	inline int Get_CSId(void) const;
	//�õ�����ϵ����
	inline string Get_Name(void) const;
	//�õ�����ϵ˵��
	inline string Get_Explain(void) const;
	//�õ���λ��
	inline Bit_UnitSystem Get_US(void) const;
	//�õ����ȵ�λ
	inline double Get_LengthUnit(void) const; 
	
private:
	//��������ֱ������ϵ
	Bit_CSWithExplain RCSExplain_;
	//����ϵ
	Bit_UnitSystem US_;
};
#endif
