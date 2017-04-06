#pragma once
 #include <QLineEdit>

#include "../../Public/VRSoft.h"

class CEidteUI : public QLineEdit, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT 

public:
	CEidteUI(void);
	virtual ~CEidteUI(void);

public:
	virtual VR_Soft::IAttributeItemUI* Clone(void);
	// 设置信息
	virtual void SetInfor(void);
	// 保存信息
	virtual void SaveInfo(void);
	// 获得类型
	virtual VR_Soft::Contrl GetContrlType(void);
	// 获得控件
	virtual void GetContrl(void* pContrl) ;

protected slots:
	void setValueToSystem(const QString& text);
};

