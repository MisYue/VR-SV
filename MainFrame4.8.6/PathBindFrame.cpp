#include "PathBindFrame.h"
#include <QGridLayout>
#include <QHBoxLayout>

#include "../../Public/AirLineSystem/AirLineSystem.h"

CPathBindFrame::CPathBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent )
	:m_pIEntityBase(pIEntityBase),QDialog(parent)
{
	setAttribute(Qt::WA_ShowModal, true);
	QGridLayout* pGridLayout = new QGridLayout(this);
	pGridLayout->setMargin(0);

	m_pListWidget = new QListWidget;
	pGridLayout->addWidget(m_pListWidget);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout();
	pGridLayout->addLayout(pHBoxLayout,1, 0);
	pHBoxLayout->addSpacerItem(new QSpacerItem(40, 20));
	m_pPbtCancel = new QPushButton(QString::fromLocal8Bit("取消"));
	pHBoxLayout->addWidget(m_pPbtCancel);
	pHBoxLayout->addWidget(m_pPbtOK = new QPushButton(QString::fromLocal8Bit("确定")));

	connect(m_pPbtOK, SIGNAL(pressed ()), this, SLOT(BtnOK()));
	connect(m_pPbtCancel, SIGNAL(pressed ()), this, SLOT(BtnCancel()));

	InitData();
}


CPathBindFrame::~CPathBindFrame(void)
{

}

void CPathBindFrame::BtnCancel(void)
{
	QDialog::close();
}

// 获得界面名称
const VR_Soft::VRString CPathBindFrame::GetUIName( void ) const
{
	return ("PathBind");
}


void CPathBindFrame::BtnOK( void )
{
	if (NULL == m_pIEntityBase || m_pListWidget->selectedItems().empty())
	{
		return;
	}

	QListWidgetItem* pListWidgetItem = m_pListWidget->currentItem();
	if (NULL == pListWidgetItem)
	{
		return;
	}

	QVariant var = pListWidgetItem->data(1);
	
	VR_Soft::IPath* pIPath = (VR_Soft::IPath*)var.value<void*>();
	
	// 获得运动属性
	VR_Soft::IEntityMoveAttribute* pIMoveAttribute = dynamic_cast<VR_Soft::IEntityMoveAttribute*>(m_pIEntityBase->GetAttribute("运动属性"));
	if (NULL == pIMoveAttribute)
	{
		return;
	}

	pIMoveAttribute->SetMovePath(pIPath);
	
	QDialog::accept();
}

// 初始化数据
void CPathBindFrame::InitData( void )
{
	typedef std::vector<VR_Soft::IPath*> ListPaths;
	ListPaths listPaths = VR_Soft::IPathManager::GetInstance().GetAllPath();
	ListPaths::const_iterator cstItor = listPaths.begin();
	for (; listPaths.end() != cstItor; ++cstItor)
	{
		const VR_Soft::IPath* pIPath = *cstItor;
		const VR_Soft::VRString& strName = pIPath->GetName();
		QListWidgetItem* pListWidgetItem = new QListWidgetItem(QString::fromLocal8Bit(strName.c_str()));
		pListWidgetItem->setData(1 , QVariant::fromValue((void *) pIPath));
		m_pListWidget->addItem(pListWidgetItem);
	}
}
