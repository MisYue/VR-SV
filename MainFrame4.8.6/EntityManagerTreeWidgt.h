#pragma once

#include <QListWidget>

class CEntityManagerTreeWidgt : public QListWidget
{

	Q_OBJECT

public:
	CEntityManagerTreeWidgt(QWidget *parent = 0);
	~CEntityManagerTreeWidgt(void);

protected slots:
	// ɾ��ʵ��
	void DeleteEntity(void);
	// ����ʵ��
	bool TrackEntity();
	// ��·��
	bool BindPath();
	// ����ָ��
	bool BindAction(void);
	// ��������
	bool BindAttribute(void);

protected:
	// ��ʼ��
	void InitMenu(void);
	// �Ҽ�
	virtual void mousePressEvent(QMouseEvent *event);
	// ˫��
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	

private:
	QMenu* m_pPopMenu;
};

