#pragma once

#include <QWidget>
#include "ui_ToolWidget.h"

class CToolWidget : public QWidget
{
	Q_OBJECT

public:
	CToolWidget(QWidget* parent = NULL);
	~CToolWidget(void);

private:
	Ui::ToolWidget ui;
};
