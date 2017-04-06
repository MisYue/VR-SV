#pragma once

#include <QColorDialog>
#include <QToolButton>
#include "../../Public/VRSoft.h"

class CColorUI : public QToolButton, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT

public:
	CColorUI(void);
	~CColorUI(void);

public:
	virtual VR_Soft::IAttributeItemUI* Clone(void);
	// 设置信息
	virtual void SetInfor(void);
	// 保存信息
	virtual void SaveInfo(void);
	// 获得类型
	virtual VR_Soft::Contrl GetContrlType(void);
	// 获得控件
	virtual void GetContrl(void* pContrl);// {return (&m_comBox);}

protected slots:
	void Change(bool index);

private:
	osg::Vec4 m_vColor;
};

