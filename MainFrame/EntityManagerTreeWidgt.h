#pragma once

#include <QTreeWidget>

class CEntityManagerTreeWidgt : public QTreeWidget
{

	Q_OBJECT

public:
	CEntityManagerTreeWidgt(QWidget *parent = 0);
	~CEntityManagerTreeWidgt(void);

protected slots:
	// ɾ��ʵ��
	void DeleteEntity(void);

protected:
	// ��ʼ��
	void InitMenu(void);
	// �Ҽ�
	virtual void mousePressEvent(QMouseEvent *event);

private:
	QMenu* m_pPopMenu;
};

