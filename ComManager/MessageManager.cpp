

#include "../../Public/VRSoft.h"
#include "Message.h"
#include "MessageManager.h"

namespace VR_Soft
{
	CMessageManager::CMessageManager(void)
	{
	}


	CMessageManager::~CMessageManager(void)
	{
	}

	// ������Ϣ
	void CMessageManager::DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* pIEntityReceiver,UINT uMsg, \
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
			DispatchMessage( 0, pIEntityReceiver->GetID(), uMsg, delay, ExtraInfo);
		}
		// ��������Ϊ��
		else
		{
			DispatchMessage( pIEntitySender->GetID(), pIEntityReceiver->GetID(), uMsg, delay, ExtraInfo);
		}
	}

	// ������Ϣ
	void CMessageManager::DispatchMessage(const uint64_t uSendID, const uint64_t uReceiverID, UINT uMsg, \
		const double delay /*= SEND_MSG_IMMEDIATELY*/, void*  ExtraInfo/* = NO_ADDITIONAL_INFO*/)
	{
		CMessage msg(delay, uSendID, uReceiverID, uMsg, ExtraInfo);

		// ���ʵ��
		IEntityBase* pIEntityBase = msg.GetReceiver();

		// �жϵ�ǰ�Ľ������Ƿ����
		if (NULL == pIEntityBase)
		{
			ILogManager::GetInstance().SetLogMessage( "û���ҵ���ǰģ��", ERROR_NOT_FIND);
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
	void CMessageManager::DispatchMessage(IEntityBase* pIEntityBase, const IMessage* pMessage)
	{
		if (!pIEntityBase->HandleMessage(pMessage))
		{
			ILogManager::GetInstance().SetLogMessage("��Ϣû�б�ִ��", ERROR_NOT_FIND);
			return;
		}
	}

	// ��Ϣѭ��
	void CMessageManager::DispatchDelayedMessages(void)
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

