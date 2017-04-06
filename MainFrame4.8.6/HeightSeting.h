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
	//���߶�
	double FireHeight;
	//��ը�߶�
	double BoomHeight;
	//���߶�
	double MaxHeight;
private slots:
	//Func
	void SetOk();
	void SetCancle();
};
#endif
