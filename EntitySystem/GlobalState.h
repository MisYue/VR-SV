/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ȫ��״̬�࣬����ģ�ͷ���״̬		                            */
/* ʱ�䣺 2015-11-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _GLOBALSTATE_H_
#define _GLOBALSTATE_H_

#pragma once

namespace VR_Soft
{
	class CGlobalState : public IState
	{
	public:
		explicit CGlobalState(void);
		virtual ~CGlobalState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage) ;
	};
}


#endif // !_GOLABSTATE_H_