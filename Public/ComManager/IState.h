/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体状态类			                                        */
/* 时间： 2015-08-31                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISTATE_H_
#define _PUBLICE_ISTATE_H_

namespace VR_Soft
{
	class IEntityBase;
	class IMessage;

	class VRSOFT_DLL IState
	{
	public:
		virtual ~IState() { }
		// 进入状态
		virtual void Enter(IEntityBase* pEntityBase) = 0;
		// 执行状态
		virtual void Execute(IEntityBase* pEntityBase) = 0;
		// 离开状态
		virtual void Exit(IEntityBase* pEntityBase) = 0;

		// 消息处理
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage) = 0;

	};
}

#endif // _PUBLICE_ISTATE_H_