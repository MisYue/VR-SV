#include "../../Public/VRSoft.h"
#include "EidteUI.h"

#include <QTreeWidgetItem>


CEidteUI::CEidteUI(void)
{
	connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(setValueToSystem(const QString&)));
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

	VR_Soft::VRString strText = pIItem->GetValueToString();
	setText(QString::fromLocal8Bit(strText.c_str()));
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
	QString qstrName = QString::fromLocal8Bit(pIItem->GetTypeName().c_str());
	pSubTreeWidgetItem->setText(0, qstrName);
	setText(QString::fromLocal8Bit(pIItem->GetValueToString().c_str()));
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1,  (QLineEdit*)this);
}

void CEidteUI::setValueToSystem(const QString& text)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	VR_Soft::VRString strName = text.toLocal8Bit().data();
	pIItem->SetValue(strName);
}