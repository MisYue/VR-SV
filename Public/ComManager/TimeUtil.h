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
		// ���캯��
		CTimeUtil(long long ticks);
		// ���캯��
		CTimeUtil(int hours, int minutes, int seconds);
		// ���캯��
		CTimeUtil(int days, int hours, int minutes, int seconds);
		// ���캯��
		CTimeUtil(int days, int hours, int minutes, int seconds, int microseconds);
		// ��������
		~CTimeUtil(void);
		// ���
		CTimeUtil Add(const CTimeUtil& ts) const;
		// ���
		CTimeUtil Subtract(const CTimeUtil& ts) const;
		// �Ƚ�
		int Compare(const CTimeUtil& ts) const;
		// ���
		bool Equals(const CTimeUtil& ts) const;
		// �����
		int Day() const;
		// ���Сʱ
		int Hour() const;
		// ��÷���
		int Minute() const;
		// �����
		int Second() const;
		// ��ú���
		int Milliseconds(void) const;
		// ���΢��
		int Microsecond() const;
		// ���Ticks
		long long GetTicks() const;
		// �ܹ�����
		double TotalDays() const;
		// �ܹ�Сʱ��
		double TotalHours() const;
		// �ܷ�����
		double TotalMinutes() const;
		// ������
		double TotalSeconds() const;
		// �ܺ�����
		double TotalMilliseconds() const;
		// ��΢����
		double TotalMicroseconds() const;

	protected:
		// ����ticks
		void CalculateTicks(int days, int hours, int minutes, int seconds, int microseconds);

	private:
		long long m_ticks;
	};

	// ���ز�����

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
