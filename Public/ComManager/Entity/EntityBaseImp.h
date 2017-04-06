/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ���ģ����			                                        */
/* ʱ�䣺 2015-08-03                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _IENTITYBASEIMP_H_
#define _IENTITYBASEIMP_H_

#include <boost/unordered_map.hpp>
#include <osg/Vec3>

#include "IEntityBase.h"

namespace VR_Soft
{
	class IMessage;
	class IStateMachine;
	class IEntityID;
	class IEntityBaseAttribute;

	template <class T>
	class CEntityBaseImp : public T
	{
	public:
		CEntityBaseImp::CEntityBaseImp():m_pIStateMachine(NULL),m_pIEntitiyDrawManager(NULL),\
			m_pIEntityBaseAttribute(NULL),m_pIEntityDrawAttribute(NULL)
		{
			m_lstStrAttribtes.clear();
			m_listAttributes.clear();
		}

		// ��������
		virtual ~CEntityBaseImp() 
		{
			// ɾ������
			RemoveAll();
			// ɾ����Ⱦ����
			VRSOFT_DELETE(m_pIEntitiyDrawManager);
			// ɾ��״̬��
			VRSOFT_DELETE(m_pIStateMachine);
		}

		// ��������
		virtual void SetName(const VRString& strName) 
		{
			if (NULL == m_pIEntityBaseAttribute)
			{
				return;
			}
			m_pIEntityBaseAttribute->SetEntityName(strName);
		}

		// �������
		virtual VRString GetName(void) const
		{
			if (NULL == m_pIEntityBaseAttribute)
			{
				return ("");
			}
			return (m_pIEntityBaseAttribute->GetEntityName());
		}

		// ����ʵ���������
		virtual void SetBaseAttribute(IEntityBaseAttribute* pIEntityBaseAttribute)
		{
			m_pIEntityBaseAttribute = pIEntityBaseAttribute;
			AddAttributes(pIEntityBaseAttribute);
		}

		// ��û������Զ���
		virtual IEntityBaseAttribute* GetBaseAttribute(void) const
		{
			return (m_pIEntityBaseAttribute);
		}

		// ����ʵ����Ⱦ����
		virtual void SetEntityDrawAttribute(IEntityDrawAttribute* pIEntityDrawAttribute)
		{
			m_pIEntityDrawAttribute = pIEntityDrawAttribute;
		}

		// ���ʵ����Ⱦ����
		virtual IEntityDrawAttribute* GetEntityDrawAttribute(void) const
		{
			return (m_pIEntityDrawAttribute);
		}

		// ��������
		virtual void AddAttributes(IAttribute* pIAttribute) 
		{
			// ���߳�ͬ��
			VR_MUTEX_AUTO

			// ��õ�ǰ�������Ƿ����
			const VRString& strName = pIAttribute->GetName();
			ListStrAttributes::const_iterator cstItor = m_lstStrAttribtes.find(strName); //->std::find(m_lstAttribtes.begin(), m_lstAttribtes.end(), pIAttribute);
			if (m_lstStrAttribtes.end() != cstItor )
			{
				// �Ѿ�����
				IComManager::GetInstance().WriteLogMsg(pIAttribute->GetName() + "�Ѿ����ڣ��������");
				return;
			}

			// ����������
			m_lstStrAttribtes.insert(ListStrAttributes::value_type(strName, pIAttribute));
			m_listAttributes.push_back(pIAttribute);

			InitAttribute(pIAttribute); 

			// �ж���Ⱦ�Ƿ����
			if (NULL == m_pIEntitiyDrawManager)
			{
				return;
			}

			// ת������Ⱦ����
			IDrawAttribute* pIDrawAttribute = dynamic_cast<IDrawAttribute*>(pIAttribute);
			if (NULL != pIDrawAttribute)
			{
				m_pIEntitiyDrawManager->Add(pIDrawAttribute);
			}

			// ���µ�����UI
			IAttributeManager::GetInstance().BindAttribute(this, pIAttribute);

			// �ж��Ƿ�Ϊʵ��ѡ������
			IEntityDrawAttribute* pIEntityDrawAttribute = dynamic_cast<IEntityDrawAttribute*>(pIAttribute);
			if (NULL != pIEntityDrawAttribute)
			{
				m_pIEntityDrawAttribute = pIEntityDrawAttribute;
			}
			
		}

		// �������
		virtual IAttribute* GetAttribute(const VRString& strAttrName) const
		{
			ListStrAttributes::const_iterator cstItor = m_lstStrAttribtes.find(strAttrName);// begin();
			if (m_lstStrAttribtes.end() != cstItor)
			{
				return (cstItor->second);
			}

			return (NULL);
		}

		// �Ƴ�����
		virtual bool RemoveAttribute(const VRString& strAttrName)
		{
			// ���߳�ͬ��
			VR_MUTEX_AUTO

			// �ж��Ƿ�Ϊ�Ӵ�����
			if (0 == strAttrName.compare("��������"))
			{
				ILogManager::GetInstance().SetLogMessage("�������Բ���ɾ��");
				return (false);
			}

			// �������
			ListStrAttributes::iterator itor = m_lstStrAttribtes.find(strAttrName);
			if (m_lstStrAttribtes.end() == itor)
			{
				return (false);
			}

			// �ж���Ⱦ�Ƿ����
			if (NULL != m_pIEntitiyDrawManager)
			{
				m_pIEntitiyDrawManager->Remove(strAttrName);
			}

			IAttribute* pIAttribute = itor->second;
			// ����UI����
			IAttributeManager::GetInstance().UnBindAttribute(this, pIAttribute);

			// �ж��Ƿ�ͻ�����Ⱦ������ͬ
			if (m_pIEntityDrawAttribute == pIAttribute)
			{
				m_pIEntityDrawAttribute = NULL;
			}

			// ��ѯɾ��
			ListAttributes::iterator listItor = std::find(m_listAttributes.begin(), m_listAttributes.end(), pIAttribute);
			if (m_listAttributes.end() != listItor)
			{
				m_listAttributes.erase(listItor);
			}
			
			VRSOFT_DELETE(pIAttribute);
			m_lstStrAttribtes.erase(itor);

			return (true);
		}

		// �������Ⱥ
		virtual void AddAttributes(const IEntityBase::ListAttributes& lstAttribtes)
		{
			IEntityBase::ListAttributes::const_iterator cstItor = lstAttribtes.begin();
			for (; lstAttribtes.end() != cstItor; ++cstItor)
			{
				AddAttributes(*cstItor);
			}
		}

		// �����������
		virtual IEntityBase::ListAttributes GetAllAttribute(void) const
		{
			return (m_listAttributes);
		}

		// ������Ⱦ����
		virtual void SetDrawManager(IEntityDrawManager* pIDrawManager)
		{
			m_pIEntitiyDrawManager = pIDrawManager;
		}

		// �����Ⱦ����
		virtual IEntityDrawManager* GetDrawManager(void) const 
		{
			return (m_pIEntitiyDrawManager);
		}

		// ������Ⱦ����
		virtual void AddDrawAttribute(IDrawAttribute* pIDrawAttribute)
		{
			// �����Ƿ���ڵ�ǰ������
			if (IsHand(pIDrawAttribute->GetName()) || (NULL == m_pIEntitiyDrawManager) )
			{
				return;
			}

	//		m_pIEntitiyDrawManager->Add(pIDrawAttribute);

			// ��ӽ��뵽������
			AddAttributes(pIDrawAttribute);

		}
		// �����Ⱦ����
		virtual IDrawAttribute* GetDrawAttribute(const VRString& strName)
		{
			if (NULL == m_pIEntitiyDrawManager)
			{
				return (NULL);
			}

			return (m_pIEntitiyDrawManager->GetAttribute(strName));
		}

		// �Ƴ���Ⱦ����
		virtual void RemoveDrawAttribute(IDrawAttribute* pIDrawAttribute)
		{
			m_pIEntitiyDrawManager->Remove(pIDrawAttribute);
			RemoveAttribute(pIDrawAttribute->GetName());
		}
	
		// ����ģ��
		virtual void EntityUpdate(const CDateTime& dt)
		{
			// ���߳�ͬ��
			VR_MUTEX_AUTO

			struct UpdateAttribute
			{
				void operator() (IAttribute* pIAttribute)
				{
					pIAttribute->Update();
				}
			};
			// �������е�����
			std::for_each(m_listAttributes.begin(), m_listAttributes.end(), UpdateAttribute());
			
			// ״̬������
			m_pIStateMachine->Update(dt);
		}

	public:
		// ���ñ�־ ���� // ��ϵͳ�������
		virtual void SetID(IEntityID* pEntityID) 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return;
			}

			pIBaseAttribte->SetEntityID(pEntityID);
		}
		// ���ñ�־
		virtual void SetID(uint64_t uid) 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return;
			}
			pIBaseAttribte->SetEntityID(uid);
		}

		// ��ñ�־
		virtual const uint64_t GetID(void) const 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return (-1);
			}
			return (pIBaseAttribte->GetEntityID());
		}

		// ��Ҫ����
		virtual void NeedUpdate(void) 
		{
			m_bUpdate = true;
		}

		// �Ƿ��б�Ҫ����
		virtual bool IsUpdate(void) const
		{
			if (m_bUpdate)
			{
				m_bUpdate = false;
				return (true);
			}

			return (false);
		}

		// ��Ϣ����
		virtual bool HandleMessage(const IMessage* pIMessage)
		{
			// �ж�״̬���Ƿ����
			if (NULL == m_pIStateMachine)
			{
				IComManager::GetInstance().WriteLogMsg("״̬��������", ERROR_NOT_FIND);
				return (false);
			}


			return m_pIStateMachine->HandleMessage(pIMessage);
		}

		// ���״̬��
		virtual IStateMachine* GetStateMachine(void) const
		{
			return (m_pIStateMachine);
		}

		// ����״̬��
		virtual void SetStateMachine(IStateMachine* pIStateMachine)
		{
			m_pIStateMachine = pIStateMachine;
		}

	protected:
		// ��ʼ��
		void InitAttribute(IAttribute* pIAttribute)
		{
			pIAttribute->Init();		
		}

		// �Ƴ����е�����
		void RemoveAll(void)
		{
			// �Ƴ���Ⱦ����
			if (NULL != m_pIEntitiyDrawManager)
			{
				m_pIEntitiyDrawManager->RemoveAll();
			}

			ListStrAttributes::iterator itor = m_lstStrAttribtes.begin();
			for (; m_lstStrAttribtes.end() != itor; ++itor)
			{
				VRSOFT_DELETE(itor->second);
			}

			m_lstStrAttribtes.clear();
			m_listAttributes.clear();
		}

		// �����Ƿ���ڵ�ǰ����
		bool IsHand(const VRString& strName) const
		{
			ListStrAttributes::const_iterator cstItor = m_lstStrAttribtes.find(strName);
			if (m_lstStrAttribtes.end() == cstItor)
			{
				return (false);
			}

			return (true);
			
		}



	private:
		// typedef std::vector<IAttribute*> ListAttributes;
		typedef boost::unordered_map<VRString, IAttribute*> ListStrAttributes;
		typedef std::vector<IAttribute*> ListAttributes;

	private:
		IStateMachine* m_pIStateMachine; // ״̬��
		ListStrAttributes m_lstStrAttribtes; // ���Լ���
		ListAttributes m_listAttributes; // ���Լ���
		IEntityDrawManager* m_pIEntitiyDrawManager; 
		IEntityBaseAttribute* m_pIEntityBaseAttribute; // �������� ����ʹ�ã����Ҳ���ɾ�� ��˵�����Ϊһ��
		IEntityDrawAttribute* m_pIEntityDrawAttribute; // x��Ⱦ���ԣ� ����ʹ����˵�����ȡ�������
		mutable bool m_bUpdate; // ��������

		// ���̴߳���
		VR_AUTO_MUTEX
	};
}

#endif // _IENTITYBASEIMP_H_