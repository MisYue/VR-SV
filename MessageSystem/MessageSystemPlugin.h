/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体模型消息系统插件类                                        */
/* 时间： 2015-08-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _MESSAGESYSTEMPLUGIN_H_
#define _MESSAGESYSTEMPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CMessageSystemPlugin : public IPlugin
	{
	public:
		explicit CMessageSystemPlugin(void);
		virtual ~CMessageSystemPlugin(void);

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

	// 注册插件
	REGISTER_VRSOFT_PLUGIN(CMessageSystemPlugin);
}


#endif // _MESSAGESYSTEMPLUGIN_H_