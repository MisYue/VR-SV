/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  日志系统接口			                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
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
		// 析构函数
		virtual ~ILogManager() { }
		// 创建默认日志
		virtual ILog* CreateLog(const VRString& strLog, bool bDefaultLog = false,\
			bool debuggerOutput = true, bool suppressFileOutput = false) = 0;
		// 获得默认的系统日志
		virtual ILog* GetDefaultLog(void) = 0;
		// 设置当前系统日志 返回原来的系统日志
		virtual ILog* SetDefaultLog(ILog* pLog) = 0;

		// 获得系统日志对象
		virtual ILog* GetLog(const VRString& strLog) = 0;
		// 销毁日志对象
		virtual void DestoryLog(const VRString& strLog) = 0;
		virtual void DestoryLog(ILog* pLog) = 0;
		// 写入系统日志
		virtual void SetLogMessage(const VRString& strMsg, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false) = 0;
	};
}

#endif