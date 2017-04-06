/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʱ��ϵͳ������ʵ����                                        */
/* ʱ�䣺 2015-09-15                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _TIMESYSTEM_H_
#define _TIMESYSTEM_H

#pragma once

#include "Timer.h"
#include "TimeConfig.h"

namespace VR_Soft
{
	class CTimerThread;

	class CTimeSystem : public ITimeManager
	{
	public:
		explicit CTimeSystem(const VRString& strName);
		virtual ~CTimeSystem(void);

	public:
		// ���ʱ�䷵���ַ���
		virtual ITimer* GetTime(void) ;
		// ����
		virtual void Quicken(void);
		// ����
		virtual void Moderate(void);
		// ��ͣ
		virtual void Suspend(void);
		// �ָ�
		virtual void Recover(void);
		// ֹͣ����λ��
		virtual void Stop(void) ;
		// ��ʼ
		virtual void Start(void) ;
		// ��ת
		virtual void Jump(struct tm& t);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);
		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;
		CTimer m_timer; // ʱ��
		CTimerThread* m_pTimeThread; // �߳�
		CTimeConfig m_timeConfig; // �����ļ�
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CTimeSystem, TimeManager, TIMESYSTEM_TYPENAME, INSTANCE_NAME_TIMESYSTEM, TIMESYSTEM_DISC );
}


#endif // _TIMESYSTEM_H_