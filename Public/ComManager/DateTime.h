/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���������                                                    */
/* ʱ�䣺 2016-04-20                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		CDateTime(void);
		// ���캯��
		CDateTime(unsigned long long ticks);
		 // ���캯��
		CDateTime(int year, double doy);
		// ���캯��
		CDateTime(int year, int month, int day);
		// ���캯��
		CDateTime(int year, int month, int day, int hour, int minute, int second);
		// ���캯�� // ֧�ֵ����뼶��
		CDateTime(int year, int month, int day, int hour, int minute, double second);
		// ��������
		~CDateTime(void);

	public:
		// ��ʼ��
		void Initialise(int year, int month, int day, int hour, int minute,	int second,	int microsecond);
		// ��ȡ��������
		double AbsoluteDays(int year, double doy) const;
		// ��ȡ��������
		int AbsoluteDays(int year, int month, int day) const;
		// ��ȡʱ���������
		CTimeUtil TimeOfDay() const;
		// ��õ�ǰ������һ�ܵ�ֵ
		int DayOfWeek() const;
		// ��ȡ������һ���ڵ�����
		int DayOfYear(int year, int month, int day) const;
		// �Ƿ����
		bool Equals(const CDateTime& dt) const;
		// �Ƚ�
		int Compare(const CDateTime& dt) const;
		// �������
		CDateTime AddYears(const int years) const;
		// �������
		CDateTime AddMonths(const int months) const;
		// ���ʱ���������
		CDateTime Add(const CTimeUtil& t) const;
		// �������
		CDateTime AddDays(const double days) const;
		//���Сʱ
		CDateTime AddHours(const double hours) const;
		// ��ӷ�����
		CDateTime AddMinutes(const double minutes) const;
		// ���������
		CDateTime AddSeconds(const double seconds) const;
		// ��Ӻ���
		CDateTime AddMillisecond(const double millisecond) const;
		// ��Ӻ�����
		CDateTime AddMicroseconds(const double microseconds) const;
		// ���tickʱ��
		CDateTime AddTicks(long long ticks) const;
		// ���tickʱ��
		long long GetTicks(void) const ;
		// ��tick�л�ȡ������
		void FromTicks(int& year, int& month, int& day) const;
		// �����
		int Year() const;
		// �����
		int Month() const;
		// �����
		int Day() const;
		// ���Сʱ
		int Hour() const;
		// ��÷���
		int Minute() const;
		// �����
		int Second() const;
		// ��ú���
		int Microsecond() const;
		// ���������
		double ToJulian() const;
		// ���������
		double GetJulian(void) const;
		// ת��Ϊ�������α�׼ʱ��
		double ToGreenwichSiderealTime() const;
		// ת��Ϊ����ƽ������ʱ��GMST�ӹ۲��ߵ�γ�ȣ�
		double ToLocalMeanSiderealTime(const double lon) const;
		// ת�����ַ���
		VRString ToVRString(void) const;

	public: 
		// ��õ�ǰʱ��
		static CDateTime Now(bool microseconds = false);
		// �ж��Ƿ�Ϊ����
		static bool IsLeapYear(int year);
		// �ж����Ƿ���Ч
		static bool IsValidYear(int year);
		// �ж������Ƿ���Ч
		static bool IsValidYearMonth(int year, int month);
		// �ж���Ҳ���Ƿ���Ч
		static bool IsValidYearMonthDay(int year, int month, int day);
		// ��ȡһ���µ�����
		static int DaysInMonth(int year, int month);

	private:
		unsigned long long m_encoded;
		mutable double m_dJulian; // ����ʱ�����������ʱ�䣬 ���ٷ�����̣� ����ڴ˱���һ��ʱ�䲻��ÿ�ν���ת��
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