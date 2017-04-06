#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "ItemSelect.h"

#include <QTreeWidgetItem>


CItemSelect::CItemSelect(void)
{
}


CItemSelect::~CItemSelect(void)
{
}


VR_Soft::IAttributeItemUI* CItemSelect::Clone(void)
{
	return (new CItemSelect());
}

void CItemSelect::SetInfor(void)
{
	VR_Soft::IRenderManager* pIRenderManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IRenderManager>(VR_Soft::INSTANCE_NAME_RENDERSYSTEM);
	if (NULL == pIRenderManager)
	{
		return;
	}

	VR_Soft::IMeshManager*pIMeshManager = pIRenderManager->GetMeshManager();
	const VR_Soft::IMeshManager::ListMeshObjs& listMeshObjs = pIMeshManager->GetAllMeshObj();
	VR_Soft::IMeshManager::ListMeshObjs::const_iterator cstItor = listMeshObjs.begin();
	for (; listMeshObjs.end() != cstItor; ++cstItor)
	{
		const VR_Soft::VRString &str = cstItor->m_strName;
		addItem(QString::fromLocal8Bit(str.c_str()));
	}


	// 设置当前选中项
	setCurrentIndex(0);
	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(Change(int)));

}

// 保存信息
void CItemSelect::SaveInfo(void)
{

}

// 获得类型
VR_Soft::Contrl CItemSelect::GetContrlType(void)
{
	return VR_Soft::CTRL_ITEM_SELECT;
}

// 获得控件
void CItemSelect::GetContrl(void* pContrl)
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

void CItemSelect::Change(int index)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();

	VR_Soft::VRString strName = this->itemText(index).toLocal8Bit().data();

	pIItem->SetValue(strName);
}

