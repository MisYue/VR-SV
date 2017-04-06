/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  日志接口				                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
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
		// 日志信息
		virtual void SetLogMessage(const VRString& strLog, UINT uiCode = ERROR_OK,\
			LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
		// 获取错误信息
		virtual const VRString& GetErrorMessage(void) const = 0;
		// 获取是否文件支持属性
		virtual bool IsDebugOut(void) const = 0;
		// 获取是否支持文件属性
		virtual bool IsSupperFile(void) const = 0;
		// 获取是否支持时间
		virtual bool IsTimeStampEnabled(void) const = 0;
	};
}
#endif // _ILOG_H_