/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־ϵͳ				                                        */
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _LOGSYSTEM_H_
#define _LOGSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CLogSystem : public ILogManager
	{
	public:
		// ���캯��
		explicit CLogSystem(const VRString& strName);
		// ��������
		virtual ~CLogSystem();

		// ����Ĭ����־
		virtual ILog* CreateLog(const VRString& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false);
		// ���Ĭ�ϵ�ϵͳ��־
		virtual ILog* GetDefaultLog(void);
		// ���õ�ǰϵͳ��־ ����ԭ����ϵͳ��־
		virtual ILog* SetDefaultLog(ILog* pLog);

		// ���ϵͳ��־����
		virtual ILog* GetLog(const VRString& strLog);
		// ������־����
		virtual void DestoryLog(const VRString& strLog);
		virtual void DestoryLog(ILog* pLog);
		// д��ϵͳ��־
		virtual void SetLogMessage(const VRString& strMsg, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false);
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);

		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		typedef std::map<VRString, ILog*> MapStrLog;
		MapStrLog m_mapStrLog;


	private:
		ILog* m_pDefaultLog; // Ĭ�ϴ�����־����
		VRString m_strName;

		VR_AUTO_MUTEX
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CLogSystem, LogManager, LOGSYSTEM_TYPENAME, INSTANCE_NAME_LOGSYSTEM, LOGSYSTEM_DISC );
}


#endif // LOGSYSTEM_H
