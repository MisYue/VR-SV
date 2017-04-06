#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"

#include "EnvironmentManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_ENVIRONMENT)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_ENVIRONMENT)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	CEnvironmentManager::CEnvironmentManager(IEntityFactoryManager* pIEntityFactoryManager)
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{

	}


	CEnvironmentManager::~CEnvironmentManager(void)
	{
	}

	// ���ҵ�ǰ�ļ��¼��ز��
	void CEnvironmentManager::LoadAllElecDll(void)
	{
		// ��ȡ��������еĲ���ļ�
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Environment/";

		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strElecDllPath, "*.dll", files);

		// �������е��ļ�
		Files::const_iterator cstItor = files.begin();
		for (; files.end() != cstItor; ++cstItor)
		{
			LoadElecDll(strElecDllPath + (*cstItor));
		}
	}

	// ��ǰ��̬���Ƿ������
	bool CEnvironmentManager::IsLoaded(const VRString& strElecName)
	{
		ListEnvironPlugin::const_iterator cstItor = m_lstEnvironPlugins.find(strElecName);
		return (m_lstEnvironPlugins.end() != cstItor);
	}

	// ���ص���dll�ļ�
	void CEnvironmentManager::LoadElecDll(const VRString& strElecName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		if (IsLoaded(strElecName))
		{
			return ;
		}

		// �����ļ�
		CDyLib* pDyLib = new CDyLib(strElecName);
		if (NULL == pDyLib)
		{
			IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +" ʧ��", ERROR_MALLOC);
			return;
		}

		try
		{
			pDyLib->Load();
		}
		catch (...)
		{
			return;
		}

		// ������ں���
		DLL_INSTANLL_ENVIRONMENT pFunction = (DLL_INSTANLL_ENVIRONMENT)pDyLib->GetSymbol("InstallEnvironmentPlugin");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("���ػ������:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// ���뵽����
		m_lstEnvironPlugins[strElecName] = pDyLib;

		// ִ�к���
		pFunction(m_pIEntityFactoryManager);
	}

	// ж�ص���dll�ļ�
	void CEnvironmentManager::UnLoadElecDll(const VRString& strElecName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		if (!IsLoaded(strElecName))
		{
			return ;
		}

		ListEnvironPlugin::iterator itor = m_lstEnvironPlugins.find(strElecName);
		CDyLib* pDyLib = itor->second;
		if (NULL == pDyLib)
		{
			return;
		}

		// ������ں���
		DLL_UNINSTANLL_ENVIRONMENT pFunction = (DLL_UNINSTANLL_ENVIRONMENT)pDyLib->GetSymbol("UnInstallEnvironmentPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("���ػ������:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			m_lstEnvironPlugins.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_lstEnvironPlugins.erase(itor);
	}
}
