/********************************************************************
created:	2015/03/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	��˵������ϵ����

*********************************************************************/

#ifndef BITCSWITHEXPLAIN_H__
#define BITCSWITHEXPLAIN_H__

// ��̬�⵼��
#include "BITCoordinateSystemSupport_Global.h"
// ����ϵ
#include "CoordinateSystem.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CSWithExplain
{
public:
	// �պ���
	Bit_CSWithExplain(void);
	// �����˵������ϵ
	Bit_CSWithExplain( int CSId , string Name , CoordinateSystem CS , string Explain );
	// �������캯��
	Bit_CSWithExplain( const Bit_CSWithExplain& cCSExplain);
	// ����"="��
	Bit_CSWithExplain& operator= (const Bit_CSWithExplain& cCSExplain );
	// ����"=="��
	bool operator == (const Bit_CSWithExplain& cCSExplain )const;

	//�����ĸ�����
	inline void Set_Initial( const int& CSId , const string& Name , const CoordinateSystem& CS , const string& Explain );
	//��������ϵ���
	inline void Set_CSId( const int& CSId );
	//�õ�����ϵId
	inline int Get_CSId(void) const;
	//�õ�����ϵ����
	inline string Get_Name(void) const;
	//�õ�����ϵ
	inline CoordinateSystem Get_CS(void) const;
	//�õ�˵��
	inline string Get_Explain(void) const;


	~Bit_CSWithExplain(void);

private:
	int CSId_;
	string Name_;
	string Explain_;
	CoordinateSystem CS_;
	
};
#endif
