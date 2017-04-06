/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体状态机模板类		                                        */
/* 时间： 2015-08-31                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_STATEMACHINEIMP_H_
#define _PUBLIC_STATEMACHINEIMP_H_

namespace VR_Soft
{
	template <class T>
	class CStateMachineImp : public T
	{
	public: 
		// 构造函数
		CStateMachineImp(IEntityBase* pOwer)
			:m_pOwner(pOwer),
			m_pICurrentState(NULL),
			m_pIPreviousState(NULL),
			m_pIGlobalState(NULL)
		{

		}

		// 析构函数
		virtual ~CStateMachineImp() { }

		// 设置当前状态
		virtual void SetCurrentState(IState* pIState)
		{
			m_pICurrentState = pIState;
		}

		// 设置上一状态
		virtual void SetPreviousState(IState* pIState)
		{
			m_pIPreviousState = pIState;
		}

		// 设置全局状态
		virtual void SetGlobalState(IState* pIState) 
		{
			m_pICurrentState = pIState;
		}

		// 获得当前状态
		virtual IState* GetCurrentState(void) const 
		{
			return (m_pICurrentState);
		}

		// 获得上一状态
		virtual IState* GetPreviousState(void) const
		{
			return (m_pIPreviousState);
		}

		// 获得全局状态
		virtual IState* GetGlobalState(void) const 
		{
			return (m_pIGlobalState);
		}


		// 处理消息
		virtual bool HandleMessage(const IMessage* pIMsg) 
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
		virtual void RevertToPreviousState(void) 
		{
			 ChangeState(m_pIPreviousState);
		}

		// 改变状态
		virtual void ChangeState(IState* pINewState) 
		{
			// 断言
			assert(NULL != pINewState);

			// 删除上次的状态
			VRSOFT_DELETE(m_pIPreviousState);

			// 记录当前状态
			m_pIPreviousState = m_pICurrentState;
			// 离开当前状态
			m_pICurrentState->Exit(m_pOwner);

			// 进入新的状态
			m_pICurrentState = pINewState;
			m_pICurrentState->Enter(m_pOwner);
		}

		// 获得状态名称
		virtual VRString GetStateName(void) 
		{
			VRString strName(typeid(*m_pICurrentState).name());
			return (strName);
		}

		// 判断是否为同一个状态
		virtual bool IsInState(IState* pIState) 
		{
			if (typeid(*m_pCurrentState) == typeid(*pIState)) return true;
			return false;
		}


	};
}

#endif // _PUBLIC_STATEMACHINEIMP_H_