#include "../../Public/VRSoft.h"
#include "EidteUI.h"

#include <QTreeWidgetItem>


CEidteUI::CEidteUI(void)
{
	setMaximum(INT_MAX);

	connect(this, SIGNAL(valueChanged(double)), this, SLOT(setValueToSystem(double)));
}


CEidteUI::~CEidteUI(void)
{
}

VR_Soft::IAttributeItemUI* CEidteUI::Clone(void)
{
	return (new CEidteUI());
}

void CEidteUI::SetInfor(void)
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
void CEidteUI::SaveInfo(void)
{

}

// 获得类型
VR_Soft::Contrl CEidteUI::GetContrlType(void)
{
	return VR_Soft::CTRL_EDIT;
}

// 获得控件
void CEidteUI::GetContrl(void* pContrl) 
{
	QTreeWidget* pTreeWidget = static_cast<QTreeWidget*>(pContrl);
	if (NULL == pTreeWidget)
	{
		return;
	}

	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	if (NULL == pIItem)
	{
		return;
	}

	QTreeWidgetItem* pTreeWidgetItem = new QTreeWidgetItem;
	pTreeWidgetItem->setText(0, pIItem->GetTypeName().c_str());
	pTreeWidget->addTopLevelItem(pTreeWidgetItem);
	pTreeWidget->setItemWidget(pTreeWidgetItem, 1, (QDoubleSpinBox*)this);
}

void CEidteUI::setValueToSystem(double d)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	pIItem->SetValue((float)d);
}