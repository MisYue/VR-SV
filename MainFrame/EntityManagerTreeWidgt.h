#pragma once

#include <QTreeWidget>

class CEntityManagerTreeWidgt : public QTreeWidget
{

	Q_OBJECT

public:
	CEntityManagerTreeWidgt(QWidget *parent = 0);
	~CEntityManagerTreeWidgt(void);

protected slots:
	// 删除实体
	void DeleteEntity(void);

protected:
	// 初始化
	void InitMenu(void);
	// 右键
	virtual void mousePressEvent(QMouseEvent *event);

private:
	QMenu* m_pPopMenu;
};

