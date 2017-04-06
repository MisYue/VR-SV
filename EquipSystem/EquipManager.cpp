#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "EquipManager.h"

namespace VR_Soft
{
	/////////////////////////////////////
	// 注册回调函数
	typedef void (*DLL_INSTANLL_EQUIP)(IEntityFactoryManager* pIEntityFactoryManager);
	typedef void (*DLL_UNINSTANLL_EQUIP)(IEntityFactoryManager* pIEntityFactoryManager);
	////////////////////////////////////

	// 构造函数
	CEquipManager::CEquipManager(IEntityFactoryManager* pIEntityFactoryManager)
		:m_pIEntityFactoryManager(pIEntityFactoryManager)
	{
	}

	// 析构函数
	CEquipManager::~CEquipManager(void)
	{
	}

	// 查找当前文件下加载插件
	void CEquipManager::LoadAllElecDll(void)
	{
		// 获取插件下所有的插件文件
		const VRString strElecDllPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Equip/";

		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strElecDllPath, "*.dll", files);

		// 遍历所有的文件
		Files::const_iterator cstItor = files.begin();
		for (; files.end() != cstItor; ++cstItor)
		{
			LoadElecDll(strElecDllPath + (*cstItor));
		}
	}

	// 当前动态库是否加载了
	bool CEquipManager::IsLoaded(const VRString& strElecName)
	{
		ListEquipPlugin::const_iterator cstItor = m_lstEquipPlugin.find(strElecName);
		return (m_lstEquipPlugin.end() != cstItor);
	}

	// 加载单个dll文件
	void CEquipManager::LoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
		if (IsLoaded(strElecName))
		{
			return ;
		}

		// 加载文件
		CDyLib* pDyLib = new CDyLib(strElecName);
		if (NULL == pDyLib)
		{
			IComManager::GetInstance().WriteLogMsg("加载武器插件:"+ strElecName +" 失败", ERROR_MALLOC);
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

		// 查找入口函数
		DLL_INSTANLL_EQUIP pFunction = (DLL_INSTANLL_EQUIP)pDyLib->GetSymbol("InstallEquipPlugin");

		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载武器插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			return;
		}

		// 加入到表中
		m_lstEquipPlugin[strElecName] = pDyLib;

		// 执行函数
		pFunction(m_pIEntityFactoryManager);
	}

	// 卸载单个dll文件
	void CEquipManager::UnLoadElecDll(const VRString& strElecName)
	{
		// 判断当前文件已经被加载
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

		// 查找入口函数
		DLL_UNINSTANLL_EQUIP pFunction = (DLL_UNINSTANLL_EQUIP)pDyLib->GetSymbol("UnInstallEquipPlugin");
		if (NULL == pFunction)
		{
			IComManager::GetInstance().WriteLogMsg("加载武器插件:"+ strElecName +"未识别", ERROR_NOT_FIND);
			delete pDyLib;
			m_lstEquipPlugin.erase(itor);
			return;
		}

		pFunction(m_pIEntityFactoryManager);
		m_lstEquipPlugin.erase(itor);
	}
}

