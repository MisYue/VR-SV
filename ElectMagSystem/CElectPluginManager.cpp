#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectPluginManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// 注册回调函数
	typedef void (*DLL_INSTANLL_ELECT)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_ELECT)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	CElectPluginManager::CElectPluginManager(IEntityFactoryManager* pIEntityFactoryManager) 
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{
	}
	
	CElectPluginManager::~CElectPluginManager(void)
	{
	}

	// 查找当前文件下加载插件
	void CElectPluginManager::LoadAllElecDll(void)
	{
		// 获取插件下所有的插件文件
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Elect/";

		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strElecDllPath, "*.dll", files);

		// 遍历所有的文件
		Files::const_iterator cstItor = files.begin();
		for (; files.end() != cstItor; ++cstItor)
		{
			LoadElecDll(strElecDllPath + (*cstItor));
		}

	}

	// 当前动态库是否加载了
	bool CElectPluginManager::IsLoaded(const VRString& strElecName)
	{
		MapElectPlugin::const_iterator cstItor = m_mapElectPlugin.find(strElecName);
		return (m_mapElectPlugin.end() != cstItor);
	}

	// 加载单个dll文件
	void CElectPluginManager::LoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
		if (IsLoaded(strElecName))
		{
			return ;
		}

		// 加载文件
		CDyLib* pDyLib = new CDyLib(strElecName);
		if (NULL == pDyLib)
		{
			IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +" 失败", ERROR_MALLOC);
			return;
		}

		try
		{
			pDyLib->Load();
		}
		catch (...)
		{
			return;
		}
		
		// 查找入口函数
		DLL_INSTANLL_ELECT pFunction = (DLL_INSTANLL_ELECT)pDyLib->GetSymbol("InstallElectPlugin");
		
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// 加入到表中
		m_mapElectPlugin[strElecName] = pDyLib;

		// 执行函数
		pFunction(m_pIEntityFactoryManager);
	}

	// 卸载单个dll文件
	void CElectPluginManager::UnLoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
		if (!IsLoaded(strElecName))
		{
			return ;
		}

		MapElectPlugin::iterator itor = m_mapElectPlugin.find(strElecName);
		CDyLib* pDyLib = itor->second;
		if (NULL == pDyLib)
		{
			return;
		}

		// 查找入口函数
		DLL_UNINSTANLL_ELECT pFunction = (DLL_UNINSTANLL_ELECT)pDyLib->GetSymbol("UnInstallElectPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			m_mapElectPlugin.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_mapElectPlugin.erase(itor);
	}
}

