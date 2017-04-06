#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectPluginManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_ELECT)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_ELECT)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	CElectPluginManager::CElectPluginManager(IEntityFactoryManager* pIEntityFactoryManager) 
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{
	}
	
	CElectPluginManager::~CElectPluginManager(void)
	{
	}

	// ���ҵ�ǰ�ļ��¼��ز��
	void CElectPluginManager::LoadAllElecDll(void)
	{
		// ��ȡ��������еĲ���ļ�
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Elect/";

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
	bool CElectPluginManager::IsLoaded(const VRString& strElecName)
	{
		MapElectPlugin::const_iterator cstItor = m_mapElectPlugin.find(strElecName);
		return (m_mapElectPlugin.end() != cstItor);
	}

	// ���ص���dll�ļ�
	void CElectPluginManager::LoadElecDll(const VRString& strElecName)
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
		DLL_INSTANLL_ELECT pFunction = (DLL_INSTANLL_ELECT)pDyLib->GetSymbol("InstallElectPlugin");
		
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// ���뵽����
		m_mapElectPlugin[strElecName] = pDyLib;

		// ִ�к���
		pFunction(m_pIEntityFactoryManager);
	}

	// ж�ص���dll�ļ�
	void CElectPluginManager::UnLoadElecDll(const VRString& strElecName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		if (!IsLoaded(strElecName))
		{
			return ;
		}

		MapElectPlugin::iterator itor = m_mapElectPlugin.find(strElecName);
		CDyLib* pDyLib = itor->second;
		if (NULL == pDyLib)
		{
			return;
		}

		// ������ں���
		DLL_UNINSTANLL_ELECT pFunction = (DLL_UNINSTANLL_ELECT)pDyLib->GetSymbol("UnInstallElectPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			m_mapElectPlugin.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_mapElectPlugin.erase(itor);
	}
}

