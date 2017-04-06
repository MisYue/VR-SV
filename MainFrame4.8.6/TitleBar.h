#include <QWidget>
#include <QPushButton>

#pragma once
class CTitleBar : public QWidget
{
public:
	CTitleBar(void);
	~CTitleBar(void);

private:
	QPushButton m_btnMin;
	QPushButton m_btnMax;
	QPushButton m_btnClose;
};

