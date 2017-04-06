#include "FileSelectUI.h"
#include <QHBoxLayout>
#include <QTreeWidgetItem>
#include <QFileDialog>

#include "../../Public/RenderSystem/RenderSystem.h"

CFileSelectUI::CFileSelectUI(void)
{
	connect(&m_toolButton, SIGNAL(clicked(bool)), this, SLOT(setValueToSystem(bool)));

	SetupUI();
}


CFileSelectUI::~CFileSelectUI(void)
{
}


void CFileSelectUI::SetupUI(void)
{
	QHBoxLayout* pHBoxLayout = new QHBoxLayout(this);
	pHBoxLayout->addWidget(&m_lineEidt);
	pHBoxLayout->addWidget(&m_toolButton);
}

void CFileSelectUI::setValueToSystem(bool b)
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
		"./",
		tr("Modle (*.osg *.ive *.flt);All(*.*)"));
	if (fileName.isEmpty())
	{
		return;
	}

	QDir::setCurrent(fileName);
	m_lineEidt.setText(fileName);


	VR_Soft::VRString strName = fileName.toLocal8Bit().data();
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	pIItem->SetValue(strName);
}

VR_Soft::IAttributeItemUI* CFileSelectUI::Clone(void)
{
	return (new CFileSelectUI());
}

void CFileSelectUI::SetInfor(void)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	if (NULL == pIItem)
	{
		return;
	}

	VR_Soft::VRString strText = pIItem->GetValueToString();
	m_lineEidt.setText(QString::fromLocal8Bit(strText.c_str()));
}

void CFileSelectUI::SaveInfo(void)
{

}

VR_Soft::Contrl CFileSelectUI::GetContrlType(void)
{
	return  VR_Soft::CTRL_FILE_SELECT;
}

void CFileSelectUI::GetContrl(void* pContrl)
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
	m_lineEidt.setText(QString::fromLocal8Bit(pIItem->GetValueToString().c_str()));
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1,  (QWidget*)this);
}
