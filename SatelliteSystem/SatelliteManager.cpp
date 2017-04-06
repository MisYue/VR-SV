#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"

#include "SatelliteManager.h"
#include "SatelliteEntityBuilder.h"

namespace VR_Soft
{
	CSatelliteManager::CSatelliteManager(void)
	{
	}


	CSatelliteManager::~CSatelliteManager(void)
	{
		// 注销
		IEntityFactoryManager::GetInstance().UnRegisterFactory("卫星");
	}

	// 查找当前文件下加载插件
	void CSatelliteManager::LoadAllElecDll(void)
	{
		//// 获取插件下所有的插件文件
		//const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Satellite/";

		//typedef std::vector<VRString> Files;
		//Files files;
		//CFileOperetor::GetFilesInPath(strElecDllPath, "*.dll", files);

		//// 遍历所有的文件
		//Files::const_iterator cstItor = files.begin();
		//for (; files.end() != cstItor; ++cstItor)
		//{
		//	LoadElecDll(strElecDllPath + (*cstItor));
		//}

		// 注册实体
		IEntityFactoryManager::GetInstance().RegisterFactory(CREATE_BASEENTITY_FACTORY(CSatelliteEntityBuilder));
		// 添加实体
		//m_pIEntityFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(CSatelliteEntityBuilder));
	}

	// 当前动态库是否加载了
	bool CSatelliteManager::IsLoaded(const VRString& strElecName)
	{
		/*ListSatallitePlugin::const_iterator cstItor = m_lstSatellitePlugin.find(strElecName);
		return (m_lstSatellitePlugin.end() != cstItor);*/

		return (true);
	}

	// 加载单个dll文件
	void CSatelliteManager::LoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
		//if (IsLoaded(strElecName))
		//{
		//	return ;
		//}

		//// 加载文件
		//CDyLib* pDyLib = new CDyLib(strElecName);
		//if (NULL == pDyLib)
		//{
		//	IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +" 失败", ERROR_MALLOC);
		//	return;
		//}

		//try
		//{
		//	pDyLib->Load();
		//}
		//catch (...)
		//{
		//	return;
		//}

		//// 查找入口函数
		//DLL_INSTANLL_SATELLITE pFunction = (DLL_INSTANLL_SATELLITE)pDyLib->GetSymbol("InstallSatellitePlugin");

		//if (NULL == pFunction)
		//{
		//	IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
		//	delete pDyLib;
		//	return;
		//}

		// 加入到表中
		// m_lstSatellitePlugin[strElecName] = pDyLib;

		// 执行函数
		//pFunction(m_pIEntityFactoryManager);
	}

	// 卸载单个dll文件
	void CSatelliteManager::UnLoadElecDll(const VRString& strElecName)
	{
		// 注销
		IEntityFactoryManager::GetInstance().UnRegisterFactory("卫星");
		// m_pIEntityFactoryManager->UnRegisterFactory("卫星");
		// 判断当前文件已经被加载
	/*	if (!IsLoaded(strElecName))
		{
			return ;
		}*/

		//ListSatallitePlugin::iterator itor = m_lstSatellitePlugin.find(strElecName);
		//CDyLib* pDyLib = itor->second;
		//if (NULL == pDyLib)
		//{
		//	return;
		//}

		//// 查找入口函数
		//DLL_UNINSTANLL_SATELLITE pFunction = (DLL_UNINSTANLL_SATELLITE)pDyLib->GetSymbol("UnInstallSatellitePlugin");
		//if (NULL == pFunction)
		//{
		//	IComManager::GetInstance().WriteLogMsg("加载电磁插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
		//	delete pDyLib;
		//	m_lstSatellitePlugin.erase(itor);
		//	return;
		//}

		//pFunction(m_pIEntityFactoryManager);
		//m_lstSatellitePlugin.erase(itor);
	}

}
