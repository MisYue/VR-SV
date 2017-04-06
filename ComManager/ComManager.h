/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理实现类                                                */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _COMMANAGER_H_
#define _COMMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CConfigManager;
	class CComInstanceEnumerator;
	class CInpute;
	class CEntityThread;
	class CPathManager;

	class CComManager : public IComManager
	{
	public:
		explicit CComManager(int argc, char *argv[]);
		virtual ~CComManager();

	public:
		// 初始化
		virtual void InitCom(void);
		// 添加插件
		virtual void InstallPlugin(IPlugin* pPlugin);
		// 卸载插件
		virtual void UnInstallPlugin(IPlugin* pPlugin);
		// 导入插件
		virtual void LoadPlugin(const VRString& strPluginName);
		// 卸载插件
		virtual void UnLoadPlugin(const VRString& strPluginName);
		// 注册工厂
		virtual void RegisterComManagerFactory(IComFactory* pFactory);
		// 删除工厂
		virtual void UnRegisterComManagerFactory(IComFactory* pFactory);
		// 获取系统日志
		virtual ILogManager* GetLogManager(void) const;
		// 获取插件管理
		virtual IComInstanceMerator* GetConInstanceMerator(void) const;
		// 写入日志
		virtual void WriteLogMsg(const VRString& strMsg, UINT uiCode = ERROR_OK);
		// 获得模型管理
		virtual IEntityManager* GetEntityManager(void) const;
		// 获得消息系统管理
		virtual IMessageManager* GetMessageManager(void) const;
		// 获得属性项对应工厂
		virtual IAttributeUIFactory* GetAttributeUiFactory(void);
		// 获得属性管理对象
		virtual IAttributeManager* GetAttributeManager(void);
		// 获得组件管理界面
		virtual IComManagerUI* GetComManagerUI(void) ;
		// 获得配置对象
		virtual IComManagerConfig* GetComManagerConfig(void);
		// 获得指令管理
		virtual IActionManager* GetActionManager(void) const;

		// 系统循环运行
		virtual void LoopRun(void);
		// 设置是否采用本地模型
		virtual void EnableServer(bool bServer = false);
		// 获得是否采用本地服务器
		virtual bool IsService(void) const ;

	protected:
		// 初始化
		void Init(const VRString& strPath);
		// 创建系统日志
		void CreateLogSystem(void);
		// 卸载日志系统
		void UnLoadLogSystem(void);

	protected:
		// 更新模型 判断如果当前的仿真组件设置的不是服务器则调用内部刷新
		void UpdateEntity(void);

	private:
		CDyLibManager* m_pDyLibManager; // 动态库管理
		CComInstanceEnumerator* m_pComInstance; // 插件实例管理
		CComManagerUI* m_pIComMangerUI; // 插件管理界面接口
		IComManagerConfig* m_pIComManagerConfig; // 配置组件

		// 系统核心插件 不用每次都去查找
	private:
		mutable IMessageManager*	m_pIMessageManager; // 消息系统
		mutable CEntityManager*		m_pIEntityManager; // 实体管理系统
		IAttributeManager*			m_pIAttributeManager; // 属性管理
		IAttributeUIFactory*		m_pIAttrbiteUIFactory; // 属性工厂管理
		ISimManager* m_pISimManager; // 仿真管理
		IActionManager* m_pIActionManager; // 指令管理
		ITimer* m_pITimer; // 计时器
		mutable CLogManager*		m_pLogMananger; // 日志系统
		bool m_bServer; // 是否采用本地服务器
		CConfigManager* m_pConnfigManager; // 配置管理中心
		CInpute* m_pInpute; // 输入设备
		CEntityThread* m_pEntityThread; // 实体更新类
		CPathManager* m_pPathManager; // 路径管理
	};
}


#endif // _COMMANAGER_H_
