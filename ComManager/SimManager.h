/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���������                                                    */
/* ʱ�䣺 2016-04-08                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _SIMMANAGER_H_
#define _SIMMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CSimManager : public ISimManager
	{
	public:
		// ���캯��
		CSimManager(void);
		// ��������
		virtual ~CSimManager(void);

		// ���÷��濪ʼʱ��
		virtual void SetBeginTime(const CDateTime& dtStart);
		// ���ý���ʱ��
		virtual void SetEndTime(const CDateTime& dtStop) ;
		// ��÷��濪ʼʱ��
		virtual CDateTime GetStartTime(void) const ;
		// ��ý���ʱ��
		virtual CDateTime GetEndTime( void) const;
		// ���ÿ�ʼʱ��ͽ���ʱ��
		virtual void SetSimTimRange(const CDateTime& dtStart, const CDateTime& dtStop);
		// ��ÿ�ʼʱ��ͽ���ʱ��
		virtual void GetSimTimRange(CDateTime& dtStart, CDateTime& dtStop) const ;
		// ����ʱ��ָ��
		virtual void SetSimCmd(SimCmd simCmd) ;
		// ��÷���ָ��
		virtual SimCmd  GetSimCmd(void) const ;
		// ����ʱ�䲽��
		virtual void SetTimeStep(int nStep) ;
		// ���ʱ�䲽��
		virtual int GetTimeStep(void) const ;
		// ��ȡ����ʱ��
		virtual const CDateTime& GetSimTime(void) const ;
		// ����ʱ����ת
		virtual bool JumpSimTime(const CDateTime& dt) ;

	public:
		// ÿһ֡����
		void Frame(void);

	protected:
		enum
		{
			RUN = 1,
			PUSE = 2
		};

	private:
		CDateTime m_dtBengin; // ��ʼʱ��
		CDateTime m_dtStop; // ����ʱ��
		CDateTime m_dtSim; // ����ʱ��
		double m_dSimStep; // ����
		double m_dSimMult; // ���汶��
		int m_nFlag; // ָ���־
		SimCmd m_simCmd;
		double m_dLoopStep; // ѭ������
		Timer_t m_dLastTicks; // ��һ�ε�ʱ����
	};
}


#endif // ! _SIMMANAGER_H_