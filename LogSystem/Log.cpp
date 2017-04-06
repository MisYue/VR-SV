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
		// �Ƿ�֧���ļ�����
		if (m_bSupperFile)
		{
			m_fstrLog.open(strName);
		}
	}


	CLog::~CLog(void)
	{
		//�̰߳�ȫ ����
		VR_MUTEX_AUTO
		// �ر���־�ļ�
		if (m_bSupperFile)
		{
			// ˢ�� �����ļ�
			m_fstrLog.flush();

			// �ر��ļ�
			m_fstrLog.close();
		}
	}

	// ��־��Ϣ
	void CLog::SetLogMessage(const VRString& strLog, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// �������ʱ��
		m_strLastLog = strLog;
		m_uiCode = uiCode;

		// �̵��Ƿ���ÿ���̨���
		if (m_bDebugOut && !maskDebug)
		{
			std::cerr<<strLog.c_str()<<std::endl;
		}

		// �ж��Ƿ���Ҫ����֧��
		if (!m_bSupperFile)
		{
			// ��֧���ļ�
			return;
		}

		// �Ƿ�ȡ��ʱ��
		if (m_bSupperTime)
		{
			// ��ȡʱ��
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// ��ȡϵͳʱ��
			pTime = localtime(&cTime);

			// д�뻺��
			m_fstrLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";
		}

		m_fstrLog << strLog.c_str() << std::endl;
		// ˢ�»��� д���ļ�
		m_fstrLog.flush();			
	}

	// ��ȡ������Ϣ
	const VRString& CLog::GetErrorMessage(void) const
	{
		VR_MUTEX_AUTO;
		return m_strName;
	}

	// ��ȡ�Ƿ�֧������
	bool CLog::IsDebugOut(void) const
	{
		VR_MUTEX_AUTO
		return (m_bDebugOut);
	}

	// ��ȡ�Ƿ�֧���ļ�����
	bool CLog::IsSupperFile(void) const
	{
		VR_MUTEX_AUTO
		return (m_bSupperFile);
	}

	// ��ȡ�Ƿ�֧��ʱ��
	bool CLog::IsTimeStampEnabled(void) const
	{
		VR_MUTEX_AUTO
		return (m_bSupperTime);
	}
}

