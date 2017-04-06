#include <list>
#include <QApplication>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QIcon>
#include <QTreeWidgetItem>
#include "../../Public/VRSoft.h"
#include "../../Public/EntitySystem/EntitySystem.h"
#include "EntityTypeUI.h"


CEntityTypeUI::CEntityTypeUI(void)
{
	SetupUI();

	VR_Soft::IEntityManager* pIEntityMananger = dynamic_cast<VR_Soft::IEntityManager*>(\
		VR_Soft::IComInstanceMerator::GetInstance().GetComInstance(VR_Soft::INSTANCE_NAME_ENTITYSYSTEM));
	if (NULL == pIEntityMananger)
	{
		return;
	}
	pIEntityMananger->RegisterUI(VR_Soft::IEntityManager::EMT_BEFOREADD, this);
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
	clear();

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
	const VR_Soft::VRString& strCurPath = VR_Soft::IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/ico/radar.png";

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
		const VR_Soft::IEntityFactoryManager::LstFactroys& lstFactroys = pIEntityFactoryManager->GetAllEntityFactory();
		VR_Soft::IEntityFactoryManager::LstFactroys::const_iterator cstItor = lstFactroys.begin();
		for (; lstFactroys.end() != cstItor; ++cstItor)
		{
			QTreeWidgetItem* pChildItem = new QTreeWidgetItem(pItem, QStringList(QString::fromLocal8Bit((*cstItor)->GetEntiryBaseType().c_str())));
			pChildItem->setIcon(0,QIcon(strCurPath.c_str()));
		}
		
	}
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
	QTreeWidgetItem *pieceItem = new QTreeWidgetItem(this);
	pieceItem->setIcon(0, QIcon(pixmap));
	pieceItem->setData(0, Qt::UserRole, QVariant(pixmap));
	pieceItem->setData(0, Qt::UserRole+1, location);
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
	QTreeWidgetItem* pCurItem = currentItem();
	if (NULL == pCurItem)
	{
		return;
	}

	// 获得父节点名称
	QTreeWidgetItem* pParentItem = pCurItem->parent();
	if (NULL == pParentItem)
	{
		return;
	}

	QString strName = currentItem()->text(0);
	QString strParentName = pParentItem->text(0);
	mimeData->setData("custon/parentname", strParentName.toStdString().c_str());
	mimeData->setData("custon/name", strName.toStdString().c_str());
	drag->setMimeData(mimeData);

	// 设置图片
	QPixmap drag_imag(32, 32);
	QPainter painter(&drag_imag);

	// 获取图片
	QIcon dragIcon = currentItem()->icon(0);
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

	QTreeWidget::mousePressEvent(event);
}