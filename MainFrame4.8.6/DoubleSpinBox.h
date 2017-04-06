#pragma once
#include <QDoubleSpinBox>

#include "../../Public/VRSoft.h"

class CDoubleSpinBoxUI : public QDoubleSpinBox, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT 

public:
	CDoubleSpinBoxUI(void);
	~CDoubleSpinBoxUI(void);

public:
	virtual VR_Soft::IAttributeItemUI* Clone(void);
	// ������Ϣ
	virtual void SetInfor(void);
	// ������Ϣ
	virtual void SaveInfo(void);
	// �������
	virtual VR_Soft::Contrl GetContrlType(void);
	// ��ÿؼ�
	virtual void GetContrl(void* pContrl) ;

	protected slots:
		void setValueToSystem(double d);
};

