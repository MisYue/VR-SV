#pragma once
#ifdef _DEBUG
#pragma comment(lib, "QtCored4.lib")
#pragma comment(lib, "QtGuid4.lib")
#else
#pragma comment(lib, "QtCore4.lib")
#pragma comment(lib, "QtGui4.lib")
#endif

#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QColorDialog>
#include <QColor>
#include <QObject>
#include <QString>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QSpinBox>
#include <QtGui/QApplication>
#include <QtGui/QCheckBox>