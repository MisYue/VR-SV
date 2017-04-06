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

	// 加速
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

	// 减速
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

	// 暂停
	void CTimeSystem::Suspend(void)
	{
		m_pTimeThread->SubSuspend(true);
	}

	// 恢复
	void CTimeSystem::Recover(void)
	{
		m_pTimeThread->Start();
		m_pTimeThread->SubSuspend(false);
	}

	// 停止（复位）
	void CTimeSystem::Stop(void)
	{
		m_pTimeThread->SubSuspend(true);
		m_timer.Stop();
	}

	// 开始
	void CTimeSystem::Start(void)
	{
		m_pTimeThread->Start();
		m_pTimeThread->SubSuspend(false);
	}

	// 跳转
	void CTimeSystem::Jump(struct tm& t)
	{
		m_timer.SetStartTime(t);
	}

	// 获得类型
	const VRString& CTimeSystem::GetTypeName(void) const
	{
		return (CTimeManagerFactory::FACTORY_TYPE_NAME);
	}

	// 初始化插件
	void CTimeSystem::Init(void)
	{
		// 初始化时间
		VRString strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath();
		strPath += "/Config/TimeSystem/timesystem.cfg";
		m_timeConfig.SetConfigFile(strPath);

		struct tm t;
		// 获得时间
		m_timeConfig.GetInitTime(t);
		m_timer.SetStartTime(t);

		// 设置加速倍数
		float nMulti = m_timeConfig.GetMultipeTime();
		m_timer.SetMultiple(nMulti);

		// 创建线程
		m_pTimeThread = new CTimerThread(&m_timer);
		m_pTimeThread->Start();
	}

}

