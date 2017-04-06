#define OSGERATH_PLUGIN_EXPOT
#include <vector>
#include <map>
#include <fstream>

#include "../../Public/EarthSystem/EarthSystem.h"
#include "SolarConfig.h"

namespace VR_Soft
{
	CSolarConfig::CSolarConfig(const VRString& strConfig):m_pIConfig(CreateConfigFileInstance(strConfig))
	{
		//m_config.OpenFile(strConfig);
		// 读取数据
		m_pIConfig->ReadConfig();
	}


	CSolarConfig::~CSolarConfig(void)
	{
		VRSOFT_DELETE(m_pIConfig);
	}

	// 获得行星信息
	PTR_Planet CSolarConfig::GetSolarInfo(const VRString& strPlanetName) 
	{
		// 获取数据
		VRString strValue = m_pIConfig->GetItemValue(strPlanetName, "radius");

		return (NULL);
	}

}

