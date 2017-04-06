/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��ʱ���ӿ�                                                    */
/* ʱ�䣺 2016-04-08                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLICE_ITIMER_H_
#define _PUBLICE_ITIMER_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL ITimer : public CSingleton<ITimer>
	{
	public:
		// ��������
		virtual ~ITimer(void) { }

		// ���ʱ��
		virtual Timer_t Tick() const = 0;
		// ���ʱ����
		virtual double DeltaSec( Timer_t t1, Timer_t t2 ) const = 0;
		// // ���ʱ���
		virtual double DeltaMil( Timer_t t1, Timer_t t2 ) const = 0;
		// ���ʱ�����
		virtual double DeltaMicro( Timer_t t1, Timer_t t2 ) const = 0;
		// ���ʱ������
		virtual double DeltaNano( Timer_t t1, Timer_t t2 ) const = 0;
		// ÿһ��ʱ�ӵ�����
		virtual double GetSecondsPerTick() const = 0;
	};
}

#endif // _PUBLICE_ITIMER_H_


