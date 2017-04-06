#include "../../Public/VRSoft.h"
#include "DoubleSpinBox.h"


#include <QTreeWidgetItem>


CDoubleSpinBoxUI::CDoubleSpinBoxUI(void)
{
	setMaximum(INT_MAX);
	setDecimals(6);

	connect(this, SIGNAL(valueChanged(double)), this, SLOT(setValueToSystem(double)));
}


CDoubleSpinBoxUI::~CDoubleSpinBoxUI(void)
{
}

VR_Soft::IAttributeItemUI* CDoubleSpinBoxUI::Clone(void)
{
	return (new CDoubleSpinBoxUI());
}

void CDoubleSpinBoxUI::SetInfor(void)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	if (NULL == pIItem)
	{
		return;
	}

	float d = pIItem->GetValueToFloat();
	setValue(d);
}

// 保存信息
void CDoubleSpinBoxUI::SaveInfo(void)
{

}

// 获得类型
VR_Soft::Contrl CDoubleSpinBoxUI::GetContrlType(void)
{
	return VR_Soft::CTRL_SPINBOX;
}

// 获得控件
void CDoubleSpinBoxUI::GetContrl(void* pContrl) 
{
	QTreeWidgetItem* pTreeWidgetItem = static_cast<QTreeWidgetItem*>(pContrl);
	if (NULL == pTreeWidgetItem)
	{
		return;
	}

	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	if (NULL == pIItem)
	{
		return;
	}

	QTreeWidgetItem* pSubTreeWidgetItem = new QTreeWidgetItem(pTreeWidgetItem);

	QString qstrName = QString("%1(%2)").arg(QString::fromLocal8Bit(pIItem->GetTypeName().c_str())).arg(QString::fromLocal8Bit(pIItem->GetUntil().c_str()));
	pSubTreeWidgetItem->setText(0, qstrName);
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1, (QDoubleSpinBox*)this);
	//pTreeWidgetItem->setText(0, pIItem->GetTypeName().c_str());
	//
}

void CDoubleSpinBoxUI::setValueToSystem(double d)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	pIItem->SetValue((float)d);
}
