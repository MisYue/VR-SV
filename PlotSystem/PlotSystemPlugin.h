/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘系统插件入口		                                        */
/* 时间： 2016-08-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PLOTSYSTEMPLUGIN_H_
#define _PLOTSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CPlotSystemPlugin : public IPlugin
	{
	public:
		// 构造函数
		explicit CPlotSystemPlugin(void);
		// 析构函数
		virtual ~CPlotSystemPlugin(void);

	public:
		// 获取插件名称
		virtual const VRString& GetPluginName(void) const;
		// 获得插件版本
		virtual const VRString GetPluginVersion(void) const ;
		// 获得插件描述
		virtual const VRString& GetPluginDiscribe(void) const;
		// 安装插件
		virtual void Install(void) ;
		// 初始化插件
		virtual void Initialise(void);
		// 清除插件
		virtual void Shutdown(void);
		// 卸载插件
		virtual void UnInstall(void);

	private:
		IComFactory* m_pIComFactory; // 组件工厂
	};

	// 注册渲染插件
	REGISTER_VRSOFT_PLUGIN(CPlotSystemPlugin, OSGRPLOT_DLL);
}


#endif // ! _PLOTSYSTEMPLUGIN_H_