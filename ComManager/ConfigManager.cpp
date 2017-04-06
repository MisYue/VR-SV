
#include <list>
#include <algorithm>
#include "../../Public/VRSoft.h"
#include "ConfigManager.h"

namespace VR_Soft
{
	CConfigManager::CConfigManager(void)
	{
	}

	CConfigManager::~CConfigManager(void)
	{
	}

	// ÃÌº”≈‰÷√
	void CConfigManager::AddConfig(IConfig* pIConfig)
	{
		VR_MUTEX_AUTO;

		m_lstConfig.push_back(pIConfig);
	}
	// “∆≥˝≈‰÷√
	void CConfigManager::RemoveConfig(IConfig* pIConfig)
	{
		VR_MUTEX_AUTO;
		
		// ≤È—Ø «∑Ò¥Ê‘⁄
		LstConfig::iterator itor = std::find(m_lstConfig.begin(), m_lstConfig.end(), pIConfig);
		if (m_lstConfig.end() == itor)
		{
			return;
		}

		// …æ≥˝
		m_lstConfig.erase(itor);
	}
}

