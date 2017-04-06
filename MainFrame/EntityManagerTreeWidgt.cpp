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

// ��ʼ��
void CEntityManagerTreeWidgt::InitMenu(void)
{
	QAction* pDelAction = new QAction(QString::fromLocal8Bit("ɾ��"), m_pPopMenu);//, m_pPopMenu);
	m_pPopMenu->addAction(pDelAction);
	connect(pDelAction, SIGNAL(triggered(bool)), this, SLOT(DeleteEntity()));

}

// �Ҽ�
void CEntityManagerTreeWidgt::mousePressEvent(QMouseEvent *event)
{
	if (Qt::RightButton == event->button())
	{
		// ����Ҽ��˵�
		m_pPopMenu->exec(cursor().pos());
	}

	QTreeWidget::mousePressEvent(event);
}

// ɾ��ʵ��
void CEntityManagerTreeWidgt::DeleteEntity(void)
{
	// �ж��Ƿ�ѡ��ʵ��
	QTreeWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	QString qstrName = pItem->text(0);
	const VR_Soft::VRString& strName = pItem->text(0).toStdString();
	VR_Soft::IEntityComponent* pIEntityComponent = VR_Soft::IComManager::GetInstance().GetEntityComposite(\
		)->GetEntity(strName);

	if (NULL == pIEntityComponent)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("��ǰʵ��ָ��Ϊ��",ERROR_NOT_FIND);
		return ;
	}

	VR_Soft::IEntityComponent* pIEntityParent  = pIEntityComponent->GetParentEntity();
	VR_Soft::IEntityComposite* pIEntityComposite = dynamic_cast<VR_Soft::IEntityComposite*>(pIEntityParent);
	pIEntityComposite->RemoveEntity(pIEntityComponent);
}