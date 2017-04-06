#pragma once

#include <QWidget>
#include "ui_TrajectoryFrame.h"

#include <osg/Vec3d>

class CTrajectoryFrame : public QWidget
{
	Q_OBJECT

public:
	CTrajectoryFrame(QWidget* parent = NULL);
	~CTrajectoryFrame(void);

	// ����λ��
	void SetPosition(const osg::Vec3d& v);

protected slots:
	// ������������
	void CreateTrajectory(void);

private: 
	Ui::TrajectoryForm ui; 

	bool m_bStart;
};

