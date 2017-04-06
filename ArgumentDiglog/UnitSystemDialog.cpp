#include "UnitSystemDialog.h"
UnitSystemDialog::UnitSystemDialog(QWidget *parent):QDialog(parent)
{
	setWindowTitle(QString::fromLocal8Bit("单位系统设置"));
	this->setFixedWidth(240);
	this->setFixedHeight(180);
	InitDialog();

	UnitTime = 1;
	UnitMass = 1;
	UnitLength = 1;
};
UnitSystemDialog::~UnitSystemDialog()
{
	_ListTimeBox.~vector();
	_ListMassBox.~vector();
	_ListLengthBox.~vector();
};
void UnitSystemDialog::InitDialog()
{
	QHBoxLayout *_layout = new QHBoxLayout;
	this->setLayout(_layout);


	//长度
	QGroupBox *_pLengthBox = new QGroupBox;
	_pLengthBox->setTitle(QString::fromLocal8Bit("长度单位"));
	_layout->addWidget(_pLengthBox);
	QGridLayout *_layout_Length = new QGridLayout;
	_pLengthBox->setLayout(_layout_Length);

	QCheckBox *_cbMM = new QCheckBox;
	_cbMM->setObjectName("MM");
	_cbMM->setText("mm");
	_cbMM->setCheckState(Qt::Checked);
	connect(_cbMM,SIGNAL(stateChanged(int)),this,SLOT(GetSelectLengthValue(int)));

	QCheckBox *_cbCM = new QCheckBox;
	_cbCM->setObjectName("CM");
	_cbCM->setText("cm");
	_cbCM->setEnabled(0);
	connect(_cbCM,SIGNAL(stateChanged(int)),this,SLOT(GetSelectLengthValue(int)));

	QCheckBox *_cbM = new QCheckBox;
	_cbM->setObjectName("M");
	_cbM->setText("m");
	_cbM->setEnabled(0);
	connect(_cbM,SIGNAL(stateChanged(int)),this,SLOT(GetSelectLengthValue(int)));

	QCheckBox *_cbKM = new QCheckBox;
	_cbKM->setObjectName("KM");
	_cbKM->setText("km");
	_cbKM->setEnabled(0);
	connect(_cbKM,SIGNAL(stateChanged(int)),this,SLOT(GetSelectLengthValue(int)));

	 

	_layout_Length->addWidget(_cbMM,0,0,1,1);
	_layout_Length->addWidget(_cbCM,1,0,1,1);
	_layout_Length->addWidget(_cbM,2,0,1,1);
	_layout_Length->addWidget(_cbKM,3,0,1,1);

	_ListLengthBox.push_back(_cbMM);
	_ListLengthBox.push_back(_cbCM);
	_ListLengthBox.push_back(_cbM);
	_ListLengthBox.push_back(_cbKM);

	//时间
	QGroupBox *_pTimeBox = new QGroupBox;
	_pTimeBox->setTitle(QString::fromLocal8Bit("时间单位"));
	_layout->addWidget(_pTimeBox);
	QGridLayout *_layout_Time = new QGridLayout;
	_pTimeBox->setLayout(_layout_Time);

	QCheckBox *_cbUS = new QCheckBox;
	_cbUS->setObjectName("US");
	_cbUS->setText("us");
	_cbUS->setCheckState(Qt::Checked);
	connect(_cbUS,SIGNAL(stateChanged(int)),this,SLOT(GetSelectTimeValue(int)));

	QCheckBox *_cbMS = new QCheckBox;
	_cbMS->setObjectName("MS");
	_cbMS->setText("ms");
	_cbMS->setEnabled(0);
	connect(_cbMS,SIGNAL(stateChanged(int)),this,SLOT(GetSelectTimeValue(int)));

	QCheckBox *_cbS = new QCheckBox;
	_cbS->setObjectName("S");
	_cbS->setText("s");
	_cbS->setEnabled(0);
	connect(_cbS,SIGNAL(stateChanged(int)),this,SLOT(GetSelectTimeValue(int)));

	_layout_Time->addWidget(_cbUS,0,0,1,1);
	 _layout_Time->addWidget(_cbMS,1,0,1,1);
	 _layout_Time->addWidget(_cbS,2,0,1,1);

	 _ListTimeBox.push_back(_cbUS);
	 _ListTimeBox.push_back(_cbMS);
	 _ListTimeBox.push_back(_cbS);

	 //重量
	 QGroupBox *_pMassBox = new QGroupBox;
	 _pMassBox->setTitle(QString::fromLocal8Bit("重量单位"));
	 _layout->addWidget(_pMassBox);
	 QGridLayout *_layout_Mass = new QGridLayout;
	 _pMassBox->setLayout(_layout_Mass);

	 QCheckBox *_cbG = new QCheckBox;
	 _cbG->setObjectName("G");
	 _cbG->setText("g");
	 _cbG->setCheckState(Qt::Checked);
	 connect(_cbG,SIGNAL(stateChanged(int)),this,SLOT(GetSelectMassValue(int)));

	 QCheckBox *_cbKG = new QCheckBox;
	 _cbKG->setObjectName("KG");
	 _cbKG->setText("kg");
	 _cbKG->setEnabled(0);
	 connect(_cbKG,SIGNAL(stateChanged(int)),this,SLOT(GetSelectMassValue(int)));

	 _layout_Mass->addWidget(_cbG,0,0,1,1);
	 _layout_Mass->addWidget(_cbKG,1,0,1,1);

	 _ListMassBox.push_back(_cbG);
	 _ListMassBox.push_back(_cbKG);


	 QPushButton *_OK_button = new QPushButton;
	 _OK_button->setFixedWidth(40);
	 _OK_button->setFixedHeight(20);
	 _OK_button->setText(QString::fromLocal8Bit("确定"));
	  connect(_OK_button,SIGNAL(clicked()),this,SLOT(close()));

	 _layout_Mass->addWidget(_OK_button,2,0,1,1);
};
//
void UnitSystemDialog::GetSelectTimeValue(int state)
{
	QCheckBox *_pCB = dynamic_cast<QCheckBox*>(sender());
	std::vector<QCheckBox*>::iterator _itorP;

	if (_pCB != NULL)
	{
		QString ObName = _pCB->objectName();
		if ((ObName == "US")||(ObName == "MS")||(ObName == "S"))
		{
			_itorP = _ListTimeBox.begin();
			for (;_itorP != _ListTimeBox.end();++_itorP)
			{
				if (state == 0)
				{
					(*_itorP)->setEnabled(1);
				}
				if (state == 2)
				{
					if ((*_itorP) != _pCB)
					{
						(*_itorP)->setEnabled(0);
					}
				}
			}
		}
	}
	_itorP = _ListTimeBox.begin();
	for (;_itorP != _ListTimeBox.end();++_itorP)
	{
		int checkState = (*_itorP)->checkState();
		if (checkState == Qt::Checked)
		{
			if ((*_itorP)->objectName() == "US")
			{
				UnitTime = 1;
			}
			if ((*_itorP)->objectName() == "MS")
			{
				UnitTime = 2;
			}
			if ((*_itorP)->objectName() == "S")
			{
				UnitTime = 3;
			}
		}
	}
}
//
//
void UnitSystemDialog::GetSelectLengthValue(int state)
{
	QCheckBox *_pCB = dynamic_cast<QCheckBox*>(sender());
	std::vector<QCheckBox*>::iterator _itorP;

	if (_pCB != NULL)
	{
		QString ObName = _pCB->objectName();
		if ((ObName == "MM")||(ObName == "CM")||(ObName == "M")||(ObName == "KM"))
		{
			_itorP = _ListLengthBox.begin();
			for (;_itorP != _ListLengthBox.end();++_itorP)
			{
				if (state == 0)
				{
					(*_itorP)->setEnabled(1);
				}
				if (state == 2)
				{
					if ((*_itorP) != _pCB)
					{
						(*_itorP)->setEnabled(0);
					}
				}
			}
		}
	}

	_itorP = _ListLengthBox.begin();
	for (;_itorP != _ListLengthBox.end();++_itorP)
	{
		int checkState = (*_itorP)->checkState();
		if (checkState == Qt::Checked)
		{
			if ((*_itorP)->objectName() == "MM")
			{
				UnitLength = 1;
			}
			if ((*_itorP)->objectName() == "CM")
			{
				UnitLength = 2;
			}
			if ((*_itorP)->objectName() == "M")
			{
				UnitLength = 3;
			}
			if ((*_itorP)->objectName() == "KM")
			{
				UnitLength = 4;
			}
		}
	}
}
//
void UnitSystemDialog::GetSelectMassValue(int state)
{
	QCheckBox *_pCB = dynamic_cast<QCheckBox*>(sender());
	std::vector<QCheckBox*>::iterator _itorP;

	if (_pCB != NULL)
	{
		QString ObName = _pCB->objectName();
		if ((ObName == "G")||(ObName == "KG"))
		{
			_itorP = _ListMassBox.begin();
			for (;_itorP != _ListMassBox.end();++_itorP)
			{
				if (state == 0)
				{
					(*_itorP)->setEnabled(1);
				}
				if (state == 2)
				{
					if ((*_itorP) != _pCB)
					{
						(*_itorP)->setEnabled(0);
					}
				}
			}
		}
	}
	_itorP = _ListMassBox.begin();
	for (;_itorP != _ListMassBox.end();++_itorP)
	{
		int checkState = (*_itorP)->checkState();
		if (checkState == Qt::Checked)
		{
			if ((*_itorP)->objectName() == "G")
			{
				UnitMass = 1;
			}
			if ((*_itorP)->objectName() == "KG")
			{
				UnitMass = 2;
			}
		}
	}

}
//
void UnitSystemDialog::GetUnitSystemValue(int &Mass,int &Time,int &Length) const
{
	Mass = UnitMass;
	Time = UnitTime;
	Length = UnitLength;
}