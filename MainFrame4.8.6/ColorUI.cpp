#include "ColorUI.h"
#include <QTreeWidgetItem>


CColorUI::CColorUI(void)
{
}


CColorUI::~CColorUI(void)
{
}

VR_Soft::IAttributeItemUI* CColorUI::Clone( void )
{
	return (new CColorUI());
}

void CColorUI::SetInfor( void )
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
	m_vColor = pIItem->GetValueToVec4();
	setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(m_vColor.x() * 256).arg(m_vColor.y() * 256).arg(m_vColor.z() * 256));
	// 设置当前选中项
	connect(this, SIGNAL(clicked(bool)), this, SLOT(Change(bool)));

}

void CColorUI::Change( bool index )
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();

	if (NULL == pIItem)
	{
		return;
	}

	QColor color(m_vColor.x() * 256, m_vColor.x() * 256, m_vColor.x() * 256);
	color = QColorDialog::getColor(color);
	 
	m_vColor = osg::Vec4(color.red() / 256.0, color.green() / 256.0, color.blue() / 256.0, 1.0);
	setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(m_vColor.x() * 256).arg(m_vColor.y() * 256).arg(m_vColor.z() * 256));
	pIItem->SetValue(m_vColor);
}

void CColorUI::SaveInfo( void )
{

}

VR_Soft::Contrl CColorUI::GetContrlType( void )
{
	return  VR_Soft::CTRL_COLOR;
}

void CColorUI::GetContrl( void* pContrl )
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
	pTreeWidgetItem->treeWidget()->setItemWidget(pSubTreeWidgetItem, 1, (QToolButton*)this);
}
