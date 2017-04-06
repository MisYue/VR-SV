#include <time.h>
#include <strstream>
#include <iomanip>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "TimerThread.h"
#include "Timer.h"

namespace VR_Soft
{

#ifdef WIN32

#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>

	// 构造函数
	CTimer::CTimer() : m_starTick(0), m_curTick(0), m_dMultiple(1.0)
	{
		LARGE_INTEGER frequency;
		if(QueryPerformanceFrequency(&frequency))
		{
			m_secsPerTick = 1.0/(double)frequency.QuadPart;
		}
		else
		{
			m_secsPerTick = 1.0;
		}

		// 设置当前倍数
		m_dCurMultiple = m_secsPerTick;
		
		SetStartTick();
		SetStartSystemTick();
	}


	TIME_T CTimer::GetSystemTick() const
	{
		LARGE_INTEGER frequency;
		if (QueryPerformanceCounter(&frequency))
		{
			return (frequency.QuadPart);
		}
		else
		{
			return (0);
		}
	}

	// 记录系统运行的时间
	void CTimer::SetStartSystemTick(void)
	{
		m_starSystemTick = GetSystemTick();
	}

#else
#include <unistd.h>

	// 构造函数
	CTimer::CTimer( void ): m_starTick(0), m_curTick(0)
	{
		m_secsPerTick = (1.0 / (double) 1000000);

		// 设置当前倍数
		m_dCurMultiple = m_secsPerTick;

		SetStartTick();
		SetStartSystemTick();
	}

#if defined(_POSIX_TIMERS) && ( _POSIX_TIMERS > 0 ) && defined(_POSIX_MONOTONIC_CLOCK)
#include <time.h>

	Timer_t CTimer::GetSystemTick() const
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
		/*struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return ((osg::Timer_t)ts.tv_sec)*1000000+(osg::Timer_t)ts.tv_nsec/1000;*/
	}
#else
#include <sys/time.h>

	Timer_t CTimer::tick() const
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
	}

#endif

#endif

	// 析构函数
	CTimer::~CTimer(void)
	{

	}

	bool CTimer::SetStartTime(const TIME_T t) 
	{
		m_starTick = t;
		return (true);
	}

	bool CTimer::SetStartTime(const int nyear, const int month, const int day, \
		const int hour, const int min, const int sec)
	{
		struct tm t;
		t.tm_year = nyear - 1900;
		t.tm_mon = month;
		t.tm_mday = day;
		t.tm_hour = hour;
		t.tm_min = min;
		t.tm_sec = sec;
		time_t t_t = mktime(&t);
		SetStartTime(t_t);

		return (true);
	}

	// 设置起始时间
	bool CTimer::SetStartTime(struct tm& t)
	{
		time_t t_t = mktime(&t);
		SetStartTime(t_t);

		return (true);
	}

	TIME_T CTimer::GetSimulationTime(void) const
	{
		TIME_T tick = GetTick() * m_dCurMultiple;
		return (tick  + m_starTick);
	}

	// 获得当前仿真时间
	 struct tm* CTimer::GetSimulationTimeTm(void) const
	{
		TIME_T ti = GetSimulationTime()  * m_dCurMultiple;
		return (localtime(&ti));
	}

	// 系统运行时间
	TIME_T CTimer::GetTick() const
	{
		return (m_curTick);
	}

	// 初始化开始的计数
	bool CTimer::SetStartTick(void)
	{
		m_starTick = GetSystemTick();
		return (true);
	}

	double CTimer::Milliseconds(void) const
	{
		double dMs = GetTick() * m_dCurMultiple;
		int nMs = (int)((dMs - (int)dMs) * 1000);
		return (nMs * 0.001);
	}

	// 获得时分秒
	VR_Soft::VRString CTimer::GetSimulationString(void) const
	{
		TIME_T ti = GetSimulationTime();
		struct tm*  t = localtime(&ti);

		
		char a[256] = {0};
		sprintf(a, "%d-%d-%d %d:%d:%f",\
			t->tm_year+1900,t->tm_mon, t->tm_mday, \
			t->tm_hour,t->tm_min, t->tm_sec + Milliseconds());

		return (a);
	}

	// 设置加速倍数
	void CTimer::SetMultiple(const double dMul)
	{
		// 判断是否有效
		if (dMul < 0.0)
		{
			return ;
		}

		m_dMultiple = dMul;

		m_dCurMultiple = m_secsPerTick * dMul;
	}

	// 获得加速倍数
	double CTimer::GetMultiple(void) const
	{
		return (m_dMultiple);
	}

	// 停止
	void CTimer::Stop()
	{
		m_curTick = 0;
	}

}