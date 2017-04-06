
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

	// ��÷�����
	IEntityBase* CMessage::GetSender(void) const
	{
		IEntityBase* pEntityBase = IEntityManager::GetInstance().GetEntity(m_uSendID);
		
		return (pEntityBase);

	}

	// ���÷�����
	void CMessage::SetSender(const uint64_t uID) 
	{
		m_uSendID = uID;
	}

	// ��ý�����
	IEntityBase* CMessage::GetReceiver(void) const 
	{
		IEntityBase* pEntityBase = IEntityManager::GetInstance().GetEntity(m_uRecID);
		if (NULL == pEntityBase)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("ģ��ת��ʧ��", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);
	}

	// ���ý�����
	void CMessage::SetReceiver(const uint64_t uID) 
	{
		m_uSendID = uID;
	}

	// ������Ϣ
	void CMessage::SetMessage(UINT uMsg) 
	{
		m_uMsg = uMsg;
	}

	// �����Ϣ
	UINT CMessage::GetMessage(void) const 
	{
		return (m_uMsg);
	}

	// ���ô���ʱ��
	void CMessage::SetDispatch(const double dDispatchTime) 
	{
		m_dDispatchTime = dDispatchTime;
	}

	// ��ô���ʱ��
	double CMessage::GetDispatch(void) const
	{
		return (m_dDispatchTime);
	}

	// ������չ��Ϣ
	void CMessage::SetExpendInfo(void* pExInfo) 
	{
		m_pMsgExInfo = pExInfo;
	}

	// �����չ��Ϣ
	void* CMessage::GetExpendInfo(void) const 
	{
		return (m_pMsgExInfo);
	}

	// ����==
	bool CMessage::operator== (const CMessage& msg) const
	{
		return ( fabs(m_dDispatchTime - msg.m_dDispatchTime) < SmallestDelay) &&
			(m_uSendID == msg.m_uSendID )        &&
			(m_uRecID == msg.m_uRecID)    &&
			(m_uMsg == msg.m_uMsg);
	}

	// ����<
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
