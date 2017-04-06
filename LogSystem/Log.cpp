#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include "Log.h"


namespace VR_Soft
{
	CLog::CLog(const VRString& strName, bool bDebugOut/* = false*/, bool bSupperFile /*= true*/)
		:m_bDebugOut(bDebugOut),m_bSupperFile(bSupperFile), m_bSupperTime(true), m_strName(strName)
	{
		// 是否支持文件操作
		if (m_bSupperFile)
		{
			m_fstrLog.open(strName);
		}
	}


	CLog::~CLog(void)
	{
		//线程安全 锁定
		VR_MUTEX_AUTO
		// 关闭日志文件
		if (m_bSupperFile)
		{
			// 刷新 保存文件
			m_fstrLog.flush();

			// 关闭文件
			m_fstrLog.close();
		}
	}

	// 日志信息
	void CLog::SetLogMessage(const VRString& strLog, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 设置最后时间
		m_strLastLog = strLog;
		m_uiCode = uiCode;

		// 盘点是否采用控制台输出
		if (m_bDebugOut && !maskDebug)
		{
			std::cerr<<strLog.c_str()<<std::endl;
		}

		// 判断是否需要数据支持
		if (!m_bSupperFile)
		{
			// 不支持文件
			return;
		}

		// 是否取用时间
		if (m_bSupperTime)
		{
			// 获取时间
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// 获取系统时间
			pTime = localtime(&cTime);

			// 写入缓存
			m_fstrLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";
		}

		m_fstrLog << strLog.c_str() << std::endl;
		// 刷新缓存 写入文件
		m_fstrLog.flush();			
	}

	// 获取错误信息
	const VRString& CLog::GetErrorMessage(void) const
	{
		VR_MUTEX_AUTO;
		return m_strName;
	}

	// 获取是否支持属性
	bool CLog::IsDebugOut(void) const
	{
		VR_MUTEX_AUTO
		return (m_bDebugOut);
	}

	// 获取是否支持文件属性
	bool CLog::IsSupperFile(void) const
	{
		VR_MUTEX_AUTO
		return (m_bSupperFile);
	}

	// 获取是否支持时间
	bool CLog::IsTimeStampEnabled(void) const
	{
		VR_MUTEX_AUTO
		return (m_bSupperTime);
	}
}

