/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  全局状态类，控制模型仿真状态		                            */
/* 时间： 2015-11-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _GLOBALSTATE_H_
#define _GLOBALSTATE_H_

#pragma once

namespace VR_Soft
{
	class CGlobalState : public IState
	{
	public:
		explicit CGlobalState(void);
		virtual ~CGlobalState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage) ;
	};
}


#endif // !_GOLABSTATE_H_