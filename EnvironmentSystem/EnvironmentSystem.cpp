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
		// ���ʵ�����ʵ��
		IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}

		// ��ӵ�ϵͳ��
		IEntityComponent* pIIEntityComponent =pIEntityManager->GetEntityManagerInstance()->GetEntity("����ϵͳ");

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

		VRSOFT_DELETE(m_pEnvironmentManager);

		// �Ƴ���ϵͳ��
		pIEntityManager->GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// ��ȡ��������
	const VRString& CEnvironmentSystem::GetTypeName(void) const
	{
		return (CEnvironmentManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��������г�ʼ��
	void CEnvironmentSystem::Init(void) 
	{
		// ���ʵ�����ʵ��
		IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}

		// �������
		IEntityComposite* pIEntityComposite = pIEntityManager->CreateEntityComponent("����ϵͳ");
		// ��ӵ�ϵͳ��
		pIEntityManager->GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// ��ù�������ʧ��
			IComManager::GetInstance().WriteLogMsg("��ù���ʧ��", ERROR_NOT_FIND);
			return ;
		}

		m_pEnvironmentManager = new CEnvironmentManager(pIEntityFactoryManager);
		m_pEnvironmentManager->LoadAllElecDll();
	}

	// ���Ĭ��״̬
	IState* CEnvironmentSystem::GetDefultState(void)
	{
		return (NULL);
	}

}
