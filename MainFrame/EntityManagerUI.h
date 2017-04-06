#pragma once

#include <QWidget>
#include "../../Public/VRSoft.h"

#include <QTimer>

class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;

class CEntityManagerTreeWidgt;

class CEntityManagerUI : public QWidget, public VR_Soft::IPluginUI
{
	Q_OBJECT
public:
	CEntityManagerUI(QWidget* parent = NULL);
	~CEntityManagerUI(void);

public:
	// ��ý�������
	virtual const VR_Soft::VRString GetUIName(void) const;

protected:
	virtual void InitUI(void* param = NULL, int nParam = 0);
	virtual void Update(void* param = NULL, int nParam = 0);
	void SetupUI(void);

	// �Ҽ�
	virtual void mousePressEvent(QMouseEvent *);

protected slots:
	void SelectItemp(QTreeWidgetItem * item, int column);
	void UpdateTime(void);
private:
	QLineEdit* m_pLineSearch;
	CEntityManagerTreeWidgt* m_pTreeWidget;
	QTimer m_timer;
};

