/*
    ��������������趨
	2016-07-01
	ZXD
*/
#ifndef _ROCKARGUMENTDIALOG_H
#define _ROCKARGUMENTDIALOG_H
#include "Lib.h"
#include<QtGui/QLineEdit>
//LG_Struct
struct LGRockParameter
{
	//1
	int    FragmentNumber;                      //��Ƭ����
	double Frag_Mass;                       //��Ƭ����
	
	//2
	double Rock_WarheadStaticAngle;        //�����ս������̬��ɢ��
	double Rock_WarheadStaticAngleToCenter;//ս������̬��ɢ�Ƿֲ��������뵯��ϵx��н�
	double Rock_RocketVelocity;            //������ٶ�
	double Rock_CEP;                       //�����CEP

	//3
	double ShellInterDiameter;              //Բ���ھ�
	double ShellOuterDiameter;              //Բ���⾶
	double ShellBrokenDiameter;             //Բ���ƾ�
	double ShellMass_Clylinder;             //Բ���ο�������
	double ChargeMass_Clylinder;            //Բ����װҩ����
	double AllMass_Whole;                   //ս������������
	double ChargeMass_Whole;                //װҩ��������
	double WarheadLength_Whole;             //��ͷȫ������
	double WarheadLength_Clylinder;         //��ͷԲ������

	//4
	double Density;                         //װҩ�ܶ�
	double ExplosionVelocity;               //װҩ����
	double ExplosionHeat;                   //װҩ����
	double ExplosinPressure;                //װҩ��ѹ

	//5
	double Frag_SDA;                        //��Ƭ��̬��ɢ��
	double Frag_dis;                        //��Ƭ��ɢ����
	double Frag_ResidualVelocity_Initialization;//��Ƭ�뾶�ٶ�
	double SC;                                  //������Ƭ
	double ASL;                                 //���θ߶�
	double RC;                                  //��������ϵ��

	//6
	double FireLat;                         //�����γ��
    double FireLon;                         //����㾭��
	double AimLat;                          //��׼�㾭��
	double AimLon;                          //��׼��γ��
	double BHE;                             //ը������
	double BHD;                             //ը�߱�׼��
	
	//7
	double Frag_FragmentDamageCriterion;        //�����о�
	double ShockWavePressure;
	//8
	int    InterpolationNumber;                 //��ֵ�����ݸ���
	std::vector<double>  FallingAngle;
	std::vector<double>  FireDistance;
	LGRockParameter()
	{
		//1
		FragmentNumber = 1;                      //��Ƭ����
		Frag_Mass = 0.001;                       //��Ƭ����

		//2
		Rock_WarheadStaticAngle = 0.0;        //�����ս������̬��ɢ��
		Rock_WarheadStaticAngleToCenter= 0.0;//ս������̬��ɢ�Ƿֲ��������뵯��ϵx��н�
		Rock_RocketVelocity = 0.0;            //������ٶ�
		Rock_CEP = 0.0;                       //�����CEP

		//3
		ShellInterDiameter = 0.0;              //Բ���ھ�
		ShellOuterDiameter = 0.0;              //Բ���⾶
		ShellBrokenDiameter = 0.0;             //Բ���ƾ�
		ShellMass_Clylinder = 0.0;             //Բ���ο�������
		ChargeMass_Clylinder = 0.0;            //Բ����װҩ����
		AllMass_Whole = 0.0;                   //ս������������
		ChargeMass_Whole = 0.0;                //װҩ��������
		WarheadLength_Whole = 0.0;             //��ͷ����
		WarheadLength_Clylinder = 0.0;         //��ͷԲ������
		//װҩ
		Density = 0.0;                         //װҩ�ܶ�
		ExplosionVelocity = 0.0;               //װҩ����
		ExplosionHeat = 0.0;                   //װҩ����
		ExplosinPressure = 0.0;                //װҩ��ѹ
		//
		Frag_SDA = 0.0;                        //��Ƭ��̬��ɢ��
		Frag_dis = 0.0;                        //��Ƭ��ɢ����
		Frag_ResidualVelocity_Initialization = 0.0;//��Ƭ�뾶�ٶ�
		SC = 0.0;                                  //������Ƭ
		ASL = 0.0;                                 //���θ߶�
		RC = 0.0;                                  //��������ϵ��

		//6
		FireLat = 0.0;                         //�����γ��
		FireLon = 0.0;                         //����㾭��
		AimLat = 0.0;
		AimLon = 0.0;
		BHE = 0.0;                             //ը������
		BHD = 0.0;                             //ը�߱�׼��

		//7
		Frag_FragmentDamageCriterion = 0.0;        //�����о�
		ShockWavePressure = 0.0;
		//8
		InterpolationNumber = 0;                 //��ֵ�����ݸ���
	}
	LGRockParameter& operator=(const LGRockParameter &sour)
	{
		if (this != &sour)
		{
			//1
			FragmentNumber = sour.FragmentNumber;                      //��Ƭ����
			Frag_Mass = sour.Frag_Mass;                       //��Ƭ����

			//2
			Rock_WarheadStaticAngle = sour.Rock_WarheadStaticAngle;        //�����ս������̬��ɢ��
			Rock_WarheadStaticAngleToCenter= sour.Rock_WarheadStaticAngleToCenter;//ս������̬��ɢ�Ƿֲ��������뵯��ϵx��н�
			Rock_RocketVelocity = sour.Rock_RocketVelocity;            //������ٶ�
			Rock_CEP = sour.Rock_CEP;                       //�����CEP

			//3
			ShellInterDiameter = sour.ShellInterDiameter;              //Բ���ھ�
			ShellOuterDiameter = sour.ShellOuterDiameter;              //Բ���⾶
			ShellBrokenDiameter = sour.ShellBrokenDiameter;             //Բ���ƾ�
			ShellMass_Clylinder = sour.ShellMass_Clylinder;             //Բ���ο�������
			ChargeMass_Clylinder = sour.ChargeMass_Clylinder;            //Բ����װҩ����
			AllMass_Whole = sour.AllMass_Whole;                   //ս������������
			ChargeMass_Whole = sour.ChargeMass_Whole;                //װҩ��������
			WarheadLength_Whole = sour.WarheadLength_Whole;             //��ͷ���峤��
			WarheadLength_Clylinder = sour.WarheadLength_Clylinder;         //��ͷԲ������
			Density = sour.Density;                         //װҩ�ܶ�
			ExplosionVelocity = sour.ExplosionVelocity;               //װҩ����
			ExplosionHeat = sour.ExplosionHeat;                   //װҩ����
			ExplosinPressure = sour.ExplosinPressure;                //װҩ��ѹ

			Frag_SDA = sour.Frag_SDA;                        //��Ƭ��̬��ɢ��
			Frag_dis = sour.Frag_dis;                        //��Ƭ��ɢ����
			Frag_ResidualVelocity_Initialization = sour.Frag_ResidualVelocity_Initialization;//��Ƭ�뾶�ٶ�
			SC = sour.SC;                                  //������Ƭ
			ASL = sour.ASL;                                 //���θ߶�
			RC = sour.RC;                                  //��������ϵ��

			//6
			FireLat = sour.FireLat;                         //�����γ��
			FireLon = sour.FireLon;                         //����㾭��
			AimLat = sour.AimLat;
			AimLon = sour.AimLon;
			BHE = sour.BHE;                             //ը������
			BHD = sour.BHD;                             //ը�߱�׼��

			//7
			Frag_FragmentDamageCriterion = sour.Frag_FragmentDamageCriterion;        //�����о�
			//8
			InterpolationNumber = sour.InterpolationNumber;                 //��ֵ�����ݸ���
			FireDistance = sour.FireDistance;
			FallingAngle = sour.FallingAngle;
			ShockWavePressure = sour.ShockWavePressure;
	        return *this;
		}
		return *this;
	}
};
//�������
class ArgumentDialog : public QDialog
{
	Q_OBJECT
public:
	ArgumentDialog(const QStringList&,QDialog *parent = 0);
	~ArgumentDialog();
	LGRockParameter& ReadRockParameter();
	bool IsOKOrCancancle() const;
	void GetAimLatLon(double,double);
	void GetConfigFileSettings(const LGRockParameter Object);
private:
	void InitDialog();
	void InitFragmentArgument();
	void InitOrtheArgument();
private:
	QGridLayout *_layout;
	QGroupBox *_gBox_3;
	QGroupBox *_gBox_4;

	//////////////////////////////////////////////////////////////////////////
	QDoubleSpinBox *_FragmentMass_spin;
	QSpinBox *_FragmentNum_spin;
	QDoubleSpinBox *_scatteringAngle_SpinBox;
	QDoubleSpinBox *_centerline_SpinBox;
	QDoubleSpinBox *_RocketVelocity_SpinBox;
	QDoubleSpinBox *_RocketCEP_SpinBox;
	QDoubleSpinBox *_ShellMass_Clylinder_SpinBox;
	QDoubleSpinBox *_ChargeMass_Clylinder_SpinBox;
	QDoubleSpinBox *_AllMass_Wholer_SpinBox;
	QDoubleSpinBox *_AllAmmoMass_Wholer_SpinBox;
	QDoubleSpinBox *_ShellInterDiameter_SpinBox;
	QDoubleSpinBox *_ShellOuterDiameter_SpinBox;
	QDoubleSpinBox *_ShellBrokenDiameter_SpinBox;
	QDoubleSpinBox *_WarheadLength_Whole_SpinBox;
	QDoubleSpinBox *_WarheadLength_Clylinder_SpinBox;
	QDoubleSpinBox *_Density_SpinBox;
	QDoubleSpinBox *_ExplosionVelocity_SpinBox;
	QDoubleSpinBox *_ShapeCoefficient_SpinBox;
	QDoubleSpinBox *_AboveSeaLevel_SpinBox;
	QDoubleSpinBox *_ResistanceCoefficient_SpinBox;
	QDoubleSpinBox *_FragmentDamageCriterion_SpinBox;
	QDoubleSpinBox *_FireLat_SpinBox;
	QDoubleSpinBox *_FireLon_SpinBox;
	QDoubleSpinBox *_BHE_SpinBox;
	QDoubleSpinBox *_BHDt_SpinBox;
	QDoubleSpinBox *_DropLat_SpinBox;
    QDoubleSpinBox *_DropLon_SpinBox;
	QDoubleSpinBox *_shockwavepressure_SpinBox;
	//�����������
	LGRockParameter _ObjectLGRock;
	bool SetTureFalse;
	QStringList _unitList;
	QLineEdit *_ExplosionHeat_Line;
	QLineEdit *_ExplosinPressure_Line;
private slots:
	 void GetSpinBoxValue(int);
	 void GetDoubleSpinBoxValue(double);
	 void SetingOKOrCancle();
	 void PbFileChoise();
	 void ConfigurationParameter();
signals:
	 void EmitChoiseFile();
};
#endif // ARGUMENTDIALOG_H
