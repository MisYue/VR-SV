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

	// ��ȡ����
	VRString CGroundRadarFactory::GetEntiryBaseType(void) const
	{
		return ("GroundRadar");
	}

	// ��������
	IEntityBase* CGroundRadarFactory::CreateEntityInstance(void)
	{
		IEntityBase* pIRadar = new CGroundRadar;
		return (pIRadar);
	}

	// �����������
	VRString CGroundRadarFactory::GetEntityBaseName(void)
	{
		// ת��int��string
		char szCount[256] = {0};
		sprintf(szCount, "%d", m_nCount++);
		VRString strName = RADARTYPE;
		return (strName + szCount);
	}
}

