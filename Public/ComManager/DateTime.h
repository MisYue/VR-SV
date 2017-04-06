/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真管理类                                                    */
/* 时间： 2016-04-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _DATETIME_H_
#define  _DATETIME_H_

#pragma once

#include <iostream>

#include "TimeUtil.h"

namespace VR_Soft
{
	class VRSOFT_DLL CDateTime
	{
	public:
		// 构造函数
		CDateTime(void);
		// 构造函数
		CDateTime(unsigned long long ticks);
		 // 构造函数
		CDateTime(int year, double doy);
		// 构造函数
		CDateTime(int year, int month, int day);
		// 构造函数
		CDateTime(int year, int month, int day, int hour, int minute, int second);
		// 构造函数 // 支持到毫秒级别
		CDateTime(int year, int month, int day, int hour, int minute, double second);
		// 析构函数
		~CDateTime(void);

	public:
		// 初始化
		void Initialise(int year, int month, int day, int hour, int minute,	int second,	int microsecond);
		// 获取绝对天数
		double AbsoluteDays(int year, double doy) const;
		// 获取绝对天数
		int AbsoluteDays(int year, int month, int day) const;
		// 获取时间操作对象
		CTimeUtil TimeOfDay() const;
		// 获得当前日期在一周的值
		int DayOfWeek() const;
		// 获取日期在一年内的天数
		int DayOfYear(int year, int month, int day) const;
		// 是否相等
		bool Equals(const CDateTime& dt) const;
		// 比较
		int Compare(const CDateTime& dt) const;
		// 添加年数
		CDateTime AddYears(const int years) const;
		// 添加月数
		CDateTime AddMonths(const int months) const;
		// 添加时间操作对象
		CDateTime Add(const CTimeUtil& t) const;
		// 添加天数
		CDateTime AddDays(const double days) const;
		//添加小时
		CDateTime AddHours(const double hours) const;
		// 添加分钟数
		CDateTime AddMinutes(const double minutes) const;
		// 添加秒钟数
		CDateTime AddSeconds(const double seconds) const;
		// 添加毫秒
		CDateTime AddMillisecond(const double millisecond) const;
		// 添加毫秒数
		CDateTime AddMicroseconds(const double microseconds) const;
		// 添加tick时钟
		CDateTime AddTicks(long long ticks) const;
		// 获得tick时钟
		long long GetTicks(void) const ;
		// 从tick中获取年月日
		void FromTicks(int& year, int& month, int& day) const;
		// 获得年
		int Year() const;
		// 获得月
		int Month() const;
		// 获得日
		int Day() const;
		// 获得小时
		int Hour() const;
		// 获得分钟
		int Minute() const;
		// 获得秒
		int Second() const;
		// 获得毫秒
		int Microsecond() const;
		// 获得儒略日
		double ToJulian() const;
		// 获得儒略日
		double GetJulian(void) const;
		// 转换为格林尼治标准时间
		double ToGreenwichSiderealTime() const;
		// 转换为当地平均恒星时（GMST加观测者的纬度）
		double ToLocalMeanSiderealTime(const double lon) const;
		// 转换到字符串
		VRString ToVRString(void) const;

	public: 
		// 获得当前时间
		static CDateTime Now(bool microseconds = false);
		// 判断是否为闰年
		static bool IsLeapYear(int year);
		// 判断年是否有效
		static bool IsValidYear(int year);
		// 判断年月是否有效
		static bool IsValidYearMonth(int year, int month);
		// 判断年也日是否有效
		static bool IsValidYearMonthDay(int year, int month, int day);
		// 获取一个月的天数
		static int DaysInMonth(int year, int month);

	private:
		unsigned long long m_encoded;
		mutable double m_dJulian; // 仿真时间采用儒略日时间， 加速仿真过程， 因此在此保存一次时间不用每次进行转换
	};

	inline std::ostream& operator<<(std::ostream& strm, const CDateTime& dt)
	{
		return strm << dt.ToVRString();
	}

	inline CDateTime operator+(const CDateTime& dt, CTimeUtil ts)
	{
		long long int res = dt.GetTicks() + ts.GetTicks();
		if (res < 0 || res > MaxValueTicks)
		{
			throw 1;
		}

		return CDateTime(res);
	}

	inline CDateTime operator-(const CDateTime& dt, const CTimeUtil& ts)
	{
		long long int res = dt.GetTicks() - ts.GetTicks();
		if (res < 0 || res > MaxValueTicks)
		{
			throw 1;
		}

		return CDateTime(res);
	}

	inline CTimeUtil operator-(const CDateTime& dt1, const CDateTime& dt2)
	{
		return CTimeUtil(dt1.GetTicks() - dt2.GetTicks());
	}

	inline bool operator==(const CDateTime& dt1, const CDateTime& dt2)
	{
		return dt1.Equals(dt2);
	}

	inline bool operator>(const CDateTime& dt1, const CDateTime& dt2)
	{
		return (dt1.Compare(dt2) > 0);
	}

	inline bool operator>=(const CDateTime& dt1, const CDateTime& dt2)
	{
		return (dt1.Compare(dt2) >= 0);
	}

	inline bool operator!=(const CDateTime& dt1, const CDateTime& dt2)
	{
		return !dt1.Equals(dt2);
	}

	inline bool operator<(const CDateTime& dt1, const CDateTime& dt2)
	{
		return (dt1.Compare(dt2) < 0);
	}

	inline bool operator<=(const CDateTime& dt1, const CDateTime& dt2)
	{
		return (dt1.Compare(dt2) <= 0);
	}
}

#endif // ! _DATETIME_H_