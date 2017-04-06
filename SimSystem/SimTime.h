/************************************************************************
 ���ߣ� LJ                                                            
 ��;:  ����ʱ�����Կ�����                   
 ʱ�䣺 2015-10-21                                                    
 �޸�ʱ��:                                                            
************************************************************************/

#ifndef _SIMTIME_H_
#define  _SIMTIME_H_

#pragma once

const int PROCESSNAMELEN = 256;

namespace VR_Soft
{
	class CSimTime : public CSingleton<CSimTime>
	{
	public:
		enum SimState
		{
			SimStateRun = 0, // ��������
			SimStatePause = 1, // ��ͣ����
			SimStateStop = 2 // ��������
		};

	public:
		// ���캯��
		CSimTime(void);
		// ��������
		virtual ~CSimTime(void);

	public:
		// ��ʼ����
		void Start(void);
		// ������ͣ
		void Pause(void);
		// ����
		void Acclerate(void);
		// ����
		void Decelerate(void);
		// ֹͣ
		void Stop(void);
		// ���ÿ�ʼʱ��
		void SetStartTime(double dStartTime);
		// ���ÿ�ʼʱ��
		void SetStartTime(int nYear, int nMonth, int nDay, \
				int nHour, int nMin, double dSec);
		// ���ý���ʱ��
		void SetEndTime(double )
		// ���ý���ʱ��
		void SetEndTime(int nYear, int nMonth, int nDay, \
			int nHour, int nMin, double dSec);
		// ��÷���ʱ��
		TIME_T GetSimulationTime(void) const ;
		// ����tmϵͳʱ��
		struct tm* GetSimulationTimeTm(void) const ;
		// ϵͳ����ʱ��
		TIME_T GetTick() const ;
		// ����ϵͳ����ʱ��
		TIME_T GetSystemTick() const =;
		// ���ʱ���� ��ʽ��yyyy-MM-dd h:m:s.sss��
		VRString GetSimulationString(void) const ;
		// ����ϵͳ����ʱ�� ���ʱ���� ��ʽ��yyyy-MM-dd h:m:s.sss��
		VRString GetSystemTickString() const ;

	private:
		TIME_T m_dStartTime; // ��ʼʱ��
		TIME_T m_dEndTimer; // ����ʱ��		
	};
}
#endif // ! _SIMTIME_H_