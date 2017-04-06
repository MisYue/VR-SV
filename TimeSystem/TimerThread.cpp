#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "Timer.h"
#include "TimerThread.h"

#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>


namespace VR_Soft
{
	CTimerThread::CTimerThread(CTimer* pTimer):CVRSoftThread(),m_pTimer(pTimer),m_bSubSuspend(false)
	{
	}


	CTimerThread::~CTimerThread(void)
	{
	}

	// ÔÝÍ£
	void CTimerThread::SubSuspend(bool bSubSuspend)
	{
		m_bSubSuspend = bSubSuspend;
	}

	// Èí¼þÑ­»·
	void CTimerThread::Run()
	{
		if (NULL == m_pTimer)
		{
			return;
		}
		
		TIME_T llRun = m_pTimer->GetSystemTick();
		// ÈÃÏß³ÌÐÝÃß
		//boost::this_thread::sleep(boost::posix_time::seconds(0.00001));

		if (!m_bSubSuspend)
		{
			m_pTimer->m_curTick += (llRun - m_pTimer->m_starSystemTick);
		}
		else
		{
			// ÈÃÏß³ÌÐÝÃß
			boost::this_thread::sleep(boost::posix_time::seconds(1));
		}
		

		
		m_pTimer->m_starSystemTick = llRun;
		
	}
}

