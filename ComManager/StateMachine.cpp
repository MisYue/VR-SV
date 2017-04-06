
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
		// 删除上次的状态
		VRSOFT_DELETE(m_pIPreviousState);
		// 删除当前的状态
		VRSOFT_DELETE(m_pICurrentState);
		// 删除全局的状态
		VRSOFT_DELETE(m_pIGlobalState);
	}

	// 设置当前状态
	void CStateMachine::SetCurrentState(IState* pIState)
	{
		m_pICurrentState = pIState;
	}

	// 设置上一状态
	void CStateMachine::SetPreviousState(IState* pIState)
	{
		m_pIPreviousState = pIState;
	}

	// 设置全局状态
	void CStateMachine::SetGlobalState(IState* pIState) 
	{
		m_pIGlobalState = pIState;
	}

	// 获得当前状态
	IState* CStateMachine::GetCurrentState(void) const 
	{
		return (m_pICurrentState);
	}

	// 获得上一状态
	IState* CStateMachine::GetPreviousState(void) const
	{
		return (m_pIPreviousState);
	}

	// 获得全局状态
	IState* CStateMachine::GetGlobalState(void) const 
	{
		return (m_pIGlobalState);
	}


	// 处理消息
	bool CStateMachine::HandleMessage(const IMessage* pIMsg) 
	{
		// 判断当前的状态是否为空 消息处理
		if ((NULL != m_pICurrentState) && (m_pICurrentState->OnMessage(m_pOwner, pIMsg)))
		{
			return (true);				
		}

		// 全局状态处理
		else if ((NULL != m_pIGlobalState) && (m_pIGlobalState->OnMessage(m_pOwner, pIMsg)))
		{
			return (true);
		}

		// 不处理当前消息
		else 
		{
			return (false);
		}
	}

	// 重置状态
	void CStateMachine::RevertToPreviousState(void) 
	{
		ChangeState(m_pIPreviousState);
	}

	// 改变状态
	void CStateMachine::ChangeState(IState* pINewState) 
	{
		// 断言
		assert(NULL != pINewState);

		if (NULL != m_pICurrentState)
		{
			// 删除上次的状态
			VRSOFT_DELETE(m_pIPreviousState);

			// 记录当前状态
			m_pIPreviousState = m_pICurrentState;
			// 离开当前状态
			m_pICurrentState->Exit(m_pOwner);
		}		

		// 进入新的状态
		m_pICurrentState = pINewState;
		m_pICurrentState->Enter(m_pOwner);
	}

	// 获得状态名称
	VRString CStateMachine::GetStateName(void) 
	{
		VRString strName(typeid(*m_pICurrentState).name());
		return (strName);
	}

	// 判断是否为同一个状态
	bool CStateMachine::IsInState(IState* pIState) 
	{
		if (NULL == m_pICurrentState)
		{
			return (false);
		}

		if (typeid(*m_pICurrentState) == typeid(*pIState)) return true;
		return false;
	}

	// 更新
	void CStateMachine::Update(const CDateTime& dt)
	{
		//// 是否采用本机模型
		//if (IComManager::GetInstance().IsService())
		//{
		//	// 更新模型所有策略
		//	IStrategyManager* pIStrategyManager = CEntitySystem::GetInstance().GetStrategyManagerInstance();
		//	IStrategyManager::ListStrategys lstStrategys =  pIStrategyManager->GetAllStrategy(m_pOwner);
		//	IStrategyManager::ListStrategys::iterator itorStrategy = lstStrategys.begin();
		//	for (; lstStrategys.end() != itorStrategy; ++itorStrategy)
		//	{
		//		(*itorStrategy)->Execute(dt);
		//	}
		//}

		// 判断是否执行当前状态
		if (NULL != m_pICurrentState)
		{
			m_pICurrentState->Execute(m_pOwner);
		} 

		// 判断是否需要执行全局状态
		else if (NULL != m_pIGlobalState)
		{
			m_pIGlobalState->Execute(m_pOwner);
		}
	}
}

