
#include "../../Public/VRSoft.h"
#include "Log.h"
#include "LogManager.h"

namespace VR_Soft
{
	CLogManager::CLogManager(void):m_pDefaultLog(NULL)
	{
	}

	CLogManager::~CLogManager()
	{
		// �����ڴ�
		VR_MUTEX_AUTO;

		// ����ɾ��
		MapStrLog::iterator itor = m_mapStrLog.begin();
		for (; m_mapStrLog.end() != itor; ++itor)
		{
			// �������
			VRSOFT_DELETE(itor->second);
		}

		// �����������
		m_mapStrLog.clear();
	}

	// ����Ĭ����־
	ILog* CLogManager::CreateLog(const VRString& strLog, bool bDefaultLog, bool debuggerOutput , bool suppressFileOutput )
	{
		VR_MUTEX_AUTO;
		// ������־ϵͳ
		ILog* pLog = new CLog(strLog, debuggerOutput, suppressFileOutput);
		// �ж��Ƿ����ɹ�
		if (NULL == pLog)
		{
			throw ERROR_EXCEPT;
			return (NULL);
		}

		// �����Ƿ�ΪĬ�ϵ���־ϵͳ
		if (!m_pDefaultLog || bDefaultLog)
		{
			m_pDefaultLog = pLog;
		}

		// ��ӽ��뵽ϵͳ��
		m_mapStrLog.insert(MapStrLog::value_type(strLog, pLog));
		return (pLog);
	}

	// ���Ĭ�ϵ�ϵͳ��־
	ILog* CLogManager::GetDefaultLog(void)
	{
		VR_MUTEX_AUTO;
		return (m_pDefaultLog);
	}

	// ���õ�ǰϵͳ��־
	ILog* CLogManager::SetDefaultLog(ILog* pLog)
	{
		VR_MUTEX_AUTO;

		// ���浱ǰ��־
		ILog* pOldLog = m_pDefaultLog;
		m_pDefaultLog = pLog;
		return (pOldLog);
	}

	// ���ϵͳ��־����
	ILog* CLogManager::GetLog(const VRString& strLog)
	{
		VR_MUTEX_AUTO;

		// ��ѯ��־
		MapStrLog::iterator itor = m_mapStrLog.find(strLog);
		if (m_mapStrLog.end() == itor)
		{
			throw ERROR_EXCEPT;
			return (NULL);
		}

		// ������־
		return (itor->second);
	}

	// ������־����
	void CLogManager::DestoryLog(const VRString& strLog)
	{
		// ��ѯ��־
		MapStrLog::iterator itor = m_mapStrLog.find(strLog);
		// �ж��Ƿ����
		if (m_mapStrLog.end() == itor)
		{
			return;
		}

		// �ж��Ƿ�Ϊ��ǰ��־
		if (itor->second == m_pDefaultLog)
		{
			m_pDefaultLog = NULL;
		}

		// ɾ��
		delete itor->second;
		m_mapStrLog.erase(itor);

		// �жϵ�ǰ�Ƿ�Ĭ��ֵ
		if ((NULL == m_pDefaultLog) && (!m_mapStrLog.empty()))
		{
			m_pDefaultLog = m_mapStrLog.begin()->second;
		}
	}

	void CLogManager::DestoryLog(ILog* pLog)
	{
		DestoryLog(pLog->GetName());
	}

	// д��ϵͳ��־
	void CLogManager::SetLogMessage(const VRString& strMsg, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		VR_MUTEX_AUTO;

		// �ж�Ĭ�ϵ��Ƿ�Ϊ��
		if (NULL != m_pDefaultLog)
		{
			m_pDefaultLog->SetLogMessage(strMsg, uiCode, lml, maskDebug);
		}
	}
}

