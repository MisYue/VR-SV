#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"

#include "SatelliteManager.h"
#include "SatelliteEntityBuilder.h"

namespace VR_Soft
{
	CSatelliteManager::CSatelliteManager(void)
	{
	}


	CSatelliteManager::~CSatelliteManager(void)
	{
		// ע��
		IEntityFactoryManager::GetInstance().UnRegisterFactory("����");
	}

	// ���ҵ�ǰ�ļ��¼��ز��
	void CSatelliteManager::LoadAllElecDll(void)
	{
		//// ��ȡ��������еĲ���ļ�
		//const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Satellite/";

		//typedef std::vector<VRString> Files;
		//Files files;
		//CFileOperetor::GetFilesInPath(strElecDllPath, "*.dll", files);

		//// �������е��ļ�
		//Files::const_iterator cstItor = files.begin();
		//for (; files.end() != cstItor; ++cstItor)
		//{
		//	LoadElecDll(strElecDllPath + (*cstItor));
		//}

		// ע��ʵ��
		IEntityFactoryManager::GetInstance().RegisterFactory(CREATE_BASEENTITY_FACTORY(CSatelliteEntityBuilder));
		// ���ʵ��
		//m_pIEntityFactoryManager->RegisterFactory(CREATE_BASEENTITY_FACTORY(CSatelliteEntityBuilder));
	}

	// ��ǰ��̬���Ƿ������
	bool CSatelliteManager::IsLoaded(const VRString& strElecName)
	{
		/*ListSatallitePlugin::const_iterator cstItor = m_lstSatellitePlugin.find(strElecName);
		return (m_lstSatellitePlugin.end() != cstItor);*/

		return (true);
	}

	// ���ص���dll�ļ�
	void CSatelliteManager::LoadElecDll(const VRString& strElecName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		//if (IsLoaded(strElecName))
		//{
		//	return ;
		//}

		//// �����ļ�
		//CDyLib* pDyLib = new CDyLib(strElecName);
		//if (NULL == pDyLib)
		//{
		//	IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +" ʧ��", ERROR_MALLOC);
		//	return;
		//}

		//try
		//{
		//	pDyLib->Load();
		//}
		//catch (...)
		//{
		//	return;
		//}

		//// ������ں���
		//DLL_INSTANLL_SATELLITE pFunction = (DLL_INSTANLL_SATELLITE)pDyLib->GetSymbol("InstallSatellitePlugin");

		//if (NULL == pFunction)
		//{
		//	IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
		//	delete pDyLib;
		//	return;
		//}

		// ���뵽����
		// m_lstSatellitePlugin[strElecName] = pDyLib;

		// ִ�к���
		//pFunction(m_pIEntityFactoryManager);
	}

	// ж�ص���dll�ļ�
	void CSatelliteManager::UnLoadElecDll(const VRString& strElecName)
	{
		// ע��
		IEntityFactoryManager::GetInstance().UnRegisterFactory("����");
		// m_pIEntityFactoryManager->UnRegisterFactory("����");
		// �жϵ�ǰ�ļ��Ѿ�������
	/*	if (!IsLoaded(strElecName))
		{
			return ;
		}*/

		//ListSatallitePlugin::iterator itor = m_lstSatellitePlugin.find(strElecName);
		//CDyLib* pDyLib = itor->second;
		//if (NULL == pDyLib)
		//{
		//	return;
		//}

		//// ������ں���
		//DLL_UNINSTANLL_SATELLITE pFunction = (DLL_UNINSTANLL_SATELLITE)pDyLib->GetSymbol("UnInstallSatellitePlugin");
		//if (NULL == pFunction)
		//{
		//	IComManager::GetInstance().WriteLogMsg("���ص�Ų��:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
		//	delete pDyLib;
		//	m_lstSatellitePlugin.erase(itor);
		//	return;
		//}

		//pFunction(m_pIEntityFactoryManager);
		//m_lstSatellitePlugin.erase(itor);
	}

}
