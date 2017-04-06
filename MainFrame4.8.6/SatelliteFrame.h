#pragma once

#include <QWidget>
#include "ui_SatelliteFrame.h"

class CSatelliteFrame : public QWidget
{
	Q_OBJECT

public:
	CSatelliteFrame(QWidget* parent = NULL);
	~CSatelliteFrame(void);

protected slots:
	// 创建弹道导弹
	void CreateSatellite(void);

private: 
	Ui::SatelliteFrame ui; 
};

