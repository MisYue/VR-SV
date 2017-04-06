/********************************************************************************
** Form generated from reading UI file 'TimerCtrlUI.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERCTRLUI_H
#define UI_TIMERCTRLUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimerCtrlUI
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *leSimTime;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QDateTimeEdit *dtSysTime;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pbStart;
    QPushButton *pbSuspend;
    QPushButton *pbQuicken;
    QPushButton *pbModerate;
    QPushButton *pbStop;
    QPushButton *pbJump;

    void setupUi(QWidget *TimerCtrlUI)
    {
        if (TimerCtrlUI->objectName().isEmpty())
            TimerCtrlUI->setObjectName(QStringLiteral("TimerCtrlUI"));
        TimerCtrlUI->resize(520, 165);
        gridLayout = new QGridLayout(TimerCtrlUI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(TimerCtrlUI);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        leSimTime = new QLineEdit(groupBox_2);
        leSimTime->setObjectName(QStringLiteral("leSimTime"));

        horizontalLayout_2->addWidget(leSimTime);

        horizontalSpacer = new QSpacerItem(38, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        dtSysTime = new QDateTimeEdit(groupBox_2);
        dtSysTime->setObjectName(QStringLiteral("dtSysTime"));

        gridLayout_4->addWidget(dtSysTime, 0, 1, 1, 1);

        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_4->addWidget(checkBox, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(164, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(TimerCtrlUI);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pbStart = new QPushButton(groupBox);
        pbStart->setObjectName(QStringLiteral("pbStart"));

        horizontalLayout->addWidget(pbStart);

        pbSuspend = new QPushButton(groupBox);
        pbSuspend->setObjectName(QStringLiteral("pbSuspend"));

        horizontalLayout->addWidget(pbSuspend);

        pbQuicken = new QPushButton(groupBox);
        pbQuicken->setObjectName(QStringLiteral("pbQuicken"));

        horizontalLayout->addWidget(pbQuicken);

        pbModerate = new QPushButton(groupBox);
        pbModerate->setObjectName(QStringLiteral("pbModerate"));

        horizontalLayout->addWidget(pbModerate);

        pbStop = new QPushButton(groupBox);
        pbStop->setObjectName(QStringLiteral("pbStop"));

        horizontalLayout->addWidget(pbStop);

        pbJump = new QPushButton(groupBox);
        pbJump->setObjectName(QStringLiteral("pbJump"));

        horizontalLayout->addWidget(pbJump);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);


        retranslateUi(TimerCtrlUI);

        QMetaObject::connectSlotsByName(TimerCtrlUI);
    } // setupUi

    void retranslateUi(QWidget *TimerCtrlUI)
    {
        TimerCtrlUI->setWindowTitle(QApplication::translate("TimerCtrlUI", "Form", 0));
        groupBox_2->setTitle(QApplication::translate("TimerCtrlUI", "\346\230\276\347\244\272", 0));
        label->setText(QApplication::translate("TimerCtrlUI", "\344\273\277\347\234\237\346\227\266\351\227\264", 0));
        label_2->setText(QApplication::translate("TimerCtrlUI", "\347\263\273\347\273\237\346\227\266\351\227\264", 0));
        dtSysTime->setDisplayFormat(QApplication::translate("TimerCtrlUI", "yyyy/MM/dd hh:mm.ss", 0));
        checkBox->setText(QApplication::translate("TimerCtrlUI", "\350\267\263\350\275\254", 0));
        groupBox->setTitle(QApplication::translate("TimerCtrlUI", "\346\216\247\345\210\266", 0));
        pbStart->setText(QApplication::translate("TimerCtrlUI", "\345\274\200\345\247\213", 0));
        pbSuspend->setText(QApplication::translate("TimerCtrlUI", "\346\232\202\345\201\234", 0));
        pbQuicken->setText(QApplication::translate("TimerCtrlUI", "\345\212\240\351\200\237", 0));
        pbModerate->setText(QApplication::translate("TimerCtrlUI", "\345\207\217\351\200\237", 0));
        pbStop->setText(QApplication::translate("TimerCtrlUI", "\345\201\234\346\255\242", 0));
        pbJump->setText(QApplication::translate("TimerCtrlUI", "\350\267\263\350\275\254", 0));
    } // retranslateUi

};

namespace Ui {
    class TimerCtrlUI: public Ui_TimerCtrlUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERCTRLUI_H
