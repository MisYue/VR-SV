/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ʵ����                                            */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _COMMANAGERUI_H_
#define _COMMANAGERUI_H_

#pragma once

namespace VR_Soft
{
	class CComManagerUI : public IComManagerUI
	{
	public:
		explicit CComManagerUI(void);
		virtual ~CComManagerUI(void);

	public:
		// ͨ������ע����
		virtual void InstallPlugin(const VRString& strPluginName);
		// ͨ������ж�ز��
		virtual void UnInstallPlugin(const VRString& strPluginName);
		// ע�ᴰ��
		virtual void RegisterUI(IPluginManagerUI* pIPluginManagerUI);
		// ��ע�ᴰ��
		virtual void UnRegisterUI(IPluginManagerUI* pIPluginManagerUI);
		

	public:
		// ��Ӳ��
		void InstallPlugin(IPlugin* pPlugin);
		// ж�ز��
		void UnInstallPlugin(IPlugin* pPlugin);
		// ���ز��
		void LoadPlugin(const VRString& strPluginPath);
		// ж�ز��
		void UnLoadPlugin(const VRString& strPluginName);
		// ��Ӳ��������δ����ȫ�����ص��ڴ���ȥ��
		void ConfigPlugins(void);

	protected:
		// ��ѯָ��·�������в��
		void GetAllPlugins(void);
		// ���ô���
		void ConfigPluginManagerUI(IPluginManagerUI* pIPluginManagerUI);
		// ������в��
		void ShutDownPlugin(void);
		// ж�����еĲ��
		void ShutPlugins(void);
		

	private:
		typedef std::vector<CDyLib*>  PluginLibList;

	private:
		bool m_bLoad; // �Ƿ񽫲�����ص��ڴ���
		std::list<VRString> m_strPlugins; // ���еĲ��
		PluginLibList m_pluginLibs; // ���붯̬���������
		PluginInfoList m_pluginInfos; // ����б�
		typedef std::list<IPluginManagerUI*> LstPluginManagerUI;
		LstPluginManagerUI m_lstPluginManagerUI;

		VR_AUTO_MUTEX
	};
}


#endif // _COMMANAGERUI_H_