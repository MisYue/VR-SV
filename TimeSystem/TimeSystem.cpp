#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "TimerThread.h"
#include "TimeSystem.h"


namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CTimeManagerFactory::FACTORY_TYPE_NAME = LOGSYSTEM_TYPENAME;
	///////////////////////////////////////////////
	CTimeSystem::CTimeSystem(const VRString& strName):m_pTimeThread(NULL)
	{
		SetName(strName);
	}


	CTimeSystem::~CTimeSystem(void)
	{
		m_pTimeThread->Join();
		VRSOFT_DELETE(m_pTimeThread);
	}

	ITimer* CTimeSystem::GetTime(void)
	{
		return (&m_timer);
	}

	// ����
	void CTimeSystem::Quicken(void)
	{
		double dMultiple = m_timer.GetMultiple();

		float fQuicken = m_timeConfig.GetQuicken();
		if (0.0f == fQuicken)
		{
			fQuicken = 10.0f;
		}
		
		m_timer.SetMultiple(dMultiple * fQuicken);
	}

	// ����
	void CTimeSystem::Moderate(void)
	{
		double dMultiple = m_timer.GetMultiple();
		float fQuicken = m_timeConfig.GetModerate();
		if (0.0f == fQuicken)
		{
			fQuicken = 0.1f;
		}

		m_timer.SetMultiple(dMultiple * fQuicken);
	}

	// ��ͣ
	void CTimeSystem::Suspend(void)
	{
		m_pTimeThread->SubSuspend(true);
	}

	// �ָ�
	void CTimeSystem::Recover(void)
	{
		m_pTimeThread->Start();
		m_pTimeThread->SubSuspend(false);
	}

	// ֹͣ����λ��
	void CTimeSystem::Stop(void)
	{
		m_pTimeThread->SubSuspend(true);
		m_timer.Stop();
	}

	// ��ʼ
	void CTimeSystem::Start(void)
	{
		m_pTimeThread->Start();
		m_pTimeThread->SubSuspend(false);
	}

	// ��ת
	void CTimeSystem::Jump(struct tm& t)
	{
		m_timer.SetStartTime(t);
	}

	// �������
	const VRString& CTimeSystem::GetTypeName(void) const
	{
		return (CTimeManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��ʼ�����
	void CTimeSystem::Init(void)
	{
		// ��ʼ��ʱ��
		VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath();
		strPath += "/Config/TimeSystem/timesystem.cfg";
		m_timeConfig.SetConfigFile(strPath);

		struct tm t;
		// ���ʱ��
		m_timeConfig.GetInitTime(t);
		m_timer.SetStartTime(t);

		// ���ü��ٱ���
		float nMulti = m_timeConfig.GetMultipeTime();
		m_timer.SetMultiple(nMulti);

		// �����߳�
		m_pTimeThread = new CTimerThread(&m_timer);
		m_pTimeThread->Start();
	}

}

