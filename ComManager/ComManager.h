/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �������ʵ����                                                */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _COMMANAGER_H_
#define _COMMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CConfigManager;
	class CComInstanceEnumerator;
	class CInpute;
	class CEntityThread;
	class CPathManager;

	class CComManager : public IComManager
	{
	public:
		explicit CComManager(int argc, char *argv[]);
		virtual ~CComManager();

	public:
		// ��ʼ��
		virtual void InitCom(void);
		// ��Ӳ��
		virtual void InstallPlugin(IPlugin* pPlugin);
		// ж�ز��
		virtual void UnInstallPlugin(IPlugin* pPlugin);
		// ������
		virtual void LoadPlugin(const VRString& strPluginName);
		// ж�ز��
		virtual void UnLoadPlugin(const VRString& strPluginName);
		// ע�Ṥ��
		virtual void RegisterComManagerFactory(IComFactory* pFactory);
		// ɾ������
		virtual void UnRegisterComManagerFactory(IComFactory* pFactory);
		// ��ȡϵͳ��־
		virtual ILogManager* GetLogManager(void) const;
		// ��ȡ�������
		virtual IComInstanceMerator* GetConInstanceMerator(void) const;
		// д����־
		virtual void WriteLogMsg(const VRString& strMsg, UINT uiCode = ERROR_OK);
		// ���ģ�͹���
		virtual IEntityManager* GetEntityManager(void) const;
		// �����Ϣϵͳ����
		virtual IMessageManager* GetMessageManager(void) const;
		// ����������Ӧ����
		virtual IAttributeUIFactory* GetAttributeUiFactory(void);
		// ������Թ������
		virtual IAttributeManager* GetAttributeManager(void);
		// �������������
		virtual IComManagerUI* GetComManagerUI(void) ;
		// ������ö���
		virtual IComManagerConfig* GetComManagerConfig(void);
		// ���ָ�����
		virtual IActionManager* GetActionManager(void) const;

		// ϵͳѭ������
		virtual void LoopRun(void);
		// �����Ƿ���ñ���ģ��
		virtual void EnableServer(bool bServer = false);
		// ����Ƿ���ñ��ط�����
		virtual bool IsService(void) const ;

	protected:
		// ��ʼ��
		void Init(const VRString& strPath);
		// ����ϵͳ��־
		void CreateLogSystem(void);
		// ж����־ϵͳ
		void UnLoadLogSystem(void);

	protected:
		// ����ģ�� �ж������ǰ�ķ���������õĲ��Ƿ�����������ڲ�ˢ��
		void UpdateEntity(void);

	private:
		CDyLibManager* m_pDyLibManager; // ��̬�����
		CComInstanceEnumerator* m_pComInstance; // ���ʵ������
		CComManagerUI* m_pIComMangerUI; // ����������ӿ�
		IComManagerConfig* m_pIComManagerConfig; // �������

		// ϵͳ���Ĳ�� ����ÿ�ζ�ȥ����
	private:
		mutable IMessageManager*	m_pIMessageManager; // ��Ϣϵͳ
		mutable CEntityManager*		m_pIEntityManager; // ʵ�����ϵͳ
		IAttributeManager*			m_pIAttributeManager; // ���Թ���
		IAttributeUIFactory*		m_pIAttrbiteUIFactory; // ���Թ�������
		ISimManager* m_pISimManager; // �������
		IActionManager* m_pIActionManager; // ָ�����
		ITimer* m_pITimer; // ��ʱ��
		mutable CLogManager*		m_pLogMananger; // ��־ϵͳ
		bool m_bServer; // �Ƿ���ñ��ط�����
		CConfigManager* m_pConnfigManager; // ���ù�������
		CInpute* m_pInpute; // �����豸
		CEntityThread* m_pEntityThread; // ʵ�������
		CPathManager* m_pPathManager; // ·������
	};
}


#endif // _COMMANAGER_H_
