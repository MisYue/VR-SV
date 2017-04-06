
#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	// 构造函数
	CTimeUtil::CTimeUtil(long long ticks)
		:m_ticks(ticks)
	{
	}

	// 构造函数
	CTimeUtil::CTimeUtil(int hours, int minutes, int seconds)
	{
		CalculateTicks(0, hours, minutes, seconds, 0);
	}

	// 构造函数
	CTimeUtil::CTimeUtil(int days, int hours, int minutes, int seconds)
	{
		CalculateTicks(days, hours, minutes, seconds, 0);
	}

	// 构造函数
	CTimeUtil::CTimeUtil(int days, int hours, int minutes, int seconds, int microseconds)
	{
		CalculateTicks(days, hours, minutes, seconds, microseconds);
	}

	// 析构函数
	CTimeUtil::~CTimeUtil(void)
	{
	}

	// 添加
	CTimeUtil CTimeUtil::Add(const CTimeUtil& ts) const
	{
		return CTimeUtil(m_ticks + ts.m_ticks);
	}

	// 相减
	CTimeUtil CTimeUtil::Subtract(const CTimeUtil& ts) const
	{
		return CTimeUtil(m_ticks - ts.m_ticks);
	}

	// 比较
	int CTimeUtil::Compare(const CTimeUtil& ts) const
	{
		int ret = 0;

		if (m_ticks < ts.m_ticks)
		{
			ret = -1;
		}
		if (m_ticks > ts.m_ticks)
		{
			ret = 1;
		}
		return ret;
	}

	// 相等
	bool CTimeUtil::Equals(const CTimeUtil& ts) const
	{
		return m_ticks == ts.m_ticks;
	}

	// 获得日
	int CTimeUtil::Day() const
	{
		return static_cast<int>(m_ticks / TicksPerDay);
	}

	// 获得小时
	int CTimeUtil::Hour() const
	{
		return static_cast<int>(m_ticks % TicksPerDay / TicksPerHour);
	}

	// 获得分钟
	int CTimeUtil::Minute() const
	{
		return static_cast<int>(m_ticks % TicksPerHour / TicksPerMinute);
	}

	// 获得秒
	int CTimeUtil::Second() const
	{
		return static_cast<int>(m_ticks % TicksPerMinute / TicksPerSecond);
	}

	// 获得毫秒
	int CTimeUtil::Milliseconds(void) const
	{
		return static_cast<int>(m_ticks % TicksPerSecond / TicksPerMicrosecond);
	}

	// 获得微秒
	int CTimeUtil::Microsecond() const
	{
		return static_cast<int>(m_ticks % TicksPerSecond / TicksPerMicrosecond);
	}

	// 获得Ticks
	long long CTimeUtil::GetTicks() const
	{
		return (m_ticks);
	}

	// 总共天数
	double CTimeUtil::TotalDays() const
	{
		return static_cast<double>(m_ticks) / TicksPerDay;
	}

	// 总共小时数
	double CTimeUtil::TotalHours() const
	{
		return static_cast<double>(m_ticks) / TicksPerHour;
	}

	// 总分钟数
	double CTimeUtil::TotalMinutes() const
	{
		return static_cast<double>(m_ticks) / TicksPerMinute;
	}

	// 总秒数
	double CTimeUtil::TotalSeconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerSecond;
	}

	// 总毫秒数
	double CTimeUtil::TotalMilliseconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerMillisecond;
	}

	// 总微秒数
	double CTimeUtil::TotalMicroseconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerMicrosecond;
	}

	// 计算ticks
	void CTimeUtil::CalculateTicks(int days, int hours, int minutes, int seconds, int microseconds)
	{
		m_ticks = days * TicksPerDay +
			(hours * 3600LL + minutes * 60LL + seconds) * TicksPerSecond + 
			microseconds * TicksPerMicrosecond;
	}

}

