/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  插件接口，采用外观模式                                        */
/* 时间： 2015-05-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#pragma once

namespace VR_Soft
{
	class IComManager;

	class VRSOFT_DLL IPlugin
	{
	public:
		// 析构函数
		virtual ~IPlugin() { }
		// 获取插件名称
		virtual const VRString& GetPluginName(void) const = 0;
		// 获得插件版本
		virtual const VRString GetPluginVersion(void) const = 0;
		// 获得插件描述
		virtual const VRString& GetPluginDiscribe(void) const = 0;
		// 安装插件
		virtual void Install(void) = 0;
		// 初始化插件
		virtual void Initialise(void) = 0;
		// 清除插件
		virtual void Shutdown(void) = 0;
		// 卸载插件
		virtual void UnInstall(void) = 0;
	};

	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllInstallPlugin(IComManager* pComManager);	

	//// 卸载插件接口函数
	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllUnInstallPlugin(IComManager* pComManager);
	// 注册插件宏
#define REGISTER_VRSOFT_PLUGIN(classname, export_style) \
	IPlugin* pPlugin = NULL;\
	EXTERN_CPP export_style void DllInstallPlugin(void) {\
	pPlugin = new classname; \
	IComManager::GetInstance().InstallPlugin(pPlugin);\
	}\
	EXTERN_CPP export_style void DllUnInstallPlugin(void){ \
	IComManager::GetInstance().UnInstallPlugin(pPlugin); VRSOFT_DELETE(pPlugin);\
	}
}

#endif // _PLUGIN_H_