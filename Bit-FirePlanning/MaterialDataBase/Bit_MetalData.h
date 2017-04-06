//#pragma once

/********************************************************************
created:	2016/06/02
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ϊ�����������ݿ��ṩ���ݽṹ

*********************************************************************/

#ifndef BITMETALDATA_H__
#define BITMETALDATA_H__

// ��̬��
#include "MaterialDataBase_Global.h"
// ��λ��
#include "BITUnitsSupport/Bit_UnitSystem.h"
// Ӳ��
#include "Bit_Hardness.h"

class MATERIALDATABASE_API Bit_MetalData
{
public:
	// �պ���
	Bit_MetalData(void);
	// �����ʼ������
	Bit_MetalData( Bit_UnitSystem US , string MMId , string MMaterialName
		, string MMaterialClass , double MMaterialDensity ,double CompressYieldStrength[2] 
		, double DrawYieldStrength[2] , double CompressLimitationStrength[2] 
		, double DrawLimitationStrength[2] , Bit_Hardness MHard , double DrawElongation[2] 
		, double DrawSectionShrinkage[2] , double YoungModulus[2] , double YawTangestModulus[2] 
		, double CompressionModulus[2] , double CompressionTangestModulus[2] , double PoissonRatio );
	// �������캯��
	Bit_MetalData( const Bit_MetalData& cMD );
	// ���ء�=��
	Bit_MetalData& operator= (const Bit_MetalData& cMD );
	// ���ء�==��
	bool operator == (const Bit_MetalData& cMD )const;

	// ��ʼ������
	~Bit_MetalData(void);

	//��ʼ������
	void Set_Initial( const Bit_UnitSystem& US , const string& MMId 
		, const string& MMaterialName , const string& MMaterialClass 
		, const double& MMaterialDensity , const double CompressYieldStrength[2] 
		, const double DrawYieldStrength[2] , const double CompressLimitationStrength[2] 
		, const double DrawLimitationStrength[2] , const Bit_Hardness& MHard 
		, const double DrawElongation[2] , const double DrawSectionShrinkage[2] 
		, const double YoungModulus[2] , const double YawTangestModulus[2] 
		, const double CompressionModulus[2] , const double CompressionTangestModulus[2]
		, const double PoissonRatio );

	//�õ��Ƿ���
	inline bool Get_IfDefinition(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ����ϱ��
	inline string Get_MMId(void)const;
	// �õ���������
	inline string Get_Name(void)const;
	// �õ����ϴ���
	inline string Get_Class(void)const;
	// �õ������ܶȣ���ǰ��λ�ƣ�
	inline double Get_Density(void)const;
	// �õ������ܶ�(mm-g-us)
	inline double Get_DensityForC(void)const;
	// �õ�ѹ��ǿ�ȵ�Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_CompressYieldStrength_SR(void)const;
	// �õ�ѹ��ǿ�ȣ���ǰ��λ�ƣ�
	inline double Get_CompressYieldStrength_St(void)const;
	// �õ�ѹ��ǿ�ȼ�Ӧ���ʣ���ǰ��λ�ƣ�
	void Get_CompressYieldStrength( double *SR , double *St )const;

	// �õ����켫��ǿ�ȵ�Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_DrawLimitationStrength_SR(void)const;
	// �õ����켫��ǿ�ȣ���ǰ��λ�ƣ�
	inline double Get_DrawLimitationStrength_St(void)const;

	//�õ�Ӳ��
	inline Bit_Hardness Get_MHard(void)const;

	//�õ����������ʵ�Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_DrawElongation_SR(void)const;
	//�õ�����������
	inline double Get_DrawElongation_Value(void)const;

	//�õ��������������Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_DrawSectionShrinkage_SR(void)const;
	//�õ��������������
	inline double Get_DrawSectionShrinkage_Value(void)const;

	//�õ�����ģ��Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_YoungModulus_SR(void)const;
	//�õ�����ģ��
	inline double Get_YoungModulus_Value(void)const;

	//�õ���������ģ��Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_YawTangestModulus_SR(void)const;
	//�õ���������ģ��
	inline double Get_YawTangestModulus_Value(void)const;

	//�õ�ѹ��ģ��Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_CompressionModulus_SR(void)const;
	//�õ�ѹ��ģ��
	inline double Get_CompressionModulus_Value(void)const;

	//ѹ������ģ��Ӧ���ʣ���ǰ��λ�ƣ�
	inline double Get_CompressionTangestModulus_SR(void)const;
	//�õ�ѹ��ģ��
	inline double Get_CompressionTangestModulus_Value(void)const;

	//�õ����ɱ�
	inline double Get_PoissonRatio(void)const;

	// ��������ת�����µĵ�λ����


	//����õ�������ǿ��

	// double
private:
	// ��λϵ
	Bit_UnitSystem US_;
	//(�������Ϻţ��Բ��Ͽ�)
	string MMId_;
	//��������
	string MMaterialName_;
	//���ϴ���
	string MMaterialClass_;
	//�����ܶ�
	double MMaterialDensity_;
	//ѹ������ǿ��(��Ӧ����)
	double CompressYieldStrength_[2];
	//��������ǿ��(��Ӧ����)
	double DrawYieldStrength_[2];
	//ѹ������ǿ��(��Ӧ����)
	double CompressLimitationStrength_[2];
	//���켫��ǿ��(��Ӧ����)
	double DrawLimitationStrength_[2];
	//Ӳ��
	Bit_Hardness MHard_;
	//����������
	double DrawElongation_[2];
	//�������������
	double DrawSectionShrinkage_[2];
	//����ģ��
	double YoungModulus_[2];
	//��������(tangent modulus)ģ��
	double YawTangestModulus_[2];
	//ѹ��ģ��
	double CompressionModulus_[2];
	//ѹ������ģ��
	double CompressionTangestModulus_[2];
	//���ɱ�
	double PoissonRatio_;
	//�Ƿ���
	bool IfDefinition_;
};
#endif
