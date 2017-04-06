/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ϣ�ӿ�				                                        */
/* ʱ�䣺 2015-08-27                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IMESSAGE_H_
#define _PUBLIC_IMESSAGE_H_

namespace VR_Soft
{
	class VRSOFT_DLL IMessage
	{
	public:
		// ��������
		virtual ~IMessage() { };
		// ��÷�����
		virtual IEntityBase* GetSender(void) const = 0;
		// ���÷�����
		virtual void SetSender(const uint64_t uID) = 0;
		// ��ý�����
		virtual IEntityBase* GetReceiver(void) const  = 0;
		// ���ý�����
		virtual void SetReceiver(const uint64_t uID)  = 0;
		// ������Ϣ
		virtual void SetMessage(UINT uMsg) = 0;
		// �����Ϣ
		virtual UINT GetMessage(void) const = 0;
		// ���ô���ʱ��
		virtual void SetDispatch(const double dDispatchTime) = 0;
		// ��ô���ʱ��
		virtual double GetDispatch(void) const = 0;
		// ������չ��Ϣ
		virtual void SetExpendInfo(void* pExInfo) = 0;
		// �����չ��Ϣ
		virtual void* GetExpendInfo(void) const = 0;
	};
}

#endif // _PUBLIC_IMESSAGE_H_