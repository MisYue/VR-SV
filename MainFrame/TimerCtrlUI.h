#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_TimerCtrlUI.h"

class CTimerCtrlUI : public QWidget
{
	Q_OBJECT

public:
	explicit CTimerCtrlUI(QWidget *parent = 0);
	virtual ~CTimerCtrlUI(void);

protected slots:
	// 更新时间
	void UpdateTime(void);
	// 暂停
	void Suspend();
	// 开始
	void Start();
	// 加速
	void Quicken();
	// 绑定减速
	void Moderate();
	// 绑定停止
	void Stop();
	// 绑定跳转
	void Jump();
private:
	Ui::TimerCtrlUI ui;

	QTimer m_timer;
};

