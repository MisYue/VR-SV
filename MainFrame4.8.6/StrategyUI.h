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
	// ������Ϣ
	virtual void SetInfor(void);
	// ������Ϣ
	virtual void SaveInfo(void);
	// �������
	virtual VR_Soft::Contrl GetContrlType(void);
	// ��ÿؼ�
	virtual void GetContrl(void* pContrl);// {return (&m_comBox);}

	protected slots:
		void Change();
};

