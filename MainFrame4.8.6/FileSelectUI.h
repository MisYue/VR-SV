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
	// ������Ϣ
	virtual void SetInfor(void);
	// ������Ϣ
	virtual void SaveInfo(void);
	// �������
	virtual VR_Soft::Contrl GetContrlType(void);
	// ��ÿؼ�
	virtual void GetContrl(void* pContrl) ;

protected:
	void SetupUI(void);

protected slots:
	void setValueToSystem(bool b);

private:
	QLineEdit m_lineEidt;
	QToolButton m_toolButton;
};

