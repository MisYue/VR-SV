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
	class CMessageSystem : public IMessageManager
	{
	public:
		explicit CMessageSystem(const VRString& strName);
		virtual ~CMessageSystem(void);

	public:
		// ��ȡ��������
		virtual const VRString& GetTypeName(void) const;
		// ��ʼ��ϵͳ
		virtual void Init(void);

		//��������
		SET_GET_PROPERTY(Name, VRString, str);

	public: 
		// ������Ϣ
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// ������Ϣ
		virtual void DispatchMessage(const VRString& strSendType, const VRString& strSendID, \
			 const VRString& strReceiverType, const VRString& strReceiverID, UINT uMsg, \
			 const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// ��Ϣѭ��
		virtual void DispatchDelayedMessages(void);

	protected:
		// ������Ϣ
		void DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage);

	protected:
		typedef std::set<CMessage> MsgList;

	private:
		VRString m_strName;
		MsgList m_msgList;
	};

	// ע�Ṥ��
	REGISTER_COMFACTORY(CMessageSystem, MessageManager, MESSAGESYSTEM_TYPENAME, INSTANCE_NAME_MESSAGESYSTEM, MESSAGESYSTEM_DISC );
}

#endif