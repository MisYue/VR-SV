/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  消息实现类			                                        */
/* 时间： 2015-08-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#pragma once

namespace VR_Soft
{
	class CMessage : public IMessage
	{
	public:
		explicit CMessage(void);
		explicit CMessage(const double dt, const VRString& strSendType, \
			const VRString& strSendID, const VRString& strRecType, \
			const VRString& strRecID, const UINT uMsg, void* pInfo = NULL);
		explicit CMessage(const CMessage& msg);
		virtual ~CMessage(void);

	public:
		// 获得发送者
		virtual IEntityBase* GetSender(void) const;
		// 获得发送者所属的路径
		virtual VRString GetSenderType(void) const;
		// 获得接收者所属的路径
		virtual VRString GetSenderID(void) const;
		// 设置发送者
		virtual void SetSender(const VRString& strType, const VRString& strID) ;
		// 获得接受者
		virtual IEntityBase* GetReceiver(void) const ;
		// 获得接收者所属的路径
		virtual VRString GetReceiverType(void) const ;
		// 获得接收者所属的路径
		virtual VRString GetReceiverID(void) const;
		// 设置接收者
		virtual void SetReceiver(const VRString& strType, const VRString& strID) ;
		// 设置消息
		virtual void SetMessage(UINT uMsg) ;
		// 获得消息
		virtual UINT GetMessage(void) const ;
		// 设置处理时间
		virtual void SetDispatch(const double dDispatchTime) ;
		// 获得处理时间
		virtual double GetDispatch(void) const;
		// 设置扩展消息
		virtual void SetExpendInfo(void* pExInfo) ;
		// 获得扩展消息
		virtual void* GetExpendInfo(void) const ;

	public:
		// 重载==
		bool operator== (const CMessage& msg) const ;
		// 重载<
		bool operator< (const CMessage& msg) const;

	private:
		VRString m_strSendType; // 实体所属类型
		VRString m_strSendID; // 实体标识
		VRString m_strRecType; // 实体所属类型
		VRString m_strRecID; // 实体标识
		UINT	 m_uMsg; // 消息
		double	 m_dDispatchTime; // 处理时间
		void*	 m_pMsgExInfo;		// 消息扩展的值
	};

}

#endif