/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  消息系统接口			                                        */
/* 时间： 2015-08-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IMESSAGESYSTEM_H_
#define _PUBLIC_IMESSAGESYSTEM_H_

namespace VR_Soft
{
	class IEntityBase;

	const double SEND_MSG_IMMEDIATELY = 0.0f;
	const int   NO_ADDITIONAL_INFO   = 0L;

	class VRSOFT_DLL IMessageManager : public CSingleton<IMessageManager>
	{
	public:
		// 析构函数
		virtual ~IMessageManager() { }
		// 发送消息
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO) = 0;
		// 发送消息
		virtual void DispatchMessage(const uint64_t uSendID, const uint64_t uReceiverID, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO) = 0;
		// 消息循环
		virtual void DispatchDelayedMessages(void) = 0;
	};
}

#endif // _PUBLIC_IMESSAGESYSTEM_H_