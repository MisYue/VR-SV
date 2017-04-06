

#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

#include <time.h>
#include <stdio.h>

#include "../../Public/VRSoft.h"

#ifdef WIN32

#include <Windows.h>

struct timespec
{
	long tv_sec; 
	long tv_nsec;
};

#define exp7           10000000i64     //1E+7     //C-file part
#define exp9         1000000000i64     //1E+9
#define w2ux 116444736000000000i64     //1.jan1601 to 1.jan1970

#endif // WIN32

#ifndef WIN32
#include <sys/time.h>
#endif // WIN32

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif


namespace VR_Soft
{
	const double kPI = 3.14159265358979323846264338327950288419716939937510582;
	const double kTWOPI = 2 * kPI;

	// �����������ܽ��п��ٲ�ѯ
	static int daysInMonth[2][13] = {
		//  1   2   3   4   5   6   7   8   9   10  11  12
		{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};
	static int cumulDaysInMonth[2][13] = {
		//  1  2   3   4   5    6    7    8    9    10   11   12
		{0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
		{0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
	};


	// ���캯��
	CDateTime::CDateTime(void)
	{
		Initialise(1, 1, 1, 0, 0, 0, 0);
	}

	// ���캯��
	CDateTime::CDateTime(unsigned long long ticks)
		: m_encoded(ticks)
	{

	}

	// ���캯��
	CDateTime::CDateTime(int year, double doy)
	{
		m_encoded = CTimeUtil(static_cast<long long int>(AbsoluteDays(year, doy) * TicksPerDay)).GetTicks();
	}

	// ���캯��
	CDateTime::CDateTime(int year, int month, int day)
	{
		Initialise(year, month, day, 0, 0, 0, 0);
	}

	// ���캯��
	CDateTime::CDateTime(int year, int month, int day, int hour, int minute, int second)
	{
		Initialise(year, month, day, hour, minute, second, 0);
	}

	// ���캯�� // ֧�ֵ����뼶��
	CDateTime::CDateTime(int year, int month, int day, int hour, int minute, double second)
	{
		// ������ �� ����
		int nSec = (int)second;
		// ����С���� * 1000
		int micSec = (int)((second - nSec) * 1000);

		Initialise(year, month, day, hour, minute, nSec, micSec);
	}

	CDateTime::~CDateTime(void)
	{
	}

	// ��ʼ��
	void CDateTime::Initialise(int year, int month, int day, int hour, int minute, int second, int microsecond)
	{
		if (!IsValidYearMonthDay(year, month, day) ||
			hour < 0 || hour > 23 ||
			minute < 0 || minute > 59 ||
			second < 0 || second > 59 ||
			microsecond < 0 || microsecond > 999999)
		{
			throw 1;
		}
		m_encoded = CTimeUtil(
			AbsoluteDays(year, month, day),
			hour,
			minute,
			second,
			microsecond).GetTicks();
	}

	// ��ȡ��������
	double CDateTime::AbsoluteDays(int year, double doy) const
	{
		int previousYear = year - 1;

        /*
         * + days in previous years ignoring leap days
         * + Julian leap days before this year
         * - minus prior century years
         * + plus prior years divisible by 400 days
         */
        long long daysSoFar = 365 * previousYear
            + previousYear / 4
            - previousYear / 100
            + previousYear / 400;

        return static_cast<double>(daysSoFar) + doy - 1.0;
	}

	// ��ȡ��������
	int CDateTime::AbsoluteDays(int year, int month, int day) const
	{
		  int previousYear = year - 1;

        /*
         * days this year (0 - ...)
         * + days in previous years ignoring leap days
         * + Julian leap days before this year
         * - minus prior century years
         * + plus prior years divisible by 400 days
         */
        int result = DayOfYear(year, month, day) - 1
            + 365 * previousYear
            + previousYear / 4
            - previousYear / 100
            + previousYear / 400;

        return result;
	}

	// ��ȡʱ���������
	CTimeUtil CDateTime::TimeOfDay() const
	{
		return CTimeUtil(GetTicks() % TicksPerDay);
	}

	// ��õ�ǰ������һ�ܵ�ֵ
	int CDateTime::DayOfWeek() const
	{
		return static_cast<int>(((m_encoded / TicksPerDay) + 1LL) % 7LL);
	}

	// ��ȡ������һ���ڵ�����
	int CDateTime::DayOfYear(int year, int month, int day) const
	{
		if (!IsValidYearMonthDay(year, month, day))
		{
			throw 1;
		}

		int daysThisYear = day;

		if (IsLeapYear(year))
		{
			daysThisYear += cumulDaysInMonth[1][month];
		}
		else
		{
			daysThisYear += cumulDaysInMonth[0][month];
		}

		return daysThisYear;
	}

	// �Ƿ����
	bool CDateTime::Equals(const CDateTime& dt) const
	{
		return (m_encoded == dt.m_encoded);
	}

	// �Ƚ�
	int CDateTime::Compare(const CDateTime& dt) const
	{
		int ret = 0;

		if (m_encoded < dt.m_encoded)
		{
			return -1;
		}
		else if (m_encoded > dt.m_encoded)
		{
			return 1;
		}

		return ret;
	}

	// �������
	CDateTime CDateTime::AddYears(const int years) const
	{
		return AddMonths(years * 12);
	}

	// �������
	CDateTime CDateTime::AddMonths(const int months) const
	{
		int year;
		int month;
		int day;
		FromTicks(year, month, day);
		month += months % 12;
		year += months / 12;

		if (month < 1)
		{
			month += 12;
			--year;
		}
		else if (month > 12)
		{
			month -= 12;
			++year;
		}

		int maxday = DaysInMonth(year, month);
		day = min(day, maxday);

		return CDateTime(year, month, day).Add(TimeOfDay());
	}

	// ���ʱ���������
	CDateTime CDateTime::Add(const CTimeUtil& t) const
	{
		return AddTicks(t.GetTicks());
	}

	// �������
	CDateTime CDateTime::AddDays(const double days) const
	{
		return AddMicroseconds(days * 86400000000.0);
	}

	//���Сʱ
	CDateTime CDateTime::AddHours(const double hours) const
	{
		return AddMicroseconds(hours * 3600000000.0);
	}

	// ��ӷ�����
	CDateTime CDateTime::AddMinutes(const double minutes) const
	{
		return AddMicroseconds(minutes * 60000000.0);
	}

	// ���������
	CDateTime CDateTime::AddSeconds(const double seconds) const
	{
		return AddMicroseconds(seconds * 1000000.0);
	}

	// ��Ӻ���
	CDateTime CDateTime::AddMillisecond(const double millisecond) const
	{
		return AddMicroseconds(millisecond * 1000.0);
	}

	// ��Ӻ�����
	CDateTime CDateTime::AddMicroseconds(const double microseconds) const
	{
		long long ticks = static_cast<long long>(microseconds * TicksPerMicrosecond);
		return AddTicks(ticks);
	}

	// ���tickʱ��
	CDateTime CDateTime::AddTicks(long long ticks) const
	{
		return CDateTime(m_encoded + ticks);
	}

	// ���tickʱ��
	long long CDateTime::GetTicks(void) const
	{
		return m_encoded;
	}

	// ��tick�л�ȡ������
	void CDateTime::FromTicks(int& year, int& month, int& day) const
	{
		int totalDays = static_cast<int>(m_encoded / TicksPerDay);
        
        /*
         * number of 400 year cycles
         */
        int num400 = totalDays / 146097;
        totalDays -= num400 * 146097;
        /*
         * number of 100 year cycles
         */
        int num100 = totalDays / 36524;
        if (num100 == 4)
        {
            /*
             * last day of the last leap century
             */
            num100 = 3;
        }
        totalDays -= num100 * 36524;
        /*
         * number of 4 year cycles
         */
        int num4 = totalDays / 1461;
        totalDays -= num4 * 1461;
        /*
         * number of years
         */
        int num1 = totalDays / 365;
        if (num1 == 4)
        {
            /*
             * last day of the last leap olympiad
             */
            num1 = 3;
        }
        totalDays -= num1 * 365;

        /*
         * find year
         */
        year = (num400 * 400) + (num100 * 100) + (num4 * 4) + num1 + 1;
        
        /*
         * convert day of year to month/day
         */
        const int* daysInMonthPtr;
        if (IsLeapYear(year))
        {
            daysInMonthPtr = daysInMonth[1];
        }
        else
        {
            daysInMonthPtr = daysInMonth[0];
        }

        month = 1;
        while (totalDays >= daysInMonthPtr[month] && month <= 12)
        {
            totalDays -= daysInMonthPtr[month++];
        }

        day = totalDays + 1;
	}

	// �����
	int CDateTime::Year() const
	{
		int year;
		int month;
		int day;
		FromTicks(year, month, day);
		return year;
	}

	// �����
	int CDateTime::Month() const
	{
		int year;
		int month;
		int day;
		FromTicks(year, month, day);
		return month;
	}

	// �����
	int CDateTime::Day() const
	{
		int year;
		int month;
		int day;
		FromTicks(year, month, day);
		return day;
	}

	// ���Сʱ
	int CDateTime::Hour() const
	{
		 return static_cast<int>(m_encoded % TicksPerDay / TicksPerHour);
	}

	// ��÷���
	int CDateTime::Minute() const
	{
		return static_cast<int>(m_encoded % TicksPerHour / TicksPerMinute);
	}

	// �����
	int CDateTime::Second() const
	{
		return static_cast<int>(m_encoded % TicksPerMinute / TicksPerSecond);
	}

	// ��ú���
	int CDateTime::Microsecond() const
	{
		 return static_cast<int>(m_encoded % TicksPerSecond / TicksPerMicrosecond);
	}

	// ���������
	double CDateTime::ToJulian() const
	{
		CTimeUtil ts = CTimeUtil(GetTicks());
		m_dJulian = ts.TotalDays() + 1721425.5;
		return m_dJulian;
	}

	double CDateTime::GetJulian(void) const
	{
		return (m_dJulian);
	}

	// ת��Ϊ�������α�׼ʱ��
	double CDateTime::ToGreenwichSiderealTime() const
	{
		const double t = (ToJulian() - 2451545.0) / 36525.0;

		// Rotation angle in arcseconds
		double theta = 67310.54841
			+ (876600.0 * 3600.0 + 8640184.812866) * t
			+ 0.093104 * t * t
			- 0.0000062 * t * t * t;

		// 360.0 / 86400.0 = 1.0 / 240.0
		double dTheta = (theta / 240.0) * kPI / 180.0;
		return dTheta - kTWOPI * floor(dTheta / kTWOPI);
	}

	// ת��Ϊ����ƽ������ʱ��GMST�ӹ۲��ߵ�γ�ȣ�
	double CDateTime::ToLocalMeanSiderealTime(const double lon) const
	{
		double dTheta = ToGreenwichSiderealTime() + lon;
		return dTheta - kTWOPI * floor(dTheta / kTWOPI);
	}

	// ת�����ַ���
	VRString CDateTime::ToVRString(void) const
	{
		VRStringStream ss;
		int year;
		int month;
		int day;
		FromTicks(year, month, day);
		ss << std::right << std::setfill('0');
		ss << std::setw(4) << year << "-";
		ss << std::setw(2) << month << "-";
		ss << std::setw(2) << day << " ";
		ss << std::setw(2) << Hour() << ":";
		ss << std::setw(2) << Minute() << ":";
		ss << std::setw(2) << Second() << ".";
		ss << std::setw(6) << Microsecond() << " UTC";
		return ss.str();
	}

#ifdef WIN32
	void unix_time(struct timespec *spec)
	{ 
		long wintime;
		GetSystemTimeAsFileTime((FILETIME*)&wintime); 
		wintime -=w2ux;  spec->tv_sec  =wintime / exp7;                 
		spec->tv_nsec =wintime % exp7 *100;
	}
#endif // WIN32

	int current_utc_time(struct timespec *ts)
	{

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		ts->tv_sec = mts.tv_sec;
		ts->tv_nsec = mts.tv_nsec;

#elif defined(WIN32)
		static  struct timespec startspec; static double ticks2nano;
		static __int64 startticks, tps =0;    __int64 tmp, curticks;

		QueryPerformanceFrequency((LARGE_INTEGER*)&tmp); //some strange system can

		if (tps !=tmp) 
		{
			tps =tmp; //init ~~ONCE         //possibly change freq ?

			QueryPerformanceCounter((LARGE_INTEGER*)&startticks);
			unix_time(&startspec); ticks2nano =(double)exp9 / tps;
		}

		QueryPerformanceCounter((LARGE_INTEGER*)&curticks); 
		curticks -=startticks;

		ts->tv_sec  =startspec.tv_sec   +  (curticks / tps);
		ts->tv_nsec =startspec.tv_nsec  + (double)(curticks % tps) * ticks2nano;

		if (!(ts->tv_nsec < exp9)) 
		{
			ts->tv_sec++; ts->tv_nsec -=exp9; 
		}

#else
		clock_gettime(CLOCK_REALTIME, ts);
#endif

		return 1;
	}

	CDateTime CDateTime::Now(bool microseconds /*= false*/)
	{
		CDateTime dt;

		struct timespec ts;

		if (current_utc_time(&ts))
		{
			if (microseconds)
			{
				dt = CDateTime(UnixEpoch
					+ ts.tv_sec * TicksPerSecond
					+ ts.tv_nsec / 1000LL * TicksPerMicrosecond);
			}
			else
			{
				dt = CDateTime(UnixEpoch
					+ ts.tv_sec * TicksPerSecond);
			}
		}
		else
		{
			throw 1;
		}

		return dt;
	}

	// �ж��Ƿ�Ϊ����
	bool CDateTime::IsLeapYear(int year)
	{
		if (!IsValidYear(year))
		{
			throw 1;
		}

		return (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0);
	}

	// �ж����Ƿ���Ч
	bool CDateTime::IsValidYear(int year)
	{
		bool valid = true;
		if (year < 1 || year > 9999)
		{
			valid = false;
		}
		return valid;
	}

	// �ж������Ƿ���Ч
	bool CDateTime::IsValidYearMonth(int year, int month)
	{
		bool valid = true;
		if (IsValidYear(year))
		{
			if (month < 1 || month > 12)
			{
				valid = false;
			}
		}
		else 
		{
			valid = false;
		}
		return valid;
	}

	// �ж���Ҳ���Ƿ���Ч
	bool CDateTime::IsValidYearMonthDay(int year, int month, int day)
	{
		bool valid = true;
		if (IsValidYearMonth(year, month))
		{
			if (day < 1 || day > DaysInMonth(year, month))
			{
				valid = false;
			}
		}
		else
		{
			valid = false;
		}
		return valid;
	}

	// ��ȡһ���µ�����
	int CDateTime::DaysInMonth(int year, int month)
	{
		if (!IsValidYearMonth(year, month))
		{
			throw 1;
		}

		const int* daysInMonthPtr;

		if (IsLeapYear(year))
		{
			daysInMonthPtr = daysInMonth[1];
		}
		else
		{
			daysInMonthPtr = daysInMonth[0];
		}

		return daysInMonthPtr[month];
	}

}

