#pragma once

#include <QDialog>

namespace VR_Soft
{
	class IEntityBase;
}

class QListWidgetItem;

class CStrategyManagerUI : public QDialog
{
	Q_OBJECT

public:
	CStrategyManagerUI(VR_Soft::IEntityBase* pIEntity, QWidget *parent = 0, Qt::WindowFlags f = 0);
	~CStrategyManagerUI(void);

protected:
	void InitUI(VR_Soft::IEntityBase* pIEntity);

protected slots:
	void ItemSelect( QListWidgetItem * item);

private:
	VR_Soft::IEntityBase* m_pIEntity;
};

