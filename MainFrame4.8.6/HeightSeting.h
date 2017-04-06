#ifndef _INCLUDE_HEIGHTSETING_H
#define _INCLUDE_HEIGHTSETING_H
#include "ui_HeightSet.h"

class HeightSetingWidget : public QDialog
{
	Q_OBJECT
public:
	HeightSetingWidget();
	~HeightSetingWidget();
	void GetHeightValue(double&,double&,double&);
private:
	Ui::HeightDialog ui;
	//点火高度
	double FireHeight;
	//爆炸高度
	double BoomHeight;
	//最大高度
	double MaxHeight;
private slots:
	//Func
	void SetOk();
	void SetCancle();
};
#endif
