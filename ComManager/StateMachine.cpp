
#include "../../Public/VRSoft.h"
#include "StateMachine.h"


namespace VR_Soft
{
	CStateMachine::CStateMachine(IEntityBase* pOwer)
		:m_pOwner(pOwer),
		m_pICurrentState(NULL),
		m_pIPreviousState(NULL),
		m_pIGlobalState(NULL)
	{
		
	}


	CStateMachine::~CStateMachine(void)
	{
		// ɾ���ϴε�״̬
		VRSOFT_DELETE(m_pIPreviousState);
		// ɾ����ǰ��״̬
		VRSOFT_DELETE(m_pICurrentState);
		// ɾ��ȫ�ֵ�״̬
		VRSOFT_DELETE(m_pIGlobalState);
	}

	// ���õ�ǰ״̬
	void CStateMachine::SetCurrentState(IState* pIState)
	{
		m_pICurrentState = pIState;
	}

	// ������һ״̬
	void CStateMachine::SetPreviousState(IState* pIState)
	{
		m_pIPreviousState = pIState;
	}

	// ����ȫ��״̬
	void CStateMachine::SetGlobalState(IState* pIState) 
	{
		m_pIGlobalState = pIState;
	}

	// ��õ�ǰ״̬
	IState* CStateMachine::GetCurrentState(void) const 
	{
		return (m_pICurrentState);
	}

	// �����һ״̬
	IState* CStateMachine::GetPreviousState(void) const
	{
		return (m_pIPreviousState);
	}

	// ���ȫ��״̬
	IState* CStateMachine::GetGlobalState(void) const 
	{
		return (m_pIGlobalState);
	}


	// ������Ϣ
	bool CStateMachine::HandleMessage(const IMessage* pIMsg) 
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
	void CStateMachine::RevertToPreviousState(void) 
	{
		ChangeState(m_pIPreviousState);
	}

	// �ı�״̬
	void CStateMachine::ChangeState(IState* pINewState) 
	{
		// ����
		assert(NULL != pINewState);

		if (NULL != m_pICurrentState)
		{
			// ɾ���ϴε�״̬
			VRSOFT_DELETE(m_pIPreviousState);

			// ��¼��ǰ״̬
			m_pIPreviousState = m_pICurrentState;
			// �뿪��ǰ״̬
			m_pICurrentState->Exit(m_pOwner);
		}		

		// �����µ�״̬
		m_pICurrentState = pINewState;
		m_pICurrentState->Enter(m_pOwner);
	}

	// ���״̬����
	VRString CStateMachine::GetStateName(void) 
	{
		VRString strName(typeid(*m_pICurrentState).name());
		return (strName);
	}

	// �ж��Ƿ�Ϊͬһ��״̬
	bool CStateMachine::IsInState(IState* pIState) 
	{
		if (NULL == m_pICurrentState)
		{
			return (false);
		}

		if (typeid(*m_pICurrentState) == typeid(*pIState)) return true;
		return false;
	}

	// ����
	void CStateMachine::Update(const CDateTime& dt)
	{
		//// �Ƿ���ñ���ģ��
		//if (IComManager::GetInstance().IsService())
		//{
		//	// ����ģ�����в���
		//	IStrategyManager* pIStrategyManager = CEntitySystem::GetInstance().GetStrategyManagerInstance();
		//	IStrategyManager::ListStrategys lstStrategys =  pIStrategyManager->GetAllStrategy(m_pOwner);
		//	IStrategyManager::ListStrategys::iterator itorStrategy = lstStrategys.begin();
		//	for (; lstStrategys.end() != itorStrategy; ++itorStrategy)
		//	{
		//		(*itorStrategy)->Execute(dt);
		//	}
		//}

		// �ж��Ƿ�ִ�е�ǰ״̬
		if (NULL != m_pICurrentState)
		{
			m_pICurrentState->Execute(m_pOwner);
		} 

		// �ж��Ƿ���Ҫִ��ȫ��״̬
		else if (NULL != m_pIGlobalState)
		{
			m_pIGlobalState->Execute(m_pOwner);
		}
	}
}

