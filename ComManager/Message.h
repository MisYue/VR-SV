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
		explicit CMessage(const double dt, const uint64_t uSendID, const uint64_t strRecID,  \
			const UINT uMsg, void* pInfo = NULL);
		explicit CMessage(const CMessage& msg);
		virtual ~CMessage(void);

	public:
		// ��÷�����
		virtual IEntityBase* GetSender(void) const;
		// ���÷�����
		virtual void SetSender(const uint64_t uID) ;
		// ��ý�����
		virtual IEntityBase* GetReceiver(void) const ;
		// ���ý�����
		virtual void SetReceiver(const uint64_t uID) ;
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
		uint64_t m_uSendID; // ������ID
		uint64_t m_uRecID; // ������ID
		UINT	 m_uMsg; // ��Ϣ
		double	 m_dDispatchTime; // ����ʱ��
		void*	 m_pMsgExInfo;		// ��Ϣ��չ��ֵ
	};

}

#endif