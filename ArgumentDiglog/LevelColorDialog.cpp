#include "LevelColorDialog.h"

LevelColorDialog::LevelColorDialog(QWidget *parent):QWidget(parent)
{
	this->setFixedHeight(260);
	this->setMaximumHeight(260);
	this->setFixedWidth(115);
	InitDialog();
};
//
LevelColorDialog::~LevelColorDialog()
{

};
//
void LevelColorDialog::InitDialog()
{
	QGroupBox *groupBox_11;
	QGridLayout *gridLayout_2;
	QHBoxLayout *horizontalLayout_2;
	QPushButton *button_9;
	QLabel *label_9;

	QHBoxLayout *horizontalLayout_3;
	QPushButton *button_10;
	QLabel *label_10;

	QHBoxLayout *horizontalLayout_4;
	QPushButton *label_13;
	QLabel *label_14;

	QHBoxLayout *horizontalLayout_5;
	QPushButton *label_15;
	QLabel *label_16;

	QHBoxLayout *horizontalLayout_8;
	QPushButton *label_21;
	QLabel *label_22;

	QHBoxLayout *horizontalLayout_6;
	QPushButton *label_17;
	QLabel *label_18;

	QHBoxLayout *horizontalLayout_7;
	QPushButton *label_19;
	QLabel *label_20;

	QHBoxLayout *horizontalLayout_10;
	QPushButton *label_25;
	QLabel *label_26;

	QHBoxLayout *horizontalLayout_11;
	QPushButton *label_27;
	QLabel *label_28;

	QHBoxLayout *horizontalLayout_9;
	QPushButton *label_23;
	QLabel *label_24;

	groupBox_11 = new QGroupBox(this);
	groupBox_11->setGeometry(7,7,100,250);
	groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
	groupBox_11->setEnabled(true);
	groupBox_11->setStyleSheet(QString::fromUtf8(" QGroupBox {\n"
		//"border-color:rgba(0, 0, 0, 180);\n"
		//"background-color: rgba(155, 195, 255, 100);\n"
		"\n"
		"padding:0px;\n"
		"border-radius:0px; \n"
		" }"));
	groupBox_11->setWindowOpacity(1);
	groupBox_11->setWindowFlags(Qt::FramelessWindowHint);//这个是widget的标题栏和边框去掉
	groupBox_11->setAttribute(Qt::WA_TranslucentBackground);//这个是widget的背景弄透明

	gridLayout_2 = new QGridLayout(groupBox_11);
	gridLayout_2->setContentsMargins(0, 0, 0, 0);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
	gridLayout_2->setHorizontalSpacing(6);
	gridLayout_2->setVerticalSpacing(0);
	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	button_9 = new QPushButton(groupBox_11);
	button_9->setObjectName(QString::fromUtf8("Level_1"));
	button_9->setMinimumSize(QSize(20, 20));
	button_9->setMaximumSize(QSize(20, 30));
	button_9->setStyleSheet(QString::fromUtf8("background-color: rgb(211, 255, 4);"));
	connect(button_9,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_2->addWidget(button_9);

	label_9 = new QLabel(groupBox_11);
	label_9->setObjectName(QString::fromUtf8("label_10"));

	horizontalLayout_2->addWidget(label_9);


	gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

	horizontalLayout_3 = new QHBoxLayout();
	horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	button_10 = new QPushButton(groupBox_11);
	button_10->setObjectName(QString::fromUtf8("Level_2"));
	button_10->setMinimumSize(QSize(20, 20));
	button_10->setMaximumSize(QSize(20, 30));
	button_10->setStyleSheet(QString::fromUtf8("background-color: rgb(110, 255, 0);"));
	connect(button_10,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_3->addWidget(button_10);

	label_10 = new QLabel(groupBox_11);
	label_10->setObjectName(QString::fromUtf8("label_12"));

	horizontalLayout_3->addWidget(label_10);


	gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

	horizontalLayout_4 = new QHBoxLayout();
	horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
	label_13 = new QPushButton(groupBox_11);
	label_13->setObjectName(QString::fromUtf8("Level_3"));
	label_13->setMinimumSize(QSize(20, 20));
	label_13->setMaximumSize(QSize(20, 30));
	label_13->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));
	connect(label_13,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_4->addWidget(label_13);

	label_14 = new QLabel(groupBox_11);
	label_14->setObjectName(QString::fromUtf8("label_14"));

	horizontalLayout_4->addWidget(label_14);


	gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

	horizontalLayout_5 = new QHBoxLayout();
	horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
	label_15 = new QPushButton(groupBox_11);
	label_15->setObjectName(QString::fromUtf8("Level_4"));
	label_15->setMinimumSize(QSize(20, 20));
	label_15->setMaximumSize(QSize(20, 30));
	label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(4,255,110);"));
	connect(label_15,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_5->addWidget(label_15);

	label_16 = new QLabel(groupBox_11);
	label_16->setObjectName(QString::fromUtf8("label_16"));

	horizontalLayout_5->addWidget(label_16);


	gridLayout_2->addLayout(horizontalLayout_5, 3, 0, 1, 1);

	horizontalLayout_8 = new QHBoxLayout();
	horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
	label_21 = new QPushButton(groupBox_11);
	label_21->setObjectName(QString::fromUtf8("Level_5"));
	label_21->setMinimumSize(QSize(20, 20));
	label_21->setMaximumSize(QSize(20, 30));
	label_21->setStyleSheet(QString::fromUtf8("background-color: rgb(4,255,255);"));
	connect(label_21,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_8->addWidget(label_21);

	label_22 = new QLabel(groupBox_11);
	label_22->setObjectName(QString::fromUtf8("label_22"));

	horizontalLayout_8->addWidget(label_22);


	gridLayout_2->addLayout(horizontalLayout_8, 4, 0, 1, 1);

	horizontalLayout_6 = new QHBoxLayout();
	horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
	label_17 = new QPushButton(groupBox_11);
	label_17->setObjectName(QString::fromUtf8("Level_6"));
	label_17->setMinimumSize(QSize(20, 20));
	label_17->setMaximumSize(QSize(20, 30));
	label_17->setStyleSheet(QString::fromUtf8("background-color: rgb(0,125,255);"));
	connect(label_17,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_6->addWidget(label_17);

	label_18 = new QLabel(groupBox_11);
	label_18->setObjectName(QString::fromUtf8("label_18"));

	horizontalLayout_6->addWidget(label_18);


	gridLayout_2->addLayout(horizontalLayout_6, 5, 0, 1, 1);

	horizontalLayout_7 = new QHBoxLayout();
	horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
	label_19 = new QPushButton(groupBox_11);
	label_19->setObjectName(QString::fromUtf8("Level_7"));
	label_19->setMinimumSize(QSize(20, 20));
	label_19->setMaximumSize(QSize(20, 30));
	label_19->setStyleSheet(QString::fromUtf8("background-color: rgb(0,0,255);"));
	connect(label_19,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_7->addWidget(label_19);

	label_20 = new QLabel(groupBox_11);
	label_20->setObjectName(QString::fromUtf8("label_20"));

	horizontalLayout_7->addWidget(label_20);


	gridLayout_2->addLayout(horizontalLayout_7, 6, 0, 1, 1);

	horizontalLayout_10 = new QHBoxLayout();
	horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
	label_25 = new QPushButton(groupBox_11);
	label_25->setObjectName(QString::fromUtf8("Level_8"));
	label_25->setMinimumSize(QSize(20, 20));
	label_25->setMaximumSize(QSize(20, 30));
	label_25->setStyleSheet(QString::fromUtf8("background-color: rgb(120,0,255);"));
	connect(label_25,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_10->addWidget(label_25);

	label_26 = new QLabel(groupBox_11);
	label_26->setObjectName(QString::fromUtf8("label_26"));

	horizontalLayout_10->addWidget(label_26);


	gridLayout_2->addLayout(horizontalLayout_10, 7, 0, 1, 1);

	horizontalLayout_11 = new QHBoxLayout();
	horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
	label_27 = new QPushButton(groupBox_11);
	label_27->setObjectName(QString::fromUtf8("Level_9"));
	label_27->setMinimumSize(QSize(20, 20));
	label_27->setMaximumSize(QSize(20, 30));
	label_27->setStyleSheet(QString::fromUtf8("background-color: rgb(228,0,255);"));
	connect(label_27,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_11->addWidget(label_27);

	label_28 = new QLabel(groupBox_11);
	label_28->setObjectName(QString::fromUtf8("label_28"));

	horizontalLayout_11->addWidget(label_28);


	gridLayout_2->addLayout(horizontalLayout_11, 8, 0, 1, 1);

	horizontalLayout_9 = new QHBoxLayout();
	horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
	label_23 = new QPushButton(groupBox_11);
	label_23->setObjectName(QString::fromUtf8("Level_10"));
	label_23->setMinimumSize(QSize(20, 20));
	label_23->setMaximumSize(QSize(20, 30));
	label_23->setStyleSheet(QString::fromUtf8("background-color: rgb(255,0,158);"));
	connect(label_23,SIGNAL(clicked()),this,SLOT(ChangeBackgroundColor()));
	horizontalLayout_9->addWidget(label_23);

	label_24 = new QLabel(groupBox_11);
	label_24->setObjectName(QString::fromUtf8("label_24"));

	horizontalLayout_9->addWidget(label_24);


	gridLayout_2->addLayout(horizontalLayout_9, 9, 0, 1, 1);



	groupBox_11->setTitle(QString());
	button_9->setText(QString());
	label_9->setText(QApplication::translate("Form", "0.0-10.0", 0, QApplication::UnicodeUTF8));
	button_10->setText(QString());
	label_10->setText(QApplication::translate("Form", "10.0-20.0", 0, QApplication::UnicodeUTF8));
	label_13->setText(QString());
	label_14->setText(QApplication::translate("Form", "20.0-30.0", 0, QApplication::UnicodeUTF8));
	label_15->setText(QString());
	label_16->setText(QApplication::translate("Form", "30.0-40.0", 0, QApplication::UnicodeUTF8));
	label_21->setText(QString());
	label_22->setText(QApplication::translate("Form", "40.0-50.0", 0, QApplication::UnicodeUTF8));
	label_17->setText(QString());
	label_18->setText(QApplication::translate("Form", "50.0-60.0", 0, QApplication::UnicodeUTF8));
	label_19->setText(QString());
	label_20->setText(QApplication::translate("Form", "60.0-70.0", 0, QApplication::UnicodeUTF8));
	label_25->setText(QString());
	label_26->setText(QApplication::translate("Form", "70.0-80.0", 0, QApplication::UnicodeUTF8));
	label_27->setText(QString());
	label_28->setText(QApplication::translate("Form", "80.0-90.0", 0, QApplication::UnicodeUTF8));
	label_23->setText(QString());
	label_24->setText(QApplication::translate("Form", "90.0-100.0", 0, QApplication::UnicodeUTF8));
}
//
void LevelColorDialog::ChangeBackgroundColor()
{
	QPushButton *_pButton = dynamic_cast<QPushButton*>(sender());
	QString red;
	QString blue;
	QString green;
	QString _colorStyle;

	if (_pButton != NULL)
	{
		_pColorDialog = new QColorDialog;
		connect(_pColorDialog,SIGNAL(currentColorChanged(const QColor&)),this,SLOT(GetChangColor(const QColor&))); 
		_pColorDialog->exec();
		red.setNum(_pcolor.red());
		blue.setNum(_pcolor.blue());
		green.setNum(_pcolor.green());

		red = red+","+green+","+blue;
		_colorStyle = "background-color: rgb("+red+");";
		_pButton->setStyleSheet(_colorStyle);
	}

}
//
void LevelColorDialog::GetChangColor(const QColor& _color)
{
	_pcolor = _color;
}
//
