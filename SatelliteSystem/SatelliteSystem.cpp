
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

		// �Ƴ���ϵͳ��
	//	IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// ��ȡ��������
	const VRString& CSatelliteSystem::GetTypeName(void) const
	{
		return (CSatelliteManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��������г�ʼ��
	void CSatelliteSystem::Init(void) 
	{
		// ���ʵ�����ʵ��
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

	// ���Ĭ��״̬
	IState* CSatelliteSystem::GetDefultState(void)
	{
		return (NULL);
	}

	// �������и���
	ITle* CSatelliteSystem::CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2)
	{
		return (new CSVTle(strName, strLine1, strLine2));
	}

	// ��������
	IEntityBase* CSatelliteSystem::CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID)
	{
		ISatelliteEntity* pITrajectoryEntity = dynamic_cast<ISatelliteEntity*>(IEntityManager::GetInstance().CreateEntity("����", ID));
		pITrajectoryEntity->SetName(strName);

		// �ж��Ƿ�ʧ��
		if (NULL == pITrajectoryEntity)
		{
			return (NULL);
		}

		// ��������
		ITrajectory* pITrajectory = CreateTrajectory(strTrajectory);
		if (NULL == pITrajectory)
		{
		//	pIEntityComp->RemoveEntity(pITrajectoryEntity);
			VRSOFT_DELETE(pITrajectoryEntity);
			return (NULL);
		}

		// ���ò���
		pITrajectoryEntity->SetTrajectory(pITrajectory);
		//���ò���
		pITrajectory->SetTrajectoryEntity(pITrajectoryEntity);

		return (pITrajectoryEntity);
	}

	// �����켣�㷨
	ITrajectory* CSatelliteSystem::CreateTrajectory(const VRString& strTrajectory)
	{
		ITrajectory* pITrajectory = NULL;
		if (0 == strTrajectory.compare("���ǹ��"))
		{
			pITrajectory = new CSatelliteTrajectory;
		}

		return (pITrajectory);
	}

}
