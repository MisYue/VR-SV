#include "../../Public/VRSoft.h"
#include "ComboxUI.h"

#include <QTreeWidgetItem>


CComboxUI::CComboxUI(void)
{
	//VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(this);
	
}


CComboxUI::~CComboxUI(void)
{
	//VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(this);
}


VR_Soft::IAttributeItemUI* CComboxUI::Clone(void)
{
	return (new CComboxUI());
}

void CComboxUI::SetInfor(void)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();

	if (NULL == pIItem)
	{
		return;
	}

	/*VR_Soft::VRString &str = pIItem->GetValueToString();
	addItem(QString::fromLocal8Bit(str.c_str()));
	setCurrentIndex(0);*/

	// 获得候选列表
	const std::vector<VR_Soft::VRString>& lstCanditatas = pIItem->GetCandidatas();
	 std::vector<VR_Soft::VRString>::const_iterator cstItor = lstCanditatas.begin();
	for (; lstCanditatas.end() != cstItor; ++cstItor)
	{
		const VR_Soft::VRString &str = *cstItor;
		addItem(QString::fromLocal8Bit(str.c_str()));
	}

	// 设置当前选中项
	setCurrentIndex(pIItem->SelectCandidata());
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(Change(int)));

}

// 保存信息
void CComboxUI::SaveInfo(void)
{

}

// 获得类型
VR_Soft::Contrl CComboxUI::GetContrlType(void)
{
	return VR_Soft::CTRL_COMBOX;
}

// 获得控件
void CComboxUI::GetContrl(void* pContrl)
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
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1, (QComboBox*)this);
//	pTreeWidget->setItemWidget(pTreeWidgetItem, 1, (QComboBox*)this);
}

void CComboxUI::Change(int index)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	QString strName = currentText();
	pIItem->SetValue(strName.toLocal8Bit().data());
}
