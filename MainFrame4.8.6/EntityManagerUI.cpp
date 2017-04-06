#include <list>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTreeWidget>
#include "../../Public/VRSoft.h"
#include "EntityManagerTreeWidgt.h"
#include "EntityManagerUI.h"


CEntityManagerUI::CEntityManagerUI(QWidget* parent):QWidget(parent),
	m_pLineSearch(NULL), m_pTreeWidget(NULL)
{
	
	SetupUI();


	VR_Soft::IEntityManager::GetInstance().Attach( this);

// 	QString qstrRes = VR_Soft::IComManager::GetInstance().GetComManagerConfig()->GetCurPath().c_str();
// 	QPalette left;
// 	left.setBrush(QPalette::Background, QBrush(QPixmap(qstrRes + "/res/left.png")));
// 	m_pTreeWidget->setPalette(left);

	connect(m_pTreeWidget, SIGNAL(itemClicked(QListWidgetItem*)), \
		this, SLOT(SelectItemp(QListWidgetItem*  )));
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
	QVBoxLayout* pVBoxLayout = new QVBoxLayout(this);

	pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	pVBoxLayout->setSpacing(0);


	//pVBoxLayout->addSpacerItem(new QSpacerItem(20, 60, QSizePolicy::Preferred, QSizePolicy::Preferred));
	//// 创建文本框
	//m_pLineSearch = new QLineEdit;
	//pVBoxLayout->addWidget(m_pLineSearch);

	//pVBoxLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Preferred));

	// 创建树形列表
	m_pTreeWidget = new CEntityManagerTreeWidgt;
	pVBoxLayout->addWidget(m_pTreeWidget);
	m_pTreeWidget->setDragEnabled(true);
//	m_pTreeWidget->setDragDropMode(QAbstractItemView::InternalMove);	
}


void CEntityManagerUI::InitUI(void* param , int nParam)
{
/*	VR_Soft::IEntityComposite* pIEntityComposite = static_cast<VR_Soft::IEntityComposite*>(param);
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
	
	*/
}

void CEntityManagerUI::Update(void* param /* = NULL */, int nParam /* = 0 */)
{
	/*m_pTreeWidget->clear();
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
	*/
}

void CEntityManagerUI::SelectItemp(QListWidgetItem * item)
{
	const uint64_t ID = item->data(1).toLongLong();
// 	if (strName.isEmpty())
// 	{
// 		return;
// 	}

	// 从模型管理中查询当前的模型
	//VR_Soft::IEntityComposite* pIEntityComp = VR_Soft::IComManager::GetInstance().GetEntityComposite();
	//if (NULL == pIEntityComp)
	//{
	//	return;
	//}

	VR_Soft::IEntityBase* pIEnetiyBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID);
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

// 初始化
void CEntityManagerUI::Init( VR_Soft::IEntityManager* pIEntityManager )
{
	m_pTreeWidget->clear();

	// 获得所有的实体
	const std::vector<VR_Soft::IEntityBase*>& listEntity = pIEntityManager->GetAllEntities();
	for (std::vector<VR_Soft::IEntityBase*>::const_iterator cstItor = listEntity.begin(); listEntity.end() != cstItor; ++cstItor)
	{
		VR_Soft::VRString strName = (*cstItor)->GetName();
		const uint64_t ID = (*cstItor)->GetID();
		QListWidgetItem* pListWidgetItem = new QListWidgetItem(QString::fromLocal8Bit(strName.c_str()));
		pListWidgetItem->setData(1, ID);
		m_pTreeWidget->addItem(pListWidgetItem);
	}

}

// 添加一个实体
void CEntityManagerUI::UpdateNewItem( VR_Soft::IEntityBase* pEntity )
{
	// 添加实体

	VR_Soft::VRString strName = pEntity->GetName();
	// m_pTreeWidget->addItem(QString::fromLocal8Bit(str.c_str()));
	const uint64_t ID = pEntity->GetID();
	QListWidgetItem* pListWidgetItem = new QListWidgetItem(QString::fromLocal8Bit(strName.c_str()));
	pListWidgetItem->setData(1, ID);
	m_pTreeWidget->addItem(pListWidgetItem);
}

// 移除实体
void CEntityManagerUI::UpdateDelItem( VR_Soft::IEntityBase* pEntity )
{
//	VR_Soft::VRString str = pEntity->GetName();
//	QList<QListWidgetItem *> listItems = m_pTreeWidget->findItems( QString::fromLocal8Bit(str.c_str()),Qt::MatchExactly );

	const int nCount = m_pTreeWidget->count();
	for (int index = 0; index < nCount; ++index)
	{
		QListWidgetItem* pItem = m_pTreeWidget->item(index);
		if (NULL == pItem)
		{
			continue;
		}

		uint64_t ID = pItem->data(1).toLongLong();
		if (ID == pEntity->GetID())
		{

			//QListWidgetItem * pListWidgetItem = listItems[0];
			m_pTreeWidget->removeItemWidget(pItem);
			VRSOFT_DELETE(pItem);
			return;
		}
	}
	// m_pTreeWidget->removeItemWidget(listItems[0]);
	//m_pTreeWidget->takeItem();
}

// 更改名称
//void CEntityManagerUI::UpdateEntity( const VR_Soft::VRString& strOldName,VR_Soft::IEntityBase* pEntity )
//{
//	VR_Soft::VRString str = pEntity->GetName();
//	QList<QListWidgetItem *> listItems = m_pTreeWidget->findItems( QString::fromLocal8Bit(strOldName.c_str()),Qt::MatchExactly );
//	QListWidgetItem* pListWidgetItem = listItems[0];
//	pListWidgetItem->setText(QString::fromLocal8Bit(str.c_str()));
//}

void CEntityManagerUI::UpdateItem( VR_Soft::IEntityBase* pEntity, const VR_Soft::VRString& strOldName, const VR_Soft::VRString& strNemName )
{
	//VR_Soft::VRString str = pEntity->GetName();
// 	QList<QListWidgetItem *> listItems = m_pTreeWidget->findItems( QString::fromLocal8Bit(strOldName.c_str()),Qt::MatchExactly );
// 	if (listItems.size() <= 0)
// 	{
// 		return;
// 	}
// 
// 	QListWidgetItem* pListWidgetItem = listItems[0];
// 	if (NULL == pListWidgetItem)
// 	{
// 		return;
// 	}
// 	pListWidgetItem->setText(QString::fromLocal8Bit(strNemName.c_str()));

	const int nCount = m_pTreeWidget->count();
	for (int index = 0; index < nCount; ++index)
	{
		QListWidgetItem* pItem = m_pTreeWidget->item(index);
		if (NULL == pItem)
		{
			continue;
		}

		uint64_t ID = pItem->data(1).toULongLong();
		if (ID == pEntity->GetID())
		{

			pItem->setText(QString::fromLocal8Bit(pEntity->GetName().c_str()));
			return;
		}
	}

}
