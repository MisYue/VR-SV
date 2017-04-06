#define ELECTMAG_PLUGIN_EXPOT
#include "../../Public/ElectMagSystem/ElectMagSystem.h"
#include "ElectPluginManager.h"
#include "ElectMagState.h"
#include "ElectMagSystem.h"

#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgFXd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgSimd.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthSymbologyd.lib")
#pragma comment(lib, "osgEarthAnnotationd.lib")
#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgFX.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgSim.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthSymbology.lib")
#pragma comment(lib, "osgEarthAnnotation.lib")
#endif

namespace VR_Soft
{
	///////////////////////////////////////////////
	const VRString CElecMagManagerFactory::FACTORY_TYPE_NAME = ELECMAGSYSTEM_TYPENAME;
	/////////////////////////////////////////////// 

	CElectMagSystem::CElectMagSystem(const VRString& strName):m_pElectPluginManager(NULL)
	{
		SetName(strName);
	}

	CElectMagSystem::~CElectMagSystem()
	{
		// 获得实体管理实体
		IEntityManager* pIEntityManager = IEntityManager::GetInstancePtr();

		// 添加到系统中
		IEntityComponent* pIIEntityComponent =pIEntityManager->GetEntityManagerInstance()->GetEntity("电磁系统");

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

		VRSOFT_DELETE(m_pElectPluginManager);

		// 移除到系统中
		pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// 初始化
	void CElectMagSystem::InitSystem(void)
	{
		// 获得实体管理实体
		IEntityManager* pIEntityManager =  IEntityManager::GetInstancePtr();

		// 创建电磁
		IEntityComposite* pIEntityComposite = pIEntityManager->CreateEntityComponent("电磁系统");
		// 添加到系统中
		pIEntityManager->GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// 获得工厂管理失败
			IComManager::GetInstance().WriteLogMsg("获得工厂失败", ERROR_NOT_FIND);
			return ;
		}

		m_pElectPluginManager = new CElectPluginManager(pIEntityFactoryManager);
		m_pElectPluginManager->LoadAllElecDll();
	}

	// 获取类型名称
	const VRString& CElectMagSystem::GetTypeName(void) const
	{
		return (CElecMagManagerFactory::FACTORY_TYPE_NAME);
	}

	// 对组件进行初始化
	void CElectMagSystem::Init(void) 
	{
		// 初始化系统
		InitSystem();
	}

	// 获得默认状态
	IState* CElectMagSystem::GetDefultState(void)
	{
		return (new CElectMagOnState);
	}
}

