/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体状态机接口		                                        */
/* 时间： 2015-08-31                                                    */
/* 修改时间:                                                            */
/************************************************************************/

/************************************************************************/
/* 代码原理来自《游戏人工智能编程案例精粹》一书                         */
/************************************************************************/

#ifndef _PUBLIC_ISTATEMACHINE_H_
#define _PUBLIC_ISTATEMACHINE_H_

namespace VR_Soft
{
	class IStateMachine
	{
	public:
		// 析构函数
		virtual ~IStateMachine() { }

		// 设置当前状态
		virtual void SetCurrentState(IState* pIState) = 0;
		// 设置上一状态
		virtual void SetPreviousState(IState* pIState) = 0;
		// 设置全局状态
		virtual void SetGlobalState(IState* pIState) = 0;
		// 获得当前状态
		virtual IState* GetCurrentState(void) const = 0;
		// 获得上一状态
		virtual IState* GetPreviousState(void) const = 0;
		// 获得全局状态
		virtual IState* GetGlobalState(void) const = 0;

		// 处理消息
		virtual bool HandleMessage(const IMessage* pIMsg) = 0;
		// 重置状态
		virtual void RevertToPreviousState(void) = 0;
		// 改变状态
		virtual void ChangeState(IState* pINewState) = 0;
		// 获得状态名称
		virtual VRString GetStateName(void) = 0;
		// 判断是否为同一个状态
		virtual bool IsInState(IState* pIState) = 0;
		
	public:
		// 更新状态
		virtual void Update(const CDateTime& dt) = 0;
	};
}

#endif // _PUBLIC_ISTATEMACHINE_H_