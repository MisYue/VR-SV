/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ϵͳ״̬�࣬ ���Ʒ������У���ͣ��״̬                     */
/* ʱ�䣺 2015-11-10                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SIMSTATE_H_
#define _SIMSTATE_H_

#pragma once

namespace VR_Soft
{
	/*
	class CSimStateBase : public IState
	{
	public:
		CSimStateBase()
			:m_curSimCmd(ISimManager::Stop)
		{

		}
		virtual ~CSimStateBase(void) { }
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);


	private:
		ISimManager::SimCmd m_curSimCmd; // ��ǰָ��
	};

	////////////////////////////////run state//////////////////////////////////////////
	// ����״̬
	class CSimRunState : public CSimStateBase
	{
	public:
		// ���캯��
		CSimRunState(void);
		// ��������
		virtual ~CSimRunState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);

	protected:
		// ����ģ��
		void UpdateEntity(double dSimLogicTime);

	private:
		double m_dOverheadTime; // ���й���ʱ��
		double m_dLoopStep;					//ʵʱ���沽�������ڣ�����λ�� ����
	};

	//////////////////////////////////end state////////////////////////////////////////
	// ����״̬
	class CSimEndState : public CSimStateBase
	{
	public:
		// ���캯��
		CSimEndState(void);
		// ��������
		virtual ~CSimEndState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};

	////////////////////////////////////pause state//////////////////////////////////////
	// ��ͣ״̬
	class CSimPauseState : public CSimStateBase
	{
	public:
		// ���캯��
		CSimPauseState(void);
		// ��������
		virtual ~CSimPauseState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};

	//////////////////////////////////////exit state////////////////////////////////////
	// �˳�״̬
	class CSimExitState : public CSimStateBase
	{
	public:
		// ���캯��
		CSimExitState(void);
		// ��������
		virtual ~CSimExitState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};
	*/
}


#endif // !_SIMSTATE_H_