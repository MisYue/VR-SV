/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  消息接口				                                        */
/* 时间： 2015-08-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IMESSAGE_H_
#define _PUBLIC_IMESSAGE_H_

namespace VR_Soft
{
	class IMessage
	{
	public:
		// 析构函数
		virtual ~IMessage() { };
		// 获得发送者
		virtual IEntityBase* GetSender(void) const = 0;
		// 获得发送者所属的路径
		virtual VRString GetSenderType(void) const = 0;
		// 获得发送者所属的路径
		virtual VRString GetSenderID(void) const = 0;
		// 设置发送者
		virtual void SetSender(const VRString& strType, const VRString& strID) = 0;
		// 获得接受者
		virtual IEntityBase* GetReceiver(void) const = 0;
		// 获得接收者所属的路径
		virtual VRString GetReceiverType(void) const = 0;
		// 获得接收者所属的路径
		virtual VRString GetReceiverID(void) const = 0;
		// 设置接收者
		virtual void SetReceiver(const VRString& strType, const VRString& strID) = 0;
		// 设置消息
		virtual void SetMessage(UINT uMsg) = 0;
		// 获得消息
		virtual UINT GetMessage(void) const = 0;
		// 设置处理时间
		virtual void SetDispatch(const double dDispatchTime) = 0;
		// 获得处理时间
		virtual double GetDispatch(void) const = 0;
		// 设置扩展消息
		virtual void SetExpendInfo(void* pExInfo) = 0;
		// 获得扩展消息
		virtual void* GetExpendInfo(void) const = 0;
	};
}

#endif // _PUBLIC_IMESSAGE_H_