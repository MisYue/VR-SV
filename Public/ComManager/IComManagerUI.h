/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理界面接口                                              */
/* 时间： 2015-07-23                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGERUI_H_
#define _ICOMMANAGERUI_H_

namespace VR_Soft
{
	class IPluginManagerUI;

	class IComManagerUI
	{

	public: 
		enum LoadType
		{
			Default = 0x0001, // 默认加载 不能变更
			Loaded = 0x0002, // 已经加载
			UnLoad = 0x0004// 未加载
		};

		typedef struct PluginInfo_TYP
		{
			IPlugin* _pPlugin; // 插件指针
			int _loadType; // 扩展

			PluginInfo_TYP():_pPlugin(NULL), _loadType(UnLoad)
			{

			}

			PluginInfo_TYP(IPlugin* pPlugin):_pPlugin(pPlugin), _loadType(UnLoad)
			{

			}

			bool operator==(IPlugin* pPlugin)
			{
				return (pPlugin == _pPlugin);
			}

		}PluginInfo, *PTR_PluginInfo;

		typedef std::list<PluginInfo> PluginInfoList;

	public:
		// 析构函数
		virtual ~IComManagerUI() { }

		// 通过名称注册插件
		virtual void InstallPlugin(const VRString& strPluginName) = 0;
		// 通过名称卸载插件
		virtual void UnInstallPlugin(const VRString& strPluginName) = 0;
		// 注册窗口
		virtual void RegisterUI(IPluginManagerUI* pIPluginManagerUI) = 0;
		// 反注册窗口
		virtual void UnRegisterUI(IPluginManagerUI* pIPluginManagerUI) = 0;
	};
}

#endif