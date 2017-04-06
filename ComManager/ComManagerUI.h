/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理界面实现类                                            */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _COMMANAGERUI_H_
#define _COMMANAGERUI_H_

#pragma once

namespace VR_Soft
{
	class CComManagerUI : public IComManagerUI
	{
	public:
		explicit CComManagerUI(void);
		virtual ~CComManagerUI(void);

	public:
		// 通过名称注册插件
		virtual void InstallPlugin(const VRString& strPluginName);
		// 通过名称卸载插件
		virtual void UnInstallPlugin(const VRString& strPluginName);
		// 注册窗口
		virtual void RegisterUI(IPluginManagerUI* pIPluginManagerUI);
		// 反注册窗口
		virtual void UnRegisterUI(IPluginManagerUI* pIPluginManagerUI);
		

	public:
		// 添加插件
		void InstallPlugin(IPlugin* pPlugin);
		// 卸载插件
		void UnInstallPlugin(IPlugin* pPlugin);
		// 加载插件
		void LoadPlugin(const VRString& strPluginPath);
		// 卸载插件
		void UnLoadPlugin(const VRString& strPluginName);
		// 添加插件（但是未进行全部加载到内存中去）
		void ConfigPlugins(void);

	protected:
		// 查询指定路径下所有插件
		void GetAllPlugins(void);
		// 配置窗口
		void ConfigPluginManagerUI(IPluginManagerUI* pIPluginManagerUI);
		// 清除所有插件
		void ShutDownPlugin(void);
		// 卸载所有的插件
		void ShutPlugins(void);
		

	private:
		typedef std::vector<CDyLib*>  PluginLibList;

	private:
		bool m_bLoad; // 是否将插件加载到内存中
		std::list<VRString> m_strPlugins; // 所有的插件
		PluginLibList m_pluginLibs; // 导入动态库组件对象
		PluginInfoList m_pluginInfos; // 插件列表
		typedef std::list<IPluginManagerUI*> LstPluginManagerUI;
		LstPluginManagerUI m_lstPluginManagerUI;

		VR_AUTO_MUTEX
	};
}


#endif // _COMMANAGERUI_H_