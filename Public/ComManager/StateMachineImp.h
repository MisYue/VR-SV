/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��״̬��ģ����		                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_STATEMACHINEIMP_H_
#define _PUBLIC_STATEMACHINEIMP_H_

namespace VR_Soft
{
	template <class T>
	class CStateMachineImp : public T
	{
	public: 
		// ���캯��
		CStateMachineImp(IEntityBase* pOwer)
			:m_pOwner(pOwer),
			m_pICurrentState(NULL),
			m_pIPreviousState(NULL),
			m_pIGlobalState(NULL)
		{

		}

		// ��������
		virtual ~CStateMachineImp() { }

		// ���õ�ǰ״̬
		virtual void SetCurrentState(IState* pIState)
		{
			m_pICurrentState = pIState;
		}

		// ������һ״̬
		virtual void SetPreviousState(IState* pIState)
		{
			m_pIPreviousState = pIState;
		}

		// ����ȫ��״̬
		virtual void SetGlobalState(IState* pIState) 
		{
			m_pICurrentState = pIState;
		}

		// ��õ�ǰ״̬
		virtual IState* GetCurrentState(void) const 
		{
			return (m_pICurrentState);
		}

		// �����һ״̬
		virtual IState* GetPreviousState(void) const
		{
			return (m_pIPreviousState);
		}

		// ���ȫ��״̬
		virtual IState* GetGlobalState(void) const 
		{
			return (m_pIGlobalState);
		}


		// ������Ϣ
		virtual bool HandleMessage(const IMessage* pIMsg) 
		{
			// �жϵ�ǰ��״̬�Ƿ�Ϊ�� ��Ϣ����
			if ((NULL != m_pICurrentState) && (m_pICurrentState->OnMessage(m_pOwner, pIMsg)))
			{
				return (true);				
			}

			// ȫ��״̬����
			else if ((NULL != m_pIGlobalState) && (m_pIGlobalState->OnMessage(m_pOwner, pIMsg)))
			{
				return (true);
			}

			// ������ǰ��Ϣ
			else 
			{
				return (false);
			}
		}

		// ����״̬
		virtual void RevertToPreviousState(void) 
		{
			 ChangeState(m_pIPreviousState);
		}

		// �ı�״̬
		virtual void ChangeState(IState* pINewState) 
		{
			// ����
			assert(NULL != pINewState);

			// ɾ���ϴε�״̬
			VRSOFT_DELETE(m_pIPreviousState);

			// ��¼��ǰ״̬
			m_pIPreviousState = m_pICurrentState;
			// �뿪��ǰ״̬
			m_pICurrentState->Exit(m_pOwner);

			// �����µ�״̬
			m_pICurrentState = pINewState;
			m_pICurrentState->Enter(m_pOwner);
		}

		// ���״̬����
		virtual VRString GetStateName(void) 
		{
			VRString strName(typeid(*m_pICurrentState).name());
			return (strName);
		}

		// �ж��Ƿ�Ϊͬһ��״̬
		virtual bool IsInState(IState* pIState) 
		{
			if (typeid(*m_pCurrentState) == typeid(*pIState)) return true;
			return false;
		}


	};
}

#endif // _PUBLIC_STATEMACHINEIMP_H_