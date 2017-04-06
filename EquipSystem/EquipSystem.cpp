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
		// ���ʵ�����ʵ��
	/*	IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}*/

		// ��ӵ�ϵͳ��
		IEntityComponent* pIIEntityComponent = IEntityManager::GetInstance().GetEntityManagerInstance()->GetEntity("װ��ϵͳ");

		// ��ù�������
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIIEntityComponent);
		if (NULL == pIEntityComposite)
		{
			// ��ӵ�ϵͳ��
			IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			return;
		}

		IEntityFactoryManager* pIEntityFactoryManager =  pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// �Ƴ���ϵͳ��
			IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
			// ��ù�������ʧ��
			IComManager::GetInstance().WriteLogMsg("��ù���ʧ��", ERROR_NOT_FIND);
			return ;
		}

		VRSOFT_DELETE(m_pEquitManager);

		// �Ƴ���ϵͳ��
		IEntityManager::GetInstance().GetEntityManagerInstance()->RemoveEntity(pIIEntityComponent);
	}

	// ��ȡ��������
	const VRString& CEquipSystem::GetTypeName(void) const
	{
		return (CEquipManagerFactory::FACTORY_TYPE_NAME);
	}

	// ��������г�ʼ��
	void CEquipSystem::Init(void) 
	{
		// ���ʵ�����ʵ��
	/*	IEntityManager* pIEntityManager = dynamic_cast<IEntityManager*>(\
			IComInstanceMerator::GetInstance().GetComInstance(INSTANCE_NAME_ENTITYSYSTEM));
		if (NULL == pIEntityManager)
		{
			return;
		}*/

		// ����װ��
		IEntityComposite* pIEntityComposite = IEntityManager::GetInstance().CreateEntityComponent("װ��ϵͳ");
		// ��ӵ�ϵͳ��
		IEntityManager::GetInstance().GetEntityManagerInstance()->AddEntity(pIEntityComposite);
		IEntityFactoryManager* pIEntityFactoryManager = pIEntityComposite->GetEntityFactoryManager();
		if (NULL == pIEntityFactoryManager)
		{
			// ��ù�������ʧ��
			IComManager::GetInstance().WriteLogMsg("��ù���ʧ��", ERROR_NOT_FIND);
			return ;
		}

		m_pEquitManager = new CEquipManager(pIEntityFactoryManager);
		m_pEquitManager->LoadAllElecDll();
	}

	// ���Ĭ��״̬
	IState* CEquipSystem::GetDefultState(void)
	{
		return (NULL);
	}

	// ���װ�����
	CEquipManager* CEquipSystem::GetEquipManager(void) const
	{
		return (m_pEquitManager);
	}

}

