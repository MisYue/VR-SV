/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־ϵͳ�ӿ�			                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ILOGMANAGER_H_
#define _ILOGMANAGER_H_

#pragma once

#include "ILog.h"

namespace VR_Soft
{
	class VRSOFT_DLL ILogManager : public CSingleton<ILogManager>
	{
	public:
		// ��������
		virtual ~ILogManager() { }
		// ����Ĭ����־
		virtual ILog* CreateLog(const VRString& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false) = 0;
		// ���Ĭ�ϵ�ϵͳ��־
		virtual ILog* GetDefaultLog(void) = 0;
		// ���õ�ǰϵͳ��־ ����ԭ����ϵͳ��־
		virtual ILog* SetDefaultLog(ILog* pLog) = 0;

		// ���ϵͳ��־����
		virtual ILog* GetLog(const VRString& strLog) = 0;
		// ������־����
		virtual void DestoryLog(const VRString& strLog) = 0;
		virtual void DestoryLog(ILog* pLog) = 0;
		// д��ϵͳ��־
		virtual void SetLogMessage(const VRString& strMsg, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
	};
}

#endif