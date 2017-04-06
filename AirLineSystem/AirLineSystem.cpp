#define VRSOFT_PLUGIN_EXPORT

#include <iostream>
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "AirLineManager.h"
#include "AirLineSystem.h"
#include "BallMissileTraject.h"
#include "FeatureGeomtry.h"
#include "FeatureGeomtryFactory.h"

#ifdef _DEBUG
#pragma comment (lib, "osgd.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")
#pragma comment(lib, "osgEarthFeaturesd.lib")

#else

#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#pragma comment(lib, "osgEarthFeatures.lib")
#endif

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CAirLineManagerFactory::FACTORY_TYPE_NAME = AIRLINESYSTEM_TYPENAME;
	/////////////////////////////////////////////// 

	CAirLineSystem::CAirLineSystem(const VRString& strName)
		:m_pAirLineManager(NULL),m_featureGeomtryFactory(NULL)
	{
		SetName(strName);
	}

	CAirLineSystem::~CAirLineSystem(void)
	{
		VRSOFT_DELETE(m_featureGeomtryFactory);
		VRSOFT_DELETE(m_pAirLineManager);
	}

	// 创建弹道
	ITrajectoryEntity* CAirLineSystem::CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID)
	{
		/*IEntityComposite* pIEntityComp = VR_Soft::IComManager::GetInstance().GetEntityComposite();
		ITrajectoryEntity* pITrajectoryEntity = dynamic_cast<ITrajectoryEntity*>(pIEntityComp->CreateEntity("航线系统", strName, ID));

		// 判断是否失败
		if (NULL == pITrajectoryEntity)
		{
			return (NULL);
		}

		// 创建策略
		ITrajectory* pITrajectory = CreateTrajectory(strName);
		if (NULL == pITrajectory)
		{
			pIEntityComp->RemoveEntity(pITrajectoryEntity);
			VRSOFT_DELETE(pITrajectoryEntity);
			return (NULL);
		}

		// 设置策略
		pITrajectoryEntity->SetTrajectory(pITrajectory);
		//设置策略
		pITrajectory->SetTrajectoryEntity(pITrajectoryEntity);

		return (pITrajectoryEntity);
		*/
		return (NULL);
	}

	// 创建轨迹算法
	ITrajectory* CAirLineSystem::CreateTrajectory(const VRString& strTrajectory)
	{
		ITrajectory* pITrajectory = NULL;
		if (0 == strTrajectory.compare("弹道导弹"))
		{
//			pITrajectory = new CBallMissileTraject;
		}
		
		return (pITrajectory);
	}

	//// 注册编辑界面
	//void CAirLineSystem::RegisterUI(IAirLineUI* pIAirLineUI)
	//{
	////	m_pIAirLineUI = pIAirLineUI;
	//}

	//// 反注册编辑界面
	//void CAirLineSystem::UnReginsterUI(void)
	//{
	////	m_pIAirLineUI = NULL;
	//}

	// 初始化
	void CAirLineSystem::InitSystem(void)
	{
		//// 获得实体管理实体
		//IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
		//	IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		//if (NULL == pIEntityManager)
		//{
		//	return;
		//}

		m_pAirLineManager = new CAirLineManager(IEntityFactoryManager::GetInstancePtr());
		m_pAirLineManager->LoadAllElecDll();
	}

	// 获取类型名称
	const VRString& CAirLineSystem::GetTypeName(void) const
	{
		return (CAirLineManagerFactory::FACTORY_TYPE_NAME);
	}

	// 对组件进行初始化
	void CAirLineSystem::Init(void) 
	{
		// 初始化系统
		InitSystem();

		m_featureGeomtryFactory = new CFeatureGeomtryFactory;
	}

	// 创建地球显示几何图形
	IFeatureGeomtry* CAirLineSystem::CreateFeatureGeomtry( OsgEarthGeomtry* pOsgEarthGeomtry )
	{
		return (new CFeatureGeomtry(pOsgEarthGeomtry));
	}

	// 几何图形抽象工厂
	IFeatureGeomtryFactory* CAirLineSystem::GetFeatureGeomtryFactory( void ) const
	{
		return (m_featureGeomtryFactory);
	}

/*	// 获得可编辑的航线
	IAirLine* CAirLineSystem::GetEidtAirLine(void) const
	{
		//// 返回可编辑的航线
		//if (NULL == m_pEidtAirLine)
		//{
		//	return (m_pEidtAirLine);
		//}

		//// 判断当前是否可编辑，不可编辑直接返回空
		//return (m_pEidtAirLine->EidtState() ? m_pEidtAirLine : NULL);
		return (NULL);
	}

	// 编辑完毕
	void CAirLineSystem::EndEidtAirLine(void) 
	{
		//// 关闭编辑
		//m_pEidtAirLine->EnableEidt(false);
		//m_pEidtAirLine = NULL;

		//// 反注册事件
		//// 注册事件
		//IRenderManager* pIRender = IComManager::GetInstance().GetRenderManager();
		//if (NULL == pIRender)
		//{
		//	return;
		//}
		//pIRender->UnRegisterEvnet(m_pIEvent);
	}

	// 获得绑定航线
	IAirLineBind* CAirLineSystem::GetAirLineBind(void) const
	{
		return (NULL);
	}

	// 设置可编辑的航线
	void CAirLineSystem::SetEditAriLine(IAirLine* pIAirLine)
	{
		//if (NULL == m_pEidtAirLine)
		//{
		//	m_pEidtAirLine = pIAirLine;
		//	// 设置可编辑状态
		//	m_pEidtAirLine->EnableEidt(true);
		//}
		//else
		//{
		//	// 先关闭编辑状态
		//	m_pEidtAirLine->EnableEidt(false);
		//	// 设置新的编辑状态
		//	m_pEidtAirLine = pIAirLine;
		//	// 设置可编辑状态
		//	m_pEidtAirLine->EnableEidt(true);
		//}

		//

		//// 注册事件
		//IRenderManager* pIRender = IComManager::GetInstance().GetRenderManager();
		//if (NULL == pIRender)
		//{
		//	return;
		//}
		//pIRender->RegisterEvnet(m_pIEvent);
	}
	*/
}

