#include "HeightSeting.h"
//
HeightSetingWidget::HeightSetingWidget()
{
	ui.setupUi(this);
	connect(ui.pb_set,SIGNAL(clicked()),this,SLOT(SetOk()));
	connect(ui.pb_cancle,SIGNAL(clicked()),this,SLOT(SetCancle()));
};
//
HeightSetingWidget::~HeightSetingWidget()
{

};
//
void HeightSetingWidget::SetOk()
{
	FireHeight = ui.Height_Fire->text().toDouble();
	BoomHeight = ui.Height_Boom->text().toDouble();
	MaxHeight = ui.Heightest->text().toDouble();
	this->close();
};
//
void HeightSetingWidget::SetCancle()
{
	this->close();
};
//
void HeightSetingWidget::GetHeightValue(double&H_f,double&H_b,double&H_m)
{
	H_f = FireHeight;
	H_b = BoomHeight;
	H_m = MaxHeight;
};