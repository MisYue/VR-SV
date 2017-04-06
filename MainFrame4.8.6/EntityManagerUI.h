#pragma once

#include <QWidget>
#include "../../Public/VRSoft.h"

#include <QTimer>

class QLineEdit;
class QTreeWidget;
class QListWidgetItem;

class CEntityManagerTreeWidgt;

class CEntityManagerUI : public QWidget, public VR_Soft::IEntityManagerUI
{
	Q_OBJECT
public:
	CEntityManagerUI(QWidget* parent = NULL);
	~CEntityManagerUI(void);

public:
	// ��ý�������
	virtual const VR_Soft::VRString GetUIName(void) const;

public:
	// ��ʼ��
	virtual void Init(VR_Soft::IEntityManager* pIEntityManager) ;
	// ���һ��ʵ��
	virtual void UpdateNewItem(VR_Soft::IEntityBase* pEntity) ;
	// �Ƴ�ʵ��
	virtual void UpdateDelItem(VR_Soft::IEntityBase* pEntity) ;
	// ����ʵ������
	virtual void UpdateItem(VR_Soft::IEntityBase* pEntity, const VR_Soft::VRString& strOldName, const VR_Soft::VRString& strNemName ) ;

protected:
	virtual void InitUI(void* param = NULL, int nParam = 0);
	virtual void Update(void* param = NULL, int nParam = 0);
	void SetupUI(void);

	// �Ҽ�
	virtual void mousePressEvent(QMouseEvent *);

protected slots:
	void SelectItemp(QListWidgetItem * item);
	void UpdateTime(void);
private:
	QLineEdit* m_pLineSearch;
	CEntityManagerTreeWidgt* m_pTreeWidget;
	QTimer m_timer;
};

