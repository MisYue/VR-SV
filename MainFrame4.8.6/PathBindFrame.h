#pragma once

#include <QDialog>
#include <QListWidget>
#include <QPushButton>

#include "../../Public/VRSoft.h"

class CPathBindFrame  : public QDialog
{
	Q_OBJECT

public:
	CPathBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent = NULL);
	~CPathBindFrame(void);

public:
	// 获得界面名称
	virtual const VR_Soft::VRString GetUIName(void) const;

protected slots:
	void BtnOK(void);
	void BtnCancel(void);

public:
	// 初始化数据
	void InitData(void);

private:
	QListWidget* m_pListWidget;
	QPushButton *m_pPbtOK;
	QPushButton *m_pPbtCancel;
	VR_Soft::IEntityBase* m_pIEntityBase;
};

