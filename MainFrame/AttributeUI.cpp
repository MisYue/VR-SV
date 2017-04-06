#include <QTreeWidget>
#include <QStringList>
#include <QLineEdit>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/IAttributeUI.h"
#include "../../Public/EntitySystem/IAttributeItem.h"
#include "EidteUI.h"
#include "ComboxUI.h"
#include "TreeUI.h"
#include "AttributeUI.h"


CAttributeUI::CAttributeUI(void):m_pIAttribute(NULL)
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
}

void CAttributeUI::SetupUI(void)
{
	// 设置表头为属性和值
	setColumnCount(2);
	QStringList strList;
	strList<<QString::fromLocal8Bit("属性")<<QString::fromLocal8Bit("属性值");
	setHeaderLabels(strList);

	// 注册到属性管理中
	VR_Soft::IAttributeManager* pAttributeManager = VR_Soft::IComManager::GetInstance().GetAttributeManager();
	if (NULL == pAttributeManager)
	{
		return;
	}

	pAttributeManager->RegisterUI(this);

	m_pEidt = new CEidteUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pEidt);
	m_pCombox = new CComboxUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pCombox);
	m_pTreeUI = new CTreeUI;
	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(m_pTreeUI);
}

// 更新UI
void CAttributeUI::Update(void* param, int nParam  )
{
	clear();
	m_pIAttribute = static_cast<VR_Soft::IAttribute*>(param);
	if (NULL == m_pIAttribute)
	{
		return;
	}

	// 属性名称
	QTreeWidgetItem* pTreeWidgetItem = new QTreeWidgetItem;
	pTreeWidgetItem->setText(0, "Object Name");
	addTopLevelItem(pTreeWidgetItem);
	QLineEdit* pLineEdit = new QLineEdit(m_pIAttribute->GetName().c_str());
	connect(pLineEdit, SIGNAL(returnPressed()), this, SLOT(UpdateEdit()));
	setItemWidget(pTreeWidgetItem, 1, pLineEdit);

	// 获得属性值
	VR_Soft::IAttribute::LstAttrItems lstAttrItems = m_pIAttribute->GetAttrItems();
	// 遍历属性值
	for (VR_Soft::IAttribute::LstAttrItems::const_iterator cstItor = lstAttrItems.begin(); \
		lstAttrItems.end() != cstItor; ++cstItor)
	{
// 		// 判断控件类型
 /*		VR_Soft::Contrl contrl = (*cstItor)->GetCtrlType();
		if (VR_Soft::CTRL_TREE == contrl)
		{
			continue;
		}*/
// 		
// 		QTreeWidgetItem* pTreeWidgetItem = new QTreeWidgetItem;
// 		pTreeWidgetItem->setText(0, (*cstItor)->GetTypeName().c_str());
// 		addTopLevelItem(pTreeWidgetItem);
 		VR_Soft::IAttributeItem* pIAttributeItem = (*cstItor);
		VR_Soft::IAttributeItemUI* pIAttributeItemUI = VR_Soft::IComManager::GetInstance( \
			).GetAttributeUiFactory()->GetContrl(pIAttributeItem);
		pIAttributeItemUI->GetContrl((void*)this);

//		setItemWidget(pTreeWidgetItem, 1, (QWidget*)pLineEdit->GetContrl());

			/*QLineEdit* pLineEdit = new QLineEdit((*cstItor)->GetValueToString().c_str());
 			connect(pLineEdit, SIGNAL(returnPressed()), this, SLOT(UpdateEdit()));
 			setItemWidget(pTreeWidgetItem, 1, pLineEdit);*/
	}
}

// 更新文本框数据
void CAttributeUI::UpdateEdit()
{
	QTreeWidgetItem* pItem = currentItem();
	QLineEdit* pWidget = (QLineEdit*)itemWidget(pItem, 1);
	if (NULL == pWidget)
	{
		return;
	}
	QString text = pWidget->text();
	if (NULL == m_pIAttribute)
	{
		return;
	}

	// 判断是否为对象名称
	const QString& str = pItem->text(0);
	if (0 == str.compare("Object Name"))
	{
		m_pIAttribute->SetName(text.toStdString());
	}
	else
	{
		// 获得当前的属性项
		VR_Soft::IAttributeItem* pAttrItem = m_pIAttribute->GetItem(str.toStdString());
		if (NULL == pAttrItem)
		{
			return;
		}
	//	pAttrItem->SetValue(text.toStdString());
	}

}
