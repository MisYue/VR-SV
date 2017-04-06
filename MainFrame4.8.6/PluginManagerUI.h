#pragma once

#include <QWidget>
#include "../../Public/VRSoft.h"
#include "../../Public/ComManager/IPluginManagerUI.h"

class QTableWidget;

class CPluginManagerUI : public QWidget, public VR_Soft::IPluginManagerUI
{
	Q_OBJECT

public:
	explicit CPluginManagerUI(QWidget* parent = NULL);
	virtual ~CPluginManagerUI(void);

public:
	// 初始化UI
	virtual void InitUI(const VR_Soft::IComManagerUI::PluginInfoList& lstPlugin);

protected:
	
	// 关闭
	virtual void closeEvent(QCloseEvent * event);

protected slots:
	// 应用
	void Apply(void);
	// 取消
	void Cancel(void);
	// 确定
	void Confirm(void);

private:
	QTableWidget* m_pTableWidget; // 树形列表
};

