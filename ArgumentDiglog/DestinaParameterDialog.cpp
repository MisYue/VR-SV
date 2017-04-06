#include "DestinaParameterDialog.h"
//
TargetZoneDialog::TargetZoneDialog(const QStringList &unitList,QDialog *parent):QDialog(parent),_unitList(unitList)
{
	this->setFixedWidth(400);
	this->setFixedHeight(360);
    this->setWindowTitle(QString::fromLocal8Bit("目标区域"));
	InitDialog();
};
//
TargetZoneDialog::~TargetZoneDialog()
{

};
//
TargetAreaParameter& TargetZoneDialog::GetTargetZoneData()
{
	return object_area;
};
//
void TargetZoneDialog::InitDialog()
{
	QGridLayout *_layoutBox_2 = new QGridLayout;
	this->setLayout(_layoutBox_2);
	//
	QGroupBox *_pointBox = new QGroupBox;
	QVBoxLayout *_PointBox_layout = new QVBoxLayout;
	_pointBox->setLayout(_PointBox_layout);
	_layoutBox_2->addWidget(_pointBox,0,0,1,1);
	///添加系统单位提示
	QHBoxLayout *_UnitLayout = new QHBoxLayout;
	QString _qstr_unit;
	for (int i =0; i < _unitList.size();++i)
	{
		_qstr_unit = _qstr_unit+_unitList.at(i)+"  ";
	}
	QLabel *_unit_layel = new QLabel;
	_unit_layel->setText(_qstr_unit);
	_unit_layel->setMaximumHeight(15);
	//_unit_layel->setAlignment(Qt::AlignHCenter);
	_UnitLayout->addWidget(_unit_layel);
	_PointBox_layout->addLayout(_UnitLayout);
	///添加目标坐标系说明
	QHBoxLayout *_ExplainLayout = new QHBoxLayout;
	QLabel *_explain_layel = new QLabel;
	_explain_layel->setText(QString::fromLocal8Bit("目标坐标系： X轴正方向 -> 高北纬，Y轴正方向 -> 西经增"));
	_explain_layel->setMaximumHeight(15);
	//_explain_layel->setAlignment(Qt::AlignHCenter);
	//_ExplainLayout->addWidget(_explain_layel);
	_PointBox_layout->addLayout(_ExplainLayout);
	//////////
	QHBoxLayout *_point_LW_layout = new QHBoxLayout;
	QLabel *_point_LW = new QLabel;
	_point_LW->setText(QString::fromLocal8Bit("长-宽:"));
	QLabel *_point_Length = new QLabel;
	_point_Length->setText(QString::fromLocal8Bit("长度:"));
	_point_Length_spinbox_x = new QDoubleSpinBox;
	_point_Length_spinbox_x->setDecimals(8);
	_point_Length_spinbox_x->setRange(-100000000.0,100000000.0);
	_point_Length_spinbox_x->setObjectName("LengthZoon");

	connect(_point_Length_spinbox_x,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));

	QLabel *_point_Width = new QLabel;
	_point_Width->setText(QString::fromLocal8Bit("宽度:"));
	_point_Width_spinbox_y = new QDoubleSpinBox;
	_point_Width_spinbox_y->setDecimals(8);
	_point_Width_spinbox_y->setRange(-10000000.0,10000000.0);
	_point_Width_spinbox_y->setObjectName("WidthZoon");
	connect(_point_Width_spinbox_y,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));
	 

	//_point_LW_layout->addWidget(_point_LW);
	_point_LW_layout->addWidget(_point_Length);
	_point_LW_layout->addWidget(_point_Length_spinbox_x);
	_point_LW_layout->addWidget(_point_Width);
	_point_LW_layout->addWidget(_point_Width_spinbox_y);

	_PointBox_layout->addLayout(_point_LW_layout);
	
	///中心纬度
	QHBoxLayout *_AimLat_layout = new QHBoxLayout;
	QLabel *_AimLat = new QLabel;
	_AimLat->setText(QString::fromLocal8Bit("中心纬度:"));
	_Aimlat_spin = new QDoubleSpinBox;
	_Aimlat_spin->setDecimals(8);
	_Aimlat_spin->setMinimum(-90.0);
	_Aimlat_spin->setMaximum(90.0);
	_AimLat_layout->addWidget(_AimLat);
	_AimLat_layout->addWidget(_Aimlat_spin);
	_Aimlat_spin->setObjectName("AimLat");
	connect(_Aimlat_spin,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));
	_PointBox_layout->addLayout(_AimLat_layout);


	//中心经度
	QLabel *_AimLon = new QLabel;
	_AimLon->setText(QString::fromLocal8Bit("中心经度:"));
	_AimLon_spin = new QDoubleSpinBox;
	_AimLon_spin->setMinimum(-180.0);
	_AimLon_spin->setMaximum(180.0);
	_AimLon_spin->setDecimals(8);
	_AimLon_spin->setObjectName("AimLon");
	connect(_AimLon_spin,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));
	_AimLat_layout->addWidget(_AimLon);
	_AimLat_layout->addWidget(_AimLon_spin);
	
	//长方向单元尺寸
	QHBoxLayout *_N02_layout = new QHBoxLayout;
	QLabel *_N02Lab = new QLabel;
	_N02Lab->setText(QString::fromLocal8Bit("长划分(N_02):"));
	_N02_spin = new QDoubleSpinBox;
	_N02_spin->setRange(-10000000.0,10000000.0);
	_N02_spin->setObjectName("N02");
	_N02_spin->setDecimals(8);
	connect(_N02_spin,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));

	_N02_layout->addWidget(_N02Lab);
	_N02_layout->addWidget(_N02_spin);
	_PointBox_layout->addLayout(_N02_layout);

	//宽方向单元尺寸
	QHBoxLayout *_N13_layout = new QHBoxLayout;
	QLabel *_N13Lab = new QLabel;
	_N13Lab->setText(QString::fromLocal8Bit("宽划分(N_13):"));
	_N13_spin = new QDoubleSpinBox;
	_N13_spin->setRange(-10000000.0,10000000.0);
	_N13_spin->setObjectName("N13");
	_N13_spin->setDecimals(8);
	connect(_N13_spin,SIGNAL(valueChanged(double)),this,SLOT(GetChangedValue(double)));

	_N02_layout->addWidget(_N13Lab);
	_N02_layout->addWidget(_N13_spin);
	////
	QHBoxLayout *_goalpoint_layout = new QHBoxLayout;

	QPushButton *pb_ok = new QPushButton;
	pb_ok->setText(QString::fromLocal8Bit("完成"));
	pb_ok->setObjectName("OK");
	pb_ok->setFixedWidth(40);
	_goalpoint_layout->addWidget(pb_ok);
	connect(pb_ok,SIGNAL(clicked()),this,SLOT(SetingOKOrCancle()));

	QPushButton *pb_configuration = new QPushButton;
	pb_configuration->setText(QString::fromLocal8Bit("配置"));
	pb_configuration->setObjectName("Config");
	pb_configuration->setFixedWidth(40);
	_goalpoint_layout->addWidget(pb_configuration);
	connect(pb_configuration,SIGNAL(clicked()),this,SLOT(ConfigurationParameter()));



	QPushButton *pb_cancle = new QPushButton;
	pb_cancle->setText(QString::fromLocal8Bit("取消"));
	pb_cancle->setObjectName("Cancle");
	pb_cancle->setFixedWidth(40);
	_goalpoint_layout->addWidget(pb_cancle);
	connect(pb_cancle,SIGNAL(clicked()),this,SLOT(SetingOKOrCancle()));


	_PointBox_layout->addLayout(_goalpoint_layout);

	
};
//
void TargetZoneDialog::GetChangedValue(double value)
{
	QDoubleSpinBox* _pSp = dynamic_cast<QDoubleSpinBox*>(sender());
	if (_pSp != NULL)
	{
		if (_pSp->objectName() == "LengthZoon")
		{
			object_area.Aim_Long = _pSp->value();
		}
		else if (_pSp->objectName() == "WidthZoon")
		{
			object_area.Aim_Wide = _pSp->value();
		}
		else if (_pSp->objectName() == "AimLat")
		{
			object_area.AimCenterPointLat = _pSp->value();
		}
		else if (_pSp->objectName() == "AimLon")
		{
			object_area.AimCenterPointLon = _pSp->value();
		}
		else if (_pSp->objectName() == "N02")
		{
			object_area.Length_N_02 = _pSp->value();
		}
		else if (_pSp->objectName() == "N13")
		{
			object_area.Length_N_13 = _pSp->value();
		}
	}
}
//
bool TargetZoneDialog::IsOKOrCancancle() const
{
	return SetTureFalse;
}
//
 void TargetZoneDialog::SetingOKOrCancle()
 {
	 QPushButton *_pButton = dynamic_cast<QPushButton*>(sender());
	 if (_pButton != NULL)
	 {
		 if (_pButton->objectName() == "OK")
		 {
			 SetTureFalse  = true;
			 this->close();
		 }
		 else if (_pButton->objectName() == "Cancle")
		 {
			 SetTureFalse = false;
			 this->close();
		 }
	 }
 };
 //
 void TargetZoneDialog::ConfigurationParameter()
 {
	 _point_Length_spinbox_x->setValue(200.0);
	 _point_Width_spinbox_y->setValue(300.0);
	 _Aimlat_spin->setValue(10.0);
	 _AimLon_spin->setValue(10.0);
	 _N02_spin->setValue(10.0);
	 _N13_spin->setValue(10.0);
 }
 //
 void TargetZoneDialog::GetConfigZone(const TargetAreaParameter Area)
 {
	 _point_Length_spinbox_x->setValue(Area.Aim_Long);
	 _point_Width_spinbox_y->setValue(Area.Aim_Wide);
	 _Aimlat_spin->setValue(Area.AimCenterPointLat);
	 _AimLon_spin->setValue(Area.AimCenterPointLon);
	 _N02_spin->setValue(Area.Length_N_02);
	 _N13_spin->setValue(Area.Length_N_13);
 }
//
DamageAreaData::DamageAreaData()
{
	InitWidget();
};
//
DamageAreaData::DamageAreaData(double _d1,double _d2,double _d3) : _totalArea(_d1),_damageArea(_d2),_massive_data(_d3)
{
	InitWidget();
};
//
DamageAreaData::~DamageAreaData()
{

}
//
void DamageAreaData::GetAllAreaData(double _data)
{
	_totalArea = _data;
	QString str;
	_lab_Total_Area_data->setText(str.setNum(_totalArea));
}
//
void DamageAreaData::GetDamageAreaData(double _data)
{
	_damageArea = _data;
	QString str;
	_lab_Damage_Area_data->setText(str.setNum(_damageArea));
}
//
void DamageAreaData::GetMassiveData(double _data)
{
	_massive_data = _data;
	QString str;
	_lab_Damage_massive_data->setText(str.setNum(_massive_data));
}
//
void DamageAreaData::InitWidget()
{
    QGridLayout *_layout = new QGridLayout;
	this->setLayout(_layout);

	_lab_Total_Area  = new QLabel;
	_lab_Total_Area_data = new QLabel;
	_lab_Damage_Area = new QLabel;
	_lab_Damage_Area_data = new QLabel;
    _lab_Damage_massive = new QLabel;
	_lab_Damage_massive_data = new QLabel;


	_lab_Total_Area->setText(QString::fromLocal8Bit("目标区域面积:"));
	_lab_Damage_Area->setText(QString::fromLocal8Bit("毁伤幅员:"));
	_lab_Damage_massive->setText(QString::fromLocal8Bit("毁伤面积比:"));

	QString str;
	_lab_Total_Area_data->setText(str.setNum(_totalArea));
	str.clear();
	_lab_Damage_Area_data->setText(str.setNum(_damageArea));
	str.clear();
	_lab_Damage_massive_data->setText(str.setNum(_massive_data));

	_layout->addWidget(_lab_Total_Area,0,0,1,1);
	_layout->addWidget(_lab_Total_Area_data,0,1,1,1);

	_layout->addWidget(_lab_Damage_Area,1,0,1,1);
	_layout->addWidget(_lab_Damage_Area_data,1,1,1,1);

	_layout->addWidget(_lab_Damage_massive,2,0,1,1);
	_layout->addWidget(_lab_Damage_massive_data,2,1,1,1);
}
