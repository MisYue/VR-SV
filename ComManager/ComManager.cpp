
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
			// ���·��
			const VRString str = argv[0];
			Init(str);

			// ������־ϵͳ
			CreateLogSystem();
		}

		CComManager::~CComManager()
		{
			// д����־ �������
			WriteLogMsg("���������˳�");

			if (NULL != m_pEntityThread)
			{
				m_pEntityThread->Join();
			}

			VRSOFT_DELETE(m_pEntityThread);

			// ж����־ϵͳ
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

		// ��ʼ��
		void CComManager::Init(const VRString& strPath)
		{
			m_pLogMananger = new CLogManager;
			// ����ϵͳ��־
			m_pDyLibManager = new CDyLibManager;
			// ����������ϵͳ
			m_pComInstance = new CComInstanceEnumerator;	
			// �����������
			m_pIComMangerUI = new CComManagerUI;
			// �������ù���
			m_pIComManagerConfig = new CComManagerConfig(strPath);
			m_pConnfigManager = new CConfigManager;

			// �¼�
			m_pInpute = new CInpute;

			// ·������
			m_pPathManager = new CPathManager;
			// ��Ϣϵͳ
			m_pIMessageManager = new CMessageManager;
			// ʵ��ϵͳ
			m_pIEntityManager = new CEntityManager;
			m_pIEntityManager->Init();
			// ʱ���ʱ��
			m_pITimer = new CTimer;
			// �������
			m_pISimManager = new CSimManager;
			// ָ�����
			m_pIActionManager = new CActionManager;
			// ���Թ���
			m_pIAttributeManager = new CAttributeManager;
			// ����UI��������
			m_pIAttrbiteUIFactory = new CAttributeUIFactory;
			// �������е�ָ��ϵͳ
			m_pIActionManager->LoadAction();
		}

		// ����ϵͳ��־
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

			// ����ʱ�����
			//	LoadPlugin(strPath + "/TimeSystem.dll");
			// ������Ⱦ���
			//	LoadPlugin(strPath + "/RenderSystem.dll");
			// ����ģ�͹������
			//	LoadPlugin(strPath + "/EntitySystem.dll");
			// ���ص����
			//	LoadPlugin(strPath + "/EarthSystem.dll");
			// ������Ϣ���
			//	LoadPlugin(strPath + "/MessageSystem.dll");

			// �������
			m_pIComMangerUI->ConfigPlugins();
		}

		// ж����־ϵͳ
		void CComManager::UnLoadLogSystem(void)
		{
			const VRString& strPath = m_pIComManagerConfig->GetCurPath();

			UnLoadPlugin(strPath + "/EntitySystem.dll");

		}

		// ����ģ�� �ж������ǰ�ķ���������õĲ��Ƿ�����������ڲ�ˢ��
		void CComManager::UpdateEntity(void)
		{
			//// ��û�÷�����
			//if (NULL == m_pISimManager)
			//{
			//	m_pISimManager = dynamic_cast<ISimManager*>(m_pComInstance->GetComInstance(INSTANCE_NAME_SIMSYSTEM));
			//}

			//// ���������ж�
			//if (NULL == m_pISimManager || !m_pISimManager->IsServer())
			//{
			//	// ������Ϣѭ������
			//	IMessageManager* pIMessageManager = GetMessageManager();
			//	if (NULL != pIMessageManager)
			//	{
			//		pIMessageManager->DispatchDelayedMessages();
			//	}

			//	// ��ϵͳģ�ͽ��и���
			//	IEntityComposite* pIEntityComposite = GetEntityComposite();
			//	if (NULL != pIEntityComposite)
			//	{
			//		pIEntityComposite->EntityUpdate(0.0);
			//	}

			//}
		}

		// д����־
		void CComManager::WriteLogMsg(const VRString& strMsg, UINT uiCode)
		{
			// ��ȡϵͳ��־
			ILogManager* pILogManager = GetLogManager();
			if (NULL == pILogManager)
			{
				return;
			}

			// д����־
			pILogManager->SetLogMessage(strMsg, uiCode);
		}

		// ���ģ�͹���
		IEntityManager* CComManager::GetEntityManager(void) const
		{
			return (m_pIEntityManager);
		}

		// �����Ϣϵͳ����
		IMessageManager* CComManager::GetMessageManager(void) const
		{
			return (IMessageManager::GetInstancePtr());
		}

		// ����������Ӧ����
		IAttributeUIFactory* CComManager::GetAttributeUiFactory(void) 
		{
			return (m_pIAttrbiteUIFactory);
		}

		// ������Թ������
		IAttributeManager* CComManager::GetAttributeManager(void)
		{
			return (m_pIAttributeManager);
		}

		// ��ʼ��
		void CComManager::InitCom(void)
		{
			// ͨ�����ö����ʼ��ϵͳ
			m_pIComManagerConfig->Init();
		}

		// ��Ӳ��
		void CComManager::InstallPlugin(IPlugin* pPlugin)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("���ز��ʧ��");
				return;
			}
			m_pIComMangerUI->InstallPlugin(pPlugin);
		}

		// ж�ز��
		void CComManager::UnInstallPlugin(IPlugin* pPlugin)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("���ز��ʧ��");
				return;
			}

			m_pIComMangerUI->UnInstallPlugin(pPlugin);
		}

		// ������
		void CComManager::LoadPlugin(const VRString& strPluginName)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("���ز��ʧ��");
				return;
			}
			m_pIComMangerUI->LoadPlugin(strPluginName);

		}

		// ж�ز��
		void CComManager::UnLoadPlugin(const VRString& strPluginName)
		{
			if (NULL == m_pIComMangerUI)
			{

				WriteLogMsg("���ز��ʧ��");
				return;
			}
			m_pIComMangerUI->UnLoadPlugin(strPluginName);
		}

		// ע�Ṥ��
		void CComManager::RegisterComManagerFactory(IComFactory* pFactory)
		{
			// ��ӹ��� ���ҳ�ʼ��
			m_pComInstance->AddFactory(pFactory);
		}

		// ɾ������
		void CComManager::UnRegisterComManagerFactory(IComFactory* pFactory)
		{
			m_pComInstance->RemoveFactory(pFactory);
		}

		// ��ȡϵͳ��־
		ILogManager* CComManager::GetLogManager(void) const
		{
			return (m_pLogMananger);
		}

		// ��ȡ�������
		IComInstanceMerator* CComManager::GetConInstanceMerator(void) const
		{
			return (m_pComInstance);
		}

		//// ��ȡ��Ⱦ����
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

		// ע��������
		IComManagerUI* CComManager::GetComManagerUI(void)
		{
			return (m_pIComMangerUI);
			/*pIComManagerUI->InitUI();*/
		}

		// ������ö���
		IComManagerConfig* CComManager::GetComManagerConfig(void)
		{
			return (m_pIComManagerConfig);
		}

		// ϵͳѭ������
		void CComManager::LoopRun(void)
		{
			// ����ģ��
			// UpdateEntity();
			//// ����ÿһ֡����
			//IRenderManager* pIRenderManager = GetRenderManager();
			//if (NULL != pIRenderManager)
			//{
			//	// �����ͼ����
			//	IViewManager* pIViewManager = pIRenderManager->GetViewManager();
			//	pIViewManager->Flush();
			//}
		}

		// �����Ƿ���ñ���ģ��
		void CComManager::EnableServer(bool bServer /*= false*/)
		{
			if (NULL == m_pEntityThread)
			{
				m_pEntityThread = new CEntityThread;
			}

			m_pEntityThread->Start();
			m_bServer = bServer;
		}

		// ����Ƿ���ñ��ط�����
		bool CComManager::IsService(void) const
		{
			return (m_bServer);
		}

		// ���ָ�����
		IActionManager* CComManager::GetActionManager( void ) const
		{
			return (m_pIActionManager);
		}

		// ��������
		IComManager* CreateInstance(int argc, char *argv[])
		{
			return new CComManager(argc, argv);
		}
}
