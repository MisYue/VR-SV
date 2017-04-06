
#include <list>
#include "../../Public/VRSoft.h"

#include "EntityFactoryManager.h"
#include "StateMachine.h"
//#include "GlobalState.h"
#include "EntityID.h"
#include "EntityBaseAttribute.h"
#include "EntityDirctor.h"
#include "EntityManager.h"
#include "EntityBase.h"
#include "EntityFileManager.h"

namespace VR_Soft
{
	CEntityManager::CEntityManager(void)
	{
	}

	CEntityManager::~CEntityManager(void)
	{
		m_entityFactoryManager.UnRegisterFactory("系统模型");
		RemoveAllFactroy();
		//m_listEntityManagerUI.clear();
	}

	// 获得实体模型
	IEntityBase* CEntityManager::GetEntity(const VRString& strEntityName) const
	{
		// 线程安全
		VR_MUTEX_AUTO;

		VectEntities::const_iterator cstItor = m_vecEntities.begin();
		for (; m_vecEntities.end() != cstItor; ++cstItor)
		{
			if (0 == (*cstItor)->GetName().compare(strEntityName))
			{
				return (*cstItor);
			}
		}
		return (NULL);
	}

	// 添加视图模型
	void CEntityManager::AddEntity(IEntityBase* pIEntity)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 检查是否存在当前的实体
		const uint64_t ID = pIEntity->GetID();
		// 查找当前的模型
		ListIDEntities::const_iterator cstItor = m_listIDEntities.find(ID);
		if (m_listIDEntities.end() != cstItor)
		{
			// 已经被加载过程
			IComManager::GetInstance().WriteLogMsg("实体：" + pIEntity->GetName() + "已经被加载过");
			return;
		}

		// 加入到场景中
		m_listIDEntities.insert(ListIDEntities::value_type(ID, pIEntity));
		// 加入到更新列表中
		m_vecEntities.push_back(pIEntity);

		// 添加新的实体
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateNewItem(pIEntity);
		}
	}

	// 移除对象
	void CEntityManager::RemoveEntity(IEntityBase* pIEntity)
	{
		if (NULL == pIEntity)
		{
			return;
		}

		VR_MUTEX_AUTO

		// 从更新列表中移除
		VectEntities::iterator vitor = std::find(m_vecEntities.begin(), m_vecEntities.end(), pIEntity);
		if (m_vecEntities.end() != vitor)
		{
			m_vecEntities.erase(vitor);
		}

		// 获得实体ID
		const uint64_t ID = pIEntity->GetID();
		// 在当前中查找是否存在
		ListIDEntities::iterator itor = m_listIDEntities.find(ID);
		if (m_listIDEntities.end() == itor)
		{
			return;
		}

		VRString strName = pIEntity->GetName();

		// 判断是否为当前的激活属性
		if (IAttributeManager::GetInstance().GetCurrentEntityBaseID() == ID)
		{
			IAttributeManager::GetInstance().SetCurrentEntityBase(NULL);
		}

		// 移除实体
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateDelItem(pIEntity);
		}

		// 删除实体
		VRSOFT_DELETE(pIEntity);
		m_listIDEntities.erase(itor);
		IComManager::GetInstance().WriteLogMsg("成功清除：" + strName);
	}

	// 移除对象
	void CEntityManager::RemoveEntity(const VRString& strName)
	{
		IEntityBase* pIEntity = GetEntity(strName);
		RemoveEntity(pIEntity);
	}

	// 移除对象
	void CEntityManager::RemoveEntity( const uint64_t ID )
	{
		IEntityBase* pIEntity = GetEntity(ID);
		RemoveEntity(pIEntity);
	}

	// 删除所有的子实例
	void CEntityManager::RemoveAllEntity(void)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 移除所有的
		m_listIDEntities.clear();
		m_listFactoryEntities.clear();

		// 遍历所有子目录
		for (VectEntities::iterator itor = m_vecEntities.begin(); \
			m_vecEntities.end() != itor; ++itor)
		{
			// 删除所有的子目录
			VRSOFT_DELETE(*itor);
		}

		// 清除目录
		m_vecEntities.clear();	



		IComManager::GetInstance().WriteLogMsg("成功全部清除");
		// 更新界面
//		IEntityManager::GetInstance().UpdateUI();
	}

	// 获取所有的子集
	const std::vector<IEntityBase*>& CEntityManager::GetAllEntities(void) const
	{
		// 返回
		return (m_vecEntities);
	}

	// 获得模型个数
	int CEntityManager::GetCount( void ) const
	{
		return (m_listIDEntities.size());
	}

	// 通过名称查询实体 找到第一个实现的值直接返回
	IEntityBase* CEntityManager::GetEntity( const uint64_t uID ) const
	{
		// 查询map
		ListIDEntities::const_iterator cstItor = m_listIDEntities.find(uID);
		if (m_listIDEntities.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	// 更新所有的模型
	void CEntityManager::EntityUpdate(const CDateTime& dt)
	{
		// 遍历所有的模型
		VectEntities::iterator itor = m_vecEntities.begin();
		for (; m_vecEntities.end() != itor; ++itor)
		{
			// 更新模型
			(*itor)->EntityUpdate(dt);
		}
	}

	// 获得工厂管理
	IEntityFactoryManager* CEntityManager::GetEntityFactoryManager(void)
	{
		return (&m_entityFactoryManager);
	}

	// 通过组名称来查询对应的实体
	IEntityBase* CEntityManager::CreateEntity(const VRString& strName, const uint64_t ID)
	{
		// 判断创建文件实体是否成功
		IEntityBase* pEntity = CEntityFileManager::GetInstance().CreateEntity(strName, ID);
		if (NULL == pEntity)
		{
			pEntity = CreateEntityByFactory(strName, ID);
		}

		return (pEntity);
	}

	// 初始化
	void CEntityManager::Init( void )
	{
		IEntityBaseFactory* pIEntityBaseFactory = new CEntityBaseBuilderFactory;
		m_entityFactoryManager.RegisterFactory(pIEntityBaseFactory);
	}

	// 移除工厂
	void CEntityManager::RemoveFactory( IEntityBaseFactory* pIEntityBaseFactory )
	{
		ListFactoryEntities::iterator itor = m_listFactoryEntities.find(pIEntityBaseFactory);
		if (m_listFactoryEntities.end() == itor)
		{
			return;
		}

		VectEntityIDs& vecEntities = itor->second;
		for (VectEntityIDs::iterator vecItor = vecEntities.begin(); vecEntities.end() != vecItor; ++vecItor)
		{
			// 移除实体
			RemoveEntity(*vecItor);
		}

		m_listFactoryEntities.erase(itor);
	}

	// 添加观察者
	void CEntityManager::Attach( IEntityManagerUI* pIEntityManagerUI )
	{
		ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.find(pIEntityManagerUI);
		if (m_listEntityManagerUI.end() == cstItor)
		{
			m_listEntityManagerUI.insert(pIEntityManagerUI);
			pIEntityManagerUI->Init(this);
		}
	}

	void CEntityManager::Detach( IEntityManagerUI* pIEntityManagerUI )
	{
		ListEntityManagerUI::iterator itor = m_listEntityManagerUI.find(pIEntityManagerUI);
		if (m_listEntityManagerUI.end() != itor)
		{
			m_listEntityManagerUI.erase(itor);
		}
	}

	// 通过工厂创建系统实体非文件实体
	IEntityBase* CEntityManager::CreateEntityByFactory( const VRString& strName, const uint64_t ID )
	{
		// 获得工厂
		IEntityBaseFactory* pIEntityBaseFactory  = m_entityFactoryManager.GetEntityFactory(strName);
		if (NULL == pIEntityBaseFactory)
		{
			IComManager::GetInstance().WriteLogMsg("工厂对象为空", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBulider* pIEntityBulider = pIEntityBaseFactory->CreateEntityBuilder();
		if (NULL == pIEntityBulider)
		{
			IComManager::GetInstance().WriteLogMsg("对象创建失败", ERROR_MALLOC);
			return (NULL);
		}

		CEntityDirctor entityDirctor(pIEntityBulider);
		IEntityBase* pIEntityObj = entityDirctor.Construct();
		if (NULL == pIEntityObj)
		{
			IComManager::GetInstance().WriteLogMsg("对象创建失败", ERROR_MALLOC);
			return (NULL);
		}

		// 创建UID
		pIEntityObj->SetID(ID);

		// 设置状态机
		IStateMachine* pIStateMachince = new CStateMachine(pIEntityObj);
		pIEntityObj->SetStateMachine(pIStateMachince);
		pIEntityObj->InitStateMachine(pIStateMachince);

		// 进入状态
		IState* pIState = pIStateMachince->GetCurrentState();
		if (NULL != pIState)
		{
			pIState->Enter(pIEntityObj);
		}

		// 添加到实体中
		AddEntity(pIEntityObj);

		// 模型初始化
		pIEntityObj->Init();

		ListFactoryEntities::iterator itor = m_listFactoryEntities.find(pIEntityBaseFactory);
		if (m_listFactoryEntities.end() == itor)
		{
			VectEntityIDs vecEntities;
			vecEntities.push_back(pIEntityObj->GetID());
			m_listFactoryEntities.insert(ListFactoryEntities::value_type(pIEntityBaseFactory, vecEntities));
		}
		else
		{
			VectEntityIDs& vecEntities = itor->second;
			vecEntities.push_back(pIEntityObj->GetID());
		}

		// 添加到
		// 更新已添加实体属性框
		//		CEntitySystem::GetInstance().UpdateUI();

		IComManager::GetInstance().WriteLogMsg("成功创建对象");
		return (pIEntityObj);	
	}

	// 修改实体名称
	void CEntityManager::ChangeEntityName( IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew ) const
	{
		// 更新实体
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateItem(pIEntity, strOld, strNew);
		}
	}

	// 获得类型子集
	std::vector<IEntityBase*> CEntityManager::GetEntities( const VRString& strType ) const
	{
		std::vector<IEntityBase*> listEntityBases;
		for (VectEntities::const_iterator cstItor = m_vecEntities.begin(); \
			m_vecEntities.end() != cstItor; ++cstItor)
		{
			IEntityBase* pIEntityBase = *cstItor;
			//const VRString strType = pIEntityBase->GetEntityType();
			IEntityBaseAttribute* pIEntityBaseAttribute = pIEntityBase->GetBaseAttribute();
			const VRString strEntityType = pIEntityBaseAttribute->GetEntityType();
			if (0 == strEntityType.compare(strType))
			{
				listEntityBases.push_back(pIEntityBase);
			}
		}

		return (listEntityBases);
	}

	// 移除所有的工厂
	void CEntityManager::RemoveAllFactroy( void )
	{
		for (ListFactoryEntities::iterator itor = m_listFactoryEntities.begin(); m_listFactoryEntities.end() != itor; ++itor)
		{
			VectEntityIDs& vecEntities = itor->second;
			for (VectEntityIDs::iterator vecItor = vecEntities.begin(); vecEntities.end() != vecItor; ++vecItor)
			{
				// 移除实体
				RemoveEntity(*vecItor);
			}

//			VRSOFT_DELETE(itor->first);
		}

		m_listFactoryEntities.clear();

	}

}