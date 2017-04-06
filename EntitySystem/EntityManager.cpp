#define VRSOFT_PLUGIN_EXPORT
#include <list>
#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "../../Public/EntitySystem/IEntityComponent.h"
#include "EntitySystem.h"
#include "EntityFactoryManager.h"
#include "StateMachine.h"
//#include "GlobalState.h"
#include "EntityID.h"
#include "EntityManager.h"


namespace VR_Soft
{
	CEntityManager::CEntityManager(const VRString& strComponentName)
	{
		SetName(strComponentName);
	}

	CEntityManager::~CEntityManager(void)
	{
	}

	// ���ʵ��ģ��
	IEntityComponent* CEntityManager::GetEntity(const VRString& strEntityID) const
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(strEntityID);
		return (cstItor->second);
	}

	// �����ͼģ��
	void CEntityManager::AddEntity(IEntityComponent* pIEntity)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ��ǰ�Ƿ��Ѿ�����
		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(pIEntity->GetName());
		if (m_mapStrEntity.end() != cstItor)
		{
			// �Ѿ������ع���
			IComManager::GetInstance().WriteLogMsg("ʵ�壺" + pIEntity->GetName() + "�Ѿ������ع�");
			return;
		}

		// �ж�·���Ƿ�Ϊ��
		VRString strPath = GetPath();
		if (strPath.empty())
		{
			// ��Ŀ¼ ����·��
			SetPath(GetName());
		}
		
		// �жϸ�Ŀ¼�Ƿ���ӹ�
		if (-1 != strPath.find(pIEntity->GetName() + "."))
		{
			// �Ѿ������ع���
			IComManager::GetInstance().WriteLogMsg("ʵ�壺" + pIEntity->GetName() + "�Ѿ������ع�");
			return;
		}
		else if (-1 == strPath.find("." + pIEntity->GetName()))
		{
			// ������������

			// ���·��
			const VRString strChildPath = GetPath() + "." + pIEntity->GetName();
			// ������ģ��·��
			pIEntity->SetPath(strChildPath);
			m_mapStrEntity[pIEntity->GetName()] = pIEntity;
			pIEntity->SetParentEntity(this);

			// �Ѿ������ع���
			IComManager::GetInstance().WriteLogMsg("ʵ�壺" + pIEntity->GetName() + "���سɹ�");

			// ���½���
			IEntityManager::GetInstance().UpdateUI();
		}
		else
		{
			// �Ѿ������ع���
			IComManager::GetInstance().WriteLogMsg("ʵ�壺" + pIEntity->GetName() + "�Ѿ������ع�");
		}
	}

	// �Ƴ�����
	void CEntityManager::RemoveEntity(IEntityComponent* pIEntity)
	{
		VR_MUTEX_AUTO
		// ���̴�����ʵ�� ������ʵ��ֱ��ɾ��
		// �ڵ�ǰ�в����Ƿ����
		const VRString strName = pIEntity->GetName();

		MapStrEntity::iterator itor = m_mapStrEntity.find(strName);
		if (m_mapStrEntity.end() != itor)
		{
			IEntityComposite* pIComposite = dynamic_cast<IEntityComposite*>(pIEntity);
			if (NULL != pIComposite)
			{
				// ɾ����Ŀ¼
				pIComposite->RemoveAllEntity();
			}

			// ɾ��ʵ�����
			VRSOFT_DELETE (pIEntity);
			// �Ӹ��ڵ���ɾ��
			m_mapStrEntity.erase(itor);
			
		}

		IComManager::GetInstance().WriteLogMsg("�ɹ������" + strName);

		// ���½���
		IEntityManager::GetInstance().UpdateUI();
	}

	// �Ƴ����� ����ɾ��ʵ�ʶ��� �����޸����ƶ��ѣ�
	void CEntityManager::RemoveEntity(const VRString& strName)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ���̴�����ʵ�� ������ʵ��ֱ��ɾ��
		// �ڵ�ǰ�в����Ƿ����
		MapStrEntity::iterator itor = m_mapStrEntity.find(strName);
		m_mapStrEntity.erase(itor);
	}

	// ɾ�����е���ʵ��
	void CEntityManager::RemoveAllEntity(void)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ����������Ŀ¼
		for (MapStrEntity::iterator itor = m_mapStrEntity.begin(); \
			m_mapStrEntity.end() != itor; ++itor)
		{
			// ɾ�����е���Ŀ¼
			IEntityComposite* pIComposite = dynamic_cast<IEntityComposite*>(itor->second);
			if (NULL != pIComposite)
			{
				// ɾ����Ŀ¼
				pIComposite->RemoveAllEntity();
			}
			VRSOFT_DELETE(itor->second);
		}

		// ���Ŀ¼
		m_mapStrEntity.clear();	

		IComManager::GetInstance().WriteLogMsg("�ɹ������" + GetName());
		// ���½���
		IEntityManager::GetInstance().UpdateUI();
	}

	// �ı�ʵ��ģ�����Ʒ�����в���
	bool CEntityManager::ChangeEntityName(IEntityComponent* pIEntity, const VRString& strNewName)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ��ѯ��ǰģ���Ƿ�����ڵ�ǰ�ļ�����
		MapStrEntity::iterator itor = m_mapStrEntity.find(pIEntity->GetName());
		if ( m_mapStrEntity.end() != itor)
		{
			m_mapStrEntity.erase(itor);
			m_mapStrEntity[strNewName] = pIEntity;
			return (true);
		}

		// ��ѯ�����µ�ģ��
		itor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != itor; ++itor)
		{
			IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(itor->second);
			if (NULL == pIEntityComposite)
			{
				continue;
			}

			const bool bChangeed = pIEntityComposite->ChangeEntityName(pIEntity, strNewName);
			if (bChangeed)
			{
				// �ҵ�������
				return (true);
			}
		}

		return (false);

	}

	// ��ȡ���е��Ӽ�
	const IEntityComposite::LstEntitys CEntityManager::GetLstEntitys(void) const
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		LstEntitys lstEntitys;

		// ѭ������
		for (MapStrEntity::const_iterator cstItor = m_mapStrEntity.begin(); \
			m_mapStrEntity.end() != cstItor; ++cstItor)
		{
			lstEntitys.push_back(cstItor->second);
		}

		// ����
		return (lstEntitys);
	}


	// ͨ�����Ʋ�ѯʵ�� �ҵ���һ��ʵ�ֵ�ֱֵ�ӷ���
	IEntityComponent* CEntityManager::GetEntity(const VRString& strName)
	{
		// �ж��Ƿ��ڵ�ǰ������
		MapStrEntity::const_iterator cstItor = m_mapStrEntity.find(strName);
		if (m_mapStrEntity.end() != cstItor)
		{
			return (cstItor->second);;
		}

		// ��������
		cstItor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != cstItor; ++cstItor)
		{
			IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(cstItor->second);
			if (NULL == pIEntityComposite)
			{
				continue;
			}
			

			// ��ѯ��Ŀ¼
			IEntityComponent* pIComPonent = pIEntityComposite->GetEntity(strName);
			if (NULL != pIComPonent)
			{
				return (pIComPonent);
			}
		}
		return (NULL);
	}

	// ͨ������������ѯ��Ӧ��ʵ��
	IEntityComponent* CEntityManager::GetEntity(const VRString& strCompName, const VRString& strType)
	{
		// ��ѯ��һ���Ƿ����
		IEntityComponent* pIEntityComonent = GetEntity(strCompName);
		if (NULL == pIEntityComonent)
		{
			return (NULL);
		}

		return (GetEntity(pIEntityComonent, strType));
	}

	// ͨ�������ͻ�ö�Ӧ��ʵ��
	IEntityComponent* CEntityManager::GetEntity(IEntityComponent* pIComponent, const VRString& strType)
	{
		IEntityComposite* pIEntityComposite = dynamic_cast<IEntityComposite*>(pIComponent);
		if (NULL == pIEntityComposite)
		{
			// д����־ϵͳ
			IComManager::GetInstance().WriteLogMsg("ģ��ת��ʧ��", ERROR_FAILE_CONVERT);
			return (NULL);
		}
		// ����ʵ������ֱ�Ӳ���
		
		return (pIEntityComposite->GetEntity(strType));
	}

	// �������е�ģ��
	void CEntityManager::EntityUpdate(double dt)
	{
		// �������е�ģ��
		MapStrEntity::iterator itor = m_mapStrEntity.begin();
		for (; m_mapStrEntity.end() != itor; ++itor)
		{
			// ����ģ��
			itor->second->EntityUpdate(dt);
		}
	}

	// ��ù�������
	IEntityFactoryManager* CEntityManager::GetEntityFactoryManager(void)
	{
		return (&m_entityFactoryManager);
	}

	// ͨ����������������Ӧ��ʵ��
	IEntityComponent* CEntityManager::CreateEntity(const VRString& strCompName, const VRString& strType, const uint64_t ID)
	{
		// ��ѯ��һ���Ƿ����
		IEntityComponent* pIEntityComonent = GetEntity(strCompName);
		if (NULL == pIEntityComonent)
		{
			return (NULL);
		}

		// ͨ������Ƿ��е�ǰ������
		return (CreateEntity(pIEntityComonent, strType, ID));
	}

	// ͨ������������ѯ��Ӧ��ʵ��
	IEntityComponent* CEntityManager::CreateEntity(IEntityComponent* pIComponent, const VRString& strType, const uint64_t ID)
	{
		// �ж�����Ƿ����չ��
		IEntityComposite* pIEntiyComposite = dynamic_cast<IEntityComposite*>(pIComponent);
		if (NULL == pIEntiyComposite && !pIEntiyComposite->IsExport())
		{
			IComManager::GetInstance().WriteLogMsg("��ǰʵ�岻�������ʵ����ߵ�ǰʵ��Ϊ��", ERROR_NOT_ADD);
			return (NULL);
		}

		// ��ù���
		IEntityFactoryManager* pIEntiryFactoryManager = pIEntiyComposite->GetEntityFactoryManager();
		if ( NULL == pIEntiryFactoryManager )
		{
			IComManager::GetInstance().WriteLogMsg("��ǰ�����������Ϊ��", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBaseFactory* pIEntityBaseFactory  = pIEntiryFactoryManager->GetEntityFactory(strType);
		if (NULL == pIEntityBaseFactory)
		{
			IComManager::GetInstance().WriteLogMsg("��������Ϊ��", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBase* pIEntityObj = pIEntityBaseFactory->CreateEntityInstance();
		if (NULL == pIEntityObj)
		{
			IComManager::GetInstance().WriteLogMsg("���󴴽�ʧ��", ERROR_MALLOC);
			return (NULL);
		}

		// ��������
		IAttribute* pIAttribute = pIEntityObj->CreateAttribute();
		// ��������
		pIEntityObj->SetAttribute(pIAttribute);
		// ��ʼ������
		pIAttribute->Init();

		// ��������
		pIEntityObj->SetName(pIEntityBaseFactory->GetEntityBaseName());

		// ����UID
		CEntityID* pEntityID = new CEntityID(pIEntityObj, ID);
		pIEntityObj->SetID(pEntityID);

		// ����״̬��
		IStateMachine* pIStateMachince = new CStateMachine(pIEntityObj);
		((CEntityBaseImp<IEntityBase>*)pIEntityObj)->SetStateMachine(pIStateMachince);
		pIEntityObj->InitStateMachine(pIStateMachince);

		// ����״̬
		IState* pIState = pIStateMachince->GetCurrentState();
		if (NULL != pIState)
		{
			pIState->Enter(pIEntityObj);
		}
		// ����ȫ��״̬
		//pIStateMachince->SetGlobalState(new CGlobalState);
		
		// ��ӵ�ʵ����
		pIEntiyComposite->AddEntity(pIEntityObj);

		// �������Ե�����
		pIAttribute->WriteMemory();

		// ģ�ͳ�ʼ��
		pIEntityObj->Init();

		// ���µ�ǰ�����Կ�
		CEntitySystem::GetInstance().GetAttributeManagerInstance()->SetCurrentEntityBase(pIEntityObj);
		// ���������ʵ�����Կ�
		CEntitySystem::GetInstance().UpdateUI();

		IComManager::GetInstance().WriteLogMsg("�ɹ���������");
		return (pIEntityObj);	
	}
}

