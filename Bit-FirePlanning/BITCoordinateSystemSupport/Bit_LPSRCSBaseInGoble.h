/********************************************************************
created:	2016/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�ڵ�������ϵ�е�����ƽ��ռ�ֱ������ϵ(LocalPlaneSpaceRectangularCoordinates)

*********************************************************************/

// ��̬�⵼��
#include "BITCoordinateSystemSupport_Global.h"

//��ѧ��������
//#include "MathCalculationSupport/CoordinatesPosition.h"
//����ϵ����
#include "Bit_CSWithExpAndUS.h"

#ifndef BITLPSRCSBASEINGOBLE_H__
#define BITLPSRCSBASEINGOBLE_H__

class BITCOORDINATESYSTEMSUPPORT_API Bit_LPSRCSBaseInGoble
{
public:
	//�պ���
	Bit_LPSRCSBaseInGoble(void);
	//�����ʼ��
	Bit_LPSRCSBaseInGoble( Bit_CSWithExpAndUS RCS );
	// �������캯��
	Bit_LPSRCSBaseInGoble( const Bit_LPSRCSBaseInGoble& cLPSRCS);
	// ����"="�ź���
	Bit_LPSRCSBaseInGoble& operator= (const Bit_LPSRCSBaseInGoble& cLPSRCS );

	~Bit_LPSRCSBaseInGoble(void);

	//ͨ�����ý�������ϵ�ĳ�ʼ��
	inline void Set_LPSRCSBaseInGoble( const Bit_CSWithExpAndUS& RCS );
	//�õ�����λ�ƺ���������������ϵ
	inline Bit_CSWithExpAndUS Get_RCSExplainAndUS(void)const;
	//�õ�������ֱ������ϵ
	inline Bit_CSWithExplain Get_RCSExplain(void) const;
	//�õ���λ�ƶ�
	inline Bit_UnitSystem Get_RCSUS(void) const;
	//�õ����ȵ�λ
	inline double Get_RCSLengthUnit(void)const;
	//�õ��Ƿ����˵�λ
	inline bool Get_IfUS(void)const;
	//��������ľ��ȡ�γ�Ⱥ͸߶ȵõ���Ӧ�Ŀռ�����(�������곤��)
	CoordinatesPosition ComputeRCSOnB_L_H( const double& B , const double& L, const double&H , const double& H_LengthUnit)const;
	//��������ľ��ȡ�γ�Ⱥ͸߶ȵõ���Ӧ�Ŀռ�����(�ڸö�������ϵ�ĵ�λ����)
	CoordinatesPosition ComputeRCSOnB_L_HInUS( const double& B , const double& L, const double&H)const;

private:
	//��������ֱ������ϵ
	Bit_CSWithExpAndUS RCS_;
	//�ж��Ƿ������˵�λϵͳ
	bool IfUS_;
};
#endif
