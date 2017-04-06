#pragma once

#include <QListWidget>
#include "../../Public/VRSoft.h"


class QTreeWidget;

class CEntityTypeUI : public QListWidget , public VR_Soft::IEntityTypeUI
{
	Q_OBJECT
public:
	explicit CEntityTypeUI(void);
	virtual ~CEntityTypeUI(void);


public:
	// ��ý�������
	virtual const VR_Soft::VRString GetUIName(void) const;
	 void addPiece(QPixmap pixmap, QPoint location);

public:
	// ��ʼ��
	virtual void Init(VR_Soft::IEntityFactoryManager* pIEntityFactoryManager);
	// ���һ��ʵ��
	virtual void UpdateNewItem(VR_Soft::IEntityBaseFactory* pEntity) ;
	// �Ƴ�ʵ��
	virtual void UpdateDelItem(VR_Soft::IEntityBaseFactory* pEntity);

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
	QListWidgetItem* m_dragItem;


};

