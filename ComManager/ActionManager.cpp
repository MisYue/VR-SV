#include "../../Public/VRSoft.h"
#include "DyLibManager.h"
#include "ActionManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_ACTION)(void);
	typedef void (*DLL_UNINSTANLL_ACTION)(void);
	////////////////////////////////////

	// ���캯��
	CActionManager::CActionManager(void)
		:IActionManager()
	{
	}

	// ��������
	CActionManager::~CActionManager(void)
	{
	}

	// ���ָ��
	void CActionManager::AddAction( IEntityBase* pIEnity, const VRString& strAciton)
	{
		// ���߳�ͬ��
		VR_MUTEX_AUTO

		ListActionFactories::iterator itor = m_listActionFactorues.find(strAciton);
		if (m_listActionFactorues.end() == itor)
		{
			ILogManager::GetInstance().SetLogMessage(strAciton + ":ָ���ȷ", ERROR_NOT_FIND);
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

	// �Ƴ�ָ��
	void CActionManager::RemoveAction(IEntityBase* pIEnity, const int index)
	{
		// ���߳�ͬ��
		VR_MUTEX_AUTO

		ListEntityActions::iterator itor = m_listEntityAcitons.find(pIEnity);
		if (m_listEntityAcitons.end() == itor)
		{
			ILogManager::GetInstance().SetLogMessage(pIEnity->GetName() + ":ģ����ָ��", ERROR_NOT_FIND);
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

	// ���ļ��м���ָ��dll�� 
	void CActionManager::LoadAction( void )
	{
		// �Ӿ���Ŀ¼����dll��̬��
		const VRString& strCurPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Action/";
		
		// ��ȡ��ǰĿ¼�����е��ļ�
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strCurPath, ".dll", files);

		// ����dll��
		Files::const_iterator cstItor = files.begin();
		while (files.end() != cstItor)
		{
			const VRString& strDll = strCurPath + *cstItor;
			LoadDll(strDll);

			++cstItor;
		}
		
	}

	// ����dll��
	void CActionManager::LoadDll( const VRString& strDllPath )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��·��
		ListActionDlls::const_iterator cstItor = m_listActionDlls.find(strDllPath);
		if (m_listActionDlls.end() != cstItor)
		{
			return;
		}

		// ���뵱ǰ��dll��
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strDllPath);

		try
		{
			DLL_INSTANLL_ACTION pDllInstanAction = (DLL_INSTANLL_ACTION)pLib->GetSymbol("DllInstallAction");
			if (NULL == pDllInstanAction)
			{
				ILogManager::GetInstance().SetLogMessage(strDllPath + "ָ�����ʧ��", ERROR_NOT_FIND);
				return;
			}

			// ���ز��
			m_listActionDlls.insert(ListActionDlls::value_type(strDllPath, pLib));

			// ���ز��
			pDllInstanAction();
		}
		catch (...)
		{
			ILogManager::GetInstance().SetLogMessage(strDllPath + "����ָ����", ERROR_NOT_COM);
		}
		
	}

	// ��ȡ���е�dllָ������
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

	// ��õ�ǰʵ���ָ��
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

	// �Ƴ�dll��
	void CActionManager::RemoveActionDll( const VRString& strDll )
	{
		// ���߳�ͬ��
		VR_MUTEX_AUTO

		// ��ѯ
		ListActionDlls::iterator itor = m_listActionDlls.find(strDll);
		if (m_listActionDlls.end() != itor)
		{
			try
			{
				DLL_UNINSTANLL_ACTION pDllUnInstanAction = (DLL_UNINSTANLL_ACTION)itor->second->GetSymbol("DllUnInstallPlugin");
				if (NULL == pDllUnInstanAction)
				{
					ILogManager::GetInstance().SetLogMessage(strDll + "ָ�����ʧ��", ERROR_NOT_FIND);
					return;
				}

				// ���ز��
				pDllUnInstanAction();
			}

			catch (...)
			{
				ILogManager::GetInstance().SetLogMessage(strDll + "����ָ����", ERROR_NOT_COM);
			}

			itor->second->Unload();
			m_listActionDlls.erase(itor);
		}
	}

	// ִ��ָ��
	void CActionManager::Execute( const CDateTime& dt )
	{
		// ���߳�ͬ��
		VR_MUTEX_AUTO

		for (ListAction::iterator itor = m_listSimAction.begin(); \
			m_listSimAction.end() != itor; )
		{
			IAction* pIAction = *itor;
			// �ж��Ƿ�ִ��
			if (pIAction->Executed(dt))
			{
				 itor = m_listSimAction.erase(itor);
				continue;
			}

			++itor;

			const CDateTime& actionDt = pIAction->GetDateTime();
			if (1 == dt.Compare(actionDt))
			{
				// ִ��Ч��
				pIAction->Execute(dt);
			}
		}
	}

	// ��ӹ���
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

	// �Ƴ�����
	void CActionManager::RemoveFactory( const VRString& strFactory )
	{
		// ��ѯ��ǰ�ĵ�
		ListActionFactories::iterator itor = m_listActionFactorues.find(strFactory);
		if (m_listActionFactorues.end() != itor)
		{
			VRSOFT_DELETE(itor->second);
			m_listActionFactorues.erase(itor);
		}

		// �Ƴ������ص�����ָ��
		ListEntityActions::iterator actionItor = m_listEntityAcitons.begin();
		int index = 0;
		while (m_listEntityAcitons.end() != actionItor)
		{
			RemoveAction(actionItor->first, index++);
		}
	}

	// ���ָ��
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

	// ��ʼ��
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
				// ��ӵ�������
				m_listSimAction.push_back(*itor);
				++itor;
			}	

			++actionItor;
		}	
	}

}
