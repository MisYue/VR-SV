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
	// 获得界面名称
	virtual const VR_Soft::VRString GetUIName(void) const;

public:
	// 初始化
	virtual void Init(VR_Soft::IEntityManager* pIEntityManager) ;
	// 添加一个实体
	virtual void UpdateNewItem(VR_Soft::IEntityBase* pEntity) ;
	// 移除实体
	virtual void UpdateDelItem(VR_Soft::IEntityBase* pEntity) ;
	// 更改实体名称
	virtual void UpdateItem(VR_Soft::IEntityBase* pEntity, const VR_Soft::VRString& strOldName, const VR_Soft::VRString& strNemName ) ;

protected:
	virtual void InitUI(void* param = NULL, int nParam = 0);
	virtual void Update(void* param = NULL, int nParam = 0);
	void SetupUI(void);

	// 右键
	virtual void mousePressEvent(QMouseEvent *);

protected slots:
	void SelectItemp(QListWidgetItem * item);
	void UpdateTime(void);
private:
	QLineEdit* m_pLineSearch;
	CEntityManagerTreeWidgt* m_pTreeWidget;
	QTimer m_timer;
};

