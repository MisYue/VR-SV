/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����				                                        */
/* ʱ�䣺 2016-06-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _ENTITYBASE_H_
#define _ENTITYBASE_H_

#pragma once

namespace VR_Soft
{
	////////////////////////////ϵͳģ��//////////////////////////////////////////////
	class CEntityBase : public CEntityBaseImp<IEntityBase>
	{
	public:
		// ���캯��
		explicit CEntityBase(void);
		// ��������
		virtual ~CEntityBase(void);

	public:
		// ��ʼ��
		virtual void Init(void);
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);
		// �������
		virtual const VRString GetEntityType(void) const;
	};

	////////////////////////////ϵͳģ��������//////////////////////////////////////////////
	class CEntityBaseBuilder : public IEntityBulider
	{
	public:
		// ���캯��
		explicit CEntityBaseBuilder(void);
		// ��������
		virtual ~CEntityBaseBuilder(void);

	public:
		// ������Ⱦ��������
		virtual void CreateDrawManager(void);
		// ������Ⱦ����
		virtual void CreateDrawAttribute(void);
		// ��������������
		virtual void CreateAttribute(void) ;
		// �������
		virtual VRString CreateEntityName(void) const ;
		// ��ò�Ʒ
		virtual IEntityBase* GetEntity(void);
		// �Ƿ񴴽��˶����� ����true �򴴽�
		virtual bool IsCreateMoveAttribute(void);

	private:
		CEntityBase* m_pEntityBase;
	};

	// ע��ϵͳ����
	REGISTER_BASEENTITY_FACTORY(CEntityBaseBuilder, "ϵͳģ��")
}


#endif