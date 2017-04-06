#include <QDateTime>
#include <QMessageBox>
#include "../../Public/VRSoft.h"
#include "TimerCtrlUI.h"


CTimerCtrlUI::CTimerCtrlUI(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);

	// �󶨸���ʱ��
	connect(&m_timer,SIGNAL(timeout()), this,  SLOT(UpdateTime()));
	m_timer.start( 1 );

	// �󶨿�ʼ
	connect(ui.pbStart, SIGNAL(clicked(bool)), this, SLOT(Start()));
	// ����ͣ
	connect(ui.pbSuspend, SIGNAL(clicked(bool)), this, SLOT(Suspend()));
	// �󶨼���
	connect(ui.pbQuicken, SIGNAL(clicked(bool)), this, SLOT(Quicken()));
	// �󶨼���
	connect(ui.pbModerate, SIGNAL(clicked(bool)), this, SLOT(Moderate()));
	// ��ֹͣ
	connect(ui.pbStop, SIGNAL(clicked(bool)), this, SLOT(Stop()));
	// ����ת
	connect(ui.pbJump, SIGNAL(clicked(bool)), this, SLOT(Jump()));
}


CTimerCtrlUI::~CTimerCtrlUI(void)
{
}

// ����ʱ��
void CTimerCtrlUI::UpdateTime(void)
{
	VR_Soft::VRString strTime = VR_Soft::IComManager::GetInstance().GetTimerManager()->GetTime()->GetSimulationString();
	ui.leSimTime->setText(strTime.c_str());

	if (ui.checkBox->isChecked())
	{
		return;
	}
	QDateTime dt = QDateTime::currentDateTime();
	ui.dtSysTime->setDateTime(dt);
}

// ��ͣ
void CTimerCtrlUI::Suspend()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Suspend();
}

// ��ʼ
void CTimerCtrlUI::Start()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Start();
}

// �󶨼���
void CTimerCtrlUI::Quicken()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Quicken();
}

void CTimerCtrlUI::Moderate()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Moderate();
}

// ��ֹͣ
void CTimerCtrlUI::Stop()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Stop();
}

// ����ת
void CTimerCtrlUI::Jump()
{
	if (!ui.checkBox->isChecked())
	{
		QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��ѡ����ת"));
		return;
	}

	QDateTime dt = ui.dtSysTime->dateTime();
	VR_Soft::ITimer* pITimer = VR_Soft::IComManager::GetInstance().GetTimerManager()->GetTime();
	pITimer->SetStartTime(dt.date().year(), dt.date().month(), dt.date().day(), \
		dt.time().hour(), dt.time().minute(), dt.time().second());
}
