#include "LayerManagerUI.h"
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QFileDialog>


CLayerManagerUI::CLayerManagerUI(void)
{
	Init();

	// 初始化菜单
	InitMenu();
	// 绑定信号槽
	connect(this,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
}


CLayerManagerUI::~CLayerManagerUI(void)
{
}

// 初始化
void CLayerManagerUI::Init( void )
{
	header()->hide();
	// 创建影像图层
	m_pImageItem = new QTreeWidgetItem;
	m_pImageItem->setText(0, QString::fromLocal8Bit("影像图层"));
	addTopLevelItem(m_pImageItem);

	// 创建高程图层
	m_pElevationItem = new QTreeWidgetItem;
	m_pElevationItem->setText(0, QString::fromLocal8Bit("高程图层"));
	addTopLevelItem(m_pElevationItem);

	// 创建适量图层
	m_pFeartureItem = new QTreeWidgetItem;
	m_pFeartureItem->setText(0, QString::fromLocal8Bit("矢量图层"));
	addTopLevelItem(m_pFeartureItem);

	// 获得图层管理
	VR_Soft::IEarthManager* pIEarthManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IEarthManager>(VR_Soft::INSTANCE_NAME_EARTHSYSTEM);
	if (NULL == pIEarthManager)
	{
		return;
	}

	m_pIEarthLayerManager = pIEarthManager->GetEarthLayerManager();

	// 获得所有图层
	typedef VR_Soft::IEarthLayerManager::ListEarthLayers EarthLayers;
	EarthLayers listEarthLayers = m_pIEarthLayerManager->GetAllLayer();
	for (EarthLayers::const_iterator cstIor = listEarthLayers.begin(); listEarthLayers.end() != cstIor; ++cstIor)
	{
		// 创建一个项
		QTreeWidgetItem* pTreeWidgetItem = new QTreeWidgetItem;
		pTreeWidgetItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);

		VR_Soft::IEarthLayer* pIEarthLayer = *cstIor;
		pTreeWidgetItem->setText(0, QString::fromLocal8Bit(pIEarthLayer->GetLayerName().c_str()));
		pTreeWidgetItem->setCheckState(0, Qt::Checked);
		pTreeWidgetItem->setData(1, 0, QVariant::fromValue((void*)pIEarthLayer));
		if (VR_Soft::IMAGET_TYPE == pIEarthLayer->GetLayerType())
		{
			m_pImageItem->addChild(pTreeWidgetItem);
		}
		else if (VR_Soft::ELEVATION_TYPE == pIEarthLayer->GetLayerType())
		{
			m_pElevationItem->addChild(pTreeWidgetItem);
		}
		else if (VR_Soft::FEARTRUE_TYPE == pIEarthLayer->GetLayerType())
		{
			m_pFeartureItem->addChild(pTreeWidgetItem);
		}
	}
}

// 选项发生改变
void CLayerManagerUI::treeItemChanged( QTreeWidgetItem* pTreeWidgetItem, int )
{
	QVariant var = pTreeWidgetItem->data(1, 0);
 	VR_Soft::IEarthLayer* pIEarthLayer = (VR_Soft::IEarthLayer*)var.value<void*>();
 	if (NULL == pIEarthLayer)
 	{
 		return;
 	}
 
 	// 判断是否可见
 	if (Qt::Checked == pTreeWidgetItem->checkState(0))
 	{
 		pIEarthLayer->SetVisible(true);
 	}
 	else if	(Qt::Unchecked == pTreeWidgetItem->checkState(0))
 	{
 		pIEarthLayer->SetVisible(false);
 	}
}

// 初始化菜单
void CLayerManagerUI::InitMenu()
{
	m_pAddPopMenu = new QMenu;
	QAction* pAddAction = new QAction(QString::fromLocal8Bit("添加图层"), m_pAddPopMenu);//, m_pPopMenu);
	m_pAddPopMenu->addAction(pAddAction);
	connect(pAddAction, SIGNAL(triggered(bool)), this, SLOT(AddLayer()));

	m_pDelPopMenu = new QMenu;
	QAction* pDelAction = new QAction(QString::fromLocal8Bit("删除图层"), m_pDelPopMenu);
	m_pDelPopMenu->addAction(pDelAction);
	connect(pDelAction, SIGNAL(triggered(bool)), this, SLOT(DelLayer()));
}

// 右键
void CLayerManagerUI::mousePressEvent(QMouseEvent *event)
{
	if (Qt::RightButton == event->button())
	{
		m_point = event->pos();
		QTreeWidgetItem* pTreeWidgetItem = itemAt(m_point);
		if (NULL == pTreeWidgetItem)
		{
			return;
		}

		if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("影像图层")))
		{
			m_pAddPopMenu->exec(cursor().pos());
		}
		else if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("高程图层")))
		{
			m_pAddPopMenu->exec(cursor().pos());
		}
		else if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("矢量图层")))
		{
			m_pAddPopMenu->exec(cursor().pos());
		}
		else
		{
			m_pDelPopMenu->exec(cursor().pos());
		}
		
	}

	QTreeWidget::mousePressEvent(event);
}

void CLayerManagerUI::AddLayer( void )
{
	QTreeWidgetItem* pTreeWidgetItem = itemAt(m_point);
	if (NULL == pTreeWidgetItem)
	{
		return;
	}

	VR_Soft::IEarthLayer* pIEarthLayer = NULL;

	QString strLayer = pTreeWidgetItem->text(0);

	if (0 != strLayer.compare(QString::fromLocal8Bit("矢量图层")))
	{

		// 获得图层名称
		QString str = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("加载图层"), "./", "*.tif");
		if (str.isEmpty())
		{
			return;
		}

	
		if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("影像图层")))
		{
			pIEarthLayer = m_pIEarthLayerManager->CreateEarthLayer(str.toLocal8Bit().data(), VR_Soft::IMAGET_TYPE);
			QTreeWidgetItem* pImageItem = new QTreeWidgetItem;
			pImageItem->setText(0, QString::fromLocal8Bit(pIEarthLayer->GetLayerName().c_str()));
			pImageItem->setCheckState(0, Qt::Checked);
			pImageItem->setData(1, 0, QVariant::fromValue((void*)pIEarthLayer));
			m_pImageItem->addChild(pImageItem);

		}
		else if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("高程图层")))
		{
			pIEarthLayer = m_pIEarthLayerManager->CreateEarthLayer(str.toLocal8Bit().data(), VR_Soft::ELEVATION_TYPE);
			QTreeWidgetItem* pImageItem = new QTreeWidgetItem;
			pImageItem->setText(0, QString::fromLocal8Bit(pIEarthLayer->GetLayerName().c_str()));
			pImageItem->setCheckState(0, Qt::Checked);
			pImageItem->setData(1, 0, QVariant::fromValue((void*)pIEarthLayer));
			m_pImageItem->addChild(pImageItem);
		}

	}
	else
	{
		// 获得图层名称
		QString str = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("加载矢量数据"), "./", "*.shp");
		if (str.isEmpty())
		{
			return;
		}

		pIEarthLayer = m_pIEarthLayerManager->CreateEarthLayer(str.toLocal8Bit().data(), VR_Soft::FEARTRUE_TYPE);
		QTreeWidgetItem* pImageItem = new QTreeWidgetItem;
		pImageItem->setText(0, QString::fromLocal8Bit(pIEarthLayer->GetLayerName().c_str()));
		pImageItem->setCheckState(0, Qt::Checked);
		pImageItem->setData(1, 0, QVariant::fromValue((void*)pIEarthLayer));
		m_pFeartureItem->addChild(pImageItem);

	}
// 	else if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("矢量图层")))
// 	{
// 		m_pPopMenu->exec(cursor().pos());
// 	}

	
}

void CLayerManagerUI::DelLayer( void )
{
	QTreeWidgetItem* pTreeWidgetItem = itemAt(m_point);
	if (NULL == pTreeWidgetItem)
	{
		return;
	}

	QVariant var = pTreeWidgetItem->data(1, 0);
	VR_Soft::IEarthLayer* pIEarthLayer = (VR_Soft::IEarthLayer*)var.value<void*>();
	m_pIEarthLayerManager->RemoveEarthLayer(pIEarthLayer);
	QTreeWidgetItem* pParentItem = pTreeWidgetItem->parent();
	if (0 == pParentItem->text(0).compare(QString::fromLocal8Bit("影像图层")))
	{
		m_pImageItem->removeChild(pTreeWidgetItem);
	}
	else if (0 == pTreeWidgetItem->text(0).compare(QString::fromLocal8Bit("高程图层")))
	{
		m_pElevationItem->removeChild(pTreeWidgetItem);
	}

}
