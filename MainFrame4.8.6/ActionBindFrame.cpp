#include "../../Public/VRSoft.h"
#include "ActionBindFrame.h"

#include <QListWidgetItem>


CActionBindFrame::CActionBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent)
	:QDialog(parent),m_pIEntity(pIEntityBase)
{
	ui.setupUi(this);

	// 设置初始化内容
	InitAction();

	connect(ui.psbBind, SIGNAL(	clicked (bool)), this, SLOT(BindAction()));
	connect(ui.psbUnBind, SIGNAL(	clicked (bool)), this, SLOT(UnBindAction()));
	connect(ui.lstWgtbindAction, SIGNAL(itemClicked(QListWidgetItem * )), this, SLOT(ActionDTSeting(QListWidgetItem * )));
	connect(ui.dateTimeEdit, SIGNAL(dateTimeChanged(const QDateTime&)), this, SLOT(DataTimeChanged(const QDateTime&)));
}


CActionBindFrame::~CActionBindFrame(void)
{
}

// 设置初始化内容
void CActionBindFrame::InitAction( void )
{
	VR_Soft::IActionManager::GetInstance().LoadAction();
	const VR_Soft::ListString listStr = VR_Soft::IActionManager::GetInstance().GetAllActionDll();
	VR_Soft::ListString::const_iterator cstItor = listStr.begin();
	while (listStr.end() != cstItor)
	{
		ui.lstWgtAction->addItem(new QListWidgetItem(QString::fromLocal8Bit(cstItor->c_str())));
		++cstItor;
	}

	// 获得已经加载的
	if (NULL == m_pIEntity)
	{
		return;
	}

	VR_Soft::ListString listActionStr = VR_Soft::IActionManager::GetInstance().GetAllActionDll(m_pIEntity);
	VR_Soft::ListString::const_iterator actCstItor = listActionStr.begin();
	while (listActionStr.end() != actCstItor)
	{
		ui.lstWgtbindAction->addItem(new QListWidgetItem(QString::fromLocal8Bit(actCstItor->c_str())));
		++actCstItor;
	}
}

bool CActionBindFrame::BindAction()
{
	if (NULL == m_pIEntity)
	{
		return (false);
	}

	QString strText = ui.lstWgtAction->currentItem()->text();
	VR_Soft::IActionManager::GetInstance().AddAction(m_pIEntity, strText.toLocal8Bit().data());
	ui.lstWgtbindAction->addItem(new QListWidgetItem(strText));
	return (true);
}

bool CActionBindFrame::UnBindAction()
{
	if (NULL == m_pIEntity)
	{
		return (false);
	}

	QModelIndex modelIndex = ui.lstWgtbindAction->currentIndex();
	VR_Soft::IActionManager::GetInstance().RemoveAction(m_pIEntity, modelIndex.row());

	QList<QListWidgetItem*> list = ui.lstWgtbindAction->selectedItems();
	QListWidgetItem* sel = list[0]; 
	int r = ui.lstWgtbindAction->row(sel);  
	ui.lstWgtbindAction->takeItem(r);  

	return (true);
}

bool CActionBindFrame::ActionDTSeting(QListWidgetItem * item)
{
	if (NULL == m_pIEntity)
	{
		return (false);
	}

	QModelIndex modelIndex = ui.lstWgtbindAction->currentIndex();
	VR_Soft::IAction* pIAction = VR_Soft::IActionManager::GetInstance().GetAction(m_pIEntity, modelIndex.row());
	if (NULL == pIAction)
	{
		return (false);
	}

	const VR_Soft::CDateTime& dt = pIAction->GetDateTime();
	ui.dateTimeEdit->setDateTime(QDateTime(QDate(dt.Year(), dt.Month(), dt.Day()), QTime(dt.Hour(), dt.Minute(), dt.Second())));

	return (true);
}

bool CActionBindFrame::DataTimeChanged( const QDateTime& dt )
{
	QModelIndex modelIndex = ui.lstWgtbindAction->currentIndex();
	VR_Soft::IAction* pIAction = VR_Soft::IActionManager::GetInstance().GetAction(m_pIEntity, modelIndex.row());
	if (NULL == pIAction)
	{
		return (false);
	}

	const VR_Soft::CDateTime dateTime(dt.date().year(), dt.date().month(), dt.date().day(), \
		dt.time().hour(), dt.time().minute(), dt.time().second());

	pIAction->SetDateTime(dateTime);

	return (true);
}
