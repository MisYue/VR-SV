/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��״̬��			                                        */
/* ʱ�䣺 2015-08-31                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISTATE_H_
#define _PUBLICE_ISTATE_H_

namespace VR_Soft
{
	class IEntityBase;
	class IMessage;

	class VRSOFT_DLL IState
	{
	public:
		virtual ~IState() { }
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase) = 0;
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase) = 0;
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase) = 0;

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage) = 0;

	};
}

#endif // _PUBLICE_ISTATE_H_