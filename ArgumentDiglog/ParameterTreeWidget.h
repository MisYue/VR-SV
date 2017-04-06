/*
   ˵������ʾ��λϵͳ��Ŀ�����򡢵���Ȳ���
   ���ڣ�2016.7.8
   �����ߣ�ZXD
*/
#ifndef _PARAMETERTREEWIDGET_H
#define _PARAMETERTREEWIDGET_H
#include "Lib.h"
#include <QtGui/QTreeWidget>
#include"RockArgumentdialog.h"
#include "DestinaParameterDialog.h"


class ParameterTree : public QTreeWidget
{
	Q_OBJECT
public:
	ParameterTree(QTreeWidget *parent = 0);
	~ParameterTree();
	void GetUnitSystemParameter(std::vector<int>&);
	void GetTargetAreaParameter(TargetAreaParameter&);
	void GetRockObjcetParameter(LGRockParameter&);
private:
	void InitWidget();

	 QTreeWidgetItem *UnitSystemRoot;
	 QTreeWidgetItem *TargetAreaRoot;
	 QTreeWidgetItem *RockBodyRoot;
};
#endif