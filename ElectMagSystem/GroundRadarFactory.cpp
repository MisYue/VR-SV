#define VRSOFT_PLUGIN_EXPORT
#include "../Public/VRSoft.h"
#include "../Public/ElectMagSystem/IRadar.h"
#include "GroundRadar.h"
#include "GroundRadarFactory.h"

namespace VR_Soft
{
	int IEntityBaseFactory::m_nCount = 0;
	CGroundRadarFactory::CGroundRadarFactory(void)
	{
	}


	CGroundRadarFactory::~CGroundRadarFactory(void)
	{
	}

	// 获取类型
	VRString CGroundRadarFactory::GetEntiryBaseType(void) const
	{
		return ("GroundRadar");
	}

	// 创建类型
	IEntityBase* CGroundRadarFactory::CreateEntityInstance(void)
	{
		IEntityBase* pIRadar = new CGroundRadar;
		return (pIRadar);
	}

	// 获得类型名称
	VRString CGroundRadarFactory::GetEntityBaseName(void)
	{
		// 转换int到string
		char szCount[256] = {0};
		sprintf(szCount, "%d", m_nCount++);
		VRString strName = RADARTYPE;
		return (strName + szCount);
	}
}

