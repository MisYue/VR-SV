/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间计时器实现类		                                        */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

namespace VR_Soft
{
	class CTimer : public ITimer
	{
	public:
		// 构造函数
		explicit CTimer(void);
		// 析构函数
		virtual ~CTimer(void);

	public:
		// 设置起始时间
		virtual bool SetStartTime(const TIME_T t) ;
		// 设置起始时间
		virtual bool SetStartTime(struct tm& t) ;
		// 设置起始时间
		virtual bool SetStartTime(const int nyear, const int month, const int day, \
			const int hour, const int min, const int sec) ;
		// 获得当前仿真时间
		virtual TIME_T GetSimulationTime(void) const;
		// 返回tm系统时间
		virtual struct tm* GetSimulationTimeTm(void) const;
		// 系统运行时间
		virtual TIME_T GetTick() const;
		// 获得时分秒 格式（yyyy-MM-dd h:m:s.sss）
		virtual VRString GetSimulationString(void) const ;
		// 设置加速倍数
		virtual void SetMultiple(const double dMul);
		// 获得加速倍数
		virtual double GetMultiple(void) const;

	public:
		// 初始化开始的计数
		bool SetStartTick(void);
		// 停止
		void Stop(void);

	protected:
		// 计算当前的秒数对应的十分秒
		//struct tm GetTmFromTick(const TIME_T t);
		// 获得秒数
		double Milliseconds(void) const;

	private:
		// 记录系统运行的时间
		void SetStartSystemTick(void);
		// 操作系统运行时间
		virtual TIME_T GetSystemTick() const ;
		
	private:
		TIME_T m_starSystemTick; // 开始的计数
		TIME_T m_starTick; // 开始的计数
		mutable TIME_T m_curTick; // 开始的计数
		double m_secsPerTick; // 每一秒CPU计算个数
		double m_dMultiple; // 加速倍数
		double m_dCurMultiple; // 当前倍数


		friend class CTimerThread;
	};

}

#endif //  _TIMER_H_