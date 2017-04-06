/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��״̬���ӿ�		                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

/************************************************************************/
/* ����ԭ�����ԡ���Ϸ�˹����ܱ�̰������⡷һ��                         */
/************************************************************************/

#ifndef _PUBLIC_ISTATEMACHINE_H_
#define _PUBLIC_ISTATEMACHINE_H_

namespace VR_Soft
{
	class IStateMachine
	{
	public:
		// ��������
		virtual ~IStateMachine() { }

		// ���õ�ǰ״̬
		virtual void SetCurrentState(IState* pIState) = 0;
		// ������һ״̬
		virtual void SetPreviousState(IState* pIState) = 0;
		// ����ȫ��״̬
		virtual void SetGlobalState(IState* pIState) = 0;
		// ��õ�ǰ״̬
		virtual IState* GetCurrentState(void) const = 0;
		// �����һ״̬
		virtual IState* GetPreviousState(void) const = 0;
		// ���ȫ��״̬
		virtual IState* GetGlobalState(void) const = 0;

		// ������Ϣ
		virtual bool HandleMessage(const IMessage* pIMsg) = 0;
		// ����״̬
		virtual void RevertToPreviousState(void) = 0;
		// �ı�״̬
		virtual void ChangeState(IState* pINewState) = 0;
		// ���״̬����
		virtual VRString GetStateName(void) = 0;
		// �ж��Ƿ�Ϊͬһ��״̬
		virtual bool IsInState(IState* pIState) = 0;
		
	public:
		// ����״̬
		virtual void Update(const CDateTime& dt) = 0;
	};
}

#endif // _PUBLIC_ISTATEMACHINE_H_