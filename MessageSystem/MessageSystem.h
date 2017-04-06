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
	class CMessageSystem : public IMessageManager
	{
	public:
		explicit CMessageSystem(const VRString& strName);
		virtual ~CMessageSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);

		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	public: 
		// 发送消息
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// 发送消息
		virtual void DispatchMessage(const VRString& strSendType, const VRString& strSendID, \
			 const VRString& strReceiverType, const VRString& strReceiverID, UINT uMsg, \
			 const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO);
		// 消息循环
		virtual void DispatchDelayedMessages(void);

	protected:
		// 处理消息
		void DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage);

	protected:
		typedef std::set<CMessage> MsgList;

	private:
		VRString m_strName;
		MsgList m_msgList;
	};

	// 注册工厂
	REGISTER_COMFACTORY(CMessageSystem, MessageManager, MESSAGESYSTEM_TYPENAME, INSTANCE_NAME_MESSAGESYSTEM, MESSAGESYSTEM_DISC );
}

#endif