#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "Message.h"
#include "MessageSystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CMessageManagerFactory::FACTORY_TYPE_NAME = MESSAGESYSTEM_TYPENAME;
	///////////////////////////////////////////////

	CMessageSystem::CMessageSystem(const VRString& strName)
	{
		SetName(strName);
	}


	CMessageSystem::~CMessageSystem(void)
	{
	}

	const VRString& CMessageSystem::GetTypeName(void) const
	{
		return CMessageManagerFactory::FACTORY_TYPE_NAME;
	}

	// 初始化系统
	void CMessageSystem::Init(void)
	{

	}

	// 发送消息
	void CMessageSystem::DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* pIEntityReceiver,UINT uMsg, \
		const double delay/* = SEND_MSG_IMMEDIATELY*/, void*  ExtraInfo/* = NO_ADDITIONAL_INFO*/)
	{
		// 判断接收者是否为空
		if (NULL == pIEntityReceiver)
		{
			return;
		}
		// 判断发送者是否为空
		else if ((NULL == pIEntitySender))
		{
			// 获得接受者的类型
			IEntityComponent* pIEntityReceiverType = pIEntityReceiver->GetParentEntity();

			if (NULL == pIEntityReceiverType)
			{
				DispatchMessage("", "", "", pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
			}
			else
			{
				DispatchMessage("", "", pIEntityReceiverType->GetName(), pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
			}
		}
		// 两个都不为空
		else
		{
			// 获得接受者的类型
			IEntityComponent* pIEntityReceiverType = pIEntityReceiver->GetParentEntity();

			// 获得发送模型的类型
			IEntityComponent* pIEntitySenderType = pIEntitySender->GetParentEntity();
			// 接受者没有父类型
			if (NULL == pIEntityReceiverType)
			{
				// 判断发送者是否有父类型
				if (NULL == pIEntitySenderType)
				{
					DispatchMessage("", pIEntitySender->GetName(), "", pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
				}
				else
				{
					DispatchMessage(pIEntitySenderType->GetName(), pIEntitySender->GetName(),\
						"", pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
				}
				
			}
			else
			{
				// 判断发送者是否有父类型
				if (NULL == pIEntitySenderType)
				{
					DispatchMessage("", pIEntitySender->GetName(), pIEntityReceiverType->GetName(),\
						pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
				}
				else
				{
					DispatchMessage(pIEntitySenderType->GetName(), pIEntitySender->GetName(),\
						pIEntityReceiverType->GetName(), pIEntityReceiver->GetName(), uMsg, delay, ExtraInfo);
				}
			}
		}		
	}

	// 发送消息
	void CMessageSystem::DispatchMessage(const VRString& strSendType, const VRString& strSendID, \
		const VRString& strReceiverType, const VRString& strReceiverID, UINT uMsg, \
		const double delay /*= SEND_MSG_IMMEDIATELY*/, void*  ExtraInfo/* = NO_ADDITIONAL_INFO*/)
	{
		CMessage msg(delay, strSendType, strSendID, strReceiverType, strReceiverID, uMsg, ExtraInfo);

		// 获得实体
		IEntityBase* pIEntityBase = msg.GetReceiver();

		// 判断当前的接受者是否存在
		if (NULL == pIEntityBase)
		{
			IComManager::GetInstance().WriteLogMsg(strReceiverID + "没有找到当前模型", ERROR_NOT_FIND);
			return;
		}

		// 判断是否到时间处理
		if (0.0 >= delay)
		{
			DispatchMessage(pIEntityBase, &msg);
		}

		// 添加到消息列表中
		else
		{
			double dCurrentTime = 111;
			double dCurrentDelay = msg.GetDispatch() + dCurrentTime;
			msg.SetDispatch(dCurrentDelay);
			m_msgList.insert(msg);
		}
	}

	// 处理消息
	void CMessageSystem::DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage)
	{
		if (!pIEntityBase->HandleMessage(pMessage))
		{
			IComManager::GetInstance().WriteLogMsg("消息没有被执行", ERROR_NOT_FIND);
			return;
		}
	}

	// 消息循环
	void CMessageSystem::DispatchDelayedMessages(void)
	{
		// 获得系统时间 系统加上时间之后直接获取 目前采用0表示
		double dCurrentTime = 10.0;

		// 遍历消息列表进行直接出来消息
		while((!m_msgList.empty()) \
			&& (m_msgList.begin()->GetDispatch() > dCurrentTime)\
			&& (m_msgList.begin()->GetDispatch() > 0))
		{
			// 获得消息
			const CMessage& msg = *m_msgList.begin();

			// 获得接收对象
			IEntityBase* pIEntityBase = msg.GetReceiver();
			// 处理消息
			DispatchMessage(pIEntityBase, &msg);

			// 移除消息队列从当前的列表中
			m_msgList.erase(m_msgList.begin());
		}
		
	}
}

