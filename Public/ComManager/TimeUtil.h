#pragma once

#include <iostream>

namespace VR_Soft
{
	static const long long TicksPerDay =  86400000000LL;
	static const long long TicksPerHour =  3600000000LL;
	static const long long TicksPerMinute =  60000000LL;
	static const long long TicksPerSecond =   1000000LL;
	static const long long TicksPerMillisecond = 1000LL;
	static const long long TicksPerMicrosecond =    1LL;

	static const long long UnixEpoch = 62135596800000000LL;

	static const long long MaxValueTicks = 315537897599999999LL;

	// 1582-Oct-15
	static const long long GregorianStart = 49916304000000000LL;

	class VRSOFT_DLL CTimeUtil
	{
	public:
		// 构造函数
		CTimeUtil(long long ticks);
		// 构造函数
		CTimeUtil(int hours, int minutes, int seconds);
		// 构造函数
		CTimeUtil(int days, int hours, int minutes, int seconds);
		// 构造函数
		CTimeUtil(int days, int hours, int minutes, int seconds, int microseconds);
		// 析构函数
		~CTimeUtil(void);
		// 添加
		CTimeUtil Add(const CTimeUtil& ts) const;
		// 相减
		CTimeUtil Subtract(const CTimeUtil& ts) const;
		// 比较
		int Compare(const CTimeUtil& ts) const;
		// 相等
		bool Equals(const CTimeUtil& ts) const;
		// 获得日
		int Day() const;
		// 获得小时
		int Hour() const;
		// 获得分钟
		int Minute() const;
		// 获得秒
		int Second() const;
		// 获得毫秒
		int Milliseconds(void) const;
		// 获得微秒
		int Microsecond() const;
		// 获得Ticks
		long long GetTicks() const;
		// 总共天数
		double TotalDays() const;
		// 总共小时数
		double TotalHours() const;
		// 总分钟数
		double TotalMinutes() const;
		// 总秒数
		double TotalSeconds() const;
		// 总毫秒数
		double TotalMilliseconds() const;
		// 总微秒数
		double TotalMicroseconds() const;

	protected:
		// 计算ticks
		void CalculateTicks(int days, int hours, int minutes, int seconds, int microseconds);

	private:
		long long m_ticks;
	};

	// 重载操作符

	inline CTimeUtil operator+(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return ts1.Add(ts2);
	}

	inline CTimeUtil operator-(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return ts1.Subtract(ts2);
	}

	inline bool operator==(const CTimeUtil& ts1, CTimeUtil& ts2)
	{
		return ts1.Equals(ts2);
	}

	inline bool operator>(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return (ts1.Compare(ts2) > 0);
	}

	inline bool operator>=(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return (ts1.Compare(ts2) >= 0);
	}

	inline bool operator!=(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return !ts1.Equals(ts2);
	}

	inline bool operator<(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return (ts1.Compare(ts2) < 0);
	}

	inline bool operator<=(const CTimeUtil& ts1, const CTimeUtil& ts2)
	{
		return (ts1.Compare(ts2) <= 0);
	}


}
