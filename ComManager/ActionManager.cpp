#include "../../Public/VRSoft.h"
#include "DyLibManager.h"
#include "ActionManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// 注册回调函数
	typedef void (*DLL_INSTANLL_ACTION)(void);
	typedef void (*DLL_UNINSTANLL_ACTION)(void);
	////////////////////////////////////

	// 构造函数
	CActionManager::CActionManager(void)
		:IActionManager()
	{
	}

	// 析构函数
	CActionManager::~CActionManager(void)
	{
	}

	// 添加指令
	void CActionManager::AddAction( IEntityBase* pIEnity, const VRString& strAciton)
	{
		// 多线程同步
		VR_MUTEX_AUTO

		ListActionFactories::iterator itor = m_listActionFactorues.find(strAciton);
		if (m_listActionFactorues.end() == itor)
		{
			ILogManager::GetInstance().SetLogMessage(strAciton + ":指令不正确", ERROR_NOT_FIND);
			return ;
		}

		IActionFactory* pIActionFactory = itor->second;

		IAction* pIAction = pIActionFactory->CreateInstance();
		pIAction->SetEntity(pIEnity);
		pIAction->SetName(pIActionFactory->GetName());

		ListEntityActions::iterator actionItor = m_listEntityAcitons.find(pIEnity);
		if (m_listEntityAcitons.end() == actionItor)
		{
			ListAction listAction;
			listAction.push_back(pIAction);
			m_listEntityAcitons.insert(ListEntityActions::value_type(pIEnity, listAction));
		}
		else
		{
			ListAction& listAction = actionItor->second;
			listAction.push_back(pIAction);
		}

		m_listSimAction.push_back(pIAction);

	}

	// 移除指令
	void CActionManager::RemoveAction(IEntityBase* pIEnity, const int index)
	{
		// 多线程同步
		VR_MUTEX_AUTO

		ListEntityActions::iterator itor = m_listEntityAcitons.find(pIEnity);
		if (m_listEntityAcitons.end() == itor)
		{
			ILogManager::GetInstance().SetLogMessage(pIEnity->GetName() + ":模型无指令", ERROR_NOT_FIND);
			return ;
		}

		ListAction& listAction = itor->second;
		ListAction::iterator actionItor = listAction.begin();
		
		int i = 0;
		while (i++ < index && listAction.end() != actionItor)
		{
			++actionItor;
		}

		if (listAction.end() != actionItor)
		{
			ListAction::iterator itor = std::find(m_listSimAction.begin(), m_listSimAction.end(), *actionItor);
			m_listSimAction.erase(itor);


			VRSOFT_DELETE(*actionItor);
			listAction.erase(actionItor);
		}

	}

	// 从文件中加载指令dll库 
	void CActionManager::LoadAction( void )
	{
		// 从具体目录加载dll动态库
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Action/";
		
		// 获取当前目录下所有的文件
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".dll", files);

		// 加载dll库
		Files::const_iterator cstItor = files.begin();
		while (files.end() != cstItor)
		{
			const VRString& strDll = strCurPath + *cstItor;
			LoadDll(strDll);

			++cstItor;
		}
		
	}

	// 导入dll库
	void CActionManager::LoadDll( const VRString& strDllPath )
	{
		// 查询是否存在当前的路径
		ListActionDlls::const_iterator cstItor = m_listActionDlls.find(strDllPath);
		if (m_listActionDlls.end() != cstItor)
		{
			return;
		}

		// 加入当前的dll库
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strDllPath);

		try
		{
			DLL_INSTANLL_ACTION pDllInstanAction = (DLL_INSTANLL_ACTION)pLib->GetSymbol("DllInstallAction");
			if (NULL == pDllInstanAction)
			{
				ILogManager::GetInstance().SetLogMessage(strDllPath + "指令加载失败", ERROR_NOT_FIND);
				return;
			}

			// 加载插件
			m_listActionDlls.insert(ListActionDlls::value_type(strDllPath, pLib));

			// 加载插件
			pDllInstanAction();
		}
		catch (...)
		{
			ILogManager::GetInstance().SetLogMessage(strDllPath + "不是指令插件", ERROR_NOT_COM);
		}
		
	}

	// 获取所有的dll指令名称
	ListString CActionManager::GetAllActionDll( void ) const
	{
		ListString listString;

		ListActionFactories::const_iterator cstItor = m_listActionFactorues.begin();
		while (m_listActionFactorues.end() != cstItor)
		{
			const IActionFactory* pIActionFactory = cstItor->second;
			listString.push_back(pIActionFactory->GetName());
			++cstItor;
		}

		return (listString);
	}

	// 获得当前实体的指令
	VR_Soft::ListString CActionManager::GetAllActionDll( IEntityBase* pIEntity ) const
	{
		ListString listString;

		ListEntityActions::const_iterator cstItor = m_listEntityAcitons.find(pIEntity);
		if (m_listEntityAcitons.end() == cstItor)
		{
			return (listString);
		}

		const ListAction& listAction = cstItor->second;
		ListAction::const_iterator actionCstItor = listAction.begin();
		while (listAction.end() != actionCstItor)
		{
			const IAction* pIAction = *actionCstItor;
			listString.push_back(pIAction->GetName());
			++actionCstItor;
		}

		return (listString);
	}

	// 移除dll库
	void CActionManager::RemoveActionDll( const VRString& strDll )
	{
		// 多线程同步
		VR_MUTEX_AUTO

		// 查询
		ListActionDlls::iterator itor = m_listActionDlls.find(strDll);
		if (m_listActionDlls.end() != itor)
		{
			try
			{
				DLL_UNINSTANLL_ACTION pDllUnInstanAction = (DLL_UNINSTANLL_ACTION)itor->second->GetSymbol("DllUnInstallPlugin");
				if (NULL == pDllUnInstanAction)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "指令加载失败", ERROR_NOT_FIND);
					return;
				}

				// 加载插件
				pDllUnInstanAction();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "不是指令插件", ERROR_NOT_COM);
			}

			itor->second->Unload();
			m_listActionDlls.erase(itor);
		}
	}

	// 执行指令
	void CActionManager::Execute( const CDateTime& dt )
	{
		// 多线程同步
		VR_MUTEX_AUTO

		for (ListAction::iterator itor = m_listSimAction.begin(); \
			m_listSimAction.end() != itor; )
		{
			IAction* pIAction = *itor;
			// 判断是否执行
			if (pIAction->Executed(dt))
			{
				 itor = m_listSimAction.erase(itor);
				continue;
			}

			++itor;

			const CDateTime& actionDt = pIAction->GetDateTime();
			if (1 == dt.Compare(actionDt))
			{
				// 执行效果
				pIAction->Execute(dt);
			}
		}
	}

	// 添加工厂
	void CActionManager::AddFactory( IActionFactory* pIActionFactory )
	{
		const VRString& strName = pIActionFactory->GetName();
		ListActionFactories::const_iterator cstItor = m_listActionFactorues.find(strName);
		if (m_listActionFactorues.end() != cstItor)
		{
			return;
		}

		m_listActionFactorues.insert(ListActionFactories::value_type(strName, pIActionFactory));
	}

	// 移除工厂
	void CActionManager::RemoveFactory( const VRString& strFactory )
	{
		// 查询当前的的
		ListActionFactories::iterator itor = m_listActionFactorues.find(strFactory);
		if (m_listActionFactorues.end() != itor)
		{
			VRSOFT_DELETE(itor->second);
			m_listActionFactorues.erase(itor);
		}

		// 移除组件相关的所有指令
		ListEntityActions::iterator actionItor = m_listEntityAcitons.begin();
		int index = 0;
		while (m_listEntityAcitons.end() != actionItor)
		{
			RemoveAction(actionItor->first, index++);
		}
	}

	// 获得指令
	IAction* CActionManager::GetAction( IEntityBase* pIEntity, const int index ) const
	{
		ListEntityActions::const_iterator cstItor = m_listEntityAcitons.find(pIEntity);
		if (m_listEntityAcitons.end() == cstItor)
		{
			return (NULL);
		}

		const ListAction& listAction = cstItor->second;
		ListAction::const_iterator actionItor = listAction.begin();

		int i = 0;
		while (i++ < index && listAction.end() != actionItor)
		{
			++actionItor;
		}

		if (listAction.end() != actionItor)
		{
			return (*actionItor);
		}

		return (NULL);
	}

	// 初始化
	void CActionManager::Init( void )
	{
		m_listSimAction.clear();

		ListEntityActions::iterator actionItor = m_listEntityAcitons.begin();
		while (m_listEntityAcitons.end() != actionItor)
		{
			ListAction& listAcion = actionItor->second;
			ListAction::iterator itor = listAcion.begin();
			while(listAcion.end() != itor)
			{
				// 添加到仿真中
				m_listSimAction.push_back(*itor);
				++itor;
			}	

			++actionItor;
		}	
	}

}
