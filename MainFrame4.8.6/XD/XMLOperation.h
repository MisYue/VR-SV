/*
    ����˵�������桢��ȡXML�����ļ����ݣ����������Ի�������ʽ�ͳ�
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
	//Ŀ�����
	TargetAreaParameter _TargetArea;
	std::vector<TargetAreaParameter> AreaVector;
	//�������
	LGRockParameter _RockObject;
	std::vector<LGRockParameter> RockVector;
	//XML�ļ���λϵͳ
	std::vector<Bit_UnitSystem*> XMLFileUnity;
	QStringList _xmlFileUnity;
	//���ص�λϵͳ
	Bit_UnitSystem *_LocalUnity;
	//��ȡ���ݹ�����ϵͳ
	Bit_UnitSystem *_p;
	//
	int _length;
	int _time;
	int _mass;
	//
	int area_row;
	int rock_row;
	//˽�к���
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