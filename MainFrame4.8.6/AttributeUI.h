#pragma once

#include <QTreeWidget>
#include "../../Public/VRSoft.h"

class CEidteUI;
class CComboxUI;
class CTreeUI;
class CDoubleSpinBoxUI;
class CStrategyUI;
class CFileSelectUI;
class CItemSelect;
class CColorUI;

class CAttributeUI : public QTreeWidget, public VR_Soft::IAttributeUI
{
	Q_OBJECT

public:
	CAttributeUI(void);
	~CAttributeUI(void);

public:
	// ����������Խ���
	virtual void Clear(void) ;
	// ����UI
	virtual void ChangeEntity(VR_Soft::IEntityBase* pIEntity);
	// ���һ��ʵ��
	virtual void UpdateNewItem(VR_Soft::IAttribute* pIAttribute);
	// �Ƴ�ʵ��
	virtual void UpdateDelItem(VR_Soft::IAttribute* pIAttribute);

protected:
	// ��ʼ��
	void SetupUI(void);

public slots:
	// �����ı�������
	void UpdateEdit();
	// ������ʾ����
	void ShowAttribute(VR_Soft::IAttribute* pIAttribute);
private:
	//VR_Soft::IAttribute* m_pIAttribute;

	CEidteUI* m_pEidt;
	CComboxUI* m_pCombox;
	CTreeUI* m_pTreeUI;
	CDoubleSpinBoxUI* m_pDoubleBoxUI;
	CStrategyUI* m_pStrategyUI;
	CFileSelectUI* m_pFileSlectUI;
	CItemSelect* m_pItemSelect;
	CColorUI* m_pColor;

};

