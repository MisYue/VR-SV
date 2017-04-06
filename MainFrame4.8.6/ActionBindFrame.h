#pragma once

#include <QDialog>


#include "../../Public/VRSoft.h"

#include "ui_ActionBindFrame.h"

class CActionBindFrame  : public QDialog
{
	Q_OBJECT
public:
	CActionBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent = NULL);
	~CActionBindFrame(void);

protected:
	// 设置初始化内容
	void InitAction( void );

protected slots:
	bool BindAction();
	bool UnBindAction();
	bool ActionDTSeting(QListWidgetItem * item);
	bool DataTimeChanged( const QDateTime& dt );
private:
	Ui::ActionBindFrame ui;
	VR_Soft::IEntityBase* m_pIEntity;
};

