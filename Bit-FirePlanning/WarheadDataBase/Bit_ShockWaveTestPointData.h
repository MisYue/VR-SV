/********************************************************************
created:	2016/03/19
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	�����������Ե����ݵ����ݽṹ

*********************************************************************/

#ifndef BITSHOCKWAVETESTPOINTDATA_H__
#define BITSHOCKWAVETESTPOINTDATA_H__


// ս�������ݶ�̬��
#include "WarheadDataBase_Global.h"
// ������
#include "BITCoordinateSystemSupport/Bit_CylinderCoordinate.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 2D����
#include "MathCalculationSupport/Bit_2DCurve.h"

class WARHEADDATABASE_API Bit_ShockWaveTestPointData
{
public:
	// �պ���
	Bit_ShockWaveTestPointData(void);
	// ��ʼ�����캯��
	Bit_ShockWaveTestPointData( int TestPoint_Id , string Exp 
		, Bit_UnitSystem US , Bit_CylinderCoordinate Position_CC 
		, Bit_2DCurve Curve );
	// �������캯��
	Bit_ShockWaveTestPointData( const Bit_ShockWaveTestPointData& cSWTPD );
	// ���صȺ�
	Bit_ShockWaveTestPointData& operator= (const Bit_ShockWaveTestPointData& cSWTPD );
	// ���ء�==���Ⱥ�
	bool operator == (const Bit_ShockWaveTestPointData& cSWTPD )const;

	~Bit_ShockWaveTestPointData(void);

	// �������г�ʼֵ
	void Set_Initial( const int& TestPoint_Id , const string& Exp ,const Bit_UnitSystem& US
		, const Bit_CylinderCoordinate& Position_CC , const Bit_2DCurve& Curve );
	// ���ó�ѹ��ֵ
	inline void Set_OverPressure( const double& OverPressure );
	// ���ñȳ���
	inline void Set_SpecificImpulse( const double& SpecificImpulse );

	// �õ��Ƿ���
	inline bool Get_IfDefinition(void)const; 
	// �õ����Ե�ID
	inline int Get_TestPointId(void)const;
	// �õ����Ե�����
	inline string Get_Explain(void)const;
	// �õ����Ե�����(Բ������ϵ)
	inline Bit_CylinderCoordinate Get_PositionCC(void)const;
	// �õ���λ��
	inline Bit_UnitSystem Get_US(void)const;
	// �õ����Ե�����
	inline Bit_2DCurve Get_2DCurve(void)const;
	// �õ���ѹ
	inline double Get_OverPressure(void)const;
	// �õ��ȳ���
	inline double Get_SpecificImpulse(void)const;

	// �������߻�ó�ѹ

	// �������߻�ñȳ���

private:
	//���Ե�ID
	int TestPoint_Id_;
	//���Ե�����
	string Exp_;
	//���Ե�λ��
	Bit_CylinderCoordinate Position_CC_;
	//�洢��λ�ƶ�
	Bit_UnitSystem US_;
	//���Ե�����
	Bit_2DCurve Curve_;
	// ��ѹ
	double OverPressure_;
	// �ȳ���
	double SpecificImpulse_;
	// �Ƿ���
	bool IfDefinition_;
	// ��ѹ�ֹ����붨��
	bool InPutOP_;
	// �ȳ����ֹ����붨��
	bool InPutSP_;
};

#endif

