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

	// ��������
	ITrajectoryEntity* CAirLineSystem::CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID)
	{
		/*IEntityComposite* pIEntityComp = VR_Soft::IComManager::GetInstance().GetEntityComposite();
		ITrajectoryEntity* pITrajectoryEntity = dynamic_cast<ITrajectoryEntity*>(pIEntityComp->CreateEntity("����ϵͳ", strName, ID));

		// �ж��Ƿ�ʧ��
		if (NULL == pITrajectoryEntity)
		{
			return (NULL);
		}

		// ��������
		ITrajectory* pITrajectory = CreateTrajectory(strName);
		if (NULL == pITrajectory)
		{
			pIEntityComp->RemoveEntity(pITrajectoryEntity);
			VRSOFT_DELETE(pITrajectoryEntity);
			return (NULL);
		}

		// ���ò���
		pITrajectoryEntity->SetTrajectory(pITrajectory);
		//���ò���
		pITrajectory->SetTrajectoryEntity(pITrajectoryEntity);

		return (pITrajectoryEntity);
		*/
		return (NULL);
	}

	// �����켣�㷨
	ITrajectory* CAirLineSystem::CreateTrajectory(const VRString& strTrajectory)
	{
		ITrajectory* pITrajectory = NULL;
		if (0 == strTrajectory.compare("��������"))
		{
//			pITrajectory = new CBallMissileTraject;
		}
		
		return (pITrajectory);
	}

	//// ע��༭����
	//void CAirLineSystem::RegisterUI(IAirLineUI* pIAirLineUI)
	//{
	////	m_pIAirLineUI = pIAirLineUI;
	//}

	//// ��ע��༭����
	//void CAirLineSystem::UnReginsterUI(void)
	//{
	////	m_pIAirLineUI = NULL;
	//}

	// ��ʼ��
	void CAirLineSystem::InitSystem(void)
	{
		//// ���ʵ�����ʵ��
		//IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
		//	IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		//if (NULL == pIEntityManager)
		//{
		//	return;
		//}

		m_pAirLineManager = new CAirLineManager(IEntityFactoryManager::GetInstancePtr());
		m_pAirLineManager->LoadAllElecDll();
	}

	// ��ȡ��������
	const VRString& CAirLineSystem::GetTypeName(void) const
	{
		return (CAirLineManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��������г�ʼ��
	void CAirLineSystem::Init(void) 
	{
		// ��ʼ��ϵͳ
		InitSystem();

		m_featureGeomtryFactory = new CFeatureGeomtryFactory;
	}

	// ����������ʾ����ͼ��
	IFeatureGeomtry* CAirLineSystem::CreateFeatureGeomtry( OsgEarthGeomtry* pOsgEarthGeomtry )
	{
		return (new CFeatureGeomtry(pOsgEarthGeomtry));
	}

	// ����ͼ�γ��󹤳�
	IFeatureGeomtryFactory* CAirLineSystem::GetFeatureGeomtryFactory( void ) const
	{
		return (m_featureGeomtryFactory);
	}

/*	// ��ÿɱ༭�ĺ���
	IAirLine* CAirLineSystem::GetEidtAirLine(void) const
	{
		//// ���ؿɱ༭�ĺ���
		//if (NULL == m_pEidtAirLine)
		//{
		//	return (m_pEidtAirLine);
		//}

		//// �жϵ�ǰ�Ƿ�ɱ༭�����ɱ༭ֱ�ӷ��ؿ�
		//return (m_pEidtAirLine->EidtState() ? m_pEidtAirLine : NULL);
		return (NULL);
	}

	// �༭���
	void CAirLineSystem::EndEidtAirLine(void) 
	{
		//// �رձ༭
		//m_pEidtAirLine->EnableEidt(false);
		//m_pEidtAirLine = NULL;

		//// ��ע���¼�
		//// ע���¼�
		//IRenderManager* pIRender = IComManager::GetInstance().GetRenderManager();
		//if (NULL == pIRender)
		//{
		//	return;
		//}
		//pIRender->UnRegisterEvnet(m_pIEvent);
	}

	// ��ð󶨺���
	IAirLineBind* CAirLineSystem::GetAirLineBind(void) const
	{
		return (NULL);
	}

	// ���ÿɱ༭�ĺ���
	void CAirLineSystem::SetEditAriLine(IAirLine* pIAirLine)
	{
		//if (NULL == m_pEidtAirLine)
		//{
		//	m_pEidtAirLine = pIAirLine;
		//	// ���ÿɱ༭״̬
		//	m_pEidtAirLine->EnableEidt(true);
		//}
		//else
		//{
		//	// �ȹرձ༭״̬
		//	m_pEidtAirLine->EnableEidt(false);
		//	// �����µı༭״̬
		//	m_pEidtAirLine = pIAirLine;
		//	// ���ÿɱ༭״̬
		//	m_pEidtAirLine->EnableEidt(true);
		//}

		//

		//// ע���¼�
		//IRenderManager* pIRender = IComManager::GetInstance().GetRenderManager();
		//if (NULL == pIRender)
		//{
		//	return;
		//}
		//pIRender->RegisterEvnet(m_pIEvent);
	}
	*/
}

