/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ�����				                                        */
/* ʱ�䣺 2015-05-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _IENTITYBASE_H_
#define _IENTITYBASE_H_

#pragma once


namespace VR_Soft
{
	class IAttribute;
	class IStateMachine;
	class IEntityDrawManager;
	class IDrawAttribute;
	class IEntityBaseAttribute;
	class IEntityDrawAttribute;
	class IEntityID;
	class IMessage;
	class IEntityVisitor;

	class VRSOFT_DLL IEntityBase
	{
	public:
		typedef std::vector<IAttribute*> ListAttributes;

	public:
		// ��������
		virtual ~IEntityBase() { }

	public:
		// ��ʼ��
		virtual void Init(void) = 0;
		// �������
		virtual const VRString GetEntityType(void) const = 0;
		// ����ʵ���������
		virtual void SetBaseAttribute(IEntityBaseAttribute* pIEntityBaseAttribute) = 0;
		// ��û������Զ���
		virtual IEntityBaseAttribute* GetBaseAttribute(void) const = 0;
		// ����ʵ����Ⱦ����
		virtual void SetEntityDrawAttribute(IEntityDrawAttribute* pIEntityDrawAttribute) = 0;
		// ���ʵ����Ⱦ����
		virtual IEntityDrawAttribute* GetEntityDrawAttribute(void) const = 0;
		// ��������
		virtual void AddAttributes(IAttribute* pIAttribute) = 0;
		// �������
		virtual IAttribute* GetAttribute(const VRString& strAttrName) const = 0;
		// �Ƴ�����
		virtual bool RemoveAttribute(const VRString& strAttrName) = 0;
		// �������Ⱥ
		virtual void AddAttributes(const ListAttributes& lstAttribtes) = 0; 
		// �����������
		virtual ListAttributes GetAllAttribute(void) const = 0;
		// ������Ⱦ����
		virtual void SetDrawManager(IEntityDrawManager* pIDrawManager) = 0;
		// �����Ⱦ����
		virtual IEntityDrawManager* GetDrawManager(void) const  = 0;
		// ������Ⱦ����
		virtual void AddDrawAttribute(IDrawAttribute* pIDrawAttribute) = 0;
		// �����Ⱦ����
		virtual IDrawAttribute* GetDrawAttribute(const VRString& strName) = 0;
		// �Ƴ���Ⱦ����
		virtual void RemoveDrawAttribute(IDrawAttribute* pIDrawAttribute) = 0;

		// ��־
	public: 
		// ���ñ�־
		virtual void SetID(uint64_t uID) = 0;
		// ��ñ�־
		virtual const uint64_t GetID(void) const = 0;
		// ��������
		virtual void SetName(const VRString& strName) = 0;
		// �������
		virtual VRString GetName(void) const = 0;
		// ��Ҫ����
		virtual void NeedUpdate(void) = 0;
		// �Ƿ��б�Ҫ����
		virtual bool IsUpdate(void) const = 0;
		// ģ�͸��£�ÿһ����֡����)
		virtual void EntityUpdate(const CDateTime& dt) = 0;

		// ��Ϣ���
	public:
		// ������Ϣ
		virtual bool HandleMessage(const IMessage* pIMessage) = 0;
		// ���״̬��
		virtual IStateMachine* GetStateMachine(void) const = 0;
		// ����״̬��
		virtual void SetStateMachine(IStateMachine* pIStateMachine) = 0;
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine) = 0;
	};
}

#endif // _IENTITYBASE_H_