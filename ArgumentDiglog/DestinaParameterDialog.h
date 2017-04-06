/*
   目标属性界面
   2016-6-29
   实现目标区域参数设置
   XD
*/
#pragma once
#include "Lib.h"
//目标区域参数
struct TargetAreaParameter
{
	double Aim_Long;   //目标区域长度
	double Aim_Wide;   //目标区域宽度
	double Length_N_02; //目标区域长划分
	double Length_N_13; //目标区域宽划分
	double AimCenterPointLat;//目标区域中心纬度
	double AimCenterPointLon;//目标区域中心经度

	TargetAreaParameter()
	{
		Aim_Long = 0;
		Aim_Wide = 0;
		Length_N_02 = 0;
		Length_N_13 = 0;
		AimCenterPointLat = 0;
		AimCenterPointLon = 0;
	}

	TargetAreaParameter& operator=(const TargetAreaParameter &sour)
	{
		if (this != &sour)
		{
			this->Aim_Long = sour.Aim_Long;
			this->Aim_Wide = sour.Aim_Wide;
			this->Length_N_02 = sour.Length_N_02;
			this->Length_N_13 = sour.Length_N_13;
			this->AimCenterPointLat = sour.AimCenterPointLat;
			this->AimCenterPointLon = sour.AimCenterPointLon;
			return *this;
		}
		return *this;
	}
};
//获取设定目标区域参数
class TargetZoneDialog : public QDialog
{
	Q_OBJECT
public:
	TargetZoneDialog(const QStringList &,QDialog *parent = 0);
	~TargetZoneDialog();
	TargetAreaParameter& GetTargetZoneData();
	bool IsOKOrCancancle() const;
	void GetConfigZone(const TargetAreaParameter Area);
private:
	void InitDialog();
	TargetAreaParameter object_area;
	bool SetTureFalse;
	QStringList _unitList;

	//
	QDoubleSpinBox *_point_Length_spinbox_x;
	QDoubleSpinBox *_point_Width_spinbox_y;
	QDoubleSpinBox *_Aimlat_spin;
	QDoubleSpinBox *_AimLon_spin;
	QDoubleSpinBox *_N02_spin;
	QDoubleSpinBox *_N13_spin;

private slots:
   void GetChangedValue(double);
   void SetingOKOrCancle();
   void ConfigurationParameter();
};
//获取显示毁伤幅员面积
class DamageAreaData : public QWidget
{
	Q_OBJECT
public:
	DamageAreaData();
	DamageAreaData(double _d1,double _d2,double _d3);
	~DamageAreaData();
	void GetAllAreaData(double);        //总面积
	void GetDamageAreaData(double); 
	void GetMassiveData(double);
private:
	void InitWidget();
	//
	QLabel *_lab_Total_Area;
	QLabel *_lab_Total_Area_data;
	QLabel *_lab_Damage_Area;
	QLabel *_lab_Damage_Area_data;

	QLabel *_lab_Damage_massive;
	QLabel *_lab_Damage_massive_data;

	double _totalArea;
	double _damageArea;
	double _massive_data;
};
