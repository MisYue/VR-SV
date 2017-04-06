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
	// ������������
	void CreateSatellite(void);

private: 
	Ui::SatelliteFrame ui; 
};

