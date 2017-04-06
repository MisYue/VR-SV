/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ���ʱ��ʵ���߳���	                                        */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
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

		// ��ͣ
		void SubSuspend(bool bSubSuspend);

	protected:
		// ���ѭ��
		virtual void Run();

	private:
		CTimer* m_pTimer; // ʱ��
		bool m_bSubSuspend; // ��ͣ
	};
}


#endif //  _TIMERTHREAD_H_