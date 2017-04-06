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

// 设置位置
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

// 创建弹道导弹
void CTrajectoryFrame::CreateTrajectory(void)
{
/*	QString qstrName = ui.leName->text();
	if (qstrName.length() <= 0)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("弹道名称不能为空"));
		return;
	}

	// 创建弹道
	VR_Soft::IAirLineManager* pIAirLineManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::IAirLineManager>(VR_Soft::INSTANCE_NAME_AIRLINESYSTEM);
	if (NULL == pIAirLineManager)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("通知"), QString::fromLocal8Bit("创建弹道导弹失败") );
		return;
	}

	// 创建弹道
	VR_Soft::ITrajectoryEntity* pITrajectoryEntity = pIAirLineManager->CreateTrajectroryEntity("弹道导弹", "弹道导弹", VR_Soft::CGUID::Generate());
	if (NULL == pITrajectoryEntity)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("通知"), QString::fromLocal8Bit("创建弹道导弹失败") );
		return;
	}

	// 设置名称
	pITrajectoryEntity->SetName(qstrName.toLocal8Bit().data());

	osg::Vec3d vStart(ui.leStartLat->text().toDouble(), ui.leStartLon->text().toDouble(), ui.leStartAlt->text().toDouble());
	pITrajectoryEntity->GetAttribute("弹道导弹弹道属性")->GetItem("起始位置")->SetValue(vStart);
	osg::Vec3d vEnd(ui.leEndLat->text().toDouble(), ui.leEndLon->text().toDouble(), ui.leEndAlt->text().toDouble());
	pITrajectoryEntity->GetAttribute("弹道导弹弹道属性")->GetItem("终点位置")->SetValue(vEnd);

	// 最大高度
	pITrajectoryEntity->GetAttribute("弹道导弹弹道属性")->GetItem("最大高度")->SetValue((float)ui.dsbHeight->value() * 1000);

	// 生成弹道
	pITrajectoryEntity->Generate();
	// 更新弹道
	pITrajectoryEntity->NeedUpdate();

	// 获得经纬高度
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("地球组件获取失败", ERROR_NOT_COM);
		return;
	}

	// 获得高程
	double lat, lon, height;
	VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
	pIEarth->AddModel(pITrajectoryEntity, 0, 0, 0);
*/
}
