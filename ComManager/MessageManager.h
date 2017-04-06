/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ϣϵͳʵ����		                                        */
/* ʱ�䣺 2015-08-27                                                    */
/* �޸�ʱ��:                                                            */
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
		// ������Ϣ
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// ������Ϣ
		virtual void DispatchMessage(const uint64_t uSendID, const uint64_t uReceiverID, UINT uMsg, \
			 const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// ��Ϣѭ��
		virtual void DispatchDelayedMessages(void);

	protected:
		// ������Ϣ
		void DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage);

	protected:
		typedef std::set<CMessage> MsgList;

	private:
		MsgList m_msgList;
	};
}

#endif