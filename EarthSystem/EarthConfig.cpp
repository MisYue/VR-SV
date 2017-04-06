#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "EarthConfig.h"

namespace VR_Soft
{
	CEarthConfig::CEarthConfig(const VRString& strFile):m_pIConfig(NULL)
	{
		m_pIConfig = CreateConfigFileInstance(strFile);

		IConfigManager::GetInstance().AddConfig(this);
	}


	CEarthConfig::~CEarthConfig(void)
	{
		VRSOFT_DELETE(m_pIConfig);
	}

	// 设置配置文件
	void CEarthConfig::SetConfigFile(const VRString& strfile) 
	{
		m_pIConfig->OpenFile(strfile);
	}

	// 保存文件
	bool CEarthConfig::SaveConfigFile(void) 
	{
		return (true);
	}
}
