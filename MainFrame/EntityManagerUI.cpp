#include <list>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTreeWidget>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/EntitySystem.h"
#include "EntityManagerTreeWidgt.h"
#include "EntityManagerUI.h"


CEntityManagerUI::CEntityManagerUI(QWidget* parent):QWidget(parent),
	m_pLineSearch(NULL), m_pTreeWidget(NULL)
{
	SetupUI();

	VR_Soft::IEntityManager* pIEntityMananger = dynamic_cast<VR_Soft::IEntityManager*>(\
		VR_Soft::IComInstanceMerator::GetInstance().GetComInstance(VR_Soft::INSTANCE_NAME_ENTITYSYSTEM));
	if (NULL == pIEntityMananger)
	{
		return;
	}

	pIEntityMananger->RegisterUI(VR_Soft::IEntityManager::EMT_ADDED, this);

	connect(m_pTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), \
		this, SLOT(SelectItemp(QTreeWidgetItem* , int )));
	connect( &m_timer, SIGNAL(timeout()), this, SLOT(UpdateTime()) );
	//m_timer.start( 1 );

}

CEntityManagerUI::~CEntityManagerUI(void)
{
}

// 获得界面名称
const VR_Soft::VRString CEntityManagerUI::GetUIName(void) const
{
	return ("entityUI");
}


void CEntityManagerUI::SetupUI(void)
{
	// 创建布局器
	QVBoxLayout* pVBoxLayout = new QVBoxLayout;
	setLayout(pVBoxLayout);

	// 创建文本框
	m_pLineSearch = new QLineEdit;
	pVBoxLayout->addWidget(m_pLineSearch);

	// 创建树形列表
	m_pTreeWidget = new CEntityManagerTreeWidgt;
	pVBoxLayout->addWidget(m_pTreeWidget);
	m_pTreeWidget->setDragEnabled(true);
	m_pTreeWidget->setDragDropMode(QAbstractItemView::InternalMove);	
}


void CEntityManagerUI::InitUI(void* param , int nParam)
{
	VR_Soft::IEntityComposite* pIEntityComposite = static_cast<VR_Soft::IEntityComposite*>(param);
	if (NULL == pIEntityComposite)
	{
		return;
	}

	// 获取所有组件
	VR_Soft::IEntityComposite::LstEntitys lstEntity = pIEntityComposite->GetLstEntitys();
	if (lstEntity.empty())
	{
		return;
	}

	for (VR_Soft::IEntityComposite::LstEntitys::const_iterator itor = lstEntity.begin(); \
		lstEntity.end() != itor; ++itor)
	{
		QTreeWidgetItem* pItem = new QTreeWidgetItem(m_pTreeWidget, QStringList(QString::fromLocal8Bit((*itor)->GetName().c_str())));
		m_pTreeWidget->addTopLevelItem(pItem);
	}
	

}

void CEntityManagerUI::Update(void* param /* = NULL */, int nParam /* = 0 */)
{
	m_pTreeWidget->clear();
	//VR_Soft::IEntityComposite* pIEntityComposite = static_cast<VR_Soft::IEntityComposite*>(param);

	VR_Soft::IEntityComposite* pIEntityComposite = static_cast<VR_Soft::IEntityComposite*>(param);
	if (NULL == pIEntityComposite)
	{
		return;
	}

	// 获取所有组件
	VR_Soft::IEntityComposite::LstEntitys lstEntity = pIEntityComposite->GetLstEntitys();
	if (lstEntity.empty())
	{
		return;
	}

	for (VR_Soft::IEntityComposite::LstEntitys::const_iterator itor = lstEntity.begin(); \
		lstEntity.end() != itor; ++itor)
	{
		VR_Soft::VRString str = (*itor)->GetName();

		QStringList list;
		list<<QString::fromLocal8Bit(str.c_str());

		QTreeWidgetItem* pItemParent = new QTreeWidgetItem(m_pTreeWidget,  list);
		m_pTreeWidget->insertTopLevelItem(0,pItemParent);

		if ((*itor)->IsExport())
		{
			VR_Soft::IEntityComposite* pIEntityComposite = dynamic_cast<VR_Soft::IEntityComposite*>(*itor);
			VR_Soft::IEntityComposite::LstEntitys lstsubEntity = pIEntityComposite->GetLstEntitys();
			if (lstsubEntity.empty())
			{
				continue;;
			}
			for (VR_Soft::IEntityComposite::LstEntitys::const_iterator itor = lstsubEntity.begin(); \
				lstsubEntity.end() != itor; ++itor)
			{
				new QTreeWidgetItem(pItemParent, QStringList(QString::fromLocal8Bit((*itor)->GetName().c_str())));				
			}
		}

	}

}

void CEntityManagerUI::SelectItemp(QTreeWidgetItem * item, int column)
{
	const QString strName = item->text(column);
	if (strName.isEmpty())
	{
		return;
	}

	// 从模型管理中查询当前的模型
	VR_Soft::IEntityComposite* pIEntityComp = VR_Soft::IComManager::GetInstance().GetEntityComposite();
	if (NULL == pIEntityComp)
	{
		return;
	}

	VR_Soft::IEntityBase* pIEnetiyBase = (VR_Soft::IEntityBase*)pIEntityComp->GetEntity(strName.toStdString());
	if (NULL == pIEnetiyBase)
	{
		return;
	}

	// 获得属性管理
	VR_Soft::IAttributeManager* pAttributeManager = VR_Soft::IComManager::GetInstance().GetAttributeManager();
	if (NULL == pAttributeManager)
	{
		return;
	}

	pAttributeManager->SetCurrentEntityBase(pIEnetiyBase);
}

// 右键
void CEntityManagerUI::mousePressEvent(QMouseEvent *)
{

}

void CEntityManagerUI::UpdateTime(void)
{

}
