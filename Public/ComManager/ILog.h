/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��־�ӿ�				                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ILOG_H_
#define _ILOG_H_

#pragma once

namespace VR_Soft
{
	enum LogMessageLevel
	{
		LML_TRIVIAL = 1,
		LML_NORMAL = 2,
		LML_CRITICAL = 3
	};

	class VRSOFT_DLL ILog
	{
	public:
		virtual const VRString& GetName(void) const = 0;
		// ��־��Ϣ
		virtual void SetLogMessage(const VRString& strLog, UINT uiCode = ERROR_OK,\
			LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
		// ��ȡ������Ϣ
		virtual const VRString& GetErrorMessage(void) const = 0;
		// ��ȡ�Ƿ��ļ�֧������
		virtual bool IsDebugOut(void) const = 0;
		// ��ȡ�Ƿ�֧���ļ�����
		virtual bool IsSupperFile(void) const = 0;
		// ��ȡ�Ƿ�֧��ʱ��
		virtual bool IsTimeStampEnabled(void) const = 0;
	};
}
#endif // _ILOG_H_