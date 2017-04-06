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

	// ��ú�ѡ�б�
	const VR_Soft::IAttributeItem::LstCandidatas& lstCanditatas = pIItem->GetCandidatas();
	VR_Soft::IAttributeItem::LstCandidatas::const_iterator cstItor = lstCanditatas.begin();
	for (; lstCanditatas.end() != cstItor; ++cstItor)
	{
		const VR_Soft::VRString &str = cstItor->strText;
		addItem(QString::fromLocal8Bit(str.c_str()));
	}

	// ���õ�ǰѡ����
	setCurrentIndex(pIItem->SelectCandidata());
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(Change(int)));

}

// ������Ϣ
void CComboxUI::SaveInfo(void)
{

}

// �������
VR_Soft::Contrl CComboxUI::GetContrlType(void)
{
	return VR_Soft::CTRL_COMBOX;
}

// ��ÿؼ�
void CComboxUI::GetContrl(void* pContrl)
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
	pTreeWidget->setItemWidget(pTreeWidgetItem, 1, (QComboBox*)this);
}

void CComboxUI::Change(int index)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();

	pIItem->SetSelect(index);
}
