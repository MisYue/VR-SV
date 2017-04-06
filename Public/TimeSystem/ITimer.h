/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间计时器接口		                                        */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITIMER_H_
#define _PUBLIC_ITIMER_H_

namespace VR_Soft
{
	// 定义时间类型
#if defined(_MSC_VER)
	typedef __int64 TIME_T;
#else
	typedef unsigned long long TIME_T;
#endif

	class VRSOFT_PLUGIN_DLL ITimer
	{
	public:
		// 析构函数
		virtual ~ITimer() { }

		// 设置起始时间
		virtual bool SetStartTime(const TIME_T t)  = 0;
		// 设置起始时间
		virtual bool SetStartTime(const int nyear, const int month, const int day, \
			const int hour, const int min, const int sec) = 0;
		// 获得当前仿真时间
		virtual TIME_T GetSimulationTime(void) const = 0;
		// 返回tm系统时间
		virtual struct tm* GetSimulationTimeTm(void) const = 0;
		// 系统运行时间
		virtual TIME_T GetTick() const = 0;
		// 操作系统运行时间
		virtual TIME_T GetSystemTick() const = 0;
		// 获得时分秒 格式（yyyy-MM-dd h:m:s.sss）
		virtual VRString GetSimulationString(void) const = 0;
	};
}

#endif // _PUBLIC_ITIMER_H_