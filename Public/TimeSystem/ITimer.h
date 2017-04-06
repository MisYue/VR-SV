/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ���ʱ���ӿ�		                                        */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_ITIMER_H_
#define _PUBLIC_ITIMER_H_

namespace VR_Soft
{
	// ����ʱ������
#if defined(_MSC_VER)
	typedef __int64 TIME_T;
#else
	typedef unsigned long long TIME_T;
#endif

	class VRSOFT_PLUGIN_DLL ITimer
	{
	public:
		// ��������
		virtual ~ITimer() { }

		// ������ʼʱ��
		virtual bool SetStartTime(const TIME_T t)  = 0;
		// ������ʼʱ��
		virtual bool SetStartTime(const int nyear, const int month, const int day, \
			const int hour, const int min, const int sec) = 0;
		// ��õ�ǰ����ʱ��
		virtual TIME_T GetSimulationTime(void) const = 0;
		// ����tmϵͳʱ��
		virtual struct tm* GetSimulationTimeTm(void) const = 0;
		// ϵͳ����ʱ��
		virtual TIME_T GetTick() const = 0;
		// ����ϵͳ����ʱ��
		virtual TIME_T GetSystemTick() const = 0;
		// ���ʱ���� ��ʽ��yyyy-MM-dd h:m:s.sss��
		virtual VRString GetSimulationString(void) const = 0;
	};
}

#endif // _PUBLIC_ITIMER_H_