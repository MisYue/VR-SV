#include "../../Public/VRSoft.h"
#include "StrategyUI.h"

#include "StrategyManagerUI.h"
#include <QTreeWidgetItem>

CStrategyUI::CStrategyUI(void)
{
	connect(this, SIGNAL(pressed()), this, SLOT(Change()));
	setText(QString::fromLocal8Bit("��ѡ��"));
}


CStrategyUI::~CStrategyUI(void)
{
}


VR_Soft::IAttributeItemUI* CStrategyUI::Clone(void)
{
	return (new CStrategyUI());
}

void CStrategyUI::SetInfor(void)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();

	if (NULL == pIItem)
	{
		return;
	}

	/*VR_Soft::VRString &str = pIItem->GetValueToString();
	addItem(QString::fromLocal8Bit(str.c_str()));
	setCurrentIndex(0);*/

}

// ������Ϣ
void CStrategyUI::SaveInfo(void)
{

}

// �������
VR_Soft::Contrl CStrategyUI::GetContrlType(void)
{
	return VR_Soft::CTRL_TRATEGY;
}

// ��ÿؼ�
void CStrategyUI::GetContrl(void* pContrl)
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
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1, (QPushButton*)this);
}

void CStrategyUI::Change()
{
	// ��õ�ǰ�����ģ��
	//VR_Soft::IComManager::GetInstance().GetAttributeManager()->SetCurrentEntityBase()
	VR_Soft::CAttributeItemImp<VR_Soft::IAttributeItem>* pItem = dynamic_cast<VR_Soft::CAttributeItemImp<VR_Soft::IAttributeItem>*>(GetAttributeItem());
	VR_Soft::IEntityBase* pEntity = pItem->GetAttribute()->GetEntity();
	CStrategyManagerUI StrategyManagerUI(pEntity);;
	StrategyManagerUI.exec();
}
