#include "TrajectoryFrame.h"
#include <QMessageBox>

#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"


CTrajectoryFrame::CTrajectoryFrame(QWidget* parent/* = NULL*/)
	:QWidget(parent),m_bStart(true)
{
	ui.setupUi(this);

//	setAttribute(Qt::WA_ShowModal, true);
	setWindowFlags(Qt::Tool );

	connect(ui.psbCreate, SIGNAL(pressed()), this, SLOT(CreateTrajectory()));
}


CTrajectoryFrame::~CTrajectoryFrame(void)
{
}

// ����λ��
void CTrajectoryFrame::SetPosition(const osg::Vec3d& v)
{
	QString qstrLat = QString::number(v.x(), 'f', 6);
	QString qstrLon = QString::number(v.y(), 'f', 6);
	QString qstrAlt = QString::number(v.z(), 'f', 6);

	if (m_bStart)
	{
		ui.leStartLat->setText(qstrLat);
		ui.leStartLon->setText(qstrLon);
		ui.leStartAlt->setText(qstrAlt);
	}
	else
	{
		ui.leEndLat->setText(qstrLat);
		ui.leEndLon->setText(qstrLon);
		ui.leEndAlt->setText(qstrAlt);
	}

	m_bStart = !m_bStart;
}

// ������������
void CTrajectoryFrame::CreateTrajectory(void)
{
/*	QString qstrName = ui.leName->text();
	if (qstrName.length() <= 0)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������Ʋ���Ϊ��"));
		return;
	}

	// ��������
	VR_Soft::IAirLineManager* pIAirLineManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IAirLineManager>(VR_Soft::INSTANCE_NAME_AIRLINESYSTEM);
	if (NULL == pIAirLineManager)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("֪ͨ"), QString::fromLocal8Bit("������������ʧ��") );
		return;
	}

	// ��������
	VR_Soft::ITrajectoryEntity* pITrajectoryEntity = pIAirLineManager->CreateTrajectroryEntity("��������", "��������", VR_Soft::CGUID::Generate());
	if (NULL == pITrajectoryEntity)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("֪ͨ"), QString::fromLocal8Bit("������������ʧ��") );
		return;
	}

	// ��������
	pITrajectoryEntity->SetName(qstrName.toLocal8Bit().data());

	osg::Vec3d vStart(ui.leStartLat->text().toDouble(), ui.leStartLon->text().toDouble(), ui.leStartAlt->text().toDouble());
	pITrajectoryEntity->GetAttribute("����������������")->GetItem("��ʼλ��")->SetValue(vStart);
	osg::Vec3d vEnd(ui.leEndLat->text().toDouble(), ui.leEndLon->text().toDouble(), ui.leEndAlt->text().toDouble());
	pITrajectoryEntity->GetAttribute("����������������")->GetItem("�յ�λ��")->SetValue(vEnd);

	// ���߶�
	pITrajectoryEntity->GetAttribute("����������������")->GetItem("���߶�")->SetValue((float)ui.dsbHeight->value() * 1000);

	// ���ɵ���
	pITrajectoryEntity->Generate();
	// ���µ���
	pITrajectoryEntity->NeedUpdate();

	// ��þ�γ�߶�
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("���������ȡʧ��", ERROR_NOT_COM);
		return;
	}

	// ��ø߳�
	double lat, lon, height;
	VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
	pIEarth->AddModel(pITrajectoryEntity, 0, 0, 0);
*/
}
