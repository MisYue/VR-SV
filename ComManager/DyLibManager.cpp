
#include "../../Public/VRSoft.h"
#include "DyLibManager.h"

namespace VR_Soft
{
	CDyLibManager::CDyLibManager(void)
	{
	}

	CDyLibManager::~CDyLibManager(void)
	{
		// ж�����еĶ���
		MapStrLib::iterator itor = m_mapStrLib.begin();
		for (; m_mapStrLib.end() != itor; ++itor)
		{
			itor->second->Unload();
			VRSOFT_DELETE(itor->second);
		}

		m_mapStrLib.clear();
	}

	// �������
	CDyLib* CDyLibManager::Load(const VRString& fileName)
	{
		// ��ѯ�ļ�
		MapStrLib::const_iterator cstItor = m_mapStrLib.find(fileName);
		// �ж��Ƿ����
		if (m_mapStrLib.end() == cstItor)
		{
			CDyLib* pLib = new CDyLib(fileName.c_str());
			pLib->Load();
			m_mapStrLib[fileName] = pLib;
			return (pLib);
		}

		// ���ڶ���
		return (cstItor->second);
	}

	// ж�����
	void CDyLibManager::Unload(CDyLib* pLib)
	{
		// ��ѯ��ǰ�Ƿ����
		MapStrLib::iterator itor = m_mapStrLib.find(pLib->GetName());
		// �ж��Ƿ����
		if (m_mapStrLib.end() != itor)
		{
			// �����ڵ�ǰ��ָ�����
			m_mapStrLib.erase(itor);
		}
		
		// ж�����
		pLib->Unload();
		VRSOFT_DELETE(pLib);
	}
}

