/*
   毁伤等级颜色设定
   2016.7.1
   ZXD
*/
#pragma once
#include "Lib.h"

class LevelColorDialog : public QWidget
{
	Q_OBJECT
public:
	LevelColorDialog(QWidget *parent = 0);
	~LevelColorDialog();
 	void InitDialog();

private slots:
		void ChangeBackgroundColor();
		void GetChangColor(const QColor&);
private:
	QColorDialog *_pColorDialog;
	QColor _pcolor;
};