#include <list>
#include <QApplication>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QIcon>
#include <QListWidgetItem>
#include "../../Public/VRSoft.h"
#include "EntityTypeUI.h"


CEntityTypeUI::CEntityTypeUI(void)
{
	SetupUI();

	VR_Soft::IEntityFactoryManager::GetInstance().Attach(this);
//	VR_Soft::IEntityManager::GetInstance().RegisterUI(this, VR_Soft::IEntityManager::EMT_BEFOREADD);
}


CEntityTypeUI::~CEntityTypeUI(void)
{
}

// 获得界面名称
const VR_Soft::VRString CEntityTypeUI::GetUIName(void) const
{
	return ("entityTypeUI");
}


void CEntityTypeUI::SetupUI(void)
{
	setDragEnabled(true);
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
}


void CEntityTypeUI::InitUI(void* param , int nParam)
{
	// 清空控件
/*	clear();

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

	// 获得路径
	//const VR_Soft::VRString& strCurPath = VR_Soft::IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/ico/radar.png";

	for (VR_Soft::IEntityComposite::LstEntitys::const_iterator itor = lstEntity.begin(); \
		lstEntity.end() != itor; ++itor)
	{
		if (!(*itor)->IsExport())
		{
			continue;
		}

		// 设置级别
		QTreeWidgetItem* pItem = new QTreeWidgetItem(this, QStringList(QString::fromLocal8Bit((*itor)->GetName().c_str())));
		addTopLevelItem(pItem);

		// 获得工厂管理
		VR_Soft::IEntityComposite* pIEntityComposite = dynamic_cast<VR_Soft::IEntityComposite*>(*itor);
		if (NULL == pIEntityComposite)
		{
			continue;
		}
		VR_Soft::IEntityFactoryManager* pIEntityFactoryManager =  pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			continue;
		}

		// 获得所有工厂
		const VR_Soft::IEntityFactoryManager::ListFactroys& lstFactroys = pIEntityFactoryManager->GetAllEntityFactory();
		VR_Soft::IEntityFactoryManager::ListFactroys::const_iterator cstItor = lstFactroys.begin();
		for (; lstFactroys.end() != cstItor; ++cstItor)
		{
			VR_Soft::IEntityBaseFactory* pFactry = (*cstItor);
			QTreeWidgetItem* pChildItem = new QTreeWidgetItem(pItem, QStringList(QString::fromLocal8Bit(pFactry->GetEntiryBaseType().c_str())));
//			pChildItem->setIcon(0,QIcon(pFactry->GetModel2D().c_str()));
		}
		
	}*/
}

void CEntityTypeUI::Update(void* param /* = NULL */, int nParam /* = 0 */)
{
	InitUI(param, nParam);
}


void CEntityTypeUI::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("image/modelico"))
		event->accept();
	else
		event->ignore();
}

void CEntityTypeUI::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("image/modelico")) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	} else {
		event->ignore();
	}
}

void CEntityTypeUI::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("image/modelico")) {
		QByteArray pieceData = event->mimeData()->data("image/modelico");
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		QPixmap pixmap;
		QPoint location;
		dataStream >> pixmap >> location;

		addPiece(pixmap, location);

		event->setDropAction(Qt::MoveAction);
		event->accept();
	} else {
		event->ignore();
	}
}


void CEntityTypeUI::addPiece(QPixmap pixmap, QPoint location)
{
	QListWidgetItem *pieceItem = new QListWidgetItem(this);
	pieceItem->setIcon(QIcon(pixmap));
	pieceItem->setData(0, QVariant(pixmap));
	pieceItem->setData(0, location);
	pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
}

void CEntityTypeUI::mouseMoveEvent(QMouseEvent *event)
{
	if (!(event->buttons()  & Qt::LeftButton))
	{
		return;
	}

	if ((event->pos() - m_dragPosition).manhattanLength() < QApplication::startDragDistance())
	{
		return;
	}

	QDrag *drag = new QDrag(this);
	QMimeData* mimeData = new QMimeData;

	// 获得当前项
	QListWidgetItem* pCurItem = currentItem();
	if (NULL == pCurItem)
	{
		return;
	}

	
	QString strName = currentItem()->text();
	mimeData->setData("custon/name", strName.toLocal8Bit().data());
	drag->setMimeData(mimeData);

	// 设置图片
	QPixmap drag_imag(32, 32);
	QPainter painter(&drag_imag);

	// 获取图片
	QIcon dragIcon = currentItem()->icon();
	QPixmap pixmap = dragIcon.pixmap(32, 32);
	painter.drawPixmap(0, 0, 32, 32, pixmap);
	drag->setPixmap(drag_imag);
	drag->setHotSpot(QPoint(16, 16));

	Qt::DropAction resultAction = drag->exec(Qt::MoveAction);
	if (resultAction == Qt::MoveAction)
	{
	}
}

void CEntityTypeUI::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_dragItem = itemAt(event->pos());
		m_dragPosition = event->pos();
	}

	QListWidget::mousePressEvent(event);
}

// 初始化
void CEntityTypeUI::Init( VR_Soft::IEntityFactoryManager* pIEntityFactoryManager )
{
	// 清空控件
	clear();

	// 获得所有的工厂
	VR_Soft::ListString listFactory = pIEntityFactoryManager->GetAllEntityFactory();
	for (VR_Soft::ListString::const_iterator itor = listFactory.begin(); \
		listFactory.end() != itor; ++itor)
	{
	//	VR_Soft::VRString str = (*itor)->GetEntiryBaseType();
		addItem(QString::fromLocal8Bit(itor->c_str()));
	}

}

// 添加一个实体
void CEntityTypeUI::UpdateNewItem( VR_Soft::IEntityBaseFactory* pEntity )
{
	// 添加实体

	VR_Soft::VRString str = pEntity->GetEntiryBaseType();
	addItem(QString::fromLocal8Bit(str.c_str()));
}

// 移除实体
void CEntityTypeUI::UpdateDelItem( VR_Soft::IEntityBaseFactory* pEntity )
{
	VR_Soft::VRString str = pEntity->GetEntiryBaseType();
	QList<QListWidgetItem *> listItems =findItems( QString::fromLocal8Bit(str.c_str()),Qt::MatchExactly );
	removeItemWidget(listItems[0]);
	//addItem(QString::fromLocal8Bit(str.c_str()));
}
