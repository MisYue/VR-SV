#include "SatelliteFrame.h"
#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"

#include <QMessageBox>

CSatelliteFrame::CSatelliteFrame(QWidget* parent)
	:QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::Tool );

	connect(ui.psbCreate, SIGNAL(pressed()), this, SLOT(CreateSatellite()));
}


CSatelliteFrame::~CSatelliteFrame(void)
{
}

// 创建弹道导弹
void CSatelliteFrame::CreateSatellite(void)
{
	// 创建弹道
	VR_Soft::ISatelliteManager* pISatelliteManager = VR_Soft::CComManagerImp::GetComponent<VR_Soft::ISatelliteManager>(VR_Soft::INSTANCE_NAME_SATELLITESYSTEM);
	if (NULL == pISatelliteManager)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("通知"), QString::fromLocal8Bit("创建弹道导弹失败") );
		return;
	}

	// 创建弹道
	VR_Soft::ISatelliteEntity* pIStatelliteEntity = (VR_Soft::ISatelliteEntity* )pISatelliteManager->CreateSatelliteEntity("卫星", "卫星轨道", VR_Soft::CGUID::Generate());
	if (NULL == pIStatelliteEntity)
	{
		QMessageBox::about(this, QString::fromLocal8Bit("通知"), QString::fromLocal8Bit("创建弹道导弹失败") );
		return;
	}

	// 设置名称
	pIStatelliteEntity->SetName("卫星0");

	// 获得经纬高度
	VR_Soft::IEarthManager* pIEarthManager = dynamic_cast<VR_Soft::IEarthManager*>(\
		VR_Soft::IComManager::GetInstance().GetConInstanceMerator()->GetComInstance(VR_Soft::INSTANCE_NAME_EARTHSYSTEM));
	if (NULL == pIEarthManager)
	{
		VR_Soft::IComManager::GetInstance().WriteLogMsg("地球组件获取失败", ERROR_NOT_COM);
		return;
	}

	// 获得高程
// 	double lat, lon, height;
// 	VR_Soft::IEarth* pIEarth = pIEarthManager->GetEarth();
// 	pIEarth->AddModel(pIStatelliteEntity, 0, 0, 0);
// 
// 	// 创建两行根数
// 	VR_Soft::ITle* pITle  = pISatelliteManager->CreateTle("test", "1 00011U 59001A   16061.51941404  .00000061  00000-0  36534-4 0  9991", "2 00011  32.8658 184.0504 1469647  37.1688 332.2105 11.85244394430484");
// 	pIStatelliteEntity->SetTle(pITle);
// 
// 	// 生成弹道
// 	pIStatelliteEntity->GenerateTrajectory();
// 
	
}
