/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体状态机类			                                        */
/* 时间： 2015-08-31                                                    */
/* 修改时间:                                                            */
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
		// 设置当前状态
		virtual void SetCurrentState(IState* pIState);
		// 设置上一状态
		virtual void SetPreviousState(IState* pIState);
		// 设置全局状态
		virtual void SetGlobalState(IState* pIState);
		// 获得当前状态
		virtual IState* GetCurrentState(void) const;
		// 获得上一状态
		virtual IState* GetPreviousState(void) const;
		// 获得全局状态
		virtual IState* GetGlobalState(void) const;

		// 处理消息
		virtual bool HandleMessage(const IMessage* pIMsg);
		// 重置状态
		virtual void RevertToPreviousState(void);
		// 改变状态
		virtual void ChangeState(IState* pINewState);
		// 获得状态名称
		virtual VRString GetStateName(void);
		// 判断是否为同一个状态
		virtual bool IsInState(IState* pIState);

	public:
		// 更新
		virtual void Update(const CDateTime& dt);

	private:
		IEntityBase* m_pOwner; // 状态拥有者
		IState* m_pICurrentState; // 当前状态
		IState* m_pIPreviousState; // 上一个状态
		IState* m_pIGlobalState; // 全局状态
	};
}


#endif // _STATEMACHINE_H_