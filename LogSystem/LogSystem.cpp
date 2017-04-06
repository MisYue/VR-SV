#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "Log.h"
#include "LogSystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CLogManagerFactory::FACTORY_TYPE_NAME = LOGSYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CLogSystem::CLogSystem(const VRString& strName):m_pDefaultLog(NULL)
	{
		SetName(strName);
	}

	CLogSystem::~CLogSystem()
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
	ILog* CLogSystem::CreateLog(const VRString& strLog, bool bDefaultLog, bool debuggerOutput , bool suppressFileOutput )
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
	ILog* CLogSystem::GetDefaultLog(void)
	{
		VR_MUTEX_AUTO;
		return (m_pDefaultLog);
	}

	// ���õ�ǰϵͳ��־
	ILog* CLogSystem::SetDefaultLog(ILog* pLog)
	{
		VR_MUTEX_AUTO;

		// ���浱ǰ��־
		ILog* pOldLog = m_pDefaultLog;
		m_pDefaultLog = pLog;
		return (pOldLog);
	}

	// ���ϵͳ��־����
	ILog* CLogSystem::GetLog(const VRString& strLog)
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
	void CLogSystem::DestoryLog(const VRString& strLog)
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

	void CLogSystem::DestoryLog(ILog* pLog)
	{
		DestoryLog(pLog->GetName());
	}

	// д��ϵͳ��־
	void CLogSystem::SetLogMessage(const VRString& strMsg, UINT uiCode, LogMessageLevel lml, bool maskDebug)
	{
		VR_MUTEX_AUTO;

		// �ж�Ĭ�ϵ��Ƿ�Ϊ��
		if (NULL != m_pDefaultLog)
		{
			m_pDefaultLog->SetLogMessage(strMsg, uiCode, lml, maskDebug);
		}
	}

	const VRString& CLogSystem::GetTypeName(void) const
	{
		return CLogManagerFactory::FACTORY_TYPE_NAME;
	}

	// ��ʼ��ϵͳ
	void CLogSystem::Init(void)
	{

	}
}

