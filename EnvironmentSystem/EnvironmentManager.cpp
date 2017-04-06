#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"

#include "EnvironmentManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// 注册回调函数
	typedef void (*DLL_INSTANLL_ENVIRONMENT)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_ENVIRONMENT)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	CEnvironmentManager::CEnvironmentManager(IEntityFactoryManager* pIEntityFactoryManager)
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{

	}


	CEnvironmentManager::~CEnvironmentManager(void)
	{
	}

	// 查找当前文件下加载插件
	void CEnvironmentManager::LoadAllElecDll(void)
	{
		// 获取插件下所有的插件文件
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Environment/";

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
	bool CEnvironmentManager::IsLoaded(const VRString& strElecName)
	{
		ListEnvironPlugin::const_iterator cstItor = m_lstEnvironPlugins.find(strElecName);
		return (m_lstEnvironPlugins.end() != cstItor);
	}

	// 加载单个dll文件
	void CEnvironmentManager::LoadElecDll(const VRString& strElecName)
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
		DLL_INSTANLL_ENVIRONMENT pFunction = (DLL_INSTANLL_ENVIRONMENT)pDyLib->GetSymbol("InstallEnvironmentPlugin");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载环境插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// 加入到表中
		m_lstEnvironPlugins[strElecName] = pDyLib;

		// 执行函数
		pFunction(m_pIEntityFactoryManager);
	}

	// 卸载单个dll文件
	void CEnvironmentManager::UnLoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
		if (!IsLoaded(strElecName))
		{
			return ;
		}

		ListEnvironPlugin::iterator itor = m_lstEnvironPlugins.find(strElecName);
		CDyLib* pDyLib = itor->second;
		if (NULL == pDyLib)
		{
			return;
		}

		// 查找入口函数
		DLL_UNINSTANLL_ENVIRONMENT pFunction = (DLL_UNINSTANLL_ENVIRONMENT)pDyLib->GetSymbol("UnInstallEnvironmentPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载环境插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			m_lstEnvironPlugins.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_lstEnvironPlugins.erase(itor);
	}
}
