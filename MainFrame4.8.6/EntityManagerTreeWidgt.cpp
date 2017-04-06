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

// 初始化
void CEntityManagerTreeWidgt::InitMenu(void)
{
	QAction* pDelAction = new QAction(QString::fromLocal8Bit("删除"), m_pPopMenu);//, m_pPopMenu);
	m_pPopMenu->addAction(pDelAction);
	connect(pDelAction, SIGNAL(triggered(bool)), this, SLOT(DeleteEntity()));

	QAction* pTrackAction = new QAction(QString::fromLocal8Bit("跟踪"), m_pPopMenu);
	m_pPopMenu->addAction(pTrackAction);
	connect(pTrackAction, SIGNAL(triggered(bool)), this, SLOT(TrackEntity()));

	QAction* pPathAction = new QAction(QString::fromLocal8Bit("绑定路径"), m_pPopMenu);
	m_pPopMenu->addAction(pPathAction);
	connect(pPathAction, SIGNAL(triggered(bool)), this, SLOT(BindPath()));

	QAction* pBindAction = new QAction(QString::fromLocal8Bit("设置命令"), m_pPopMenu);
	m_pPopMenu->addAction(pBindAction);
	connect(pBindAction, SIGNAL(triggered(bool)), this, SLOT(BindAction()));

	QAction* pBindAttribute = new QAction(QString::fromLocal8Bit("设置属性"), m_pPopMenu);
	m_pPopMenu->addAction(pBindAttribute);
	connect(pBindAttribute, SIGNAL(triggered(bool)), this, SLOT(BindAttribute()));

	//header()->hide();
	setAutoFillBackground(true);

	QString qstr = QString("background-color: rgba(85, 255, 0, 0);");
	setStyleSheet(qstr);
}

// 右键
void CEntityManagerTreeWidgt::mousePressEvent(QMouseEvent *event)
{
	if (Qt::RightButton == event->button())
	{
		// 添加右键菜单
		m_pPopMenu->exec(cursor().pos());
	}

	QListWidget::mousePressEvent(event);
}

bool CEntityManagerTreeWidgt::TrackEntity()
{
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// 获得当前选项是否为空
	const uint64_t ID = pItem->data(1).toULongLong();
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	VR_Soft::ISynchroManIpManager* pISynchroManipManager = pIEarthManager->GetSynchroManIpManager();
	pISynchroManipManager->SetTrackEntity(ID);
	return (true);
}

// 删除实体
void CEntityManagerTreeWidgt::DeleteEntity(void)
{
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// 获得当前选项是否为空
	QString qstrName = pItem->text();
	// 删除
	const VR_Soft::VRString& strName = qstrName.toLocal8Bit().data();
	VR_Soft::IEntityManager::GetInstance().RemoveEntity(strName);
}

// 双击
void CEntityManagerTreeWidgt::mouseDoubleClickEvent( QMouseEvent *event )
{
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return;
	}

	// 获得当前选项是否为空
	// 获得当前选项是否为空
	const uint64_t ID = pItem->data(1).toULongLong();
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	VR_Soft::ISynchroManIpManager* pISynchroManipManager = pIEarthManager->GetSynchroManIpManager();
	pISynchroManipManager->SetTrackEntity(ID);
}

bool CEntityManagerTreeWidgt::BindPath()
{
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// 获得当前选项是否为空
	//QString qstrName = pItem->text();
	//const VR_Soft::VRString& strName = pItem->text().toLocal8Bit().data();

	// 弹出路线对话框
	// 获得当前选项是否为空
	const uint64_t ID = pItem->data(1).toULongLong();
	// 弹出路线对话框
	VR_Soft::IEntityBase* pIEntityBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID); // dynamic_cast<VR_Soft::IEntityBase*>(pIEntityComponent);
	if (NULL == pIEntityBase)
	{
		return (false);
	}

	
	CPathBindFrame pathDailog(pIEntityBase);
	pathDailog.exec();
	return (false);
}

// 设置指令
bool CEntityManagerTreeWidgt::BindAction( void )
{
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// 获得当前选项是否为空
	const uint64_t ID = pItem->data(1).toULongLong();
	// 弹出路线对话框
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
	// 判断是否选择到实体
	QListWidgetItem* pItem = currentItem();
	if (NULL == pItem)
	{
		return (false);
	}

	// 获得当前选项是否为空
	//QString qstrName = pItem->text();
	//const VR_Soft::VRString& strName = pItem->text().toLocal8Bit().data();
	const uint64_t ID = pItem->data(1).toULongLong();

	// 弹出路线对话框
	VR_Soft::IEntityBase* pIEntityBase = VR_Soft::IEntityManager::GetInstance().GetEntity(ID); // dynamic_cast<VR_Soft::IEntityBase*>(pIEntityComponent);
	if (NULL == pIEntityBase)
	{
		return (false);
	}

	CAttributeBindFrame attriuteDailog(pIEntityBase);
	attriuteDailog.exec();
	return (false);
}
