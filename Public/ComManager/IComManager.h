/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理接口	                                                */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGER_H_
#define _ICOMMANAGER_H_


namespace VR_Soft
{
	class VRSOFT_DLL IComManager : public CSingleton<IComManager>
	{
	public:
		virtual ~IComManager() {}
		// 初始化 /* 在添加显示窗口之后再进行调用 */
		virtual void InitCom(void) = 0;
		// 添加插件
		virtual void InstallPlugin(IPlugin* pPlugin) = 0;
		// 卸载插件
		virtual void UnInstallPlugin(IPlugin* pPlugin) = 0;
		// 导入插件
		virtual void LoadPlugin(const VRString& strPluginName) = 0;
		// 卸载插件
		virtual void UnLoadPlugin(const VRString& strPluginName) = 0;
		// 注册工厂
		virtual void RegisterComManagerFactory(IComFactory* pFactory) = 0;
		// 删除工厂
		virtual void UnRegisterComManagerFactory(IComFactory* pFactory) = 0;
		// 获取系统日志
		virtual ILogManager* GetLogManager(void) const = 0;
		// 获取插件管理
		virtual IComInstanceMerator* GetConInstanceMerator(void) const = 0;
		// 写入日志
		virtual void WriteLogMsg(const VRString& strMsg, UINT uiCode = ERROR_OK ) = 0;
		// 获得模型管理
		virtual IEntityManager* GetEntityManager(void) const = 0;
		// 获得属性管理对象
		virtual IAttributeManager* GetAttributeManager(void) = 0;
		// 获得属性项对应工厂
		virtual IAttributeUIFactory* GetAttributeUiFactory(void) = 0;
		// 获得组件管理界面
		virtual IComManagerUI* GetComManagerUI(void) = 0;
		// 获得配置对象
		virtual IComManagerConfig* GetComManagerConfig(void) = 0;
		// 获得指令管理
		virtual IActionManager* GetActionManager(void) const = 0;

		// 系统循环运行
		virtual void LoopRun(void) = 0;
		// 设置是否采用本地模型
		virtual void EnableServer(bool bServer = false) = 0;
		// 获得是否采用本地服务器
		virtual bool IsService(void) const = 0;

	};

	// 采用简单工厂进行初始化
	EXTERN_CPP VRSOFT_DLL IComManager* CreateInstance(int argc, char *argv[]);
}

#endif // _ICOMMANAGER_H_