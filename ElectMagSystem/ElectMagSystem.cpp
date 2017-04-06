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
		// ���ʵ�����ʵ��
		IEntityManager* pIEntityManager = IEntityManager::GetInstancePtr();

		// ��ӵ�ϵͳ��
		IEntityComponent* pIIEntityComponent =pIEntityManager->GetEntityManagerInstance()->GetEntity("���ϵͳ");

		// ��ù�������
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIIEntityComponent);
		if (NULL == pIEntityComposite)
		{
			// ��ӵ�ϵͳ��
			pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			return;
		}

		IEntityFactoryManager* pIEntityFactoryManager =  pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// �Ƴ���ϵͳ��
			pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			// ��ù�������ʧ��
			IComManager::GetInstance().WriteLogMsg("��ù���ʧ��", ERROR_NOT_FIND);
			return ;
		}

		VRSOFT_DELETE(m_pElectPluginManager);

		// �Ƴ���ϵͳ��
		pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// ��ʼ��
	void CElectMagSystem::InitSystem(void)
	{
		// ���ʵ�����ʵ��
		IEntityManager* pIEntityManager =  IEntityManager::GetInstancePtr();

		// �������
		IEntityComposite* pIEntityComposite = pIEntityManager->CreateEntityComponent("���ϵͳ");
		// ��ӵ�ϵͳ��
		pIEntityManager->GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// ��ù�������ʧ��
			IComManager::GetInstance().WriteLogMsg("��ù���ʧ��", ERROR_NOT_FIND);
			return ;
		}

		m_pElectPluginManager = new CElectPluginManager(pIEntityFactoryManager);
		m_pElectPluginManager->LoadAllElecDll();
	}

	// ��ȡ��������
	const VRString& CElectMagSystem::GetTypeName(void) const
	{
		return (CElecMagManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��������г�ʼ��
	void CElectMagSystem::Init(void) 
	{
		// ��ʼ��ϵͳ
		InitSystem();
	}

	// ���Ĭ��״̬
	IState* CElectMagSystem::GetDefultState(void)
	{
		return (new CElectMagOnState);
	}
}

