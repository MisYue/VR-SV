
#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	// ���캯��
	CTimeUtil::CTimeUtil(long long ticks)
		:m_ticks(ticks)
	{
	}

	// ���캯��
	CTimeUtil::CTimeUtil(int hours, int minutes, int seconds)
	{
		CalculateTicks(0, hours, minutes, seconds, 0);
	}

	// ���캯��
	CTimeUtil::CTimeUtil(int days, int hours, int minutes, int seconds)
	{
		CalculateTicks(days, hours, minutes, seconds, 0);
	}

	// ���캯��
	CTimeUtil::CTimeUtil(int days, int hours, int minutes, int seconds, int microseconds)
	{
		CalculateTicks(days, hours, minutes, seconds, microseconds);
	}

	// ��������
	CTimeUtil::~CTimeUtil(void)
	{
	}

	// ���
	CTimeUtil CTimeUtil::Add(const CTimeUtil& ts) const
	{
		return CTimeUtil(m_ticks + ts.m_ticks);
	}

	// ���
	CTimeUtil CTimeUtil::Subtract(const CTimeUtil& ts) const
	{
		return CTimeUtil(m_ticks - ts.m_ticks);
	}

	// �Ƚ�
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

	// ���
	bool CTimeUtil::Equals(const CTimeUtil& ts) const
	{
		return m_ticks == ts.m_ticks;
	}

	// �����
	int CTimeUtil::Day() const
	{
		return static_cast<int>(m_ticks / TicksPerDay);
	}

	// ���Сʱ
	int CTimeUtil::Hour() const
	{
		return static_cast<int>(m_ticks % TicksPerDay / TicksPerHour);
	}

	// ��÷���
	int CTimeUtil::Minute() const
	{
		return static_cast<int>(m_ticks % TicksPerHour / TicksPerMinute);
	}

	// �����
	int CTimeUtil::Second() const
	{
		return static_cast<int>(m_ticks % TicksPerMinute / TicksPerSecond);
	}

	// ��ú���
	int CTimeUtil::Milliseconds(void) const
	{
		return static_cast<int>(m_ticks % TicksPerSecond / TicksPerMicrosecond);
	}

	// ���΢��
	int CTimeUtil::Microsecond() const
	{
		return static_cast<int>(m_ticks % TicksPerSecond / TicksPerMicrosecond);
	}

	// ���Ticks
	long long CTimeUtil::GetTicks() const
	{
		return (m_ticks);
	}

	// �ܹ�����
	double CTimeUtil::TotalDays() const
	{
		return static_cast<double>(m_ticks) / TicksPerDay;
	}

	// �ܹ�Сʱ��
	double CTimeUtil::TotalHours() const
	{
		return static_cast<double>(m_ticks) / TicksPerHour;
	}

	// �ܷ�����
	double CTimeUtil::TotalMinutes() const
	{
		return static_cast<double>(m_ticks) / TicksPerMinute;
	}

	// ������
	double CTimeUtil::TotalSeconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerSecond;
	}

	// �ܺ�����
	double CTimeUtil::TotalMilliseconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerMillisecond;
	}

	// ��΢����
	double CTimeUtil::TotalMicroseconds() const
	{
		return static_cast<double>(m_ticks) / TicksPerMicrosecond;
	}

	// ����ticks
	void CTimeUtil::CalculateTicks(int days, int hours, int minutes, int seconds, int microseconds)
	{
		m_ticks = days * TicksPerDay +
			(hours * 3600LL + minutes * 60LL + seconds) * TicksPerSecond + 
			microseconds * TicksPerMicrosecond;
	}

}

