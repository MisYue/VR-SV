/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ���ʱ��ʵ����		                                        */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

namespace VR_Soft
{
	class CTimer : public ITimer
	{
	public:
		// ���캯��
		explicit CTimer(void);
		// ��������
		virtual ~CTimer(void);

	public:
		// ������ʼʱ��
		virtual bool SetStartTime(const TIME_T t) ;
		// ������ʼʱ��
		virtual bool SetStartTime(struct tm& t) ;
		// ������ʼʱ��
		virtual bool SetStartTime(const int nyear, const int month, const int day, \
			const int hour, const int min, const int sec) ;
		// ��õ�ǰ����ʱ��
		virtual TIME_T GetSimulationTime(void) const;
		// ����tmϵͳʱ��
		virtual struct tm* GetSimulationTimeTm(void) const;
		// ϵͳ����ʱ��
		virtual TIME_T GetTick() const;
		// ���ʱ���� ��ʽ��yyyy-MM-dd h:m:s.sss��
		virtual VRString GetSimulationString(void) const ;
		// ���ü��ٱ���
		virtual void SetMultiple(const double dMul);
		// ��ü��ٱ���
		virtual double GetMultiple(void) const;

	public:
		// ��ʼ����ʼ�ļ���
		bool SetStartTick(void);
		// ֹͣ
		void Stop(void);

	protected:
		// ���㵱ǰ��������Ӧ��ʮ����
		//struct tm GetTmFromTick(const TIME_T t);
		// �������
		double Milliseconds(void) const;

	private:
		// ��¼ϵͳ���е�ʱ��
		void SetStartSystemTick(void);
		// ����ϵͳ����ʱ��
		virtual TIME_T GetSystemTick() const ;
		
	private:
		TIME_T m_starSystemTick; // ��ʼ�ļ���
		TIME_T m_starTick; // ��ʼ�ļ���
		mutable TIME_T m_curTick; // ��ʼ�ļ���
		double m_secsPerTick; // ÿһ��CPU�������
		double m_dMultiple; // ���ٱ���
		double m_dCurMultiple; // ��ǰ����


		friend class CTimerThread;
	};

}

#endif //  _TIMER_H_