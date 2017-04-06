#include "CsvNumDialog.h"
//
CSVDialog::CSVDialog(QString filename,QDialog *parent):fileName(filename),QDialog(parent)
{
	this->setMinimumHeight(200);
	this->setMaximumHeight(200);
	this->setMinimumWidth(400);
	this->setMaximumWidth(400);
	_pReadNum = new CSVRead;
};
//
CSVDialog::~CSVDialog()
{

};
//
void CSVDialog::InitFrameDialog()
{
	this->setWindowTitle(fileName);
	QGridLayout *layout = new QGridLayout;
	this->setLayout(layout);
	count = 0;
	//设置射程插值表数组
	QHBoxLayout *_FireDistance_layout = new QHBoxLayout;
	QLabel *_FireDistance_label = new QLabel;
	_FireDistance_label->setText(QString::fromLocal8Bit("射程插值表:"));
	_FireDistance_label->setMinimumWidth(60);
	_FireDistance_Line = new QLineEdit;
	//_FireDistance_Line->setMaximumWidth(250);
	_FireDistance_Line->setObjectName("FireDistance");
	_FireDistance_layout->addWidget(_FireDistance_label);
	_FireDistance_layout->addWidget(_FireDistance_Line);

	//设置落角插值表数组
	QHBoxLayout *_FallingAngle_layout = new QHBoxLayout;
	QLabel *_FallingAngle_label = new QLabel;
	_FallingAngle_label->setText(QString::fromLocal8Bit("落角插值表:"));
	_FallingAngle_label->setMinimumWidth(60);
	_FallingAngle_Line = new QLineEdit;
	//_FallingAngle_Line->setMaximumWidth(250);
	_FallingAngle_Line->setObjectName("FallingAngle");
	_FallingAngle_layout->addWidget(_FallingAngle_label);
	_FallingAngle_layout->addWidget(_FallingAngle_Line);

	QHBoxLayout *Button_layout = new QHBoxLayout;
	QPushButton *pb_ok = new QPushButton;
	pb_ok->setText(QString::fromLocal8Bit("确定"));
	pb_ok->setMaximumWidth(80);
	connect(pb_ok,SIGNAL(clicked()),this,SLOT(close()));
	QPushButton *pb_cancle = new QPushButton;
	pb_cancle->setText(QString::fromLocal8Bit("取消"));
	pb_cancle->setMaximumWidth(80);
	connect(pb_cancle,SIGNAL(clicked()),this,SLOT(close()));
	Button_layout->addWidget(pb_ok);
	Button_layout->addWidget(pb_cancle);

	layout->addLayout(_FireDistance_layout,1,0,1,1);
	layout->addLayout(_FallingAngle_layout,2,0,1,1);
	layout->addLayout(Button_layout,3,0,1,1);

 
	int lineID = 0;
	QString strAngle;
	QString strDis;
	

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

	}

	while (!file.atEnd()) 
	{
		QString str  = file.readLine();	
		QStringList ll = str.split(",");
		strAngle = strAngle+ll.at(1)+",";
		strDis   = strDis+ll.at(0)+",";
	}

		_FireDistance_Line->setText(strDis);
		_FallingAngle_Line->setText(strAngle);
}
//
void CSVDialog::SelectCSVfile(std::vector<double>&pDis,std::vector<double>&pAngle)
{
	/*double a;
	int lineID = 0;
	QStringList _dis;
	QStringList _angle;
	QString strLine;

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

	}

	while (!file.atEnd()) 
	{
	strLine  = file.readLine();	
	if (lineID == 0)
	{
	_FireDistance_Line->setText(strLine);
	_dis = strLine.split(",");
	_dis.removeAt(_dis.size() -1);
	}
	if (lineID == 1)
	{
	_FallingAngle_Line->setText(strLine);
	_angle = strLine.split(",");
	_angle.removeAt(_angle.size() -1);
	}
	++lineID;
	}

	lineID = _dis.size();
	for (int i = 0; i <lineID;++i)
	{
	pDis.push_back(_dis.at(i).toDouble());
	}
	lineID = _dis.size();
	for (int i = 0; i <lineID;++i)
	{
	pAngle.push_back(_angle.at(i).toDouble());
	}
	count = _angle.size();*/

	pDis.clear();
	pAngle.clear();
	int CountRow(0);
	if (fileName.isEmpty())
	{
		count = 0;
	}
	else
	{
		_pReadNum->inputDateBase(fileName.toStdString());
		CountRow = _pReadNum->getLineCount();
		count = CountRow;
		for (int i = 1; i <= CountRow;++i)
		{
			pDis.push_back(_pReadNum->transformStringDouble(_pReadNum->getFigure(i,1)));
			pAngle.push_back(_pReadNum->transformStringDouble(_pReadNum->getFigure(i,2)));
		}
	}
}
//
int CSVDialog::GetNumCount()
{
	return count;
}
//
void CSVDialog::SetFileName(QString file)
{
	fileName = file;
	InitFrameDialog();
};