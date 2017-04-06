#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "EquipManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_EQUIP)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_EQUIP)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	// ���캯��
	CEquipManager::CEquipManager(IEntityFactoryManager* pIEntityFactoryManager)
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{
	}

	// ��������
	CEquipManager::~CEquipManager(void)
	{
	}

	// ���ҵ�ǰ�ļ��¼��ز��
	void CEquipManager::LoadAllElecDll(void)
	{
		// ��ȡ��������еĲ���ļ�
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Equip/";

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
	bool CEquipManager::IsLoaded(const VRString& strElecName)
	{
		ListEquipPlugin::const_iterator cstItor = m_lstEquipPlugin.find(strElecName);
		return (m_lstEquipPlugin.end() != cstItor);
	}

	// ���ص���dll�ļ�
	void CEquipManager::LoadElecDll(const VRString& strElecName)
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
			IComManager::GetInstance().WriteLogMsg("�����������:"+ strElecName +" ʧ��", ERROR_MALLOC);
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
		DLL_INSTANLL_EQUIP pFunction = (DLL_INSTANLL_EQUIP)pDyLib->GetSymbol("InstallEquipPlugin");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("�����������:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// ���뵽����
		m_lstEquipPlugin[strElecName] = pDyLib;

		// ִ�к���
		pFunction(m_pIEntityFactoryManager);
	}

	// ж�ص���dll�ļ�
	void CEquipManager::UnLoadElecDll(const VRString& strElecName)
	{
		// �жϵ�ǰ�ļ��Ѿ�������
		if (!IsLoaded(strElecName))
		{
			return ;
		}

		ListEquipPlugin::iterator itor = m_lstEquipPlugin.find(strElecName);
		CDyLib* pDyLib = itor->second;
		if (NULL == pDyLib)
		{
			return;
		}

		// ������ں���
		DLL_UNINSTANLL_EQUIP pFunction = (DLL_UNINSTANLL_EQUIP)pDyLib->GetSymbol("UnInstallEquipPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("�����������:"+ strElecName +"δʶ��", ERROR_NOT_FIND);
			delete pDyLib;
			m_lstEquipPlugin.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_lstEquipPlugin.erase(itor);
	}
}

