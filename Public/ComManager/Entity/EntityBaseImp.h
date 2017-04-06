/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基模板类			                                        */
/* 时间： 2015-08-03                                                    */
/* 修改时间:                                                            */
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

		// 析构函数
		virtual ~CEntityBaseImp() 
		{
			// 删除属性
			RemoveAll();
			// 删除渲染管理
			VRSOFT_DELETE(m_pIEntitiyDrawManager);
			// 删除状态机
			VRSOFT_DELETE(m_pIStateMachine);
		}

		// 设置名称
		virtual void SetName(const VRString& strName) 
		{
			if (NULL == m_pIEntityBaseAttribute)
			{
				return;
			}
			m_pIEntityBaseAttribute->SetEntityName(strName);
		}

		// 获得名称
		virtual VRString GetName(void) const
		{
			if (NULL == m_pIEntityBaseAttribute)
			{
				return ("");
			}
			return (m_pIEntityBaseAttribute->GetEntityName());
		}

		// 设置实体基本属性
		virtual void SetBaseAttribute(IEntityBaseAttribute* pIEntityBaseAttribute)
		{
			m_pIEntityBaseAttribute = pIEntityBaseAttribute;
			AddAttributes(pIEntityBaseAttribute);
		}

		// 获得基本属性对象
		virtual IEntityBaseAttribute* GetBaseAttribute(void) const
		{
			return (m_pIEntityBaseAttribute);
		}

		// 设置实体渲染属性
		virtual void SetEntityDrawAttribute(IEntityDrawAttribute* pIEntityDrawAttribute)
		{
			m_pIEntityDrawAttribute = pIEntityDrawAttribute;
		}

		// 获得实体渲染属性
		virtual IEntityDrawAttribute* GetEntityDrawAttribute(void) const
		{
			return (m_pIEntityDrawAttribute);
		}

		// 设置属性
		virtual void AddAttributes(IAttribute* pIAttribute) 
		{
			// 多线程同步
			VR_MUTEX_AUTO

			// 获得当前的属性是否存在
			const VRString& strName = pIAttribute->GetName();
			ListStrAttributes::const_iterator cstItor = m_lstStrAttribtes.find(strName); //->std::find(m_lstAttribtes.begin(), m_lstAttribtes.end(), pIAttribute);
			if (m_lstStrAttribtes.end() != cstItor )
			{
				// 已经存在
				IComManager::GetInstance().WriteLogMsg(pIAttribute->GetName() + "已经存在，无需添加");
				return;
			}

			// 加入链表中
			m_lstStrAttribtes.insert(ListStrAttributes::value_type(strName, pIAttribute));
			m_listAttributes.push_back(pIAttribute);

			InitAttribute(pIAttribute); 

			// 判断渲染是否存在
			if (NULL == m_pIEntitiyDrawManager)
			{
				return;
			}

			// 转换成渲染属性
			IDrawAttribute* pIDrawAttribute = dynamic_cast<IDrawAttribute*>(pIAttribute);
			if (NULL != pIDrawAttribute)
			{
				m_pIEntitiyDrawManager->Add(pIDrawAttribute);
			}

			// 更新到属性UI
			IAttributeManager::GetInstance().BindAttribute(this, pIAttribute);

			// 判断是否为实体选人属性
			IEntityDrawAttribute* pIEntityDrawAttribute = dynamic_cast<IEntityDrawAttribute*>(pIAttribute);
			if (NULL != pIEntityDrawAttribute)
			{
				m_pIEntityDrawAttribute = pIEntityDrawAttribute;
			}
			
		}

		// 获得属性
		virtual IAttribute* GetAttribute(const VRString& strAttrName) const
		{
			ListStrAttributes::const_iterator cstItor = m_lstStrAttribtes.find(strAttrName);// begin();
			if (m_lstStrAttribtes.end() != cstItor)
			{
				return (cstItor->second);
			}

			return (NULL);
		}

		// 移除属性
		virtual bool RemoveAttribute(const VRString& strAttrName)
		{
			// 多线程同步
			VR_MUTEX_AUTO

			// 判断是否为接触属性
			if (0 == strAttrName.compare("基础属性"))
			{
				ILogManager::GetInstance().SetLogMessage("基础属性不能删除");
				return (false);
			}

			// 获得属性
			ListStrAttributes::iterator itor = m_lstStrAttribtes.find(strAttrName);
			if (m_lstStrAttribtes.end() == itor)
			{
				return (false);
			}

			// 判断渲染是否存在
			if (NULL != m_pIEntitiyDrawManager)
			{
				m_pIEntitiyDrawManager->Remove(strAttrName);
			}

			IAttribute* pIAttribute = itor->second;
			// 更新UI界面
			IAttributeManager::GetInstance().UnBindAttribute(this, pIAttribute);

			// 判断是否和基础渲染属性相同
			if (m_pIEntityDrawAttribute == pIAttribute)
			{
				m_pIEntityDrawAttribute = NULL;
			}

			// 查询删除
			ListAttributes::iterator listItor = std::find(m_listAttributes.begin(), m_listAttributes.end(), pIAttribute);
			if (m_listAttributes.end() != listItor)
			{
				m_listAttributes.erase(listItor);
			}
			
			VRSOFT_DELETE(pIAttribute);
			m_lstStrAttribtes.erase(itor);

			return (true);
		}

		// 添加属性群
		virtual void AddAttributes(const IEntityBase::ListAttributes& lstAttribtes)
		{
			IEntityBase::ListAttributes::const_iterator cstItor = lstAttribtes.begin();
			for (; lstAttribtes.end() != cstItor; ++cstItor)
			{
				AddAttributes(*cstItor);
			}
		}

		// 获得所有属性
		virtual IEntityBase::ListAttributes GetAllAttribute(void) const
		{
			return (m_listAttributes);
		}

		// 设置渲染管理
		virtual void SetDrawManager(IEntityDrawManager* pIDrawManager)
		{
			m_pIEntitiyDrawManager = pIDrawManager;
		}

		// 获得渲染管理
		virtual IEntityDrawManager* GetDrawManager(void) const 
		{
			return (m_pIEntitiyDrawManager);
		}

		// 设置渲染属性
		virtual void AddDrawAttribute(IDrawAttribute* pIDrawAttribute)
		{
			// 查找是否存在当前的属性
			if (IsHand(pIDrawAttribute->GetName()) || (NULL == m_pIEntitiyDrawManager) )
			{
				return;
			}

	//		m_pIEntitiyDrawManager->Add(pIDrawAttribute);

			// 添加进入到属性中
			AddAttributes(pIDrawAttribute);

		}
		// 获得渲染属性
		virtual IDrawAttribute* GetDrawAttribute(const VRString& strName)
		{
			if (NULL == m_pIEntitiyDrawManager)
			{
				return (NULL);
			}

			return (m_pIEntitiyDrawManager->GetAttribute(strName));
		}

		// 移除渲染属性
		virtual void RemoveDrawAttribute(IDrawAttribute* pIDrawAttribute)
		{
			m_pIEntitiyDrawManager->Remove(pIDrawAttribute);
			RemoveAttribute(pIDrawAttribute->GetName());
		}
	
		// 更新模型
		virtual void EntityUpdate(const CDateTime& dt)
		{
			// 多线程同步
			VR_MUTEX_AUTO

			struct UpdateAttribute
			{
				void operator() (IAttribute* pIAttribute)
				{
					pIAttribute->Update();
				}
			};
			// 更新所有的属性
			std::for_each(m_listAttributes.begin(), m_listAttributes.end(), UpdateAttribute());
			
			// 状态机更新
			m_pIStateMachine->Update(dt);
		}

	public:
		// 设置标志 对象 // 由系统自身调用
		virtual void SetID(IEntityID* pEntityID) 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return;
			}

			pIBaseAttribte->SetEntityID(pEntityID);
		}
		// 设置标志
		virtual void SetID(uint64_t uid) 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return;
			}
			pIBaseAttribte->SetEntityID(uid);
		}

		// 获得标志
		virtual const uint64_t GetID(void) const 
		{
			IEntityBaseAttribute* pIBaseAttribte = GetBaseAttribute();
			if (NULL == pIBaseAttribte)
			{
				return (-1);
			}
			return (pIBaseAttribte->GetEntityID());
		}

		// 需要更新
		virtual void NeedUpdate(void) 
		{
			m_bUpdate = true;
		}

		// 是否有必要更新
		virtual bool IsUpdate(void) const
		{
			if (m_bUpdate)
			{
				m_bUpdate = false;
				return (true);
			}

			return (false);
		}

		// 消息处理
		virtual bool HandleMessage(const IMessage* pIMessage)
		{
			// 判断状态机是否存在
			if (NULL == m_pIStateMachine)
			{
				IComManager::GetInstance().WriteLogMsg("状态机不存在", ERROR_NOT_FIND);
				return (false);
			}


			return m_pIStateMachine->HandleMessage(pIMessage);
		}

		// 获得状态机
		virtual IStateMachine* GetStateMachine(void) const
		{
			return (m_pIStateMachine);
		}

		// 设置状态机
		virtual void SetStateMachine(IStateMachine* pIStateMachine)
		{
			m_pIStateMachine = pIStateMachine;
		}

	protected:
		// 初始化
		void InitAttribute(IAttribute* pIAttribute)
		{
			pIAttribute->Init();		
		}

		// 移除所有的属性
		void RemoveAll(void)
		{
			// 移除渲染属性
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

		// 查找是否存在当前属性
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
		IStateMachine* m_pIStateMachine; // 状态机
		ListStrAttributes m_lstStrAttribtes; // 属性集合
		ListAttributes m_listAttributes; // 属性集合
		IEntityDrawManager* m_pIEntitiyDrawManager; 
		IEntityBaseAttribute* m_pIEntityBaseAttribute; // 基础属性 经常使用，并且不能删除 因此单独作为一个
		IEntityDrawAttribute* m_pIEntityDrawAttribute; // x渲染属性， 经常使用因此单独获取无需查找
		mutable bool m_bUpdate; // 更新需求

		// 多线程处理
		VR_AUTO_MUTEX
	};
}

#endif // _IENTITYBASEIMP_H_