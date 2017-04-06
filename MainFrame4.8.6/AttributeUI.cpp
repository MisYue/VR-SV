#include <QTreeWidget>
#include <QStringList>
#include <QLineEdit>
#include "../../Public/VRSoft.h"
#include "EidteUI.h"
#include "ComboxUI.h"
#include "DoubleSpinBox.h"
#include "TreeUI.h"
#include "StrategyUI.h"
#include "FileSelectUI.h"
#include "AttributeUI.h"
#include "ItemSelect.h"
#include "ColorUI.h"


CAttributeUI::CAttributeUI(void)
{
	SetupUI();
}


CAttributeUI::~CAttributeUI(void)
{
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pEidt);
	VRSOFT_DELETE(m_pEidt);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pCombox);
	VRSOFT_DELETE(m_pCombox);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pTreeUI);
	VRSOFT_DELETE(m_pTreeUI);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pDoubleBoxUI);
	VRSOFT_DELETE(m_pDoubleBoxUI);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pStrategyUI);
	VRSOFT_DELETE(m_pStrategyUI);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pFileSlectUI);
	VRSOFT_DELETE(m_pFileSlectUI);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pItemSelect);
	VRSOFT_DELETE(m_pItemSelect);
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(m_pColor);
	VRSOFT_DELETE(m_pColor);

	VR_Soft::IAttributeManager* pIAttributeManager = VR_Soft::IAttributeManager::GetInstancePtr();
	if (NULL != pIAttributeManager)
	{
		pIAttributeManager->Detach(this);
	}
}

void CAttributeUI::SetupUI(void)
{
	// ���ñ�ͷΪ���Ժ�ֵ
	setColumnCount(2);
	QStringList strList;
	strList<<QString::fromLocal8Bit("����")<<QString::fromLocal8Bit("����ֵ");
	setHeaderLabels(strList);

	// ע�ᵽ���Թ�����
	VR_Soft::IAttributeManager* pAttributeManager = VR_Soft::IComManager::GetInstance().GetAttributeManager();
	if (NULL == pAttributeManager)
	{
		return;
	}

	pAttributeManager->Attach(this);

	m_pEidt = new CEidteUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pEidt);
	m_pCombox = new CComboxUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pCombox);
	m_pTreeUI = new CTreeUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pTreeUI);
	m_pDoubleBoxUI = new CDoubleSpinBoxUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pDoubleBoxUI);
	m_pStrategyUI = new CStrategyUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pStrategyUI);
	m_pFileSlectUI = new CFileSelectUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pFileSlectUI);
	m_pItemSelect = new CItemSelect;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pItemSelect);
	m_pColor = new CColorUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pColor);
}

// ����������Խ���
void CAttributeUI::Clear(void) 
{
	clear();
}

// ����UI
void CAttributeUI::ChangeEntity(VR_Soft::IEntityBase* pIEntity)
{
	Clear();
	// ��ȡ���е�����
	VR_Soft::IEntityBase::ListAttributes listAttributes = pIEntity->GetAllAttribute();
	if (listAttributes.empty())
	{
		return;
	}

	// ��������
	VR_Soft::IEntityBase::ListAttributes::const_iterator cstItor = listAttributes.begin();
	for (; listAttributes.end() != cstItor; ++cstItor)
	{
		// ������ʾ����
		ShowAttribute(*cstItor);
	}
}

// �����ı�������
void CAttributeUI::UpdateEdit()
{
	//QTreeWidgetItem* pItem = currentItem();
	//QLineEdit* pWidget = (QLineEdit*)itemWidget(pItem, 1);
	//if (NULL == pWidget)
	//{
	//	return;
	//}
	//QString text = pWidget->text();
	//if (NULL == m_pIAttribute)
	//{
	//	return;
	//}

	//// �ж��Ƿ�Ϊ��������
	//const QString& str = pItem->text(0);
	//if (0 == str.compare("����"))
	//{
	//	m_pIAttribute->SetName(text.toStdString());
	//}
	//else
	//{
	//	// ��õ�ǰ��������
	//	VR_Soft::IAttributeItem* pAttrItem = m_pIAttribute->GetItem(str.toStdString());
	//	if (NULL == pAttrItem)
	//	{
	//		return;
	//	}
	////	pAttrItem->SetValue(text.toStdString());
	//}

}

void CAttributeUI::ShowAttribute(VR_Soft::IAttribute* pIAttribute)
{
	if (NULL == pIAttribute)
	{
		return;
	}

	// �����������
	const VR_Soft::VRString& strName = pIAttribute->GetName();
	// ���ü���
	QTreeWidgetItem* pTopItem = new QTreeWidgetItem(this, QStringList(QString::fromLocal8Bit(strName.c_str())));
	addTopLevelItem(pTopItem);

	// �������ֵ
	VR_Soft::IAttribute::ListAttrItems lstAttrItems = pIAttribute->GetAttrItems();
	// ��������ֵ
	for (VR_Soft::IAttribute::ListAttrItems::const_iterator cstItor = lstAttrItems.begin(); \
		lstAttrItems.end() != cstItor; ++cstItor)
	{
 		VR_Soft::IAttributeItem* pIAttributeItem = (*cstItor);
		VR_Soft::IAttributeItemUI* pIAttributeItemUI = VR_Soft::IComManager::GetInstance( \
			).GetAttributeUiFactory()->GetContrl(pIAttributeItem);
		pIAttributeItemUI->GetContrl((void*)pTopItem);
	}
}

void CAttributeUI::UpdateNewItem( VR_Soft::IAttribute* pIAttribute )
{
	ShowAttribute(pIAttribute);
}

void CAttributeUI::UpdateDelItem( VR_Soft::IAttribute* pIAttribute )
{
	if (NULL == pIAttribute)
	{
		return;
	}
	// ��õ�ǰ�������Ե�����
	const VR_Soft::VRString strName = pIAttribute->GetName();
	
	// ���������Ķ���ڵ�
	int nSize = topLevelItemCount();
	for (int index = 0; index < nSize; ++index)
	{
		QTreeWidgetItem* pTopItem = topLevelItem(index);
		if (NULL == pTopItem)
		{
			continue;
		}
		if (0 == pTopItem->text(0).compare(QString::fromLocal8Bit(strName.c_str())))
		{
			delete takeTopLevelItem(index);
		}
	}
}
