#pragma once

#include <QPushButton>
#include "../../Public/VRSoft.h"

class CStrategyUI : public QPushButton, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT


public:
	CStrategyUI(void);
	~CStrategyUI(void);

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
		void Change();
};

