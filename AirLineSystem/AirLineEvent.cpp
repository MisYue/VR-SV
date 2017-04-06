#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "AirLineEvent.h"


namespace VR_Soft
{
	CAirLineEvent::CAirLineEvent(void)
	{
	}


	CAirLineEvent::~CAirLineEvent(void)
	{
	}

	// 鼠标左键按下
	void CAirLineEvent::OnLButtonDown(const float x, const float y)
	{
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

		pIEarth->GetLongLatHightByPoint(x, y, lat, lon, height);

		IAirLineManager::GetInstance().GetEidtAirLine()->AddAirLinePoint(CTimePoint(lat, lon, 1000.0f));
	}

	// 鼠标左键弹起
	void CAirLineEvent::OnRButtonDown(const float x, const float y)
	{
		IAirLineManager::GetInstance().EndEidtAirLine();
	}
}

