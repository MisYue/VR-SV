
#include <vector>
#include <list>
#include <algorithm>
#include "../../Public/VRSoft.h"

#include "DyLibManager.h"
#include "EntityManager.h"
#include "ComManagerUI.h"
#include "ComManagerConfig.h"
#include "ConfigManager.h"
#include "LogManager.h"
#include "ComInstanceEnumerator.h"
#include "MessageManager.h"
#include "ComManager.h"
#include "Inpute.h"
#include "SimManager.h"
#include "Timer.h"
#include "EntityThread.h"
#include "ActionManager.h"
#include "AttributeManager.h"
#include "AttributeUIFactory.h"
#include "PathManager.h"

#ifdef _DEBUG

#endif // _DEBUG

namespace VR_Soft
{
	CComManager::CComManager(int argc, char *argv[]):
			IComManager(),
			m_pDyLibManager(NULL),
			m_pIComMangerUI(NULL),
			m_pIComManagerConfig(NULL),
			m_pIMessageManager(NULL),
			m_pIEntityManager(NULL),
			m_pIAttributeManager(NULL),
			m_pIAttrbiteUIFactory(NULL),
			m_pISimManager(NULL),
			m_pIActionManager(NULL),
			m_pITimer(NULL),
			m_pLogMananger(NULL),
			m_bServer(false),
			m_pConnfigManager(NULL),
			m_pInpute(NULL),
			m_pEntityThread(NULL)
		{
			// 获得路径
			const VRString str = argv[0];
			Init(str);

			// 创建日志系统
			CreateLogSystem();
		}

		CComManager::~CComManager()
		{
			// 写入日志 程序结束
			WriteLogMsg("程序正常退出");

			if (NULL != m_pEntityThread)
			{
				m_pEntityThread->Join();
			}

			VRSOFT_DELETE(m_pEntityThread);

			// 卸载日志系统
			//UnLoadLogSystem();
			VRSOFT_DELETE(m_pPathManager);
			VRSOFT_DELETE(m_pIAttrbiteUIFactory);
			VRSOFT_DELETE(m_pIActionManager);
			VRSOFT_DELETE(m_pIEntityManager);
			VRSOFT_DELETE(m_pIAttributeManager);
			VRSOFT_DELETE(m_pIComMangerUI);
			VRSOFT_DELETE(m_pITimer);
			VRSOFT_DELETE(m_pISimManager);
			VRSOFT_DELETE(m_pDyLibManager);
			VRSOFT_DELETE(m_pComInstance);
			VRSOFT_DELETE(m_pIComManagerConfig);
			VRSOFT_DELETE(m_pConnfigManager);
			VRSOFT_DELETE(m_pIMessageManager);
			VRSOFT_DELETE(m_pLogMananger);
			VRSOFT_DELETE(m_pInpute);
		}

		// 初始化
		void CComManager::Init(const VRString& strPath)
		{
			m_pLogMananger = new CLogManager;
			// 导入系统日志
			m_pDyLibManager = new CDyLibManager;
			// 导入插件管理系统
			m_pComInstance = new CComInstanceEnumerator;	
			// 创建管理界面
			m_pIComMangerUI = new CComManagerUI;
			// 创建配置管理
			m_pIComManagerConfig = new CComManagerConfig(strPath);
			m_pConnfigManager = new CConfigManager;

			// 事件
			m_pInpute = new CInpute;

			// 路径管理
			m_pPathManager = new CPathManager;
			// 消息系统
			m_pIMessageManager = new CMessageManager;
			// 实体系统
			m_pIEntityManager = new CEntityManager;
			m_pIEntityManager->Init();
			// 时间计时器
			m_pITimer = new CTimer;
			// 仿真管理
			m_pISimManager = new CSimManager;
			// 指令管理
			m_pIActionManager = new CActionManager;
			// 属性管理
			m_pIAttributeManager = new CAttributeManager;
			// 属性UI工厂管理
			m_pIAttrbiteUIFactory = new CAttributeUIFactory;
			// 导入所有的指令系统
			m_pIActionManager->LoadAction();
		}

		// 创建系统日志
		void CComManager::CreateLogSystem(void)
		{
			const VRString& strPath = m_pIComManagerConfig->GetCurPath();

			//	LoadPlugin(strPath + "/LogSystem.dll");

			//		IComManagerFace* pIComFace = m_pComInstance->GetComInstance(INSTANCE_NAME_LOGSYSTEM);
			ILogManager* pILogManager = GetLogManager();
			if (NULL != pILogManager)
			{
				pILogManager->CreateLog(strPath + "/VRLog.log", true, true, true);
			}

			// 加载时间组件
			//	LoadPlugin(strPath + "/TimeSystem.dll");
			// 加载渲染组件
			//	LoadPlugin(strPath + "/RenderSystem.dll");
			// 加载模型管理组件
			//	LoadPlugin(strPath + "/EntitySystem.dll");
			// 加载地组件
			//	LoadPlugin(strPath + "/EarthSystem.dll");
			// 加载消息组件
			//	LoadPlugin(strPath + "/MessageSystem.dll");

			// 配置组件
			m_pIComMangerUI->ConfigPlugins();
		}

		// 卸载日志系统
		void CComManager::UnLoadLogSystem(void)
		{
			const VRString& strPath = m_pIComManagerConfig->GetCurPath();

			UnLoadPlugin(strPath + "/EntitySystem.dll");

		}

		// 更新模型 判断如果当前的仿真组件设置的不是服务器则调用内部刷新
		void CComManager::UpdateEntity(void)
		{
			//// 获得获得仿真插件
			//if (NULL == m_pISimManager)
			//{
			//	m_pISimManager = dynamic_cast<ISimManager*>(m_pComInstance->GetComInstance(INSTANCE_NAME_SIMSYSTEM));
			//}

			//// 进行锁定判断
			//if (NULL == m_pISimManager || !m_pISimManager->IsServer())
			//{
			//	// 进行消息循环处理
			//	IMessageManager* pIMessageManager = GetMessageManager();
			//	if (NULL != pIMessageManager)
			//	{
			//		pIMessageManager->DispatchDelayedMessages();
			//	}

			//	// 对系统模型进行更新
			//	IEntityComposite* pIEntityComposite = GetEntityComposite();
			//	if (NULL != pIEntityComposite)
			//	{
			//		pIEntityComposite->EntityUpdate(0.0);
			//	}

			//}
		}

		// 写入日志
		void CComManager::WriteLogMsg(const VRString& strMsg, UINT uiCode)
		{
			// 获取系统日志
			ILogManager* pILogManager = GetLogManager();
			if (NULL == pILogManager)
			{
				return;
			}

			// 写入日志
			pILogManager->SetLogMessage(strMsg, uiCode);
		}

		// 获得模型管理
		IEntityManager* CComManager::GetEntityManager(void) const
		{
			return (m_pIEntityManager);
		}

		// 获得消息系统管理
		IMessageManager* CComManager::GetMessageManager(void) const
		{
			return (IMessageManager::GetInstancePtr());
		}

		// 获得属性项对应工厂
		IAttributeUIFactory* CComManager::GetAttributeUiFactory(void) 
		{
			return (m_pIAttrbiteUIFactory);
		}

		// 获得属性管理对象
		IAttributeManager* CComManager::GetAttributeManager(void)
		{
			return (m_pIAttributeManager);
		}

		// 初始化
		void CComManager::InitCom(void)
		{
			// 通过配置对象初始化系统
			m_pIComManagerConfig->Init();
		}

		// 添加插件
		void CComManager::InstallPlugin(IPlugin* pPlugin)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("加载插件失败");
				return;
			}
			m_pIComMangerUI->InstallPlugin(pPlugin);
		}

		// 卸载插件
		void CComManager::UnInstallPlugin(IPlugin* pPlugin)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("加载插件失败");
				return;
			}

			m_pIComMangerUI->UnInstallPlugin(pPlugin);
		}

		// 导入插件
		void CComManager::LoadPlugin(const VRString& strPluginName)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("加载插件失败");
				return;
			}
			m_pIComMangerUI->LoadPlugin(strPluginName);

		}

		// 卸载插件
		void CComManager::UnLoadPlugin(const VRString& strPluginName)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("加载插件失败");
				return;
			}
			m_pIComMangerUI->UnLoadPlugin(strPluginName);
		}

		// 注册工厂
		void CComManager::RegisterComManagerFactory(IComFactory* pFactory)
		{
			// 添加工厂 并且初始化
			m_pComInstance->AddFactory(pFactory);
		}

		// 删除工厂
		void CComManager::UnRegisterComManagerFactory(IComFactory* pFactory)
		{
			m_pComInstance->RemoveFactory(pFactory);
		}

		// 获取系统日志
		ILogManager* CComManager::GetLogManager(void) const
		{
			return (m_pLogMananger);
		}

		// 获取插件管理
		IComInstanceMerator* CComManager::GetConInstanceMerator(void) const
		{
			return (m_pComInstance);
		}

		//// 获取渲染对象
		//IRenderManager* CComManager::GetRenderManager(void) const
		//{
		//	if (NULL != m_pIRenderManager)
		//	{
		//		return (m_pIRenderManager);
		//	}

		//
		//	m_pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		//	return (m_pIRenderManager);
		//}

		//ITimeManager* CComManager::GetTimerManager(void) const
		//{
		//	if (NULL != m_pITimeManager)
		//	{
		//		return (m_pITimeManager);
		//	}

		//	m_pITimeManager = CComManagerImp::GetComponent<ITimeManager>(INSTANCE_NAME_TIMESYSTEM);
		//	return (m_pITimeManager);
		//}

		// 注册管理界面
		IComManagerUI* CComManager::GetComManagerUI(void)
		{
			return (m_pIComMangerUI);
			/*pIComManagerUI->InitUI();*/
		}

		// 获得配置对象
		IComManagerConfig* CComManager::GetComManagerConfig(void)
		{
			return (m_pIComManagerConfig);
		}

		// 系统循环运行
		void CComManager::LoopRun(void)
		{
			// 更新模型
			// UpdateEntity();
			//// 处理每一帧更新
			//IRenderManager* pIRenderManager = GetRenderManager();
			//if (NULL != pIRenderManager)
			//{
			//	// 获得视图管理
			//	IViewManager* pIViewManager = pIRenderManager->GetViewManager();
			//	pIViewManager->Flush();
			//}
		}

		// 设置是否采用本地模型
		void CComManager::EnableServer(bool bServer /*= false*/)
		{
			if (NULL == m_pEntityThread)
			{
				m_pEntityThread = new CEntityThread;
			}

			m_pEntityThread->Start();
			m_bServer = bServer;
		}

		// 获得是否采用本地服务器
		bool CComManager::IsService(void) const
		{
			return (m_bServer);
		}

		// 获得指令管理
		IActionManager* CComManager::GetActionManager( void ) const
		{
			return (m_pIActionManager);
		}

		// 创建工厂
		IComManager* CreateInstance(int argc, char *argv[])
		{
			return new CComManager(argc, argv);
		}
}
