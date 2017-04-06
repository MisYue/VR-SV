/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	������Ա������

*********************************************************************/

#include "BITTargetModelSupport/Bit_TargetModelSupport_Global.h"

// ��λ�ƶ�
#include "BITUnitsSupport/Bit_UnitSystem.h"

#ifndef BITGROUNDAREA_H__
#define BITGROUNDAREA_H__

class BITTARGETMODELSUPPORT_API Bit_GroundArea
{
public:
	// ��
	Bit_GroundArea(void);
	// ��ʼ���ṹ
	Bit_GroundArea( Bit_UnitSystem US , double AreaLength , double AreaWidth
		, double LengthDivideV , double WidthDivideV );
	// �������캯��
	Bit_GroundArea( const Bit_GroundArea& cGA );
	// ���صȺ�
	Bit_GroundArea& operator= (const Bit_GroundArea& cGA );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_GroundArea& cGA )const;
	// ���ء�!=���Ⱥ�
	bool operator != (const Bit_GroundArea& cGA )const;

	~Bit_GroundArea(void);

	// ���ó�ʼ��
	void Set_Initial( const Bit_UnitSystem& US , const double& AreaLength 
		, const double& AreaWidth , const double& LengthDivideV , const double & WidthDivideV );
	// ת����λ
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//�õ��Ƿ���
	inline bool Get_USDefinition(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ�Ŀ�����򳤶�
	inline double Get_AreaLength(void)const;
	// �õ�Ŀ��������
	inline double Get_AreaWidth(void)const;
	// �õ����ȷ��򻮷�ֵ
	inline double Get_LengthDivideV(void)const;
	// ��ȷ��򻮷�ֵ
	inline double Get_WidthDivideV(void)const;
private:
	// ��λ��
	Bit_UnitSystem US_;
	// Ŀ�����򳤶�
	double AreaLength_;
	// Ŀ��������
	double AreaWidth_;
	// ���ȷ��򻮷�ֵ
	double LengthDivideV_;
	// ��ȷ��򻮷�ֵ
	double WidthDivideV_;
	//��λ�ƶ���
	bool USDefinition_;
};
#endif
