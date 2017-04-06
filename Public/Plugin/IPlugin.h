/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ӿڣ��������ģʽ                                        */
/* ʱ�䣺 2015-05-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#pragma once

namespace VR_Soft
{
	class IComManager;

	class VRSOFT_DLL IPlugin
	{
	public:
		// ��������
		virtual ~IPlugin() { }
		// ��ȡ�������
		virtual const VRString& GetPluginName(void) const = 0;
		// ��ò���汾
		virtual const VRString GetPluginVersion(void) const = 0;
		// ��ò������
		virtual const VRString& GetPluginDiscribe(void) const = 0;
		// ��װ���
		virtual void Install(void) = 0;
		// ��ʼ�����
		virtual void Initialise(void) = 0;
		// ������
		virtual void Shutdown(void) = 0;
		// ж�ز��
		virtual void UnInstall(void) = 0;
	};

	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllInstallPlugin(IComManager* pComManager);	

	//// ж�ز���ӿں���
	//EXTERN_CPP void VRSOFT_PLUGIN_DLL DllUnInstallPlugin(IComManager* pComManager);
	// ע������
#define REGISTER_VRSOFT_PLUGIN(classname, export_style) \
	IPlugin* pPlugin = NULL;\
	EXTERN_CPP export_style void DllInstallPlugin(void) {\
	pPlugin = new classname; \
	IComManager::GetInstance().InstallPlugin(pPlugin);\
	}\
	EXTERN_CPP export_style void DllUnInstallPlugin(void){ \
	IComManager::GetInstance().UnInstallPlugin(pPlugin); VRSOFT_DELETE(pPlugin);\
	}
}

#endif // _PLUGIN_H_