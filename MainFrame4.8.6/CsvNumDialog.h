#pragma  once
#include "CSVReader.h"
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QString>
#include <QPushButton>
#include <QFileDialog>
#include <QPushButton>
#include <QStringList>
#include <vector>
#include <QDebug>

class CSVDialog : public QDialog
{
	Q_OBJECT
public:
	CSVDialog(QString filename = NULL,QDialog *parent = 0);
	~CSVDialog();
	int GetNumCount();
	void SetFileName(QString file);
	void SelectCSVfile(std::vector<double>&,std::vector<double>&);
private:
	void InitFrameDialog();
private:
	int count;
	QString fileName;
	CSVRead *_pReadNum;
	QLineEdit *_FireDistance_Line;
	QLineEdit* _FallingAngle_Line;
};
