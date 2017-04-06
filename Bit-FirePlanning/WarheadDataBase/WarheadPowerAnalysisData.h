/********************************************************************
created:	2015/11/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	Ϊս�������������ṩ���ݽṹ

*********************************************************************/

#ifndef WARHEADDATABASE_H__
#define WARHEADDATABASE_H__

// ��λ������
#include "BITUnitsSupport/Bit_UnitSystem.h"
// ս�������ݶ�̬��
#include "WarheadDataBase_Global.h"
// װҩ���ݿ�
//#include "MaterialDataBase\ChargeData.h"

class WARHEADDATABASE_API WarheadPowerAnalysisData
{
public:
	// �չ��캯��
	WarheadPowerAnalysisData(void);
	// �ṹ���ʼ��
	WarheadPowerAnalysisData( int Warhead_Id , Bit_UnitSystem US , double ShellMass_Clylinder
		, double ChargeMass_Clylinder , double AllMass_Whole , double ChargeMass_Whole , int ChargeID
		, int StructureType , double ShellInterDiameter , double ShellOuterDiameter 
		,double ShellBrokenDiameter , double WarheadLength_Whole , double WarheadLength_Clylinder );

	// �������캯��
	WarheadPowerAnalysisData( const WarheadPowerAnalysisData& cWarData );
	// ���صȺ�
	WarheadPowerAnalysisData& operator= (const WarheadPowerAnalysisData& cWarData );

	// ���ء�==���Ⱥ�
	bool operator == (const WarheadPowerAnalysisData& cWarData )const;

	~WarheadPowerAnalysisData(void);

	// ��ʼ������
	void Set_Initial( const int& Warhead_Id , const Bit_UnitSystem& US ,const double& ShellMass_Clylinder
		, const double& ChargeMass_Clylinder , const double& AllMass_Whole
		, const double& ChargeMass_Whole , const int& ChargeID , const int&StructureType 
		, const double& ShellInterDiameter , const double &ShellOuterDiameter 
		, const double&ShellBrokenDiameter , const double &WarheadLength_Whole
		, const double& WarheadLength_Clylinder );

	// **********��������ת�����µĵ�λ����***********//
	// ������λ��ת�����ǲ����
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	// �õ��Ƿ���
	inline bool Get_IfDefinition(void)const; 
	// �õ�ս�������
	inline int Get_WarheadId(void)const;
	// �õ���λϵ
	inline Bit_UnitSystem Get_US(void)const;
	// �õ�Բ���ο���������ֻ���Բ���Σ�
	inline double Get_ShellMassClylinder(void)const;
	// �õ�Բ����װҩ������ֻ���Բ���Σ�
	inline double Get_ChargeMassClylinder(void)const;
	// �õ�ս������������
	inline double Get_AllMassWhole(void)const;
	// ս��������װҩ����
	inline double Get_ChargeMassWhole(void)const;
	// ս�����ṹ����
	inline int Get_StructureType(void)const;
	// ������ֱ����ֻ���Բ���Σ�
	inline double Get_ShellInterDiameter(void)const;
	// ������ֱ����ֻ���Բ���Σ�
	inline double Get_ShellOuterDiameter(void)const;
	// ��������ֱ����ֻ���Բ���Σ�
	inline double Get_ShellBrokenDiameter(void)const;
	// ս�������峤��
	inline double Get_WarheadLengthWhole(void)const;
	// ս����Բ���γ���
	inline double Get_WarheadLengthClylinder(void)const;
	// �õ�װҩ��
	inline int Get_ChargeId(void)const;

	//**********ͨ��ID����************
	// ͨ��ID���ص�λϵ
	Bit_UnitSystem Get_USOnId( const int& id )const;
	// ͨ��ID����װҩ��
	int Get_ChargeIdOnId( const int& id )const;

private:
	// ս����Id��
	int Warhead_Id_;
	// ��λϵ
	Bit_UnitSystem US_;
	// ս�����ṹ����
	int StructureType_;
	// ������ֱ����ֻ���Բ���Σ�
	double ShellInterDiameter_;
	// ������ֱ����ֻ���Բ���Σ�
	double ShellOutterDiameter_;
	// ��������ֱ����ֻ���Բ���Σ�
	double ShellBrokenDiameter_;
	// ս�������峤��
	double WarheadLength_Whole_;
	// ս����Բ���γ���
	double WarheadLength_Clylinder_;
	// Բ���ο�������
	double ShellMass_Clylinder_; 
	// Բ����װҩ����
	double ChargeMass_Clylinder_; 
	// ս������������
	double AllMass_Whole_;
	// ս��������װҩ����
	double ChargeMass_Whole_;
	// װҩID��
	int ChargeID_;
	// �Ƿ���
	bool IfDefinition_;
};
#endif
