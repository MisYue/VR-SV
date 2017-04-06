#define VRSOFT_PLUGIN_EXPORT
#include <list>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/EntitySystem/IEntityComponent.h"
#include "EntitySystem.h"
#include "EntityFactoryManager.h"
#include "StateMachine.h"
//#include "GlobalState.h"
#include "EntityID.h"
#include "EntityManager.h"


namespace VR_Soft
{
	CEntityManager::CEntityManager(const VRString& strComponentName)
	{
		SetName(strComponentName);
	}

	CEntityManager::~CEntityManager(void)
	{
	}

	// 获得实体模型
	IEntityComponent* CEntityManager::GetEntity(const VRString& strEntityID) const
	{
		// 线程安全
		VR_MUTEX_AUTO;

		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(strEntityID);
		return (cstItor->second);
	}

	// 添加视图模型
	void CEntityManager::AddEntity(IEntityComponent* pIEntity)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 当前是否已经存在
		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(pIEntity->GetName());
		if (m_mapStrEntity.end() != cstItor)
		{
			// 已经被加载过程
			IComManager::GetInstance().WriteLogMsg("实体：" + pIEntity->GetName() + "已经被加载过");
			return;
		}

		// 判断路径是否为空
		VRString strPath = GetPath();
		if (strPath.empty())
		{
			// 根目录 设置路径
			SetPath(GetName());
		}
		
		// 判断该目录是否添加过
		if (-1 != strPath.find(pIEntity->GetName() + "."))
		{
			// 已经被加载过程
			IComManager::GetInstance().WriteLogMsg("实体：" + pIEntity->GetName() + "已经被加载过");
			return;
		}
		else if (-1 == strPath.find("." + pIEntity->GetName()))
		{
			// 可以正常加载

			// 获得路径
			const VRString strChildPath = GetPath() + "." + pIEntity->GetName();
			// 设置子模型路径
			pIEntity->SetPath(strChildPath);
			m_mapStrEntity[pIEntity->GetName()] = pIEntity;
			pIEntity->SetParentEntity(this);

			// 已经被加载过程
			IComManager::GetInstance().WriteLogMsg("实体：" + pIEntity->GetName() + "加载成功");

			// 更新界面
			IEntityManager::GetInstance().UpdateUI();
		}
		else
		{
			// 已经被加载过程
			IComManager::GetInstance().WriteLogMsg("实体：" + pIEntity->GetName() + "已经被加载过");
		}
	}

	// 移除对象
	void CEntityManager::RemoveEntity(IEntityComponent* pIEntity)
	{
		VR_MUTEX_AUTO
		// 过程存在子实体 则将所有实体直接删除
		// 在当前中查找是否存在
		const VRString strName = pIEntity->GetName();

		MapStrEntity::iterator itor = m_mapStrEntity.find(strName);
		if (m_mapStrEntity.end() != itor)
		{
			IEntityComposite* pIComposite = dynamic_cast<IEntityComposite*>(pIEntity);
			if (NULL != pIComposite)
			{
				// 删除子目录
				pIComposite->RemoveAllEntity();
			}

			// 删除实体对象
			VRSOFT_DELETE (pIEntity);
			// 从父节点中删除
			m_mapStrEntity.erase(itor);
			
		}

		IComManager::GetInstance().WriteLogMsg("成功清除：" + strName);

		// 更新界面
		IEntityManager::GetInstance().UpdateUI();
	}

	// 移除对象 （不删除实际对象， 用于修改名称而已）
	void CEntityManager::RemoveEntity(const VRString& strName)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 过程存在子实体 则将所有实体直接删除
		// 在当前中查找是否存在
		MapStrEntity::iterator itor = m_mapStrEntity.find(strName);
		m_mapStrEntity.erase(itor);
	}

	// 删除所有的子实例
	void CEntityManager::RemoveAllEntity(void)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 遍历所有子目录
		for (MapStrEntity::iterator itor = m_mapStrEntity.begin(); \
			m_mapStrEntity.end() != itor; ++itor)
		{
			// 删除所有的子目录
			IEntityComposite* pIComposite = dynamic_cast<IEntityComposite*>(itor->second);
			if (NULL != pIComposite)
			{
				// 删除子目录
				pIComposite->RemoveAllEntity();
			}
			VRSOFT_DELETE(itor->second);
		}

		// 清除目录
		m_mapStrEntity.clear();	

		IComManager::GetInstance().WriteLogMsg("成功清除：" + GetName());
		// 更新界面
		IEntityManager::GetInstance().UpdateUI();
	}

	// 改变实体模型名称方便进行查找
	bool CEntityManager::ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName)
	{
		// 线程安全
		VR_MUTEX_AUTO;

		// 查询当前模型是否存在于当前的集合中
		MapStrEntity::iterator itor = m_mapStrEntity.find(pIEntity->GetName());
		if ( m_mapStrEntity.end() != itor)
		{
			m_mapStrEntity.erase(itor);
			m_mapStrEntity[strNewName] = pIEntity;
			return (true);
		}

		// 查询其以下的模型
		itor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != itor; ++itor)
		{
			IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(itor->second);
			if (NULL == pIEntityComposite)
			{
				continue;
			}

			const bool bChangeed = pIEntityComposite->ChangeEntityName(pIEntity, strNewName);
			if (bChangeed)
			{
				// 找到返回真
				return (true);
			}
		}

		return (false);

	}

	// 获取所有的子集
	const IEntityComposite::LstEntitys CEntityManager::GetLstEntitys(void) const
	{
		// 线程安全
		VR_MUTEX_AUTO;

		LstEntitys lstEntitys;

		// 循环遍历
		for (MapStrEntity::const_iterator cstItor = m_mapStrEntity.begin(); \
			m_mapStrEntity.end() != cstItor; ++cstItor)
		{
			lstEntitys.push_back(cstItor->second);
		}

		// 返回
		return (lstEntitys);
	}


	// 通过名称查询实体 找到第一个实现的值直接返回
	IEntityComponent* CEntityManager::GetEntity(const VRString& strName)
	{
		// 判断是否在当前的项中
		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(strName);
		if (m_mapStrEntity.end() != cstItor)
		{
			return (cstItor->second);;
		}

		// 遍历名称
		cstItor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != cstItor; ++cstItor)
		{
			IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(cstItor->second);
			if (NULL == pIEntityComposite)
			{
				continue;
			}
			

			// 查询子目录
			IEntityComponent* pIComPonent = pIEntityComposite->GetEntity(strName);
			if (NULL != pIComPonent)
			{
				return (pIComPonent);
			}
		}
		return (NULL);
	}

	// 通过组名称来查询对应的实体
	IEntityComponent* CEntityManager::GetEntity(const VRString& strCompName, const VRString& strType)
	{
		// 查询第一个是否存在
		IEntityComponent* pIEntityComonent = GetEntity(strCompName);
		if (NULL == pIEntityComonent)
		{
			return (NULL);
		}

		return (GetEntity(pIEntityComonent, strType));
	}

	// 通过组类型获得对应的实体
	IEntityComponent* CEntityManager::GetEntity(IEntityComponent* pIComponent, const VRString& strType)
	{
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIComponent);
		if (NULL == pIEntityComposite)
		{
			// 写入日志系统
			IComManager::GetInstance().WriteLogMsg("模型转换失败", ERROR_FAILE_CONVERT);
			return (NULL);
		}
		// 调用实例对象直接查找
		
		return (pIEntityComposite->GetEntity(strType));
	}

	// 更新所有的模型
	void CEntityManager::EntityUpdate(double dt)
	{
		// 遍历所有的模型
		MapStrEntity::iterator itor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != itor; ++itor)
		{
			// 更新模型
			itor->second->EntityUpdate(dt);
		}
	}

	// 获得工厂管理
	IEntityFactoryManager* CEntityManager::GetEntityFactoryManager(void)
	{
		return (&m_entityFactoryManager);
	}

	// 通过组名称来创建对应的实体
	IEntityComponent* CEntityManager::CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID)
	{
		// 查询第一个是否存在
		IEntityComponent* pIEntityComonent = GetEntity(strCompName);
		if (NULL == pIEntityComonent)
		{
			return (NULL);
		}

		// 通过组件是否含有当前的名称
		return (CreateEntity(pIEntityComonent, strType, ID));
	}

	// 通过组名称来查询对应的实体
	IEntityComponent* CEntityManager::CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID)
	{
		// 判断组合是否可以展开
		IEntityComposite* pIEntiyComposite = dynamic_cast<IEntityComposite*>(pIComponent);
		if (NULL == pIEntiyComposite && !pIEntiyComposite->IsExport())
		{
			IComManager::GetInstance().WriteLogMsg("当前实体不能添加子实体或者当前实体为空", ERROR_NOT_ADD);
			return (NULL);
		}

		// 获得工厂
		IEntityFactoryManager* pIEntiryFactoryManager = pIEntiyComposite->GetEntityFactoryManager();
		if ( NULL == pIEntiryFactoryManager )
		{
			IComManager::GetInstance().WriteLogMsg("当前工厂管理对象为空", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBaseFactory* pIEntityBaseFactory  = pIEntiryFactoryManager->GetEntityFactory(strType);
		if (NULL == pIEntityBaseFactory)
		{
			IComManager::GetInstance().WriteLogMsg("工厂对象为空", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBase* pIEntityObj = pIEntityBaseFactory->CreateEntityInstance();
		if (NULL == pIEntityObj)
		{
			IComManager::GetInstance().WriteLogMsg("对象创建失败", ERROR_MALLOC);
			return (NULL);
		}

		// 创建属性
		IAttribute* pIAttribute = pIEntityObj->CreateAttribute();
		// 设置属性
		pIEntityObj->SetAttribute(pIAttribute);
		// 初始化属性
		pIAttribute->Init();

		// 设置名称
		pIEntityObj->SetName(pIEntityBaseFactory->GetEntityBaseName());

		// 创建UID
		CEntityID* pEntityID = new CEntityID(pIEntityObj, ID);
		pIEntityObj->SetID(pEntityID);

		// 设置状态机
		IStateMachine* pIStateMachince = new CStateMachine(pIEntityObj);
		((CEntityBaseImp<IEntityBase>*)pIEntityObj)->SetStateMachine(pIStateMachince);
		pIEntityObj->InitStateMachine(pIStateMachince);

		// 进入状态
		IState* pIState = pIStateMachince->GetCurrentState();
		if (NULL != pIState)
		{
			pIState->Enter(pIEntityObj);
		}
		// 设置全局状态
		//pIStateMachince->SetGlobalState(new CGlobalState);
		
		// 添加到实体中
		pIEntiyComposite->AddEntity(pIEntityObj);

		// 保存属性到卡中
		pIAttribute->WriteMemory();

		// 模型初始化
		pIEntityObj->Init();

		// 更新当前的属性框
		CEntitySystem::GetInstance().GetAttributeManagerInstance()->SetCurrentEntityBase(pIEntityObj);
		// 更新已添加实体属性框
		CEntitySystem::GetInstance().UpdateUI();

		IComManager::GetInstance().WriteLogMsg("成功创建对象");
		return (pIEntityObj);	
	}
}

