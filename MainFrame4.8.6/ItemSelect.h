#pragma once

#include <QComboBox>
#include "../../Public/VRSoft.h"

class CItemSelect : public QComboBox, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT
public:
	CItemSelect(void);
	~CItemSelect(void);

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
		void Change(int index);
};

