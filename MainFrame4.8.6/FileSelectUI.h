#pragma once

#include "../../Public/VRSoft.h"

#include <QWidget>
#include <QLineEdit>
#include <QToolButton>

class CFileSelectUI : public QWidget, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT 

public:
	CFileSelectUI(void);
	virtual ~CFileSelectUI(void);

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

protected:
	void SetupUI(void);

protected slots:
	void setValueToSystem(bool b);

private:
	QLineEdit m_lineEidt;
	QToolButton m_toolButton;
};

