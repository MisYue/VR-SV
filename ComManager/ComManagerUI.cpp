
#include <vector>
#include <list>
#include <io.h>
#include <stdlib.h>
#include <algorithm>
#include "../../Public/VRSoft.h"
#include "../../Public/ComManager/IComManagerUI.h"
#include "../../Public/ComManager/IPluginManagerUI.h"
#include "DyLibManager.h"
#include "ComManagerConfig.h"
#include "ComManagerUI.h"

namespace VR_Soft
{

	/////////////////////////////////////
	// 注册回调函数
	typedef void (*DLL_INSTANLL_PLUGIN)(void);
	typedef void (*DLL_UNINSTANLL_PLUGIN)(void);
	////////////////////////////////////

	CComManagerUI::CComManagerUI(void):m_bLoad(false)
	{
	}

	CComManagerUI::~CComManagerUI(void)
	{
		ShutPlugins();
		ShutDownPlugin();
	}

	// 通过名称注册插件
	void CComManagerUI::InstallPlugin(const VRString& strPluginName)
	{
		VR_MUTEX_AUTO;

		if (1 >= (int)strPluginName.size())
		{
			return;
		}

		// 遍历所有的插件 进行插件
		PluginInfoList::iterator itor = m_pluginInfos.begin();
		for (; m_pluginInfos.end() != itor; ++itor)
		{
			IPlugin* pPlugin = itor->_pPlugin;
			VRString strName = pPlugin->GetPluginName();
			if ((NULL == pPlugin) || (0 != pPlugin->GetPluginName().compare(strPluginName)))
			{
				continue;
			}

			// 判断是否已经加载
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				// 直接返回
				break;
			}
			// 注册
			pPlugin->Initialise();
			SET_BIT(itor->_loadType, IComManagerUI::Loaded);
			SET_UNBIT(itor->_loadType, IComManagerUI::UnLoad);

			// 添加到已添加列表中
			((CComManagerConfig*)(IComManager::GetInstance().GetComManagerConfig()))->AddComName(strPluginName);

			// 写入日志中
			IComManager::GetInstance().WriteLogMsg("插件："+pPlugin->GetPluginName() + "已经载入内存");
		}
	}

	// 通过名称卸载插件
	void CComManagerUI::UnInstallPlugin(const VRString& strPluginName)
	{
		VR_MUTEX_AUTO;

		// 遍历所有的插件 进行插件
		PluginInfoList::iterator itor = m_pluginInfos.begin();
		for (; m_pluginInfos.end() != itor; ++itor)
		{
			IPlugin* pPlugin = itor->_pPlugin;
			if ((NULL == pPlugin) || (0 != pPlugin->GetPluginName().compare(strPluginName)))
			{
				continue;
			}

			// 判断是否未加载
			if (IComManagerUI::UnLoad & itor->_loadType)
			{
				// 直接跳出
				break;
			}

			// 卸载注册
			pPlugin->Shutdown();
			SET_BIT(itor->_loadType, IComManagerUI::UnLoad);
			SET_UNBIT(itor->_loadType, IComManagerUI::Loaded);

			// 添加到已添加列表中
			((CComManagerConfig*)(IComManager::GetInstance().GetComManagerConfig()))->RemoveComName(strPluginName);

			// 写入日志中
			IComManager::GetInstance().WriteLogMsg("插件："+pPlugin->GetPluginName() + "已经被移除内存");
		}


	}

	void CComManagerUI::RegisterUI(IPluginManagerUI* pIPluginManagerUI)
	{
		VR_MUTEX_AUTO;

		// 查找是否存在
		LstPluginManagerUI::const_iterator cstItor = std::find(m_lstPluginManagerUI.begin(), \
			m_lstPluginManagerUI.end(), pIPluginManagerUI);
		if (m_lstPluginManagerUI.end() != cstItor)
		{
			// 写入日志
			return;
		}

		m_lstPluginManagerUI.push_back(pIPluginManagerUI);

		ConfigPluginManagerUI(pIPluginManagerUI);
	}

	// 反注册窗口
	void CComManagerUI::UnRegisterUI(IPluginManagerUI* pIPluginManagerUI)
	{
		VR_MUTEX_AUTO;

		// 查找是否存在
		LstPluginManagerUI::iterator itor = std::find(m_lstPluginManagerUI.begin(), \
			m_lstPluginManagerUI.end(), pIPluginManagerUI);
		if (m_lstPluginManagerUI.end() == itor)
		{
			// 写入日志
			return;
		}

		m_lstPluginManagerUI.erase(itor);
	}

	// 查询指定路径下所有插件
	void CComManagerUI::GetAllPlugins(void)
	{
		// 获得
		const VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Plugin/";
		// 获取当前目录下所有的文件
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strPath, ".dll", files);

		// 优先加载配置文件中的插件
		const VRString strOrderPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/ComManager/order.cfg";

		typedef std::vector<VRString> ListFileNames;
		ListFileNames listFileNames;
		
		CFileUtil fileUtil(strOrderPath);
		while (!fileUtil.Eof())
		{
			VRString str = fileUtil.GetLine();
			listFileNames.push_back(str);
		}

		// 首先添加项
		// 遍历所有文件
		for (ListFileNames::const_iterator cstItor = listFileNames.begin(); listFileNames.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));

			// 从其他添加列表中移除
			Files::iterator itor = std::find(files.begin(), files.end(), *cstItor);
			if (files.end() != itor)
			{
				files.erase(itor);
			}
			
		}

		// 遍历所有文件
		for (Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));
		}
	}

	// 添加插件（但是未进行全部加载到内存中去）
	void CComManagerUI::ConfigPlugins(void)
	{
		m_bLoad = true;

		// 加载所有组件
		GetAllPlugins();
	}

	// 加载插件
	void CComManagerUI::LoadPlugin(const VRString& strPluginPath)
	{
		// 载入插件
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strPluginPath);
		// 查询是否存在当前插件
		PluginLibList::const_iterator cstItor = std::find(m_pluginLibs.begin(), m_pluginLibs.end(), pLib);
		if (m_pluginLibs.end() != cstItor)
		{
			// 当前插件已经存在
			return;
		}

		//调用注册函数
		DLL_INSTANLL_PLUGIN pFunc = (DLL_INSTANLL_PLUGIN)pLib->GetSymbol("DllInstallPlugin");
		if (NULL == pFunc)
		{
			IComManager::GetInstance().WriteLogMsg(strPluginPath + "无法找到插件接口函数DllInstallPlugin", ERROR_NOT_FIND);
			CDyLibManager::GetInstance().Unload(pLib);

			return;
		}

		// 还未加载， 插件
		m_pluginLibs.push_back(pLib);

		pFunc();
	}

	// 配置窗口
	void CComManagerUI::ConfigPluginManagerUI(IPluginManagerUI* pIPluginManagerUI)
	{
		// 重新加载插件
		ConfigPlugins();

		pIPluginManagerUI->InitUI(m_pluginInfos);
	}

	// 添加插件
	void CComManagerUI::InstallPlugin(IPlugin* pPlugin)
	{
		// 写入日志中
		IComManager::GetInstance().WriteLogMsg("正在读入插件: " + pPlugin->GetPluginName());
		// 添加到插件里面
		m_pluginInfos.push_back(pPlugin);
		//// 安装插件
		pPlugin->Install();

		if (m_bLoad)
		{
			return;
		}

		pPlugin->Initialise();

		// 设置最后一个为默认状态
		SET_BIT(m_pluginInfos.back()._loadType, (IComManagerUI::Default | IComManagerUI::Loaded));

		// 写入日志中
		IComManager::GetInstance().WriteLogMsg("成功加载插件：" + pPlugin->GetPluginName());
	}

	// 卸载插件
	void CComManagerUI::UnInstallPlugin(IPlugin* pPlugin)
	{
		// 写入日志中
		IComManager::GetInstance().WriteLogMsg("开始卸载插件: " + pPlugin->GetPluginName());

		// 查询插件是否存在
		PluginInfoList::iterator itor = std::find(m_pluginInfos.begin(), m_pluginInfos.end(), pPlugin);
		if (m_pluginInfos.end() != itor)
		{
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				pPlugin->Shutdown();
				pPlugin->UnInstall();
			}
			
			m_pluginInfos.erase(itor);
		}

		IComManager::GetInstance().WriteLogMsg("成功卸载插件: " + pPlugin->GetPluginName());
	}

	// 卸载插件
	void CComManagerUI::UnLoadPlugin(const VRString& strPluginName)
	{
		// 查询是否存在插件
		PluginLibList::iterator itor = m_pluginLibs.begin();
		for (; m_pluginLibs.end() != itor; ++itor)
		{
			if (strPluginName == (*itor)->GetName())
			{
				// 调用卸载函数
				DLL_UNINSTANLL_PLUGIN pFunc = (DLL_UNINSTANLL_PLUGIN)(*itor)->GetSymbol("DllUnInstallPlugin");
				if (NULL == pFunc)
				{
					IComManager::GetInstance().WriteLogMsg("无法找到插件接口函数DllInstallPlugin");
					throw ERROR_EXCEPT;
				}

				// 调用函数
				pFunc();
				IComManager::GetInstance().WriteLogMsg("卸载动态库: " + strPluginName);
			}
		}
	}

	// 清除所有插件
	void CComManagerUI::ShutDownPlugin(void)
	{
		// 遍历所有的插件
		PluginInfoList::reverse_iterator itor = m_pluginInfos.rbegin();
		for (; m_pluginInfos.rend() != itor; ++itor)
		{
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				itor->_pPlugin->Shutdown();
			}

			IComManager::GetInstance().WriteLogMsg("成功卸载组件: " + itor->_pPlugin->GetPluginName());
		}

		m_pluginInfos.clear();
	}

	// 卸载所有的插件
	void CComManagerUI::ShutPlugins(void)
	{
		// 遍历所有的插件动态库
		for (PluginLibList::reverse_iterator itor = m_pluginLibs.rbegin(); m_pluginLibs.rend() != itor; ++itor)
		{
			DLL_UNINSTANLL_PLUGIN pFunc = (DLL_UNINSTANLL_PLUGIN)(*itor)->GetSymbol("DllUnInstallPlugin");
			if (NULL == pFunc)
			{
				continue;
			}

			// 调用卸载函数
			pFunc();
			IComManager::GetInstance().WriteLogMsg("卸载动态库:" + (*itor)->GetName());

			CDyLibManager::GetInstance().Unload(*itor);
		}

		m_pluginLibs.clear();
	}

}
