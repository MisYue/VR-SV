/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  计时器类	                                                    */
/* 时间： 2016-04-08                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

namespace VR_Soft
{

#if defined(_MSC_VER)
	typedef __int64 Timer_t;
#else
	typedef unsigned long long Timer_t;
#endif

	class CTimer : public ITimer
	{
	public:
		// 构造函数
		CTimer(void);
		// 析构函数
		virtual ~CTimer(void);

	public:
		// 设置开始时间
		virtual void SetStartTick();
		// 设置开始时间
		virtual void SetStartTick(Timer_t t);
		// 获得开始时间
		virtual Timer_t GetStartTick() const;
		// 获得时钟
		virtual Timer_t Tick() const;
		// 相差时间秒
		virtual double DeltaSec( Timer_t t1, Timer_t t2 ) const ;
		// 相差时间毫秒
		virtual double DeltaMil( Timer_t t1, Timer_t t2 ) const ;
		// 相差时间微秒
		virtual double DeltaMicro( Timer_t t1, Timer_t t2 ) const ;
		// 相差时间纳秒
		virtual double DeltaNano( Timer_t t1, Timer_t t2 ) const ;
		// 每一个时钟的秒数
		virtual double GetSecondsPerTick() const ;

	private:
		Timer_t m_startTick; // 开始时间
		double  m_secsPerTick; // 
	};
}


#endif // ! _TIMER_H_