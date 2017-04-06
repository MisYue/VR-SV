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

	// ��ʼ��ϵͳ
	void CMessageSystem::Init(void)
	{

	}

	// ������Ϣ
	void CMessageSystem::DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* pIEntityReceiver,UINT uMsg, \
		const double delay/* = SEND_MSG_IMMEDIATELY*/, void*  ExtraInfo/* = NO_ADDITIONAL_INFO*/)
	{
		// �жϽ������Ƿ�Ϊ��
		if (NULL == pIEntityReceiver)
		{
			return;
		}
		// �жϷ������Ƿ�Ϊ��
		else if ((NULL == pIEntitySender))
		{
			// ��ý����ߵ�����
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
		// ��������Ϊ��
		else
		{
			// ��ý����ߵ�����
			IEntityComponent* pIEntityReceiverType = pIEntityReceiver->GetParentEntity();

			// ��÷���ģ�͵�����
			IEntityComponent* pIEntitySenderType = pIEntitySender->GetParentEntity();
			// ������û�и�����
			if (NULL == pIEntityReceiverType)
			{
				// �жϷ������Ƿ��и�����
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
				// �жϷ������Ƿ��и�����
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

	// ������Ϣ
	void CMessageSystem::DispatchMessage(const VRString& strSendType, const VRString& strSendID, \
		const VRString& strReceiverType, const VRString& strReceiverID, UINT uMsg, \
		const double delay /*= SEND_MSG_IMMEDIATELY*/, void*  ExtraInfo/* = NO_ADDITIONAL_INFO*/)
	{
		CMessage msg(delay, strSendType, strSendID, strReceiverType, strReceiverID, uMsg, ExtraInfo);

		// ���ʵ��
		IEntityBase* pIEntityBase = msg.GetReceiver();

		// �жϵ�ǰ�Ľ������Ƿ����
		if (NULL == pIEntityBase)
		{
			IComManager::GetInstance().WriteLogMsg(strReceiverID + "û���ҵ���ǰģ��", ERROR_NOT_FIND);
			return;
		}

		// �ж��Ƿ�ʱ�䴦��
		if (0.0 >= delay)
		{
			DispatchMessage(pIEntityBase, &msg);
		}

		// ��ӵ���Ϣ�б���
		else
		{
			double dCurrentTime = 111;
			double dCurrentDelay = msg.GetDispatch() + dCurrentTime;
			msg.SetDispatch(dCurrentDelay);
			m_msgList.insert(msg);
		}
	}

	// ������Ϣ
	void CMessageSystem::DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage)
	{
		if (!pIEntityBase->HandleMessage(pMessage))
		{
			IComManager::GetInstance().WriteLogMsg("��Ϣû�б�ִ��", ERROR_NOT_FIND);
			return;
		}
	}

	// ��Ϣѭ��
	void CMessageSystem::DispatchDelayedMessages(void)
	{
		// ���ϵͳʱ�� ϵͳ����ʱ��֮��ֱ�ӻ�ȡ Ŀǰ����0��ʾ
		double dCurrentTime = 10.0;

		// ������Ϣ�б����ֱ�ӳ�����Ϣ
		while((!m_msgList.empty()) \
			&& (m_msgList.begin()->GetDispatch() > dCurrentTime)\
			&& (m_msgList.begin()->GetDispatch() > 0))
		{
			// �����Ϣ
			const CMessage& msg = *m_msgList.begin();

			// ��ý��ն���
			IEntityBase* pIEntityBase = msg.GetReceiver();
			// ������Ϣ
			DispatchMessage(pIEntityBase, &msg);

			// �Ƴ���Ϣ���дӵ�ǰ���б���
			m_msgList.erase(m_msgList.begin());
		}
		
	}
}

