#include <QWidget>
#include <QTableWidget>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QCheckBox>
#include <QPushButton>
#include <QSpacerItem>
#include "../../Public/VRSoft.h"
#include "../../Public/ComManager/IPluginManagerUI.h"
#include "PluginManagerUI.h"

CPluginManagerUI::CPluginManagerUI(QWidget* parent) : QWidget(parent)
{
	VR_Soft::IComManager::GetInstance().GetComManagerUI()->RegisterUI(this);
	setAttribute(Qt::WA_ShowModal, true);
	// 设置名称
	setWindowTitle(QString::fromLocal8Bit("插件管理"));
	setFixedSize(465, 300);
}


CPluginManagerUI::~CPluginManagerUI(void)
{
}

// 初始化UI
void CPluginManagerUI::InitUI(const VR_Soft::IComManagerUI::PluginInfoList& lstPlugin)
{
	// 初始化
	QVBoxLayout* pBoxLayout = new QVBoxLayout(this);
	setLayout(pBoxLayout);

	m_pTableWidget = new QTableWidget;
	pBoxLayout->addWidget(m_pTableWidget);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout(this);
	pBoxLayout->addLayout(pHBoxLayout);

	QPushButton* pPushButton = new QPushButton(QString::fromLocal8Bit("确定"));
	connect(pPushButton, SIGNAL(clicked()), this, SLOT(Confirm()));
	pHBoxLayout->addWidget(pPushButton);
	pPushButton = new QPushButton(QString::fromLocal8Bit("取消"));
	connect(pPushButton, SIGNAL(clicked()), this, SLOT(Cancel()));
	pHBoxLayout->addWidget(pPushButton);
	pPushButton = new QPushButton(QString::fromLocal8Bit("应用"));
	connect(pPushButton, SIGNAL(clicked()), this, SLOT(Apply()));
	pHBoxLayout->addWidget(pPushButton);
	pHBoxLayout->setSpacing(70);

	m_pTableWidget->setRowCount((int)lstPlugin.size());
	m_pTableWidget->setColumnCount(3);

	m_pTableWidget->verticalHeader()->setHidden(true);
	m_pTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

	m_pTableWidget->setColumnWidth(0, 160);
	m_pTableWidget->setColumnWidth(1, 50);
	m_pTableWidget->setColumnWidth(2, 230);

	// 添加表头
	m_pTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString::fromLocal8Bit("名称")));
	m_pTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString::fromLocal8Bit("版本号")));
	m_pTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString::fromLocal8Bit("描述")));

	// 遍历所有的插件
	VR_Soft::IComManagerUI::PluginInfoList::const_iterator cstItor = lstPlugin.begin();
	for (int index = 0; lstPlugin.end() != cstItor; ++cstItor, ++index)
	{
		// 获得插件名称
		const VR_Soft::VRString& strName = cstItor->_pPlugin->GetPluginName();
		QCheckBox* pChekBox = new QCheckBox(QString::fromLocal8Bit(strName.c_str()));
		if (VR_Soft::IComManagerUI::Default & cstItor->_loadType)
		{
			pChekBox->setEnabled(false);
		}
		if (VR_Soft::IComManagerUI::Loaded & cstItor->_loadType)
		{
			pChekBox->setChecked(true);
		}
		else
		{
			pChekBox->setChecked(false);
		}
		m_pTableWidget->setCellWidget(index, 0, pChekBox);
		// 获得插件版本号
		const VR_Soft::VRString& strVersion = cstItor->_pPlugin->GetPluginVersion();
		m_pTableWidget->setItem(index, 1, new QTableWidgetItem(QString::fromLocal8Bit(strVersion.c_str())));
		// 获得描述
		const VR_Soft::VRString& strDiscibe = cstItor->_pPlugin->GetPluginDiscribe();
		m_pTableWidget->setItem(index, 2, new QTableWidgetItem(QString::fromLocal8Bit(strDiscibe.c_str())));
	}

}
   
void CPluginManagerUI::closeEvent(QCloseEvent * event)
{
	delete this;
}

// 应用
void CPluginManagerUI::Apply(void)
{
	// 获得第一列的空间
	int nCount = m_pTableWidget->rowCount();
	for (int index = 0; index < nCount; ++index)
	{
		QCheckBox* pCheckBox = (QCheckBox*)m_pTableWidget->cellWidget(index, 0);
		if (NULL == pCheckBox)
		{
			continue;
		}

		else if (Qt::Checked == pCheckBox->checkState())
		{
			VR_Soft::VRString strName = pCheckBox->text().toStdString();
			VR_Soft::IComManager::GetInstance().GetComManagerUI()->InstallPlugin(strName);
		}

		else if (Qt::Unchecked == pCheckBox->checkState())
		{
			VR_Soft::VRString strName = pCheckBox->text().toStdString();
			VR_Soft::IComManager::GetInstance().GetComManagerUI()->UnInstallPlugin(strName);
		}
	}
}

// 取消
void CPluginManagerUI::Cancel(void)
{
	close();
}

// 确定
void CPluginManagerUI::Confirm(void)
{
	Apply();
	close();
}