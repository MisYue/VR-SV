/*
    功能说明：保存、读取XML配置文件数据，并把数据以机构的形式送出
	2016-8-10
	ZXD
*/
#pragma once
#include<QtXml/QDomDocument>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "DestinaParameterDialog.h"
#include "RockArgumentdialog.h"
#include <QtGui/QTableWidget>
#include <BITUnitsSupport/Bit_UnitSystem.h>
//
class XMLOperation : public QWidget
{
	Q_OBJECT 
public:
	XMLOperation(const QString FileName = "");
	~XMLOperation();
	void SetFileName(QString name);
	bool SaveXMLFile(const TargetAreaParameter &_pT,const LGRockParameter &_pLG);
	bool OpenXMLFile();
	void GetTheUnitSystem(int length,int time,int mass);
	TargetAreaParameter GetAreaParameter();
	LGRockParameter     GetLgRockParameter();
	void SetLocalUnity(Bit_UnitSystem *unity);
private:
	void GetRatioChangeArea(TargetAreaParameter &Tarea,const Bit_UnitSystem *pV);
	void GetRatioChangeRock(LGRockParameter &LRock,const Bit_UnitSystem *pV);
	QString filename;
	//目标参数
	TargetAreaParameter _TargetArea;
	std::vector<TargetAreaParameter> AreaVector;
	//弹体参数
	LGRockParameter _RockObject;
	std::vector<LGRockParameter> RockVector;
	//XML文件单位系统
	std::vector<Bit_UnitSystem*> XMLFileUnity;
	QStringList _xmlFileUnity;
	//本地单位系统
	Bit_UnitSystem *_LocalUnity;
	//获取数据过程中系统
	Bit_UnitSystem *_p;
	//
	int _length;
	int _time;
	int _mass;
	//
	int area_row;
	int rock_row;
	//私有函数
	void AreaTable();
	void RockTable();
	//
	QDialog *_plog;
	QVBoxLayout *_playout;
	QTableWidget *_pAreaTab;
	QTableWidget *_pRockTab;
private slots:
	void GetAreaNum(int row,int column);
	void GetRockNum(int row,int column);
};