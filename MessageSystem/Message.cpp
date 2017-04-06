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

	// ��÷�����
	IEntityBase* CMessage::GetSender(void) const
	{
		// ���ʵ��������
		IEntityComposite* pIEntityComp = IComManager::GetInstance().GetEntityComposite();
		if (NULL == pIEntityComp)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("��ȡʵ�����ģ��ʧ��", ERROR_NOT_FIND);
			return (NULL);
		}

		IEntityComponent* pIEntityCast = pIEntityComp->GetEntity(m_strSendType, m_strSendID);

		IEntityBase* pEntityBase = dynamic_cast<IEntityBase*>(pIEntityCast);
		if (NULL == pEntityBase)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("ģ��ת��ʧ��", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);

	}

	// ��÷�����������·��
	VRString CMessage::GetSenderType(void) const
	{
		return (m_strSendType);
	}

	// ��ý�����������·��
	VRString CMessage::GetSenderID(void) const
	{
		return (m_strSendID);
	}

	// ���÷�����
	void CMessage::SetSender(const VRString& strType, const VRString& strID) 
	{
		m_strSendType = strType;
		m_strSendID = strID;
	}

	// ��ý�����
	IEntityBase* CMessage::GetReceiver(void) const 
	{
		// ���ʵ��������
		IEntityComposite* pIEntityComp = IComManager::GetInstance().GetEntityComposite();
		if (NULL == pIEntityComp)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("��ȡʵ�����ģ��ʧ��", ERROR_NOT_FIND);
			return (NULL);
		}

		IEntityComponent* pIEntityCast = pIEntityComp->GetEntity(m_strRecType, m_strRecID);

		IEntityBase* pEntityBase = dynamic_cast<IEntityBase*>(pIEntityCast);
		if (NULL == pEntityBase)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("ģ��ת��ʧ��", ERROR_FAILE_CONVERT);
			return (NULL);
		}

		return (pEntityBase);
	}

	// ��ý�����������·��
	VRString CMessage::GetReceiverType(void) const 
	{
		return (m_strRecType);
	}

	// ��ý�����������·��
	VRString CMessage::GetReceiverID(void) const
	{
		return (m_strRecID);
	}

	// ���ý�����
	void CMessage::SetReceiver(const VRString& strType, const VRString& strID) 
	{
		m_strRecType = strType;
		m_strRecID = strID;
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
			(0 == m_strSendType.compare(msg.m_strSendType) )        &&
			(0 == m_strSendID.compare(msg.m_strSendID))    &&
			(0 == m_strRecType.compare(msg.m_strRecType) )        &&
			(0 == m_strRecID.compare(msg.m_strRecID))    &&
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
