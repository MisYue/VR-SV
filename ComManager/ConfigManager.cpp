
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

	// �������
	void CConfigManager::AddConfig(IConfig* pIConfig)
	{
		VR_MUTEX_AUTO;

		m_lstConfig.push_back(pIConfig);
	}
	// �Ƴ�����
	void CConfigManager::RemoveConfig(IConfig* pIConfig)
	{
		VR_MUTEX_AUTO;
		
		// ��ѯ�Ƿ����
		LstConfig::iterator itor = std::find(m_lstConfig.begin(), m_lstConfig.end(), pIConfig);
		if (m_lstConfig.end() == itor)
		{
			return;
		}

		// ɾ��
		m_lstConfig.erase(itor);
	}
}

