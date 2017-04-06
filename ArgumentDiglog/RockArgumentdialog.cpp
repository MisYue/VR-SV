#include "RockArgumentdialog.h"

ArgumentDialog::ArgumentDialog(const QStringList& unitList,QDialog *parent):QDialog(parent),_unitList(unitList)
{
	this->setFixedWidth(900);
	this->setFixedHeight(700);
	InitDialog();
}
//
ArgumentDialog::~ArgumentDialog()
{

}
//
void ArgumentDialog::InitDialog()
{
	_layout = new QGridLayout;
	this->setLayout(_layout);

	//
	QGroupBox *unitBox = new QGroupBox;
	unitBox->setTitle(QString::fromLocal8Bit("ϵͳ��λ"));

	_gBox_3 = new QGroupBox;
	_gBox_3->setTitle(QString::fromLocal8Bit("��������"));
	InitFragmentArgument();
	_gBox_4 = new QGroupBox;
	_gBox_4->setTitle(QString::fromLocal8Bit("��������"));
	InitOrtheArgument();

	///���ϵͳ��λ��ʾ
	QHBoxLayout *_UnitLayout = new QHBoxLayout;
	QString _qstr_unit;
	for (int i =0; i < _unitList.size();++i)
	{
		_qstr_unit = _qstr_unit+_unitList.at(i)+"  ";
	}
	QLabel *_unit_layel = new QLabel;
	_unit_layel->setText(_qstr_unit);
	_unit_layel->setMaximumHeight(20);
	_unit_layel->setAlignment(Qt::AlignHCenter);
	_UnitLayout->addWidget(_unit_layel);
	unitBox->setLayout(_UnitLayout);
	//////////
	_layout->addWidget(unitBox,0,1,1,1);
	_layout->addWidget(_gBox_3,1,1,9,1);
	_layout->addWidget(_gBox_4,0,2,10,1);
}
//
void ArgumentDialog::InitFragmentArgument()
{
	QGridLayout *_layoutBox_3 = new QGridLayout;
	_gBox_3->setLayout(_layoutBox_3);
	//��Ƭ���ݽṹ
	QGroupBox *FragmentDataBox = new QGroupBox;
	FragmentDataBox->setTitle(QString::fromLocal8Bit("��Ƭ���ݽṹ"));
	QVBoxLayout *Fragment_Vlayout = new QVBoxLayout;

	//��Ƭ������
	QHBoxLayout *FragMentNum = new QHBoxLayout;
	QLabel *_FragmentNum_lab = new QLabel;
	_FragmentNum_lab->setText(QString::fromLocal8Bit("��Ƭ������"));
	_FragmentNum_spin = new QSpinBox;
	_FragmentNum_spin->setRange(1,100000);
	_FragmentNum_spin->setObjectName("NumOfFragments");
	connect(_FragmentNum_spin,SIGNAL(valueChanged(int)),this,SLOT(GetSpinBoxValue(int)));
	FragMentNum->addWidget(_FragmentNum_lab);
	FragMentNum->addWidget(_FragmentNum_spin);

	////��Ƭ����
	QHBoxLayout *FragMentMass = new QHBoxLayout;
	QLabel *_FragmentMass_lab = new QLabel;
	_FragmentMass_lab->setText(QString::fromLocal8Bit("��Ƭ������"));
	_FragmentMass_spin = new QDoubleSpinBox;
	_FragmentMass_spin->setDecimals(8);
	_FragmentMass_spin->setRange(0.0000,10000000.0);
	_FragmentMass_spin->setObjectName("FragmentsMass");
	connect(_FragmentMass_spin,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	FragMentMass->addWidget(_FragmentMass_lab);
	FragMentMass->addWidget(_FragmentMass_spin);
	//
	Fragment_Vlayout->addLayout(FragMentMass);
	Fragment_Vlayout->addLayout(FragMentNum);
	FragmentDataBox->setLayout(Fragment_Vlayout);
	/////�����ս����
	//��Ƭ���ݽṹ
	QGroupBox *RocketDataBox = new QGroupBox;
	RocketDataBox->setTitle(QString::fromLocal8Bit("��������ݽṹ"));
	//RocketDataBox->setFixedHeight(100);
	QVBoxLayout *Rock_Vlayout = new QVBoxLayout;
	RocketDataBox->setLayout(Rock_Vlayout);
	//�����ս������̬��ɢ��
	QHBoxLayout *_scatteringAngle_layout = new QHBoxLayout;
	QLabel *_scatteringAngle_label = new QLabel;
	_scatteringAngle_label->setText(QString::fromLocal8Bit("ս������̬��ɢ��:"));
	_scatteringAngle_SpinBox = new QDoubleSpinBox;
	_scatteringAngle_SpinBox->setRange(0.0,360.0);
	_scatteringAngle_SpinBox->setDecimals(7);
	_scatteringAngle_SpinBox->setObjectName("WarheadAngle");
	connect(_scatteringAngle_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_scatteringAngle_layout->addWidget(_scatteringAngle_label);
	_scatteringAngle_layout->addWidget(_scatteringAngle_SpinBox);
	Rock_Vlayout->addLayout(_scatteringAngle_layout);
	//�����ս������̬��ɢ�Ƿֲ��������뵯������ϵx��н�
	QHBoxLayout *_centerlineAngle_layout = new QHBoxLayout;
	QLabel *_centerline_label = new QLabel;
	_centerline_label->setText(QString::fromLocal8Bit("ս������̬��ɢ�����:"));
	_centerline_SpinBox = new QDoubleSpinBox;
	_centerline_SpinBox->setRange(0.0,360.0);
	_centerline_SpinBox->setDecimals(7);
	_centerline_SpinBox->setObjectName("CenterLineAngle");
	connect(_centerline_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_centerlineAngle_layout->addWidget(_centerline_label);
	_centerlineAngle_layout->addWidget(_centerline_SpinBox);
	Rock_Vlayout->addLayout(_centerlineAngle_layout);
	//������ٶ�
	QHBoxLayout *_RocketVelocity_layout = new QHBoxLayout;
	QLabel *_RocketVelocity_label = new QLabel;
	_RocketVelocity_label->setText(QString::fromLocal8Bit("������ٶ�:"));
	_RocketVelocity_SpinBox = new QDoubleSpinBox;
	_RocketVelocity_SpinBox->setDecimals(7);
	_RocketVelocity_SpinBox->setRange(0.0,1000000.0);
	_RocketVelocity_SpinBox->setObjectName("RocketVelocity");
	connect(_RocketVelocity_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_RocketVelocity_layout->addWidget(_RocketVelocity_label);
	_RocketVelocity_layout->addWidget(_RocketVelocity_SpinBox);
	Rock_Vlayout->addLayout(_RocketVelocity_layout);
	//�����CEP
	QHBoxLayout *_RocketCEP_layout = new QHBoxLayout;
	QLabel *_RocketCEP_label = new QLabel;
	_RocketCEP_label->setText(QString::fromLocal8Bit("�����CEP:"));
	_RocketCEP_SpinBox = new QDoubleSpinBox;
	_RocketCEP_SpinBox->setDecimals(7);
	_RocketCEP_SpinBox->setRange(0.0,10000000.0);
	_RocketCEP_SpinBox->setObjectName("RocketCEP");
	connect(_RocketCEP_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_RocketCEP_layout->addWidget(_RocketCEP_label);
	_RocketCEP_layout->addWidget(_RocketCEP_SpinBox);
	Rock_Vlayout->addLayout(_RocketCEP_layout);

	//ս����
	QGroupBox *WarheadDataBox = new QGroupBox;
	WarheadDataBox->setTitle(QString::fromLocal8Bit("ս�������ݽṹ"));
	//WarheadDataBox->setFixedHeight(100);
	QVBoxLayout *Warhead_Vlayout = new QVBoxLayout;
	WarheadDataBox->setLayout(Warhead_Vlayout);
	//Բ���ο�������
	QHBoxLayout *_ShellMass_Clylinder_layout = new QHBoxLayout;
	QLabel *_ShellMass_Clylinder_label = new QLabel;
	_ShellMass_Clylinder_label->setText(QString::fromLocal8Bit("Բ���ο�������:"));
	_ShellMass_Clylinder_SpinBox = new QDoubleSpinBox;
	_ShellMass_Clylinder_SpinBox->setDecimals(7);
	_ShellMass_Clylinder_SpinBox->setRange(0.0,1000000.0);
	_ShellMass_Clylinder_SpinBox->setObjectName("ShellMassClylinder");
	connect(_ShellMass_Clylinder_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ShellMass_Clylinder_SpinBox->setDisabled(true);

	_ShellMass_Clylinder_layout->addWidget(_ShellMass_Clylinder_label);
	_ShellMass_Clylinder_layout->addWidget(_ShellMass_Clylinder_SpinBox);
	Warhead_Vlayout->addLayout(_ShellMass_Clylinder_layout);
	//Բ����װҩ����
	QHBoxLayout *_ChargeMass_Clylinder_layout = new QHBoxLayout;
	QLabel *_ChargeMass_Clylinder_label = new QLabel;
	_ChargeMass_Clylinder_label->setText(QString::fromLocal8Bit("Բ����װҩ����:"));
	_ChargeMass_Clylinder_SpinBox = new QDoubleSpinBox;
	_ChargeMass_Clylinder_SpinBox->setDecimals(7);
	_ChargeMass_Clylinder_SpinBox->setRange(0.0,1000000.0);
	_ChargeMass_Clylinder_SpinBox->setObjectName("ChargeMassClylinder");
	connect(_ChargeMass_Clylinder_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ChargeMass_Clylinder_SpinBox->setDisabled(true);

	_ChargeMass_Clylinder_layout->addWidget(_ChargeMass_Clylinder_label);
	_ChargeMass_Clylinder_layout->addWidget(_ChargeMass_Clylinder_SpinBox);
	Warhead_Vlayout->addLayout(_ChargeMass_Clylinder_layout);
	//ս������������
	QHBoxLayout *_AllMass_Whole_layout = new QHBoxLayout;
	QLabel *_AllMass_Whole_label = new QLabel;
	_AllMass_Whole_label->setText(QString::fromLocal8Bit("ս������������:"));
	_AllMass_Wholer_SpinBox = new QDoubleSpinBox;
	_AllMass_Wholer_SpinBox->setDecimals(7);
	_AllMass_Wholer_SpinBox->setRange(0.0,1000000.0);
	_AllMass_Wholer_SpinBox->setObjectName("AllAmmoMass");
	connect(_AllMass_Wholer_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_AllMass_Wholer_SpinBox->setDisabled(true);

	_AllMass_Whole_layout->addWidget(_AllMass_Whole_label);
	_AllMass_Whole_layout->addWidget(_AllMass_Wholer_SpinBox);
	Warhead_Vlayout->addLayout(_AllMass_Whole_layout);
	//ս����װҩ����
	QHBoxLayout *_AllAmmoMass_Whole_layout = new QHBoxLayout;
	QLabel *_AllAmmoMass_Whole_label = new QLabel;
	_AllAmmoMass_Whole_label->setText(QString::fromLocal8Bit("װҩ��������:"));
	_AllAmmoMass_Wholer_SpinBox = new QDoubleSpinBox;
	_AllAmmoMass_Wholer_SpinBox->setDecimals(7);
	_AllAmmoMass_Wholer_SpinBox->setRange(0.0,1000000.0);
	_AllAmmoMass_Wholer_SpinBox->setObjectName("AllMassWholer");
	connect(_AllAmmoMass_Wholer_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_AllAmmoMass_Wholer_SpinBox->setDisabled(true);

	_AllAmmoMass_Whole_layout->addWidget(_AllAmmoMass_Whole_label);
	_AllAmmoMass_Whole_layout->addWidget(_AllAmmoMass_Wholer_SpinBox);
	Warhead_Vlayout->addLayout(_AllAmmoMass_Whole_layout);
	//ս����Բ�����ھ�
	QHBoxLayout *_ShellInterDiameter_layout = new QHBoxLayout;
	QLabel *_ShellInterDiameter_label = new QLabel;
	_ShellInterDiameter_label->setText(QString::fromLocal8Bit("ս����Բ�����ھ�:"));
	_ShellInterDiameter_SpinBox = new QDoubleSpinBox;
	_ShellInterDiameter_SpinBox->setDecimals(7);
	_ShellInterDiameter_SpinBox->setRange(0.0,1000000.0);
	_ShellInterDiameter_SpinBox->setObjectName("ShellInterDiameter");
	connect(_ShellInterDiameter_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ShellInterDiameter_SpinBox->setDisabled(true);

	_ShellInterDiameter_layout->addWidget(_ShellInterDiameter_label);
	_ShellInterDiameter_layout->addWidget(_ShellInterDiameter_SpinBox);
	Warhead_Vlayout->addLayout(_ShellInterDiameter_layout);
	//ս����Բ�����⾶
	QHBoxLayout *_ShellOuterDiameter_layout = new QHBoxLayout;
	QLabel *_ShellOuterDiameter_label = new QLabel;
	_ShellOuterDiameter_label->setText(QString::fromLocal8Bit("ս����Բ�����⾶:"));
	_ShellOuterDiameter_SpinBox = new QDoubleSpinBox;
	_ShellOuterDiameter_SpinBox->setDecimals(7);
	_ShellOuterDiameter_SpinBox->setRange(0.0,1000000.0);
	_ShellOuterDiameter_SpinBox->setObjectName("ShellOuterDiameter");
	connect(_ShellOuterDiameter_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ShellOuterDiameter_SpinBox->setDisabled(true);

	_ShellOuterDiameter_layout->addWidget(_ShellOuterDiameter_label);
	_ShellOuterDiameter_layout->addWidget(_ShellOuterDiameter_SpinBox);
	Warhead_Vlayout->addLayout(_ShellOuterDiameter_layout);
	//ս����Բ�������Ѱ뾶
	QHBoxLayout *_ShellBrokenDiameter_layout = new QHBoxLayout;
	QLabel *_ShellBrokenDiameter_label = new QLabel;
	_ShellBrokenDiameter_label->setText(QString::fromLocal8Bit("ս����Բ�������Ѱ뾶:"));
	_ShellBrokenDiameter_SpinBox = new QDoubleSpinBox;
	_ShellBrokenDiameter_SpinBox->setDecimals(7);
	_ShellBrokenDiameter_SpinBox->setRange(0.0,1000000.0);
	_ShellBrokenDiameter_SpinBox->setObjectName("ShellBrokenDiameter");
	connect(_ShellBrokenDiameter_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ShellBrokenDiameter_SpinBox->setDisabled(true);

	_ShellBrokenDiameter_layout->addWidget(_ShellBrokenDiameter_label);
	_ShellBrokenDiameter_layout->addWidget(_ShellBrokenDiameter_SpinBox);
	Warhead_Vlayout->addLayout(_ShellBrokenDiameter_layout);
	
	//��ͷ����
	QHBoxLayout *_WarheadLength_Whole_layout = new QHBoxLayout;
	QLabel *_WarheadLength_Whole_label = new QLabel;
	_WarheadLength_Whole_label->setText(QString::fromLocal8Bit("��ͷ����:"));
	_WarheadLength_Whole_SpinBox = new QDoubleSpinBox;
	_WarheadLength_Whole_SpinBox->setDecimals(7);
	_WarheadLength_Whole_SpinBox->setRange(0.0,1000000.0);
	_WarheadLength_Whole_SpinBox->setObjectName("WarheadLength_Whole");
	connect(_WarheadLength_Whole_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_WarheadLength_Whole_SpinBox->setDisabled(true);

	_WarheadLength_Whole_layout->addWidget(_WarheadLength_Whole_label);
	_WarheadLength_Whole_layout->addWidget(_WarheadLength_Whole_SpinBox);
	Warhead_Vlayout->addLayout(_WarheadLength_Whole_layout);

	//��ͷ����
	QHBoxLayout *_WarheadLength_Clylinder_layout = new QHBoxLayout;
	QLabel *_WarheadLength_Clylinder_label = new QLabel;
	_WarheadLength_Clylinder_label->setText(QString::fromLocal8Bit("��ͷԲ������:"));
	_WarheadLength_Clylinder_SpinBox = new QDoubleSpinBox;
	_WarheadLength_Clylinder_SpinBox->setDecimals(7);
	_WarheadLength_Clylinder_SpinBox->setRange(0.0,1000000.0);
	_WarheadLength_Clylinder_SpinBox->setObjectName("WarheadLength_Clylinder");
	connect(_WarheadLength_Clylinder_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_WarheadLength_Clylinder_SpinBox->setDisabled(true);

	_WarheadLength_Clylinder_layout->addWidget(_WarheadLength_Clylinder_label);
	_WarheadLength_Clylinder_layout->addWidget(_WarheadLength_Clylinder_SpinBox);
	Warhead_Vlayout->addLayout(_WarheadLength_Clylinder_layout);

	//
	_layoutBox_3->addWidget(FragmentDataBox,0,0,1,1);
	_layoutBox_3->addWidget(RocketDataBox, 1,0,1,1);
	_layoutBox_3->addWidget(WarheadDataBox,2,0,3,1);
};
//
void ArgumentDialog::InitOrtheArgument()
{
	QVBoxLayout *_layoutBox_4 = new QVBoxLayout;
	_gBox_4->setLayout(_layoutBox_4);
	//װҩ����
	QGroupBox *Chargedata_box = new QGroupBox;
	Chargedata_box->setTitle(QString::fromLocal8Bit("װҩ����"));
	QVBoxLayout *Chargedata_Layout = new QVBoxLayout;
	Chargedata_box->setLayout(Chargedata_Layout);

	//װҩ�ܶ�
	QHBoxLayout *_Density_layout = new QHBoxLayout;
	QLabel *_Density_label = new QLabel;
	_Density_label->setText(QString::fromLocal8Bit("װҩ�ܶ�:"));
	_Density_SpinBox = new QDoubleSpinBox;
	_Density_SpinBox->setDecimals(7);
	_Density_SpinBox->setRange(0.0,1000000.0);
	_Density_SpinBox->setObjectName("Density");
	connect(_Density_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_Density_SpinBox->setDisabled(true);

	_Density_layout->addWidget(_Density_label);
	_Density_layout->addWidget(_Density_SpinBox);
	//װҩ����
	QHBoxLayout *_ExplosionVelocity_layout = new QHBoxLayout;
	QLabel *_ExplosionVelocity_label = new QLabel;
	_ExplosionVelocity_label->setText(QString::fromLocal8Bit("װҩ����:"));
	_ExplosionVelocity_SpinBox = new QDoubleSpinBox;
	_ExplosionVelocity_SpinBox->setDecimals(7);
	_ExplosionVelocity_SpinBox->setRange(0.0,1000000.0);
	_ExplosionVelocity_SpinBox->setObjectName("ExplosionVelocity");
	connect(_ExplosionVelocity_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_ExplosionVelocity_SpinBox->setDisabled(true);

	_ExplosionVelocity_layout->addWidget(_ExplosionVelocity_label);
	_ExplosionVelocity_layout->addWidget(_ExplosionVelocity_SpinBox);
	//װҩ����
	QHBoxLayout *_ExplosionHeat_layout = new QHBoxLayout;
	QLabel *_ExplosionHeat_label = new QLabel;
	_ExplosionHeat_label->setText(QString::fromLocal8Bit("װҩ����:"));
	_ExplosionHeat_Line = new QLineEdit;
	_ExplosionHeat_Line->setMaximumWidth(220);
	//_ExplosionHeat_SpinBox->setDisabled(true);

	_ExplosionHeat_layout->addWidget(_ExplosionHeat_label);
	_ExplosionHeat_layout->addWidget(_ExplosionHeat_Line);
	//װҩ��ѹ
	QHBoxLayout *_ExplosinPressure_layout = new QHBoxLayout;
	QLabel *_ExplosinPressure_label = new QLabel;
	_ExplosinPressure_label->setText(QString::fromLocal8Bit("װҩ��ѹ:"));
	_ExplosinPressure_Line = new QLineEdit;
	_ExplosinPressure_Line->setMaximumWidth(220);
	//_ExplosinPressure_SpinBox->setDisabled(true);

	_ExplosinPressure_layout->addWidget(_ExplosinPressure_label);
	_ExplosinPressure_layout->addWidget(_ExplosinPressure_Line);
	//
	/*Chargedata_Layout->addLayout(_Chargedata_layout);*/
	Chargedata_Layout->addLayout(_Density_layout);
	Chargedata_Layout->addLayout(_ExplosionVelocity_layout);
	Chargedata_Layout->addLayout(_ExplosionHeat_layout);
	Chargedata_Layout->addLayout(_ExplosinPressure_layout);

	//��Ƭ�ٶ�˥���������������
	QGroupBox *_Fragmentvelocityattenuation_box = new QGroupBox;
	_Fragmentvelocityattenuation_box->setTitle(QString::fromLocal8Bit("��Ƭ�ٶ�˥���������������"));
	QVBoxLayout *Fragmentvelocityattenuation_Layout = new QVBoxLayout;
	_Fragmentvelocityattenuation_box->setLayout(Fragmentvelocityattenuation_Layout);
	  //��״ϵ��
	QHBoxLayout *_ShapeCoefficient_layout = new QHBoxLayout;
	QLabel *_ShapeCoefficient_label = new QLabel;
	_ShapeCoefficient_label->setText(QString::fromLocal8Bit("��״ϵ��:"));
	_ShapeCoefficient_SpinBox = new QDoubleSpinBox;
	_ShapeCoefficient_SpinBox->setDecimals(7);
	_ShapeCoefficient_SpinBox->setRange(0.0,1000000.0);
	_ShapeCoefficient_SpinBox->setObjectName("ShapeCoefficient");
	connect(_ShapeCoefficient_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_ShapeCoefficient_layout->addWidget(_ShapeCoefficient_label);
	_ShapeCoefficient_layout->addWidget(_ShapeCoefficient_SpinBox);
	Fragmentvelocityattenuation_Layout->addLayout(_ShapeCoefficient_layout);

	//���θ߶�
	QHBoxLayout *_AboveSeaLevel_layout = new QHBoxLayout;
	QLabel *_AboveSeaLevel_label = new QLabel;
	_AboveSeaLevel_label->setText(QString::fromLocal8Bit("���θ߶�:"));
	_AboveSeaLevel_SpinBox = new QDoubleSpinBox;
	_AboveSeaLevel_SpinBox->setDecimals(7);
	_AboveSeaLevel_SpinBox->setRange(0.0,20000000.0);
	_AboveSeaLevel_SpinBox->setObjectName("AboveSeaLevel");
	connect(_AboveSeaLevel_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_AboveSeaLevel_layout->addWidget(_AboveSeaLevel_label);
	_AboveSeaLevel_layout->addWidget(_AboveSeaLevel_SpinBox);
	Fragmentvelocityattenuation_Layout->addLayout(_AboveSeaLevel_layout);

	//��������ϵ��
	QHBoxLayout *_ResistanceCoefficient_layout = new QHBoxLayout;
	QLabel *_ResistanceCoefficient_label = new QLabel;
	_ResistanceCoefficient_label->setText(QString::fromLocal8Bit("��������ϵ��:"));
	_ResistanceCoefficient_SpinBox = new QDoubleSpinBox;
	_ResistanceCoefficient_SpinBox->setDecimals(7);
	_ResistanceCoefficient_SpinBox->setRange(0.0,1000000.0);
	_ResistanceCoefficient_SpinBox->setObjectName("ResistanceCoefficient");
	connect(_ResistanceCoefficient_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_ResistanceCoefficient_layout->addWidget(_ResistanceCoefficient_label);
	_ResistanceCoefficient_layout->addWidget(_ResistanceCoefficient_SpinBox);
	Fragmentvelocityattenuation_Layout->addLayout(_ResistanceCoefficient_layout);

	////��Ƭ��̬��ɢ��
	//QHBoxLayout *_Frag_SDA_layout = new QHBoxLayout;
	//QLabel *_Frag_SDA_label = new QLabel;
	//_Frag_SDA_label->setText(QString::fromLocal8Bit("��Ƭ��̬��ɢ��:"));
	//QDoubleSpinBox *_Frag_SDA_SpinBox = new QDoubleSpinBox;
	//_Frag_SDA_SpinBox->setDecimals(5);
	//_Frag_SDA_SpinBox->setRange(0.0,10000.0);
	//_Frag_SDA_SpinBox->setObjectName("Frag_SDA");
	//connect(_Frag_SDA_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//_Frag_SDA_SpinBox->setDisabled(true);

	//_Frag_SDA_layout->addWidget(_Frag_SDA_label);
	//_Frag_SDA_layout->addWidget(_Frag_SDA_SpinBox);
	//Fragmentvelocityattenuation_Layout->addLayout(_Frag_SDA_layout);

	//�����о�
	QGroupBox *_Damagecriterion_box = new QGroupBox;
	_Damagecriterion_box->setTitle(QString::fromLocal8Bit("�����о�"));

	QVBoxLayout *_JudgeLayout = new QVBoxLayout;

	QHBoxLayout *Damagecriterion_Layout = new QHBoxLayout;
	QLabel *_FragmentDamageCriterion_label = new QLabel;
	_FragmentDamageCriterion_label->setText(QString::fromLocal8Bit("��Ƭ�����о�:"));
	QLabel *_FragmentDamageCriterionUnit_label = new QLabel;
	_FragmentDamageCriterionUnit_label->setText(QString::fromLocal8Bit("J(����)"));
	_FragmentDamageCriterionUnit_label->setMaximumWidth(60);

	_FragmentDamageCriterion_SpinBox = new QDoubleSpinBox;
	_FragmentDamageCriterion_SpinBox->setDecimals(7);
	_FragmentDamageCriterion_SpinBox->setRange(0.0,100000.0);
	_FragmentDamageCriterion_SpinBox->setObjectName("FragmentDamageCriterion");
	connect(_FragmentDamageCriterion_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//
	QHBoxLayout *shockwavepressure_Layout = new QHBoxLayout;
	QLabel *_shockwavepressure_label = new QLabel;
	_shockwavepressure_label->setText(QString::fromLocal8Bit("�������ѹ�о�:"));

	QLabel *_shockwavepressureUnit_label = new QLabel;
	_shockwavepressureUnit_label->setText(QString::fromLocal8Bit("MPa(����)"));
	_shockwavepressureUnit_label->setMaximumWidth(60);
	_shockwavepressure_SpinBox = new QDoubleSpinBox;
	_shockwavepressure_SpinBox->setDecimals(7);
	_shockwavepressure_SpinBox->setRange(0.0,100000.0);
	_shockwavepressure_SpinBox->setObjectName("ShockWavePressure");
	connect(_shockwavepressure_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));
	//��ӻ����оݲ���
	Damagecriterion_Layout->addWidget(_FragmentDamageCriterion_label);
	Damagecriterion_Layout->addWidget(_FragmentDamageCriterion_SpinBox);
	Damagecriterion_Layout->addWidget(_FragmentDamageCriterionUnit_label);
	//��ӳ�ѹ�����оݲ���
	shockwavepressure_Layout->addWidget(_shockwavepressure_label);
	shockwavepressure_Layout->addWidget(_shockwavepressure_SpinBox);
	shockwavepressure_Layout->addWidget(_shockwavepressureUnit_label);

	_JudgeLayout->addLayout(Damagecriterion_Layout);
	_JudgeLayout->addLayout(shockwavepressure_Layout);
	_Damagecriterion_box->setLayout(_JudgeLayout);

	//���ò�ֵ�����ݸ���
	QHBoxLayout *_InterNumber_layout = new QHBoxLayout;
	QLabel *_InterNumber_label = new QLabel;
	_InterNumber_label->setText(QString::fromLocal8Bit("ѡ���ļ�:"));
	QPushButton *_InterNumber_SpinBox = new QPushButton;
	connect(_InterNumber_SpinBox,SIGNAL(clicked()),this,SLOT(PbFileChoise()));
	_InterNumber_SpinBox->setText(QString::fromLocal8Bit("...."));
	_InterNumber_layout->addWidget(_InterNumber_label);
	_InterNumber_layout->addWidget(_InterNumber_SpinBox);


	    //�����γ�ȣ�FireLat��
	QHBoxLayout *_FireLat_layout = new QHBoxLayout;
	QLabel *_FireLat_label = new QLabel;
	_FireLat_label->setText(QString::fromLocal8Bit("�����γ��:"));
	_FireLat_SpinBox = new QDoubleSpinBox;
	_FireLat_SpinBox->setDecimals(10);
	_FireLat_SpinBox->setRange(-90.0,90.0);
	_FireLat_SpinBox->setObjectName("FireLat");
	connect(_FireLat_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_FireLat_layout->addWidget(_FireLat_label);
	_FireLat_layout->addWidget(_FireLat_SpinBox);
		//����㾭�ȣ�FireLon��
	QHBoxLayout *_FireLon_layout = new QHBoxLayout;
	QLabel *_FireLon_label = new QLabel;
	_FireLon_label->setText(QString::fromLocal8Bit("����㾭��:"));
	_FireLon_SpinBox = new QDoubleSpinBox;
	_FireLon_SpinBox->setDecimals(7);
	_FireLon_SpinBox->setRange(-180.0,180.0);
	_FireLon_SpinBox->setObjectName("FireLon");
	connect(_FireLon_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_FireLon_layout->addWidget(_FireLon_label);
	_FireLon_layout->addWidget(_FireLon_SpinBox);

	//���γ�ȣ�FireLat��
	QHBoxLayout *_DropLat_layout = new QHBoxLayout;
	QLabel *_DropLat_label = new QLabel;
	_DropLat_label->setText(QString::fromLocal8Bit("��׼��γ��:"));
	_DropLat_SpinBox = new QDoubleSpinBox;
	_DropLat_SpinBox->setDecimals(7);
	_DropLat_SpinBox->setRange(-90.0,90.0);
	_DropLat_SpinBox->setObjectName("DropLat");
	connect(_DropLat_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_DropLat_layout->addWidget(_DropLat_label);
	_DropLat_layout->addWidget(_DropLat_SpinBox);
	//���γ�ȣ�FireLon��
	QHBoxLayout *_DropLon_layout = new QHBoxLayout;
	QLabel *_DropLon_label = new QLabel;
	_DropLon_label->setText(QString::fromLocal8Bit("��׼�㾭��:"));
	_DropLon_SpinBox = new QDoubleSpinBox;
	_DropLon_SpinBox->setDecimals(7);
	_DropLon_SpinBox->setRange(-180.0,180.0);
	_DropLon_SpinBox->setObjectName("DropLon");
	connect(_DropLon_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_DropLon_layout->addWidget(_DropLon_label);
	_DropLon_layout->addWidget(_DropLon_SpinBox);
		//ը��������BHE��
	QHBoxLayout *_BHE_layout = new QHBoxLayout;
	QLabel *_BHE_label = new QLabel;
	_BHE_label->setText(QString::fromLocal8Bit("ը������:"));
	_BHE_SpinBox = new QDoubleSpinBox;
	_BHE_SpinBox->setDecimals(7);
	_BHE_SpinBox->setRange(0.0,500000.0);
	_BHE_SpinBox->setObjectName("BHE");
	connect(_BHE_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_BHE_layout->addWidget(_BHE_label);
	_BHE_layout->addWidget(_BHE_SpinBox);
		//ը�߱�׼�BHD��
	QHBoxLayout *_BHD_layout = new QHBoxLayout;
	QLabel *_BHD_label = new QLabel;
	_BHD_label->setText(QString::fromLocal8Bit("ը�߱�׼��:"));
	_BHDt_SpinBox = new QDoubleSpinBox;
	_BHDt_SpinBox->setDecimals(7);
	_BHDt_SpinBox->setRange(0.0,500000.0);
	_BHDt_SpinBox->setObjectName("BHDt");
	connect(_BHDt_SpinBox,SIGNAL(valueChanged(double)),this,SLOT(GetDoubleSpinBoxValue(double)));

	_BHD_layout->addWidget(_BHD_label);
	_BHD_layout->addWidget(_BHDt_SpinBox);
	
	//
    QHBoxLayout *_Button_layout = new QHBoxLayout;
	QPushButton *_OKButton = new QPushButton;
	_OKButton->setText(QString::fromLocal8Bit("���"));
	_OKButton->setObjectName("OK");
	_OKButton->setMaximumWidth(40);
	connect(_OKButton,SIGNAL(clicked()),this,SLOT(SetingOKOrCancle()));
	_Button_layout->addWidget(_OKButton);

	QPushButton *_ConfigButton = new QPushButton;
	_ConfigButton->setText(QString::fromLocal8Bit("����"));
	_ConfigButton->setObjectName("Config");
	_ConfigButton->setMaximumWidth(40);
	connect(_ConfigButton,SIGNAL(clicked()),this,SLOT(ConfigurationParameter()));
	_Button_layout->addWidget(_ConfigButton);

	QPushButton *_CancleButton = new QPushButton;
	_CancleButton->setText(QString::fromLocal8Bit("ȡ��"));
	_CancleButton->setObjectName("Cancle");
	_CancleButton->setMaximumWidth(40);
	connect(_CancleButton,SIGNAL(clicked()),this,SLOT(SetingOKOrCancle()));
	_Button_layout->addWidget(_CancleButton);


	_layoutBox_4->addWidget(Chargedata_box);
	_layoutBox_4->addWidget(_Fragmentvelocityattenuation_box);
	_layoutBox_4->addWidget(_Damagecriterion_box);
	
	_layoutBox_4->addLayout(_InterNumber_layout);

	_layoutBox_4->addLayout(_FireLat_layout);
	_layoutBox_4->addLayout(_FireLon_layout);
	_layoutBox_4->addLayout(_DropLat_layout);
	_layoutBox_4->addLayout(_DropLon_layout);
	_layoutBox_4->addLayout(_BHE_layout);
	_layoutBox_4->addLayout(_BHD_layout);
	_layoutBox_4->addLayout(_Button_layout);
}
//
void ArgumentDialog::GetDoubleSpinBoxValue(double _dValue)
{
	QDoubleSpinBox *_pSpinBox = dynamic_cast<QDoubleSpinBox*>(sender());
	if (_pSpinBox != NULL)
	{
		QString ss = _pSpinBox->objectName();
		if (ss == "FragmentsMass")  //��Ƭ����
		{
			_ObjectLGRock.Frag_Mass = _dValue;
		}
		else if (ss == "WarheadAngle") //�����ս������̬��ɢ��
		{
			_ObjectLGRock.Rock_WarheadStaticAngle = _dValue;
		}
		else if (ss == "CenterLineAngle")  //ս������̬��ɢ�Ƿֲ��������뵯��ϵx��н�
		{
			_ObjectLGRock.Rock_WarheadStaticAngleToCenter = _dValue;
		}
		else if (ss == "RocketVelocity")   //������ٶ�
		{
			_ObjectLGRock.Rock_RocketVelocity = _dValue;
		}
		else if (ss == "RocketCEP")   //�����CEP
		{
			_ObjectLGRock.Rock_CEP = _dValue;
		}
		else if (ss == "ShellMassClylinder") //Բ���ο�������
		{
			_ObjectLGRock.ShellMass_Clylinder = _dValue;
		}
		else if (ss == "ChargeMassClylinder")   //Բ����װҩ����
		{
			_ObjectLGRock.ChargeMass_Clylinder = _dValue;
		}
		else if (ss == "AllMassWholer")         //װҩ��������
		{
			_ObjectLGRock.ChargeMass_Whole = _dValue;
		}
		else if (ss == "AllAmmoMass")           //ս������������
		{
			_ObjectLGRock.AllMass_Whole = _dValue;
		}
		else if (ss == "ShellInterDiameter")   //Բ���ھ�
		{ 
		    _ObjectLGRock.ShellInterDiameter = _dValue;
		}
		else if (ss == "ShellOuterDiameter")   //Բ���⾶
		{
			_ObjectLGRock.ShellOuterDiameter = _dValue;
		}
		else if (ss == "ShellBrokenDiameter")  //Բ�����Ѱ뾶
		{
			_ObjectLGRock.ShellBrokenDiameter = _dValue;
		}
		else if (ss == "Density")               //װҩ�ܶ�
		{
			_ObjectLGRock.Density = _dValue;
		}
		else if (ss == "ExplosionVelocity")
		{
			_ObjectLGRock.ExplosionVelocity = _dValue;
		}
		else if (ss == "ExplosionHeat")        //����
		{
			_ObjectLGRock.ExplosionHeat = _dValue;
		}
		else if (ss == "ExplosinPressure")  //��ѹ
		{
			_ObjectLGRock.ExplosinPressure = _dValue;
		}
		else if (ss == "ShapeCoefficient")
		{
			_ObjectLGRock.SC = _dValue;
		}
		else if (ss == "AboveSeaLevel")
		{
			_ObjectLGRock.ASL = _dValue;
		}
		else if (ss == "ResistanceCoefficient")
		{
			_ObjectLGRock.RC = _dValue;
		}
		else if (ss == "FireLat")           //���γ��
		{
			_ObjectLGRock.FireLat = _dValue;
		}
		else if (ss == "FireLon")         //��𾭶�
		{
			_ObjectLGRock.FireLon = _dValue;
		}
		else if (ss == "DropLat") //��׼γ��
		{
			_ObjectLGRock.AimLat = _dValue;
		}
		else if (ss == "DropLon")//��׼����
		{
			_ObjectLGRock.AimLon = _dValue;
		}
		else if (ss == "BHE")
		{
			_ObjectLGRock.BHE = _dValue;
		}
		else if (ss == "BHDt")
		{
			_ObjectLGRock.BHD = _dValue;
		}
		else if (ss == "FragmentDamageCriterion")  //�����о�
		{
			_ObjectLGRock.Frag_FragmentDamageCriterion = _dValue;
		}
		else if (ss == "WarheadLength_Whole")
		{
		   _ObjectLGRock.WarheadLength_Whole = _dValue;
		}
		else if (ss == "WarheadLength_Clylinder")
		{
			_ObjectLGRock.WarheadLength_Clylinder = _dValue;
		}
		else if (ss == "Frag_SDA")
		{
			_ObjectLGRock.Frag_SDA = _dValue;
		}
		else if (ss == "Frag_dis")
		{
			_ObjectLGRock.Frag_dis = _dValue;
		}
		else if(ss == "ShockWavePressure")
		{
			_ObjectLGRock.ShockWavePressure = _dValue;
		}
	}
}
//
void ArgumentDialog::GetSpinBoxValue(int _iValue)
{
	QSpinBox *_pSpinBox = dynamic_cast<QSpinBox*>(sender());
	if (_pSpinBox != NULL)
	{
		QString ss = _pSpinBox->objectName();
		if (ss == "NumOfFragments")  //��Ƭ����
		{
			_ObjectLGRock.FragmentNumber = _iValue;
		}
	}
}
//
LGRockParameter& ArgumentDialog::ReadRockParameter()
{
	return _ObjectLGRock;
}
//
bool ArgumentDialog::IsOKOrCancancle() const
{
	return SetTureFalse;
}
//
void ArgumentDialog::SetingOKOrCancle()
{
	QPushButton *_pButton = dynamic_cast<QPushButton*>(sender());
	if (_pButton != NULL)
	{
		if (_pButton->objectName() == "OK")
		{
			_ObjectLGRock.ExplosionHeat = _ExplosionHeat_Line->text().toDouble();
			_ObjectLGRock.ExplosinPressure = _ExplosinPressure_Line->text().toDouble();
			SetTureFalse  = true;
			this->close();
		}
		else if (_pButton->objectName() == "Cancle")
		{
			SetTureFalse = false;
			this->close();
		}
	}
}
//
void ArgumentDialog::GetAimLatLon(double lat,double lon)
{
	_DropLat_SpinBox->setValue(lat);
	_DropLat_SpinBox->setDisabled(true);
	_DropLon_SpinBox->setValue(lon);
	_DropLon_SpinBox->setDisabled(true);


	//
	_ObjectLGRock.AimLat = lat;
	_ObjectLGRock.AimLon = lon;
};
void ArgumentDialog::PbFileChoise()
{
	emit EmitChoiseFile();
}
//
void ArgumentDialog::ConfigurationParameter()
{
	_FragmentMass_spin->setValue(5.0);
	_FragmentNum_spin->setValue(300);
	_scatteringAngle_SpinBox->setValue(1.0);
	_centerline_SpinBox->setValue(1.0);
	_RocketVelocity_SpinBox->setValue(300.0);
	_RocketCEP_SpinBox->setValue(5.0);
	_ShellMass_Clylinder_SpinBox->setValue(100.0);
	_ChargeMass_Clylinder_SpinBox->setValue(50.0);
	_AllMass_Wholer_SpinBox->setValue(180.0);
	_AllAmmoMass_Wholer_SpinBox->setValue(60.0);
	_ShellInterDiameter_SpinBox->setValue(2.0);
	_ShellOuterDiameter_SpinBox->setValue(2.2);
	_ShellBrokenDiameter_SpinBox->setValue(2.5);
	_WarheadLength_Whole_SpinBox->setValue(3.0);
	_WarheadLength_Clylinder_SpinBox->setValue(3.0);
	_Density_SpinBox->setValue(1680.0);
	_ExplosionVelocity_SpinBox->setValue(7000.0);
	_ShapeCoefficient_SpinBox->setValue(0.00307);
	_AboveSeaLevel_SpinBox->setValue(15.0);
	_ResistanceCoefficient_SpinBox->setValue(0.970);
	_FragmentDamageCriterion_SpinBox->setValue(78.0);
	_FireLat_SpinBox->setValue(0.0);
	_FireLon_SpinBox->setValue(0.0);
	_BHE_SpinBox->setValue(20.0);
	_BHDt_SpinBox->setValue(0.2);
	_ExplosionHeat_Line->setText("4e7");;
	_ExplosinPressure_Line->setText("24e9");
	_shockwavepressure_SpinBox->setValue(0.02);
};
//
void ArgumentDialog::GetConfigFileSettings(const LGRockParameter Object)
{
	_FragmentMass_spin->setValue(Object.Frag_Mass);
	_FragmentNum_spin->setValue(Object.FragmentNumber);
	_scatteringAngle_SpinBox->setValue(Object.Rock_WarheadStaticAngle);
	_centerline_SpinBox->setValue(Object.Rock_WarheadStaticAngleToCenter);
	_RocketVelocity_SpinBox->setValue(Object.Rock_RocketVelocity);
	_RocketCEP_SpinBox->setValue(Object.Rock_CEP);
	_ShellMass_Clylinder_SpinBox->setValue(Object.ShellMass_Clylinder);
	_ChargeMass_Clylinder_SpinBox->setValue(Object.ChargeMass_Clylinder);
	_AllMass_Wholer_SpinBox->setValue(Object.AllMass_Whole);
	_AllAmmoMass_Wholer_SpinBox->setValue(Object.ChargeMass_Whole);
	_ShellInterDiameter_SpinBox->setValue(Object.ShellInterDiameter);
	_ShellOuterDiameter_SpinBox->setValue(Object.ShellOuterDiameter);
	_ShellBrokenDiameter_SpinBox->setValue(Object.ShellBrokenDiameter);
	_WarheadLength_Whole_SpinBox->setValue(Object.WarheadLength_Whole);
	_WarheadLength_Clylinder_SpinBox->setValue(Object.WarheadLength_Clylinder);
	_Density_SpinBox->setValue(Object.Density);
	_ExplosionVelocity_SpinBox->setValue(Object.ExplosionVelocity);
	_ShapeCoefficient_SpinBox->setValue(Object.SC);
	_AboveSeaLevel_SpinBox->setValue(Object.ASL);
	_ResistanceCoefficient_SpinBox->setValue(Object.RC);
	_FragmentDamageCriterion_SpinBox->setValue(Object.Frag_FragmentDamageCriterion);
	_FireLat_SpinBox->setValue(Object.FireLat);
	_FireLon_SpinBox->setValue(Object.FireLon);
	_BHE_SpinBox->setValue(Object.BHE);
	_BHDt_SpinBox->setValue(Object.BHD);
	QString str;
	_ExplosionHeat_Line->setText(str.setNum(Object.ExplosionHeat));
	_ExplosinPressure_Line->setText(str.setNum(Object.ExplosinPressure));
	_shockwavepressure_SpinBox->setValue(Object.ShockWavePressure);
};