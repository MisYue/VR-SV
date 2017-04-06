/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真系统状态类， 控制仿真运行，暂停等状态                     */
/* 时间： 2015-11-10                                                    */
/* 修改时间:                                                            */
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
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);


	private:
		ISimManager::SimCmd m_curSimCmd; // 当前指令
	};

	////////////////////////////////run state//////////////////////////////////////////
	// 运行状态
	class CSimRunState : public CSimStateBase
	{
	public:
		// 构造函数
		CSimRunState(void);
		// 析构函数
		virtual ~CSimRunState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);

	protected:
		// 更新模型
		void UpdateEntity(double dSimLogicTime);

	private:
		double m_dOverheadTime; // 运行过的时间
		double m_dLoopStep;					//实时仿真步长（周期），单位： 毫秒
	};

	//////////////////////////////////end state////////////////////////////////////////
	// 结束状态
	class CSimEndState : public CSimStateBase
	{
	public:
		// 构造函数
		CSimEndState(void);
		// 析构函数
		virtual ~CSimEndState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};

	////////////////////////////////////pause state//////////////////////////////////////
	// 暂停状态
	class CSimPauseState : public CSimStateBase
	{
	public:
		// 构造函数
		CSimPauseState(void);
		// 析构函数
		virtual ~CSimPauseState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};

	//////////////////////////////////////exit state////////////////////////////////////
	// 退出状态
	class CSimExitState : public CSimStateBase
	{
	public:
		// 构造函数
		CSimExitState(void);
		// 析构函数
		virtual ~CSimExitState(void);

	public:
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase);
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase);
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase);

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};
	*/
}


#endif // !_SIMSTATE_H_