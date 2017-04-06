#define VRSOFT_PLUGIN_EXPORT
#include "../../Public/EnvironmentSystem/EnvironmentSystem.h"
#include "EnvironmentManager.h"
#include "EnvironmentSystem.h"

namespace VR_Soft
{

	///////////////////////////////////////////////
	const VRString CEnvironmentManagerFactory::FACTORY_TYPE_NAME = ENVIRONEMNTSYSTEM_TYPENAME;
	/////////////////////////////////////////////// 

	CEnvironmentSystem::CEnvironmentSystem(const VRString& strName)
		:m_pEnvironmentManager(NULL)
	{
		SetName(strName);
	}


	CEnvironmentSystem::~CEnvironmentSystem(void)
	{
		// 获得实体管理实体
		IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}

		// 添加到系统中
		IEntityComponent* pIIEntityComponent =pIEntityManager->GetEntityManagerInstance()->GetEntity("环境系统");

		// 获得工厂管理
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIIEntityComponent);
		if (NULL == pIEntityComposite)
		{
			// 添加到系统中
			pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			return;
		}

		IEntityFactoryManager* pIEntityFactoryManager =  pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// 移除到系统中
			pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			// 获得工厂管理失败
			IComManager::GetInstance().WriteLogMsg("获得工厂失败", ERROR_NOT_FIND);
			return ;
		}

		VRSOFT_DELETE(m_pEnvironmentManager);

		// 移除到系统中
		pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// 获取类型名称
	const VRString& CEnvironmentSystem::GetTypeName(void) const
	{
		return (CEnvironmentManagerFactory::FACTORY_TYPE_NAME);
	}

	// 对组件进行初始化
	void CEnvironmentSystem::Init(void) 
	{
		// 获得实体管理实体
		IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}

		// 创建电磁
		IEntityComposite* pIEntityComposite = pIEntityManager->CreateEntityComponent("环境系统");
		// 添加到系统中
		pIEntityManager->GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// 获得工厂管理失败
			IComManager::GetInstance().WriteLogMsg("获得工厂失败", ERROR_NOT_FIND);
			return ;
		}

		m_pEnvironmentManager = new CEnvironmentManager(pIEntityFactoryManager);
		m_pEnvironmentManager->LoadAllElecDll();
	}

	// 获得默认状态
	IState* CEnvironmentSystem::GetDefultState(void)
	{
		return (NULL);
	}

}
