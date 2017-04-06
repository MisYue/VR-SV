


#include <stdint.h>

#if defined(__GUNC__)
#include <sys/time.h>
#include <unistd.h>
#define EPOCHFILETIME 11644473600000000ULL
#else
#include <Windows.h>
#include <time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

#include "../../Public/VRSoft.h"

inline int RAND_RAGNE(int a, int b) { int rang = b - a + 1 ; int nVal = rand() % rang + a;  return(nVal);}

namespace VR_Soft
{
	// 获得时间
	uint64_t GetTime(void);

	class CVRGUID
	{
	public:
		// 构造函数
		CVRGUID(void);
		// 析构函数
		~CVRGUID(void);
		// 设置时间
		void SetEpoch(uint64_t epoch);
		// 获得初始时间
		uint64_t GetEpoch(void) const { return (m_epoch); }
		// 设置机器码
		void SetMachine(int32_t machine);
		// 获得机器码
		int32_t GetMachine(void)  const { return (m_machine); }

	public:
		static int32_t m_sepuence;

	private:
		uint64_t m_epoch;
		uint64_t m_time;
		int32_t m_machine;
		
	};

	int32_t CVRGUID::m_sepuence = 0;

	// 构造函数
	CVRGUID::CVRGUID( void )
		:m_epoch(0),
		m_time(0),
		m_machine(0)
	{

	}

	// 析构函数
	CVRGUID::~CVRGUID( void )
	{

	}

	// 设置时间
	void CVRGUID::SetEpoch( uint64_t epoch )
	{
		m_epoch = epoch;
	}

	// 设置机器码
	void CVRGUID::SetMachine( int32_t machine )
	{
		m_machine = machine;
	}

	//////////////////////////////////////////////////////////////////////////
	CGUID::CGUID()
	{

	}

	CGUID::~CGUID()
	{

	}
	// 生成UUID
	int64_t CGUID::Generate(void)
	{
		int64_t value = 0;

		CVRGUID vrGuid;
		vrGuid.SetEpoch(uint64_t(1367505795100));

		srand((int)time(NULL));

		int nRange = RAND_RAGNE(100, 999);
		vrGuid.SetMachine(uint32_t(nRange));

		/// 获得时间
		uint64_t time = GetTime() - vrGuid.GetEpoch();

		// 保留后41位时间

		value = time << 22;

		// 中间10位机器ID
		value |= (vrGuid.GetMachine() & 0x3FF) << 12;

		// 最后12位序列号
		value |= CVRGUID::m_sepuence++ & 0xFFF;
		if ( CVRGUID::m_sepuence == 0x1000)
		{
			 CVRGUID::m_sepuence = 0;
		}

		return (value);

	}

	//////////////////////////////////////////////////////////////////////////
	uint64_t GetTime( void )
	{
#ifdef __GUNC__
		struct timeval tv;
		gettimeofday(&tv, NULL);
		uint64 time = tv.tv_usec;
		time /= 1000;
		time += (tv.tv_sec * 1000);
		return time;
#else
		FILETIME filetime;
		uint64_t time = 0;
		GetSystemTimeAsFileTime(&filetime);

		time |= filetime.dwHighDateTime;
		time <<= 32;
		time |= filetime.dwLowDateTime;

		time /= 10;
		time -= EPOCHFILETIME;
		return (time/1000);
#endif // __GUNC__

	}
}


