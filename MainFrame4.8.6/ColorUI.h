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
	// ������Ϣ
	virtual void SetInfor(void);
	// ������Ϣ
	virtual void SaveInfo(void);
	// �������
	virtual VR_Soft::Contrl GetContrlType(void);
	// ��ÿؼ�
	virtual void GetContrl(void* pContrl);// {return (&m_comBox);}

protected slots:
	void Change(bool index);

private:
	osg::Vec4 m_vColor;
};

