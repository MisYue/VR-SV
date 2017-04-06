#pragma once

#include <QTreeWidget>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/EntitySystem.h"

class CEidteUI;
class CComboxUI;
class CTreeUI;

class CAttributeUI : public QTreeWidget, public VR_Soft::IAttributeUI
{
	Q_OBJECT

public:
	CAttributeUI(void);
	~CAttributeUI(void);

public:
	// ����UI
	virtual void Update(void* param = NULL, int nParam = 0 );

protected:
	// ��ʼ��
	void SetupUI(void);

public slots:
	// �����ı�������
	void UpdateEdit();

private:
	VR_Soft::IAttribute* m_pIAttribute;

	CEidteUI* m_pEidt;
	CComboxUI* m_pCombox;
	CTreeUI* m_pTreeUI;

};

