#include <QTreeWidget>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include "../../Public/VRSoft.h"
#include "EntityManagerTreeWidgt.h"


CEntityManagerTreeWidgt::CEntityManagerTreeWidgt(QWidget *parent):QTreeWidget(parent),m_pPopMenu(new QMenu)
{
	InitMenu();
}


CEntityManagerTreeWidgt::~CEntityManagerTreeWidgt(void)
{
	delete m_pPopMenu;
}

// 初始化
void CEntityManagerTreeWidgt::InitMenu(void)
{
	QAction* pDelAction = new QAction(QString::fromLocal8Bit("删除"), m_pPopMenu);//, m_pPopMenu);
	m_pPopMenu->addAction(pDelAction);
	connect(pDelAction, SIGNAL(triggered(bool)), this, SLOT(DeleteEntity()));

}

// 右键
void CEntityManagerTreeWidgt::mousePressEvent(QMouseEvent *event)
{
	if (Qt::RightButton == event->button())
	{
		// 添加右键菜单
		m_pPopMenu->exec(cursor().pos());
	}

	QTreeWidget::mousePressEvent(event);
}

// 删除实体
void CEntityManagerTreeWidgt::DeleteEntity(void)
{
	// 判断是否选择到实体
	QTreeWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// 获得当前选项是否为空
	QString qstrName = pItem->text(0);
	const VR_Soft::VRString& strName = pItem->text(0).toStdString();
	VR_Soft::IEntityComponent* pIEntityComponent = VR_Soft::IComManager::GetInstance().GetEntityComposite(\
		)->GetEntity(strName);

	if (NULL == pIEntityComponent)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("当前实体指针为空",ERROR_NOT_FIND);
		return ;
	}

	VR_Soft::IEntityComponent* pIEntityParent  = pIEntityComponent->GetParentEntity();
	VR_Soft::IEntityComposite* pIEntityComposite = dynamic_cast<VR_Soft::IEntityComposite*>(pIEntityParent);
	pIEntityComposite->RemoveEntity(pIEntityComponent);
}