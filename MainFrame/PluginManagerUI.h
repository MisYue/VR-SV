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
	// ��ʼ��UI
	virtual void InitUI(const VR_Soft::IComManagerUI::PluginInfoList& lstPlugin);

protected:
	
	// �ر�
	virtual void closeEvent(QCloseEvent * event);

protected slots:
	// Ӧ��
	void Apply(void);
	// ȡ��
	void Cancel(void);
	// ȷ��
	void Confirm(void);

private:
	QTableWidget* m_pTableWidget; // �����б�
};

