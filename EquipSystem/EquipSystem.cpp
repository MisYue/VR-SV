#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/EquipSystem/EquipSystem.h"
#include "EquipManager.h"
#include "EquipSystem.h"

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CEquipManagerFactory::FACTORY_TYPE_NAME = EQUIPSYSTEM_TYPENAME;
	/////////////////////////////////////////////// 

	CEquipSystem::CEquipSystem(const VRString& strName)
	{
		SetName(strName);
	}


	CEquipSystem::~CEquipSystem(void)
	{
		// 获得实体管理实体
	/*	IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}*/

		// 添加到系统中
		IEntityComponent* pIIEntityComponent = IEntityManager::GetInstance().GetEntityManagerInstance()->GetEntity("装备系统");

		// 获得工厂管理
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIIEntityComponent);
		if (NULL == pIEntityComposite)
		{
			// 添加到系统中
			IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			return;
		}

		IEntityFactoryManager* pIEntityFactoryManager =  pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// 移除到系统中
			IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			// 获得工厂管理失败
			IComManager::GetInstance().WriteLogMsg("获得工厂失败", ERROR_NOT_FIND);
			return ;
		}

		VRSOFT_DELETE(m_pEquitManager);

		// 移除到系统中
		IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// 获取类型名称
	const VRString& CEquipSystem::GetTypeName(void) const
	{
		return (CEquipManagerFactory::FACTORY_TYPE_NAME);
	}

	// 对组件进行初始化
	void CEquipSystem::Init(void) 
	{
		// 获得实体管理实体
	/*	IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}*/

		// 创建装备
		IEntityComposite* pIEntityComposite = IEntityManager::GetInstance().CreateEntityComponent("装备系统");
		// 添加到系统中
		IEntityManager::GetInstance().GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// 获得工厂管理失败
			IComManager::GetInstance().WriteLogMsg("获得工厂失败", ERROR_NOT_FIND);
			return ;
		}

		m_pEquitManager = new CEquipManager(pIEntityFactoryManager);
		m_pEquitManager->LoadAllElecDll();
	}

	// 获得默认状态
	IState* CEquipSystem::GetDefultState(void)
	{
		return (NULL);
	}

	// 获得装备插件
	CEquipManager* CEquipSystem::GetEquipManager(void) const
	{
		return (m_pEquitManager);
	}

}

