
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteManager.h"
#include "SatelliteSystem.h"
#include "SVTle.h"
#include "SatelliteEntity.h"
#include "SatelliteTrajectory.h"


#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")


#else

#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#pragma comment(lib, "EntitySystem.lib")

#endif

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CSatelliteManagerFactory::FACTORY_TYPE_NAME = SATELLITESYSTEM_TYPENAME;
	/////////////////////////////////////////////// 

	CSatelliteSystem::CSatelliteSystem(const VRString& strName)
		:m_pSatelliteManager(NULL)
	{
		SetName(strName);
	}


	CSatelliteSystem::~CSatelliteSystem(void)
	{
	
		VRSOFT_DELETE(m_pSatelliteManager);

		// 移除到系统中
	//	IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// 获取类型名称
	const VRString& CSatelliteSystem::GetTypeName(void) const
	{
		return (CSatelliteManagerFactory::FACTORY_TYPE_NAME);
	}

	// 对组件进行初始化
	void CSatelliteSystem::Init(void) 
	{
		// 获得实体管理实体
	/*	IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}
*/
		m_pSatelliteManager = new CSatelliteManager;
		m_pSatelliteManager->LoadAllElecDll();
	}

	// 获得默认状态
	IState* CSatelliteSystem::GetDefultState(void)
	{
		return (NULL);
	}

	// 创建两行根数
	ITle* CSatelliteSystem::CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2)
	{
		return (new CSVTle(strName, strLine1, strLine2));
	}

	// 创建弹道
	IEntityBase* CSatelliteSystem::CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID)
	{
		ISatelliteEntity* pITrajectoryEntity = dynamic_cast<ISatelliteEntity*>(IEntityManager::GetInstance().CreateEntity("卫星", ID));
		pITrajectoryEntity->SetName(strName);

		// 判断是否失败
		if (NULL == pITrajectoryEntity)
		{
			return (NULL);
		}

		// 创建策略
		ITrajectory* pITrajectory = CreateTrajectory(strTrajectory);
		if (NULL == pITrajectory)
		{
		//	pIEntityComp->RemoveEntity(pITrajectoryEntity);
			VRSOFT_DELETE(pITrajectoryEntity);
			return (NULL);
		}

		// 设置策略
		pITrajectoryEntity->SetTrajectory(pITrajectory);
		//设置策略
		pITrajectory->SetTrajectoryEntity(pITrajectoryEntity);

		return (pITrajectoryEntity);
	}

	// 创建轨迹算法
	ITrajectory* CSatelliteSystem::CreateTrajectory(const VRString& strTrajectory)
	{
		ITrajectory* pITrajectory = NULL;
		if (0 == strTrajectory.compare("卫星轨道"))
		{
			pITrajectory = new CSatelliteTrajectory;
		}

		return (pITrajectory);
	}

}
