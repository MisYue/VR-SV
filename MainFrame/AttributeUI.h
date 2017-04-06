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
	// 更新UI
	virtual void Update(void* param = NULL, int nParam = 0 );

protected:
	// 初始化
	void SetupUI(void);

public slots:
	// 更新文本框数据
	void UpdateEdit();

private:
	VR_Soft::IAttribute* m_pIAttribute;

	CEidteUI* m_pEidt;
	CComboxUI* m_pCombox;
	CTreeUI* m_pTreeUI;

};

