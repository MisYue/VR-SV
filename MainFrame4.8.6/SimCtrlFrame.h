#pragma once

#include <QWidget>
#include "ui_SimCtrlFrame.h"

class CSimCtrlFrame : public QWidget
{
	Q_OBJECT

public:
	CSimCtrlFrame(QWidget* parent = NULL);
	~CSimCtrlFrame(void);

private:
	Ui::SimCtrlFrame ui;
};

