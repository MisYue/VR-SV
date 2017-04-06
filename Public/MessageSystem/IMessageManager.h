/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ϣϵͳ�ӿ�			                                        */
/* ʱ�䣺 2015-08-27                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IMESSAGESYSTEM_H_
#define _PUBLIC_IMESSAGESYSTEM_H_

namespace VR_Soft
{
	const VRString MESSAGESYSTEM_TYPENAME = "MESSAGESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_MESSAGESYSTEM = "MESSAGESYSTEM";
	const VRString MESSAGESYSTEM_DISC = "��Ϣϵͳ";

	const double SEND_MSG_IMMEDIATELY = 0.0f;
	const int   NO_ADDITIONAL_INFO   = 0L;

	class VRSOFT_PLUGIN_DLL IMessageManager : public CSingleton<IMessageManager>, public IComManagerFace
	{
	public:
		// ��������
		virtual ~IMessageManager() { }
		// ������Ϣ
		virtual void DispatchMessage(IEntityBase* pIEntitySender, IEntityBase* Receiver, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO) = 0;
		// ������Ϣ
		virtual void DispatchMessage(const VRString& strSendType, const VRString& strSendID, \
			const VRString& strReceiverType, const VRString& strReceiverID, UINT uMsg, \
			const double delay = SEND_MSG_IMMEDIATELY, void*  ExtraInfo = NO_ADDITIONAL_INFO) = 0;
		// ��Ϣѭ��
		virtual void DispatchDelayedMessages(void) = 0;
	};
}

#endif // _PUBLIC_IMESSAGESYSTEM_H_