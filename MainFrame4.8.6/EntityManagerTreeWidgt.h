#pragma once

#include <QListWidget>

class CEntityManagerTreeWidgt : public QListWidget
{

	Q_OBJECT

public:
	CEntityManagerTreeWidgt(QWidget *parent = 0);
	~CEntityManagerTreeWidgt(void);

protected slots:
	// 删除实体
	void DeleteEntity(void);
	// 跟踪实体
	bool TrackEntity();
	// 绑定路径
	bool BindPath();
	// 设置指令
	bool BindAction(void);
	// 设置属性
	bool BindAttribute(void);

protected:
	// 初始化
	void InitMenu(void);
	// 右键
	virtual void mousePressEvent(QMouseEvent *event);
	// 双击
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	

private:
	QMenu* m_pPopMenu;
};

