/*
   系统单位设定
   2016.7.1
   ZXD
*/
#pragma once
#include "Lib.h"
class UnitSystemDialog : public QDialog
{
	Q_OBJECT
public:
	UnitSystemDialog(QWidget *parent = 0);
	~UnitSystemDialog();
	void InitDialog();
	void GetUnitSystemValue(int&,int&,int&) const;
private:
	std::vector<QCheckBox*> _ListTimeBox;
	std::vector<QCheckBox*> _ListLengthBox;
	std::vector<QCheckBox*> _ListMassBox;

	int UnitTime;
	int UnitMass;
	int UnitLength;

private slots:
		void GetSelectMassValue(int);
		void GetSelectTimeValue(int);
		void GetSelectLengthValue(int);
};