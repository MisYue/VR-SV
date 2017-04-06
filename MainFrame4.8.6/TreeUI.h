#pragma once

#include <vector>
#include <QObject>
#include <QTreeWidget>

#include "../../Public/VRSoft.h"

class QDoubleSpinBox;

class CTreeUI : public QObject, public QTreeWidgetItem, public VR_Soft::CAttributeItemUIImp<VR_Soft::IAttributeItemUI>
{
	Q_OBJECT

public:
	explicit CTreeUI(void);
	virtual ~CTreeUI(void);

public:
	virtual VR_Soft::IAttributeItemUI* Clone(void);
	// 设置信息
	virtual void SetInfor(void);
	// 保存信息
	virtual void SaveInfo(void);
	// 获得类型
	virtual VR_Soft::Contrl GetContrlType(void);
	// 获得控件
	virtual void GetContrl(void* pContrl);// {return (&m_treeWidget);}

protected slots:
	void setValueToSystem(double d);

protected:
	typedef std::vector<QDoubleSpinBox*>  LsgDoubleSpinBox;

private:
	QString m_title;
	LsgDoubleSpinBox m_lstDoubleSpinBox;
};

