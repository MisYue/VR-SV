/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  日志对象				                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_

#pragma once

#include <fstream>

namespace VR_Soft
{
	class CLog : public ILog
	{
	public:
		explicit CLog(const VRString& strName, bool bDebugOut = false, bool bSupperFile = true);
		virtual ~CLog(void);

		// 获得名称
		const VRString& GetName(void) const { return (m_strName); }
		// 日志信息
		void SetLogMessage(const VRString& strLog, UINT uiCode = ERROR_OK, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false);
		// 获取错误信息
		const VRString& GetErrorMessage(void) const;
		// 获取是否文件支持属性
		bool IsDebugOut(void) const;
		// 获取是否支持文件属性
		bool IsSupperFile(void) const;
		// 获取是否支持时间
		bool IsTimeStampEnabled(void) const;
		// 设置错误码
		SET_GET_PROPERTY(Code, UINT, ui);


	private:
		bool m_bDebugOut; // 调试输出到控制台窗口
		bool m_bSupperFile; //是否支持
		bool m_bSupperTime; // 使用时间
		VRString m_strName; // 日志文件
		std::ofstream m_fstrLog; // 系统文件
		VRString m_strLastLog; // 获取错误
		UINT m_uiCode; // 错误码

		VR_AUTO_MUTEX
	};
}

#endif