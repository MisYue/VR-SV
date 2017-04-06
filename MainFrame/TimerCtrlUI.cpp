#include <QDateTime>
#include <QMessageBox>
#include "../../Public/VRSoft.h"
#include "TimerCtrlUI.h"


CTimerCtrlUI::CTimerCtrlUI(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);

	// 绑定更新时间
	connect(&m_timer,SIGNAL(timeout()), this,  SLOT(UpdateTime()));
	m_timer.start( 1 );

	// 绑定开始
	connect(ui.pbStart, SIGNAL(clicked(bool)), this, SLOT(Start()));
	// 绑定暂停
	connect(ui.pbSuspend, SIGNAL(clicked(bool)), this, SLOT(Suspend()));
	// 绑定加速
	connect(ui.pbQuicken, SIGNAL(clicked(bool)), this, SLOT(Quicken()));
	// 绑定减速
	connect(ui.pbModerate, SIGNAL(clicked(bool)), this, SLOT(Moderate()));
	// 绑定停止
	connect(ui.pbStop, SIGNAL(clicked(bool)), this, SLOT(Stop()));
	// 绑定跳转
	connect(ui.pbJump, SIGNAL(clicked(bool)), this, SLOT(Jump()));
}


CTimerCtrlUI::~CTimerCtrlUI(void)
{
}

// 更新时间
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

// 暂停
void CTimerCtrlUI::Suspend()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Suspend();
}

// 开始
void CTimerCtrlUI::Start()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Start();
}

// 绑定加速
void CTimerCtrlUI::Quicken()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Quicken();
}

void CTimerCtrlUI::Moderate()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Moderate();
}

// 绑定停止
void CTimerCtrlUI::Stop()
{
	VR_Soft::IComManager::GetInstance().GetTimerManager()->Stop();
}

// 绑定跳转
void CTimerCtrlUI::Jump()
{
	if (!ui.checkBox->isChecked())
	{
		QMessageBox::about(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请选择跳转"));
		return;
	}

	QDateTime dt = ui.dtSysTime->dateTime();
	VR_Soft::ITimer* pITimer = VR_Soft::IComManager::GetInstance().GetTimerManager()->GetTime();
	pITimer->SetStartTime(dt.date().year(), dt.date().month(), dt.date().day(), \
		dt.time().hour(), dt.time().minute(), dt.time().second());
}
