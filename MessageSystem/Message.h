/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ϣʵ����			                                        */
/* ʱ�䣺 2015-08-27                                                    */
/* �޸�ʱ��:                                                            */
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
		// ��÷�����
		virtual IEntityBase* GetSender(void) const;
		// ��÷�����������·��
		virtual VRString GetSenderType(void) const;
		// ��ý�����������·��
		virtual VRString GetSenderID(void) const;
		// ���÷�����
		virtual void SetSender(const VRString& strType, const VRString& strID) ;
		// ��ý�����
		virtual IEntityBase* GetReceiver(void) const ;
		// ��ý�����������·��
		virtual VRString GetReceiverType(void) const ;
		// ��ý�����������·��
		virtual VRString GetReceiverID(void) const;
		// ���ý�����
		virtual void SetReceiver(const VRString& strType, const VRString& strID) ;
		// ������Ϣ
		virtual void SetMessage(UINT uMsg) ;
		// �����Ϣ
		virtual UINT GetMessage(void) const ;
		// ���ô���ʱ��
		virtual void SetDispatch(const double dDispatchTime) ;
		// ��ô���ʱ��
		virtual double GetDispatch(void) const;
		// ������չ��Ϣ
		virtual void SetExpendInfo(void* pExInfo) ;
		// �����չ��Ϣ
		virtual void* GetExpendInfo(void) const ;

	public:
		// ����==
		bool operator== (const CMessage& msg) const ;
		// ����<
		bool operator< (const CMessage& msg) const;

	private:
		VRString m_strSendType; // ʵ����������
		VRString m_strSendID; // ʵ���ʶ
		VRString m_strRecType; // ʵ����������
		VRString m_strRecID; // ʵ���ʶ
		UINT	 m_uMsg; // ��Ϣ
		double	 m_dDispatchTime; // ����ʱ��
		void*	 m_pMsgExInfo;		// ��Ϣ��չ��ֵ
	};

}

#endif