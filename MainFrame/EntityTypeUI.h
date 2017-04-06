#pragma once

#include <QTreeWidget>
#include "../../Public/VRSoft.h"


class QTreeWidget;

class CEntityTypeUI : public QTreeWidget , public VR_Soft::IPluginUI
{
	Q_OBJECT
public:
	explicit CEntityTypeUI(void);
	virtual ~CEntityTypeUI(void);


public:
	// 获得界面名称
	virtual const VR_Soft::VRString GetUIName(void) const;
	 void addPiece(QPixmap pixmap, QPoint location);

protected:
	virtual void InitUI(void* param = NULL, int nParam = 0);
	virtual void Update(void* param = NULL, int nParam = 0);
	void SetupUI(void);

protected:
	virtual void dragEnterEvent(QDragEnterEvent *event) ;
	virtual void dragMoveEvent(QDragMoveEvent *event);
	virtual void dropEvent(QDropEvent *event) ;
	//virtual void startDrag(Qt::DropActions supportedActions) ;

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);

private:
	QPoint m_dragPosition;
	QTreeWidgetItem* m_dragItem;


};

