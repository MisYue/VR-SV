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

	// ���������ļ�
	void CEarthConfig::SetConfigFile(const VRString& strfile) 
	{
		m_pIConfig->OpenFile(strfile);
	}

	// �����ļ�
	bool CEarthConfig::SaveConfigFile(void) 
	{
		return (true);
	}
}
