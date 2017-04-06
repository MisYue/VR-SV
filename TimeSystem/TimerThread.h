/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间计时器实现线程类	                                        */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TIMERTHREAD_H_
#define _TIMERTHREAD_H_

#pragma once

namespace VR_Soft
{
	class CTimer;

	class CTimerThread : public CVRSoftThread
	{
	public:
		explicit CTimerThread(CTimer* pTimer);
		virtual ~CTimerThread(void);

		// 暂停
		void SubSuspend(bool bSubSuspend);

	protected:
		// 软件循环
		virtual void Run();

	private:
		CTimer* m_pTimer; // 时间
		bool m_bSubSuspend; // 暂停
	};
}


#endif //  _TIMERTHREAD_H_