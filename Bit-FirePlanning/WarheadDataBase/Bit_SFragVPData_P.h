/********************************************************************
created:	2016/06/02
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	������Ƭ�ڵ�������ϵ�е��ٶȺ�λ��

*********************************************************************/

#ifndef BITSFRAGVPDATA_H__
#define BITSFRAGVPDATA_H__

// ��Ƭ��������
#include "Bit_FragmentBaseData.h"
// ս�������ݶ�̬��
#include "WarheadDataBase_Global.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
// ����λ��
#include "MathCalculationSupport/CoordinatesPosition.h"
// ����
#include "MaterialDataBase/Bit_MetalData.h"

class WARHEADDATABASE_API Bit_SFragVPData_P
{
public:
	Bit_SFragVPData_P(void);
	// �������캯��
	Bit_SFragVPData_P( const Bit_SFragVPData_P& cSFD );
	// ���صȺ�
	Bit_SFragVPData_P& operator= (const Bit_SFragVPData_P& cSFD );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_SFragVPData_P& cSFD )const;

	~Bit_SFragVPData_P(void);

	//������ʼ������
	void Set_Initial( const Bit_UnitSystem& US , const int& FId , const Bit_FragmentBaseData& FraBaData
		, const double& SEVelocity , const CoordinatesPosition &SPosition_PCS 
		, const CoordinatesPosition &RPosition_PCS
		, const double& RealSVelocity , const double& RealRTVelocity );

	// ���û�������
	void Set_BaseParameters( const Bit_UnitSystem& US , const int& FId ,const double& Mass 
		, const int& FragmentShape);
	// ������Ƭ������ʼ�ٶ�
	inline void Set_SEVelocity( const double& SEVelocity );
	// �����ڵ�������ϵ�еĳ�ʼλ��
	inline void Set_SPosition_PCS( const double& SPosition_PCS );
	// �����ڵ�������ϵ�е�ʵʱλ��
	inline void Set_RPosition_PCS( const double& RPosition_PCS );
	// ��Ƭʵ�ʳ�ʼ�ٶ�(������ǣ����)

	// ��Ƭʵ��ʵʱ�ٶ�(������ǣ����)

	// ��Ƭ���ٶ�˥��(Velocity Reduction)ϵ��

	//*********�õ�����***********//
	//�õ���Ƭ������ʼ�ٶ�
	inline double Get_SEVelocity( void )const;

private:
	//��λ��
	Bit_UnitSystem US_;
	//��ƬId
	int FId_;
	//��Ƭ��������
	Bit_FragmentBaseData FraBaData_;
	//��Ƭ������ʼ�ٶ�
	double SEVelocity_;
	//�ڵ�������ϵ�еĳ�ʼλ��
	CoordinatesPosition SPosition_PCS_;
	//�ڵ�������ϵ�е�ʵʱλ��
	CoordinatesPosition RPosition_PCS_;
	//��Ƭʵ�ʳ�ʼ�ٶ�(������ǣ����)
	double RealSVelocity_;
	//��Ƭʵ��ʵʱ�ٶ�(������ǣ����)
	double RealRTVelocity_;
	//��λ�ƶ���
	bool USDefinition_;
};
#endif
