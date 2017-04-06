#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/VRSoft.h"
#include "Message.h"

const double SmallestDelay = 0.25;

namespace VR_Soft
{
	CMessage::CMessage(void)
		:m_strSendType(""),
		m_strSendID(""),
		m_strRecType(""),
		m_strRecID(""),
		m_uMsg(-1),
		m_dDispatchTime(-1.0),
		m_pMsgExInfo(NULL)
	{
	}

	CMessage::CMessage(const double dt, const VRString& strSendType, \
		const VRString& strSendID, const VRString& strRecType, \
		const VRString& strRecID, const UINT uMsg, void* pInfo/* = NULL*/)
		:m_strSendType(strSendType),
		m_strSendID(strSendID),
		m_strRecType(strRecType),
		m_strRecID(strRecID),
		m_uMsg(uMsg),
		m_dDispatchTime(dt),
		m_pMsgExInfo(pInfo)
	{

	}

	CMessage::CMessage(const CMessage& msg)
		:m_strSendType(msg.m_strSendType),
		m_strSendID(msg.m_strSendID),
		m_strRecType(msg.m_strRecType),
		m_strRecID(msg.m_strRecID),
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
		// 获得实体管理对象
		IEntityComposite* pIEntityComp = IComManager::GetInstance().GetEntityComposite();
		if (NULL == pIEntityComp)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("获取实体管理模型失败", ERROR_NOT_FIND);
			return (NULL);
		}

		IEntityComponent* pIEntityCast = pIEntityComp->GetEntity(m_strSendType, m_strSendID);

		IEntityBase* pEntityBase = dynamic_cast<IEntityBase*>(pIEntityCast);
		if (NULL == pEntityBase)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("模型转换失败", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);

	}

	// 获得发送者所属的路径
	VRString CMessage::GetSenderType(void) const
	{
		return (m_strSendType);
	}

	// 获得接收者所属的路径
	VRString CMessage::GetSenderID(void) const
	{
		return (m_strSendID);
	}

	// 设置发送者
	void CMessage::SetSender(const VRString& strType, const VRString& strID) 
	{
		m_strSendType = strType;
		m_strSendID = strID;
	}

	// 获得接受者
	IEntityBase* CMessage::GetReceiver(void) const 
	{
		// 获得实体管理对象
		IEntityComposite* pIEntityComp = IComManager::GetInstance().GetEntityComposite();
		if (NULL == pIEntityComp)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("获取实体管理模型失败", ERROR_NOT_FIND);
			return (NULL);
		}

		IEntityComponent* pIEntityCast = pIEntityComp->GetEntity(m_strRecType, m_strRecID);

		IEntityBase* pEntityBase = dynamic_cast<IEntityBase*>(pIEntityCast);
		if (NULL == pEntityBase)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("模型转换失败", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);
	}

	// 获得接收者所属的路径
	VRString CMessage::GetReceiverType(void) const 
	{
		return (m_strRecType);
	}

	// 获得接收者所属的路径
	VRString CMessage::GetReceiverID(void) const
	{
		return (m_strRecID);
	}

	// 设置接收者
	void CMessage::SetReceiver(const VRString& strType, const VRString& strID) 
	{
		m_strRecType = strType;
		m_strRecID = strID;
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
			(0 == m_strSendType.compare(msg.m_strSendType) )        &&
			(0 == m_strSendID.compare(msg.m_strSendID))    &&
			(0 == m_strRecType.compare(msg.m_strRecType) )        &&
			(0 == m_strRecID.compare(msg.m_strRecID))    &&
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
