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
	class CLogManager : public ILogManager
	{
	public:
		// ���캯��
		explicit CLogManager(void);
		// ��������
		virtual ~CLogManager();

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

	protected:
		typedef std::map<VRString, ILog*> MapStrLog;
		MapStrLog m_mapStrLog;


	private:
		ILog* m_pDefaultLog; // Ĭ�ϴ�����־����

		VR_AUTO_MUTEX
	};
}


#endif // LOGSYSTEM_H
