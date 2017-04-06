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
	// 清空所有属性界面
	virtual void Clear(void) ;
	// 更新UI
	virtual void ChangeEntity(VR_Soft::IEntityBase* pIEntity);
	// 添加一个实体
	virtual void UpdateNewItem(VR_Soft::IAttribute* pIAttribute);
	// 移除实体
	virtual void UpdateDelItem(VR_Soft::IAttribute* pIAttribute);

protected:
	// 初始化
	void SetupUI(void);

public slots:
	// 更新文本框数据
	void UpdateEdit();
	// 设置显示属性
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

