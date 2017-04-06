/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染系统插件入口		                                        */
/* 时间： 2015-05-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _RENDERSYSTEMPLUGIN_H_
#define _RENDERSYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CRenderSystemPlugin : public IPlugin
	{
	public:
		// 构造函数
		explicit CRenderSystemPlugin(void);
		// 析构函数
		virtual ~CRenderSystemPlugin(void);

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
	REGISTER_VRSOFT_PLUGIN(CRenderSystemPlugin, OSGRENDER_DLL);

}

#endif


