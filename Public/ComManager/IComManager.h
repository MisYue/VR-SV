/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ӿ�	                                                */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGER_H_
#define _ICOMMANAGER_H_


namespace VR_Soft
{
	class VRSOFT_DLL IComManager : public CSingleton<IComManager>
	{
	public:
		virtual ~IComManager() {}
		// ��ʼ�� /* �������ʾ����֮���ٽ��е��� */
		virtual void InitCom(void) = 0;
		// ��Ӳ��
		virtual void InstallPlugin(IPlugin* pPlugin) = 0;
		// ж�ز��
		virtual void UnInstallPlugin(IPlugin* pPlugin) = 0;
		// ������
		virtual void LoadPlugin(const VRString& strPluginName) = 0;
		// ж�ز��
		virtual void UnLoadPlugin(const VRString& strPluginName) = 0;
		// ע�Ṥ��
		virtual void RegisterComManagerFactory(IComFactory* pFactory) = 0;
		// ɾ������
		virtual void UnRegisterComManagerFactory(IComFactory* pFactory) = 0;
		// ��ȡϵͳ��־
		virtual ILogManager* GetLogManager(void) const = 0;
		// ��ȡ�������
		virtual IComInstanceMerator* GetConInstanceMerator(void) const = 0;
		// д����־
		virtual void WriteLogMsg(const VRString& strMsg, UINT uiCode = ERROR_OK ) = 0;
		// ���ģ�͹���
		virtual IEntityManager* GetEntityManager(void) const = 0;
		// ������Թ������
		virtual IAttributeManager* GetAttributeManager(void) = 0;
		// ����������Ӧ����
		virtual IAttributeUIFactory* GetAttributeUiFactory(void) = 0;
		// �������������
		virtual IComManagerUI* GetComManagerUI(void) = 0;
		// ������ö���
		virtual IComManagerConfig* GetComManagerConfig(void) = 0;
		// ���ָ�����
		virtual IActionManager* GetActionManager(void) const = 0;

		// ϵͳѭ������
		virtual void LoopRun(void) = 0;
		// �����Ƿ���ñ���ģ��
		virtual void EnableServer(bool bServer = false) = 0;
		// ����Ƿ���ñ��ط�����
		virtual bool IsService(void) const = 0;

	};

	// ���ü򵥹������г�ʼ��
	EXTERN_CPP VRSOFT_DLL IComManager* CreateInstance(int argc, char *argv[]);
}

#endif // _ICOMMANAGER_H_