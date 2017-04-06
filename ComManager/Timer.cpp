

#include "../../Public/VRSoft.h"
#include "Timer.h"

namespace VR_Soft
{
	// 析构函数
	CTimer::~CTimer(void)
	{
	}

	// 设置开始时间
	void CTimer::SetStartTick()
	{
		m_startTick = Tick();
	}

	// 设置开始时间
	void CTimer::SetStartTick(Timer_t t)
	{
		m_startTick = t;
	}

	// 获得开始时间
	VR_Soft::Timer_t CTimer::GetStartTick() const
	{
		return (m_startTick);
	}

#ifdef WIN32

#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>

	// 构造函数
	CTimer::CTimer(void)
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
	}

	Timer_t CTimer::Tick() const
	{
		LARGE_INTEGER qpc;
		if (QueryPerformanceCounter(&qpc))
		{
			return qpc.QuadPart;
		}
		else
		{
			return 0;
		}
	}

	// 相差时间秒
	double CTimer::DeltaSec(Timer_t t1, Timer_t t2) const
	{
		return ((double)(t2 - t1) * m_secsPerTick);
	}

	// 相差时间毫秒
	double CTimer::DeltaMil(Timer_t t1, Timer_t t2) const
	{
		return (DeltaSec(t1,t2)*1e3);
	}

	// 相差时间微秒
	double CTimer::DeltaMicro(Timer_t t1, Timer_t t2) const
	{
		return (DeltaSec(t1,t2)*1e6);
	}

	// 相差时间纳秒
	double CTimer::DeltaNano(Timer_t t1, Timer_t t2) const
	{
		return (DeltaSec(t1,t2)*1e9);
	}

	// 每一个时钟的秒数
	double CTimer::GetSecondsPerTick() const
	{
		return (m_secsPerTick);
	}

#else
#include <unistd.h>

	// 构造函数
	CTimer::CTimer(void)
	{
		m_secsPerTick = (1.0 / (double) 1000000);

		setStartTick();
	}

#if defined(_POSIX_TIMERS) && ( _POSIX_TIMERS > 0 ) && defined(_POSIX_MONOTONIC_CLOCK)
#include <time.h>

	Timer_t CTimer::Tick() const
	{
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return ((osg::Timer_t)ts.tv_sec)*1000000+(osg::Timer_t)ts.tv_nsec/1000;
	}
#else
#include <sys/time.h>

	Timer_t CTimer::Tick() const
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
	}
#endif

#endif


}
