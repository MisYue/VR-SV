
#include "../../Public/VRSoft.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include "Log.h"


namespace VR_Soft
{
	CLog::CLog(const VRString& strName, bool bDebugOut/* = false*/, bool bSupperFile /*= true*/)
		:m_bDebugOut(bDebugOut),m_bSupperFile(bSupperFile), m_bSupperTime(true), m_strName(strName),
		m_pFileLog(NULL)
	{
		// 是否支持文件操作
		if (m_bSupperFile)
		{
			//m_fstrLog.open(strName);
			m_pFileLog = fopen(strName.c_str(), "w");
		}
	}


	CLog::~CLog(void)
	{
		//线程安全 锁定
		VR_MUTEX_AUTO
		// 关闭日志文件
		if (m_bSupperFile && (NULL != m_pFileLog))
		{
			// 刷新 保存文件
			// m_fstrLog.flush();
			fflush(m_pFileLog);

			// 关闭文件
			// m_fstrLog.close();
			fclose(m_pFileLog);
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

		char szLine[256] = {0};

		// 是否取用时间
		if (m_bSupperTime)
		{
			// 获取时间
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// 获取系统时间
			pTime = localtime(&cTime);

			sprintf(szLine, "%d:%d:%d:",pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
			// 写入缓存
			/*strOutLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";*/
		}

		char szOutLog[256] = {0};
		//m_fstrLog << strLog.c_str() << std::endl;
		sprintf(szOutLog, "%s   %s\n\r",szLine, strLog.c_str());
		fwrite(szOutLog, sizeof(char), sizeof(char) * 256, m_pFileLog);
		// 刷新缓存 写入文件
		//m_fstrLog.flush();			
		fflush(m_pFileLog);
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

