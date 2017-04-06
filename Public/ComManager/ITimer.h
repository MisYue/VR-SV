/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  计时器接口                                                    */
/* 时间： 2016-04-08                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLICE_ITIMER_H_
#define _PUBLICE_ITIMER_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL ITimer : public CSingleton<ITimer>
	{
	public:
		// 析构函数
		virtual ~ITimer(void) { }

		// 获得时钟
		virtual Timer_t Tick() const = 0;
		// 相差时间秒
		virtual double DeltaSec( Timer_t t1, Timer_t t2 ) const = 0;
		// // 相差时间分
		virtual double DeltaMil( Timer_t t1, Timer_t t2 ) const = 0;
		// 相差时间毫秒
		virtual double DeltaMicro( Timer_t t1, Timer_t t2 ) const = 0;
		// 相差时间纳秒
		virtual double DeltaNano( Timer_t t1, Timer_t t2 ) const = 0;
		// 每一个时钟的秒数
		virtual double GetSecondsPerTick() const = 0;
	};
}

#endif // _PUBLICE_ITIMER_H_


