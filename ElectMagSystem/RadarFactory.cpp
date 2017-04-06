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

	// ��ȡ����
	VRString CRadarFactory::GetEntiryBaseType(void) const
	{
		return (RADARTYPE);
	}

	// ��������
	IEntityBase* CRadarFactory::CreateEntityInstance(void)
	{
		IEntityBase* pIRadar = new DetectLoop;
		return (pIRadar);
	}

	// �����������
	VRString CRadarFactory::GetEntityBaseName(void)
	{
		static int count = 0;
		// ת��int��string
		char szCount[256] = {0};
		sprintf(szCount, "%d", count++);
		VRString strName = RADARTYPE;
		return (strName + szCount);
	}
}
