#define VRSOFT_PLUGIN_EXPORT
#include "../Public/VRSoft.h"
#include "../Public/ElectMagSystem/IRadar.h"
#include "DetectLoop.h"
#include "RadarFactory.h"

namespace VR_Soft
{
	CRadarFactory::CRadarFactory(void)
	{
	}


	CRadarFactory::~CRadarFactory(void)
	{
	}

	// 获取类型
	VRString CRadarFactory::GetEntiryBaseType(void) const
	{
		return (RADARTYPE);
	}

	// 创建类型
	IEntityBase* CRadarFactory::CreateEntityInstance(void)
	{
		IEntityBase* pIRadar = new DetectLoop;
		return (pIRadar);
	}

	// 获得类型名称
	VRString CRadarFactory::GetEntityBaseName(void)
	{
		static int count = 0;
		// 转换int到string
		char szCount[256] = {0};
		sprintf(szCount, "%d", count++);
		VRString strName = RADARTYPE;
		return (strName + szCount);
	}
}
