
#include "../../Public/VRSoft.h"
#include "DyLibManager.h"

namespace VR_Soft
{
	CDyLibManager::CDyLibManager(void)
	{
	}

	CDyLibManager::~CDyLibManager(void)
	{
		// 卸载所有的对象
		MapStrLib::iterator itor = m_mapStrLib.begin();
		for (; m_mapStrLib.end() != itor; ++itor)
		{
			itor->second->Unload();
			VRSOFT_DELETE(itor->second);
		}

		m_mapStrLib.clear();
	}

	// 加载组件
	CDyLib* CDyLibManager::Load(const VRString& fileName)
	{
		// 查询文件
		MapStrLib::const_iterator cstItor = m_mapStrLib.find(fileName);
		// 判断是否存在
		if (m_mapStrLib.end() == cstItor)
		{
			CDyLib* pLib = new CDyLib(fileName.c_str());
			pLib->Load();
			m_mapStrLib[fileName] = pLib;
			return (pLib);
		}

		// 存在对象
		return (cstItor->second);
	}

	// 卸载组件
	void CDyLibManager::Unload(CDyLib* pLib)
	{
		// 查询当前是否存在
		MapStrLib::iterator itor = m_mapStrLib.find(pLib->GetName());
		// 判断是否存在
		if (m_mapStrLib.end() != itor)
		{
			// 不存在当前的指针对象
			m_mapStrLib.erase(itor);
		}
		
		// 卸载组件
		pLib->Unload();
		VRSOFT_DELETE(pLib);
	}
}

