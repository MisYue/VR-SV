/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  消息系统实现类		                                        */
/* 时间： 2015-08-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _MESSAGESYSTEM_H_
#define _MESSAGESYSTEM_H_

#pragma once

#include <set>
#include "Message.h"


namespace VR_Soft
{
	class CMessageManager : public IMessageManager
	{
	public:
		explicit CMessageManager(void);
		virtual ~CMessageManager(void);

	public: 
		// 发送消息
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// 发送消息
		virtual void DispatchMessage(const uint64_t uSendID, const uint64_t uReceiverID, UINT uMsg, \
			 const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// 消息循环
		virtual void DispatchDelayedMessages(void);

	protected:
		// 处理消息
		void DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage);

	protected:
		typedef std::set<CMessage> MsgList;

	private:
		MsgList m_msgList;
	};
}

#endif