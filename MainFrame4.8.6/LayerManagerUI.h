#pragma once

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QMouseEvent>

#include "../../Public/EarthSystem/EarthSystem.h"

class CLayerManagerUI : public QTreeWidget 
{
	Q_OBJECT
public:
	CLayerManagerUI(void);
	~CLayerManagerUI(void);

	// ��ʼ��
	void Init(void);
	// ��ʼ���˵�
	void InitMenu();

protected:
	void mousePressEvent(QMouseEvent *event);

protected slots:
	void treeItemChanged( QTreeWidgetItem* pTreeWidgetItem, int );
	void AddLayer(void);
	void DelLayer( void );
private:
	VR_Soft::IEarthLayerManager* m_pIEarthLayerManager;
	QTreeWidgetItem* m_pImageItem;
	QTreeWidgetItem* m_pElevationItem;
	QTreeWidgetItem* m_pFeartureItem;
	QMenu* m_pAddPopMenu;
	QPoint m_point;
	QMenu* m_pDelPopMenu;
};

