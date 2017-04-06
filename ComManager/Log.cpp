
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
		// �Ƿ�֧���ļ�����
		if (m_bSupperFile)
		{
			//m_fstrLog.open(strName);
			m_pFileLog = fopen(strName.c_str(), "w");
		}
	}


	CLog::~CLog(void)
	{
		//�̰߳�ȫ ����
		VR_MUTEX_AUTO
		// �ر���־�ļ�
		if (m_bSupperFile && (NULL != m_pFileLog))
		{
			// ˢ�� �����ļ�
			// m_fstrLog.flush();
			fflush(m_pFileLog);

			// �ر��ļ�
			// m_fstrLog.close();
			fclose(m_pFileLog);
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

		char szLine[256] = {0};

		// �Ƿ�ȡ��ʱ��
		if (m_bSupperTime)
		{
			// ��ȡʱ��
			struct tm* pTime;
			time_t cTime;
			time(&cTime);

			// ��ȡϵͳʱ��
			pTime = localtime(&cTime);

			sprintf(szLine, "%d:%d:%d:",pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
			// д�뻺��
			/*strOutLog << std::setw(2) << std::setfill('0') << pTime->tm_hour
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
				<< ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
				<< ": ";*/
		}

		char szOutLog[256] = {0};
		//m_fstrLog << strLog.c_str() << std::endl;
		sprintf(szOutLog, "%s   %s\n\r",szLine, strLog.c_str());
		fwrite(szOutLog, sizeof(char), sizeof(char) * 256, m_pFileLog);
		// ˢ�»��� д���ļ�
		//m_fstrLog.flush();			
		fflush(m_pFileLog);
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

