/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ���ϵͳ���													*/
/* ʱ�䣺 2015-05-22                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ELECMAGONSTATE_H_
#define _ELECMAGONSTATE_H_

#pragma once

namespace VR_Soft
{
	/************************************************************************/
	/*                            ����״̬                                  */
	/************************************************************************/
	class CElectMagOnState : public IState
	{
	public:
		explicit CElectMagOnState(void);
		virtual ~CElectMagOnState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);

	private:
		osg::Vec3d m_vRadius;
		osg::Vec3d m_vRadiusUp;
	};

	/************************************************************************/
	/*                            ɨ��״̬                                  */
	/************************************************************************/
	class CElectMagScanState : public IState
	{
	public:
		explicit CElectMagScanState(void);
		virtual ~CElectMagScanState(void);

	public:
		// ����״̬
		virtual void Enter(IEntityBase* pEntityBase);
		// ִ��״̬
		virtual void Execute(IEntityBase* pEntityBase);
		// �뿪״̬
		virtual void Exit(IEntityBase* pEntityBase);

		// ��Ϣ����
		virtual bool OnMessage(IEntityBase* pEntityBase, const IMessage* pMessage);
	};
}


#endif //  _ELECMAGONSTATE_H_