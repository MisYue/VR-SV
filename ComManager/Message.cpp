
#include "../../Public/VRSoft.h"
#include "Message.h"

const double SmallestDelay = 0.25;

namespace VR_Soft
{
	CMessage::CMessage(void)
		:m_uSendID(0),
		m_uRecID(0),
		m_uMsg(-1),
		m_dDispatchTime(-1.0),
		m_pMsgExInfo(NULL)
	{
	}

	CMessage::CMessage(const double dt, const uint64_t uSendID, const uint64_t strRecID,  \
		const UINT uMsg, void* pInfo/* = NULL*/)
		:m_uSendID(0),
		m_uRecID(0),
		m_uMsg(-1),
		m_dDispatchTime(-1.0),
		m_pMsgExInfo(NULL)
	{

	}

	CMessage::CMessage(const CMessage& msg)
		:m_uSendID(msg.m_uSendID),
		m_uRecID(msg.m_uRecID),
		m_uMsg(msg.m_uMsg),
		m_dDispatchTime(msg.m_dDispatchTime),
		m_pMsgExInfo(msg.m_pMsgExInfo)
	{

	}

	CMessage::~CMessage(void)
	{
	}

	// 获得发送者
	IEntityBase* CMessage::GetSender(void) const
	{
		IEntityBase* pEntityBase = IEntityManager::GetInstance().GetEntity(m_uSendID);
		
		return (pEntityBase);

	}

	// 设置发送者
	void CMessage::SetSender(const uint64_t uID) 
	{
		m_uSendID = uID;
	}

	// 获得接受者
	IEntityBase* CMessage::GetReceiver(void) const 
	{
		IEntityBase* pEntityBase = IEntityManager::GetInstance().GetEntity(m_uRecID);
		if (NULL == pEntityBase)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("模型转换失败", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);
	}

	// 设置接收者
	void CMessage::SetReceiver(const uint64_t uID) 
	{
		m_uSendID = uID;
	}

	// 设置消息
	void CMessage::SetMessage(UINT uMsg) 
	{
		m_uMsg = uMsg;
	}

	// 获得消息
	UINT CMessage::GetMessage(void) const 
	{
		return (m_uMsg);
	}

	// 设置处理时间
	void CMessage::SetDispatch(const double dDispatchTime) 
	{
		m_dDispatchTime = dDispatchTime;
	}

	// 获得处理时间
	double CMessage::GetDispatch(void) const
	{
		return (m_dDispatchTime);
	}

	// 设置扩展消息
	void CMessage::SetExpendInfo(void* pExInfo) 
	{
		m_pMsgExInfo = pExInfo;
	}

	// 获得扩展消息
	void* CMessage::GetExpendInfo(void) const 
	{
		return (m_pMsgExInfo);
	}

	// 重载==
	bool CMessage::operator== (const CMessage& msg) const
	{
		return ( fabs(m_dDispatchTime - msg.m_dDispatchTime) < SmallestDelay) &&
			(m_uSendID == msg.m_uSendID )        &&
			(m_uRecID == msg.m_uRecID)    &&
			(m_uMsg == msg.m_uMsg);
	}

	// 重载<
	bool CMessage::operator< (const CMessage& msg) const 
	{
		if (*this == msg)
		{
			return (false);
		}
		else
		{
			return  (m_dDispatchTime < msg.m_dDispatchTime);
		}
	}

}
