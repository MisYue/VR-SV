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
	// ����ʱ��
	void UpdateTime(void);
	// ��ͣ
	void Suspend();
	// ��ʼ
	void Start();
	// ����
	void Quicken();
	// �󶨼���
	void Moderate();
	// ��ֹͣ
	void Stop();
	// ����ת
	void Jump();
private:
	Ui::TimerCtrlUI ui;

	QTimer m_timer;
};

