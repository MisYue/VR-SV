
#include <vector>
#include <list>
#include <io.h>
#include <stdlib.h>
#include <algorithm>
#include "../../Public/VRSoft.h"
#include "../../Public/ComManager/IComManagerUI.h"
#include "../../Public/ComManager/IPluginManagerUI.h"
#include "DyLibManager.h"
#include "ComManagerConfig.h"
#include "ComManagerUI.h"

namespace VR_Soft
{

	/////////////////////////////////////
	// ע��ص�����
	typedef void (*DLL_INSTANLL_PLUGIN)(void);
	typedef void (*DLL_UNINSTANLL_PLUGIN)(void);
	////////////////////////////////////

	CComManagerUI::CComManagerUI(void):m_bLoad(false)
	{
	}

	CComManagerUI::~CComManagerUI(void)
	{
		ShutPlugins();
		ShutDownPlugin();
	}

	// ͨ������ע����
	void CComManagerUI::InstallPlugin(const VRString& strPluginName)
	{
		VR_MUTEX_AUTO;

		if (1 >= (int)strPluginName.size())
		{
			return;
		}

		// �������еĲ�� ���в��
		PluginInfoList::iterator itor = m_pluginInfos.begin();
		for (; m_pluginInfos.end() != itor; ++itor)
		{
			IPlugin* pPlugin = itor->_pPlugin;
			VRString strName = pPlugin->GetPluginName();
			if ((NULL == pPlugin) || (0 != pPlugin->GetPluginName().compare(strPluginName)))
			{
				continue;
			}

			// �ж��Ƿ��Ѿ�����
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				// ֱ�ӷ���
				break;
			}
			// ע��
			pPlugin->Initialise();
			SET_BIT(itor->_loadType, IComManagerUI::Loaded);
			SET_UNBIT(itor->_loadType, IComManagerUI::UnLoad);

			// ��ӵ�������б���
			((CComManagerConfig*)(IComManager::GetInstance().GetComManagerConfig()))->AddComName(strPluginName);

			// д����־��
			IComManager::GetInstance().WriteLogMsg("�����"+pPlugin->GetPluginName() + "�Ѿ������ڴ�");
		}
	}

	// ͨ������ж�ز��
	void CComManagerUI::UnInstallPlugin(const VRString& strPluginName)
	{
		VR_MUTEX_AUTO;

		// �������еĲ�� ���в��
		PluginInfoList::iterator itor = m_pluginInfos.begin();
		for (; m_pluginInfos.end() != itor; ++itor)
		{
			IPlugin* pPlugin = itor->_pPlugin;
			if ((NULL == pPlugin) || (0 != pPlugin->GetPluginName().compare(strPluginName)))
			{
				continue;
			}

			// �ж��Ƿ�δ����
			if (IComManagerUI::UnLoad & itor->_loadType)
			{
				// ֱ������
				break;
			}

			// ж��ע��
			pPlugin->Shutdown();
			SET_BIT(itor->_loadType, IComManagerUI::UnLoad);
			SET_UNBIT(itor->_loadType, IComManagerUI::Loaded);

			// ��ӵ�������б���
			((CComManagerConfig*)(IComManager::GetInstance().GetComManagerConfig()))->RemoveComName(strPluginName);

			// д����־��
			IComManager::GetInstance().WriteLogMsg("�����"+pPlugin->GetPluginName() + "�Ѿ����Ƴ��ڴ�");
		}


	}

	void CComManagerUI::RegisterUI(IPluginManagerUI* pIPluginManagerUI)
	{
		VR_MUTEX_AUTO;

		// �����Ƿ����
		LstPluginManagerUI::const_iterator cstItor = std::find(m_lstPluginManagerUI.begin(), \
			m_lstPluginManagerUI.end(), pIPluginManagerUI);
		if (m_lstPluginManagerUI.end() != cstItor)
		{
			// д����־
			return;
		}

		m_lstPluginManagerUI.push_back(pIPluginManagerUI);

		ConfigPluginManagerUI(pIPluginManagerUI);
	}

	// ��ע�ᴰ��
	void CComManagerUI::UnRegisterUI(IPluginManagerUI* pIPluginManagerUI)
	{
		VR_MUTEX_AUTO;

		// �����Ƿ����
		LstPluginManagerUI::iterator itor = std::find(m_lstPluginManagerUI.begin(), \
			m_lstPluginManagerUI.end(), pIPluginManagerUI);
		if (m_lstPluginManagerUI.end() == itor)
		{
			// д����־
			return;
		}

		m_lstPluginManagerUI.erase(itor);
	}

	// ��ѯָ��·�������в��
	void CComManagerUI::GetAllPlugins(void)
	{
		// ���
		const VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Plugin/";
		// ��ȡ��ǰĿ¼�����е��ļ�
		typedef std::vector<VRString> Files;
		Files files;
		CFileOperetor::GetFilesInPath(strPath, ".dll", files);

		// ���ȼ��������ļ��еĲ��
		const VRString strOrderPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/ComManager/order.cfg";

		typedef std::vector<VRString> ListFileNames;
		ListFileNames listFileNames;
		
		CFileUtil fileUtil(strOrderPath);
		while (!fileUtil.Eof())
		{
			VRString str = fileUtil.GetLine();
			listFileNames.push_back(str);
		}

		// ���������
		// ���������ļ�
		for (ListFileNames::const_iterator cstItor = listFileNames.begin(); listFileNames.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));

			// ����������б����Ƴ�
			Files::iterator itor = std::find(files.begin(), files.end(), *cstItor);
			if (files.end() != itor)
			{
				files.erase(itor);
			}
			
		}

		// ���������ļ�
		for (Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));
		}
	}

	// ��Ӳ��������δ����ȫ�����ص��ڴ���ȥ��
	void CComManagerUI::ConfigPlugins(void)
	{
		m_bLoad = true;

		// �����������
		GetAllPlugins();
	}

	// ���ز��
	void CComManagerUI::LoadPlugin(const VRString& strPluginPath)
	{
		// ������
		CDyLib* pLib = CDyLibManager::GetInstance().Load(strPluginPath);
		// ��ѯ�Ƿ���ڵ�ǰ���
		PluginLibList::const_iterator cstItor = std::find(m_pluginLibs.begin(), m_pluginLibs.end(), pLib);
		if (m_pluginLibs.end() != cstItor)
		{
			// ��ǰ����Ѿ�����
			return;
		}

		//����ע�ắ��
		DLL_INSTANLL_PLUGIN pFunc = (DLL_INSTANLL_PLUGIN)pLib->GetSymbol("DllInstallPlugin");
		if (NULL == pFunc)
		{
			IComManager::GetInstance().WriteLogMsg(strPluginPath + "�޷��ҵ�����ӿں���DllInstallPlugin", ERROR_NOT_FIND);
			CDyLibManager::GetInstance().Unload(pLib);

			return;
		}

		// ��δ���أ� ���
		m_pluginLibs.push_back(pLib);

		pFunc();
	}

	// ���ô���
	void CComManagerUI::ConfigPluginManagerUI(IPluginManagerUI* pIPluginManagerUI)
	{
		// ���¼��ز��
		ConfigPlugins();

		pIPluginManagerUI->InitUI(m_pluginInfos);
	}

	// ��Ӳ��
	void CComManagerUI::InstallPlugin(IPlugin* pPlugin)
	{
		// д����־��
		IComManager::GetInstance().WriteLogMsg("���ڶ�����: " + pPlugin->GetPluginName());
		// ��ӵ��������
		m_pluginInfos.push_back(pPlugin);
		//// ��װ���
		pPlugin->Install();

		if (m_bLoad)
		{
			return;
		}

		pPlugin->Initialise();

		// �������һ��ΪĬ��״̬
		SET_BIT(m_pluginInfos.back()._loadType, (IComManagerUI::Default | IComManagerUI::Loaded));

		// д����־��
		IComManager::GetInstance().WriteLogMsg("�ɹ����ز����" + pPlugin->GetPluginName());
	}

	// ж�ز��
	void CComManagerUI::UnInstallPlugin(IPlugin* pPlugin)
	{
		// д����־��
		IComManager::GetInstance().WriteLogMsg("��ʼж�ز��: " + pPlugin->GetPluginName());

		// ��ѯ����Ƿ����
		PluginInfoList::iterator itor = std::find(m_pluginInfos.begin(), m_pluginInfos.end(), pPlugin);
		if (m_pluginInfos.end() != itor)
		{
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				pPlugin->Shutdown();
				pPlugin->UnInstall();
			}
			
			m_pluginInfos.erase(itor);
		}

		IComManager::GetInstance().WriteLogMsg("�ɹ�ж�ز��: " + pPlugin->GetPluginName());
	}

	// ж�ز��
	void CComManagerUI::UnLoadPlugin(const VRString& strPluginName)
	{
		// ��ѯ�Ƿ���ڲ��
		PluginLibList::iterator itor = m_pluginLibs.begin();
		for (; m_pluginLibs.end() != itor; ++itor)
		{
			if (strPluginName == (*itor)->GetName())
			{
				// ����ж�غ���
				DLL_UNINSTANLL_PLUGIN pFunc = (DLL_UNINSTANLL_PLUGIN)(*itor)->GetSymbol("DllUnInstallPlugin");
				if (NULL == pFunc)
				{
					IComManager::GetInstance().WriteLogMsg("�޷��ҵ�����ӿں���DllInstallPlugin");
					throw ERROR_EXCEPT;
				}

				// ���ú���
				pFunc();
				IComManager::GetInstance().WriteLogMsg("ж�ض�̬��: " + strPluginName);
			}
		}
	}

	// ������в��
	void CComManagerUI::ShutDownPlugin(void)
	{
		// �������еĲ��
		PluginInfoList::reverse_iterator itor = m_pluginInfos.rbegin();
		for (; m_pluginInfos.rend() != itor; ++itor)
		{
			if (IComManagerUI::Loaded & itor->_loadType)
			{
				itor->_pPlugin->Shutdown();
			}

			IComManager::GetInstance().WriteLogMsg("�ɹ�ж�����: " + itor->_pPlugin->GetPluginName());
		}

		m_pluginInfos.clear();
	}

	// ж�����еĲ��
	void CComManagerUI::ShutPlugins(void)
	{
		// �������еĲ����̬��
		for (PluginLibList::reverse_iterator itor = m_pluginLibs.rbegin(); m_pluginLibs.rend() != itor; ++itor)
		{
			DLL_UNINSTANLL_PLUGIN pFunc = (DLL_UNINSTANLL_PLUGIN)(*itor)->GetSymbol("DllUnInstallPlugin");
			if (NULL == pFunc)
			{
				continue;
			}

			// ����ж�غ���
			pFunc();
			IComManager::GetInstance().WriteLogMsg("ж�ض�̬��:" + (*itor)->GetName());

			CDyLibManager::GetInstance().Unload(*itor);
		}

		m_pluginLibs.clear();
	}

}
