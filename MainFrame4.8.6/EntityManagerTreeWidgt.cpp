#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QListWidgetItem>
#include <QString>
#include <QMessageBox>
#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "EntityManagerTreeWidgt.h"
#include "PathBindFrame.h"
#include "ActionBindFrame.h"
#include "AttributeBindFrame.h"


CEntityManagerTreeWidgt::CEntityManagerTreeWidgt(QWidget *parent)
	:QListWidget(parent),m_pPopMenu(new QMenu)
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

	QAction* pTrackAction = new QAction(QString::fromLocal8Bit("����"), m_pPopMenu);
	m_pPopMenu->addAction(pTrackAction);
	connect(pTrackAction, SIGNAL(triggered(bool)), this, SLOT(TrackEntity()));

	QAction* pPathAction = new QAction(QString::fromLocal8Bit("��·��"), m_pPopMenu);
	m_pPopMenu->addAction(pPathAction);
	connect(pPathAction, SIGNAL(triggered(bool)), this, SLOT(BindPath()));

	QAction* pBindAction = new QAction(QString::fromLocal8Bit("��������"), m_pPopMenu);
	m_pPopMenu->addAction(pBindAction);
	connect(pBindAction, SIGNAL(triggered(bool)), this, SLOT(BindAction()));

	QAction* pBindAttribute = new QAction(QString::fromLocal8Bit("��������"), m_pPopMenu);
	m_pPopMenu->addAction(pBindAttribute);
	connect(pBindAttribute, SIGNAL(triggered(bool)), this, SLOT(BindAttribute()));

	//header()->hide();
	setAutoFillBackground(true);

	QString qstr = QString("background-color: rgba(85, 255, 0, 0);");
	setStyleSheet(qstr);
}

// �Ҽ�
void CEntityManagerTreeWidgt::mousePressEvent(QMouseEvent *event)
{
	if (Qt::RightButton == event->button())
	{
		// ����Ҽ��˵�
		m_pPopMenu->exec(cursor().pos());
	}

	QListWidget::mousePressEvent(event);
}

bool CEntityManagerTreeWidgt::TrackEntity()
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	const uint64_t ID = pItem->data(1).toULongLong();
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	VR_Soft::ISynchroManIpManager* pISynchroManipManager = pIEarthManager->GetSynchroManIpManager();
	pISynchroManipManager->SetTrackEntity(ID);
	return (true);
}

// ɾ��ʵ��
void CEntityManagerTreeWidgt::DeleteEntity(void)
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	QString qstrName = pItem->text();
	// ɾ��
	const VR_Soft::VRString& strName = qstrName.toLocal8Bit().data();
	VR_Soft::IEntityManager::GetInstance().RemoveEntity(strName);
}

// ˫��
void CEntityManagerTreeWidgt::mouseDoubleClickEvent( QMouseEvent *event )
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	// ��õ�ǰѡ���Ƿ�Ϊ��
	const uint64_t ID = pItem->data(1).toULongLong();
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	VR_Soft::ISynchroManIpManager* pISynchroManipManager = pIEarthManager->GetSynchroManIpManager();
	pISynchroManipManager->SetTrackEntity(ID);
}

bool CEntityManagerTreeWidgt::BindPath()
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	//QString qstrName = pItem->text();
	//const VR_Soft::VRString& strName = pItem->text().toLocal8Bit().data();

	// ����·�߶Ի���
	// ��õ�ǰѡ���Ƿ�Ϊ��
	const uint64_t ID = pItem->data(1).toULongLong();
	// ����·�߶Ի���
	VR_Soft::IEntityBase* pIEntityBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID); // dynamic_cast<VR_Soft::IEntityBase*>(pIEntityComponent);
	if (NULL == pIEntityBase)
	{
		return (false);
	}

	
	CPathBindFrame pathDailog(pIEntityBase);
	pathDailog.exec();
	return (false);
}

// ����ָ��
bool CEntityManagerTreeWidgt::BindAction( void )
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	const uint64_t ID = pItem->data(1).toULongLong();
	// ����·�߶Ի���
	VR_Soft::IEntityBase* pIEntityBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID); // dynamic_cast<VR_Soft::IEntityBase*>(pIEntityComponent);
	if (NULL == pIEntityBase)
	{
		return (false);
	}

	CActionBindFrame actinDailog(pIEntityBase);
	actinDailog.exec();
	return (false);
}


bool CEntityManagerTreeWidgt::BindAttribute( void )
{
	// �ж��Ƿ�ѡ��ʵ��
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// ��õ�ǰѡ���Ƿ�Ϊ��
	//QString qstrName = pItem->text();
	//const VR_Soft::VRString& strName = pItem->text().toLocal8Bit().data();
	const uint64_t ID = pItem->data(1).toULongLong();

	// ����·�߶Ի���
	VR_Soft::IEntityBase* pIEntityBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID); // dynamic_cast<VR_Soft::IEntityBase*>(pIEntityComponent);
	if (NULL == pIEntityBase)
	{
		return (false);
	}

	CAttributeBindFrame attriuteDailog(pIEntityBase);
	attriuteDailog.exec();
	return (false);
}
