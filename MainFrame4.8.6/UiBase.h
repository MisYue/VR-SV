
#include <QFrame>
#include <QVBoxLayout>
#include "TitleBar.h"

#pragma once
class CUiBase : public QFrame
{
public:
	CUiBase(void);
	~CUiBase(void);

private:
	QVBoxLayout* m_pMainLayout;
	CTitleBar* m_pTitleBar;
};

