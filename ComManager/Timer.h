/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ʱ����	                                                    */
/* ʱ�䣺 2016-04-08                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		CTimer(void);
		// ��������
		virtual ~CTimer(void);

	public:
		// ���ÿ�ʼʱ��
		virtual void SetStartTick();
		// ���ÿ�ʼʱ��
		virtual void SetStartTick(Timer_t t);
		// ��ÿ�ʼʱ��
		virtual Timer_t GetStartTick() const;
		// ���ʱ��
		virtual Timer_t Tick() const;
		// ���ʱ����
		virtual double DeltaSec( Timer_t t1, Timer_t t2 ) const ;
		// ���ʱ�����
		virtual double DeltaMil( Timer_t t1, Timer_t t2 ) const ;
		// ���ʱ��΢��
		virtual double DeltaMicro( Timer_t t1, Timer_t t2 ) const ;
		// ���ʱ������
		virtual double DeltaNano( Timer_t t1, Timer_t t2 ) const ;
		// ÿһ��ʱ�ӵ�����
		virtual double GetSecondsPerTick() const ;

	private:
		Timer_t m_startTick; // ��ʼʱ��
		double  m_secsPerTick; // 
	};
}


#endif // ! _TIMER_H_