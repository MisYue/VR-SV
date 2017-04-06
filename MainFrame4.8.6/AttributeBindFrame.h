#pragma once


#include <QDialog>


#include "../../Public/VRSoft.h"

#include "ui_AttributeBindFrame.h"

class CAttributeBindFrame : public QDialog
{
	Q_OBJECT 

public:
	CAttributeBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent = NULL);
	~CAttributeBindFrame(void);

protected:
	// 设置初始化内容
	void InitAttribute( void );

protected slots:
	bool BindAttribute();
	bool UnBindAttribute();

private:
	Ui::AttributedBindFrame ui;
	VR_Soft::IEntityBase* m_pIEntity;
};

