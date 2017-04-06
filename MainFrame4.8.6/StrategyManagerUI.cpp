#include <QGridLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include "../../Public/VRSoft.h"
#include "StrategyManagerUI.h"


CStrategyManagerUI::CStrategyManagerUI(VR_Soft::IEntityBase* pIEntity, QWidget *parent, Qt::WindowFlags f)
	:QDialog(parent, f),m_pIEntity(pIEntity)
{
	InitUI(pIEntity);
}


CStrategyManagerUI::~CStrategyManagerUI(void)
{
}

void CStrategyManagerUI::InitUI(VR_Soft::IEntityBase* pIEntity)
{
	QListWidget* pLstWidget = new QListWidget;

	connect(pLstWidget, SIGNAL(itemPressed( QListWidgetItem *)), this, SLOT(ItemSelect(QListWidgetItem*)));
	QGridLayout* pGridLayout = new QGridLayout(this);
	setLayout(pGridLayout);
	pGridLayout->addWidget(pLstWidget);

	// 获得所有的策略
/*	VR_Soft::IStrategyManager* pIStategryManager = VR_Soft::IEntityManager::GetInstancePtr()->GetStrategyManagerInstance();
	VR_Soft::IStrategyManager::ListStrategyFactorys lstStrategyFacotry = pIStategryManager->GetAllStrategyFactory();
	VR_Soft::IStrategyManager::ListStrategyFactorys::const_iterator cstItor = lstStrategyFacotry.begin();
	for (; lstStrategyFacotry.end() != cstItor; ++cstItor)
	{
		QListWidgetItem* pListWidgetItem = new QListWidgetItem((*cstItor)->GetType().c_str());
		pListWidgetItem->setCheckState(Qt::Unchecked);
		pLstWidget->addItem(pListWidgetItem);
	}
*/
}

void CStrategyManagerUI::ItemSelect(QListWidgetItem * item)
{
	//if (Qt::Checked == item->checkState())
	//{
	//	// 获得所有的策略
	//	VR_Soft::IStrategyManager* pIStategryManager = VR_Soft::IEntityManager::GetInstancePtr()->GetStrategyManagerInstance();
	//	pIStategryManager->AddStrategy(m_pIEntity, item->text().toLocal8Bit().data());
	//}
}
