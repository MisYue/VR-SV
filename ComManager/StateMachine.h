/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��״̬����			                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#pragma once

namespace VR_Soft
{
	class CStateMachine : public IStateMachine
	{
	public:
		explicit CStateMachine(IEntityBase* pOwer);
		virtual ~CStateMachine(void);

	public:
		// ���õ�ǰ״̬
		virtual void SetCurrentState(IState* pIState);
		// ������һ״̬
		virtual void SetPreviousState(IState* pIState);
		// ����ȫ��״̬
		virtual void SetGlobalState(IState* pIState);
		// ��õ�ǰ״̬
		virtual IState* GetCurrentState(void) const;
		// �����һ״̬
		virtual IState* GetPreviousState(void) const;
		// ���ȫ��״̬
		virtual IState* GetGlobalState(void) const;

		// ������Ϣ
		virtual bool HandleMessage(const IMessage* pIMsg);
		// ����״̬
		virtual void RevertToPreviousState(void);
		// �ı�״̬
		virtual void ChangeState(IState* pINewState);
		// ���״̬����
		virtual VRString GetStateName(void);
		// �ж��Ƿ�Ϊͬһ��״̬
		virtual bool IsInState(IState* pIState);

	public:
		// ����
		virtual void Update(const CDateTime& dt);

	private:
		IEntityBase* m_pOwner; // ״̬ӵ����
		IState* m_pICurrentState; // ��ǰ״̬
		IState* m_pIPreviousState; // ��һ��״̬
		IState* m_pIGlobalState; // ȫ��״̬
	};
}


#endif // _STATEMACHINE_H_