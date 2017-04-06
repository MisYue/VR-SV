
#include <list>
#include "../../Public/VRSoft.h"

#include "EntityFactoryManager.h"
#include "StateMachine.h"
//#include "GlobalState.h"
#include "EntityID.h"
#include "EntityBaseAttribute.h"
#include "EntityDirctor.h"
#include "EntityManager.h"
#include "EntityBase.h"
#include "EntityFileManager.h"

namespace VR_Soft
{
	CEntityManager::CEntityManager(void)
	{
	}

	CEntityManager::~CEntityManager(void)
	{
		m_entityFactoryManager.UnRegisterFactory("ϵͳģ��");
		RemoveAllFactroy();
		//m_listEntityManagerUI.clear();
	}

	// ���ʵ��ģ��
	IEntityBase* CEntityManager::GetEntity(const VRString& strEntityName) const
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		VectEntities::const_iterator cstItor = m_vecEntities.begin();
		for (; m_vecEntities.end() != cstItor; ++cstItor)
		{
			if (0 == (*cstItor)->GetName().compare(strEntityName))
			{
				return (*cstItor);
			}
		}
		return (NULL);
	}

	// �����ͼģ��
	void CEntityManager::AddEntity(IEntityBase* pIEntity)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// ����Ƿ���ڵ�ǰ��ʵ��
		const uint64_t ID = pIEntity->GetID();
		// ���ҵ�ǰ��ģ��
		ListIDEntities::const_iterator cstItor = m_listIDEntities.find(ID);
		if (m_listIDEntities.end() != cstItor)
		{
			// �Ѿ������ع���
			IComManager::GetInstance().WriteLogMsg("ʵ�壺" + pIEntity->GetName() + "�Ѿ������ع�");
			return;
		}

		// ���뵽������
		m_listIDEntities.insert(ListIDEntities::value_type(ID, pIEntity));
		// ���뵽�����б���
		m_vecEntities.push_back(pIEntity);

		// ����µ�ʵ��
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateNewItem(pIEntity);
		}
	}

	// �Ƴ�����
	void CEntityManager::RemoveEntity(IEntityBase* pIEntity)
	{
		if (NULL == pIEntity)
		{
			return;
		}

		VR_MUTEX_AUTO

		// �Ӹ����б����Ƴ�
		VectEntities::iterator vitor = std::find(m_vecEntities.begin(), m_vecEntities.end(), pIEntity);
		if (m_vecEntities.end() != vitor)
		{
			m_vecEntities.erase(vitor);
		}

		// ���ʵ��ID
		const uint64_t ID = pIEntity->GetID();
		// �ڵ�ǰ�в����Ƿ����
		ListIDEntities::iterator itor = m_listIDEntities.find(ID);
		if (m_listIDEntities.end() == itor)
		{
			return;
		}

		VRString strName = pIEntity->GetName();

		// �ж��Ƿ�Ϊ��ǰ�ļ�������
		if (IAttributeManager::GetInstance().GetCurrentEntityBaseID() == ID)
		{
			IAttributeManager::GetInstance().SetCurrentEntityBase(NULL);
		}

		// �Ƴ�ʵ��
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateDelItem(pIEntity);
		}

		// ɾ��ʵ��
		VRSOFT_DELETE(pIEntity);
		m_listIDEntities.erase(itor);
		IComManager::GetInstance().WriteLogMsg("�ɹ������" + strName);
	}

	// �Ƴ�����
	void CEntityManager::RemoveEntity(const VRString& strName)
	{
		IEntityBase* pIEntity = GetEntity(strName);
		RemoveEntity(pIEntity);
	}

	// �Ƴ�����
	void CEntityManager::RemoveEntity( const uint64_t ID )
	{
		IEntityBase* pIEntity = GetEntity(ID);
		RemoveEntity(pIEntity);
	}

	// ɾ�����е���ʵ��
	void CEntityManager::RemoveAllEntity(void)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		// �Ƴ����е�
		m_listIDEntities.clear();
		m_listFactoryEntities.clear();

		// ����������Ŀ¼
		for (VectEntities::iterator itor = m_vecEntities.begin(); \
			m_vecEntities.end() != itor; ++itor)
		{
			// ɾ�����е���Ŀ¼
			VRSOFT_DELETE(*itor);
		}

		// ���Ŀ¼
		m_vecEntities.clear();	



		IComManager::GetInstance().WriteLogMsg("�ɹ�ȫ�����");
		// ���½���
//		IEntityManager::GetInstance().UpdateUI();
	}

	// ��ȡ���е��Ӽ�
	const std::vector<IEntityBase*>& CEntityManager::GetAllEntities(void) const
	{
		// ����
		return (m_vecEntities);
	}

	// ���ģ�͸���
	int CEntityManager::GetCount( void ) const
	{
		return (m_listIDEntities.size());
	}

	// ͨ�����Ʋ�ѯʵ�� �ҵ���һ��ʵ�ֵ�ֱֵ�ӷ���
	IEntityBase* CEntityManager::GetEntity( const uint64_t uID ) const
	{
		// ��ѯmap
		ListIDEntities::const_iterator cstItor = m_listIDEntities.find(uID);
		if (m_listIDEntities.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	// �������е�ģ��
	void CEntityManager::EntityUpdate(const CDateTime& dt)
	{
		// �������е�ģ��
		VectEntities::iterator itor = m_vecEntities.begin();
		for (; m_vecEntities.end() != itor; ++itor)
		{
			// ����ģ��
			(*itor)->EntityUpdate(dt);
		}
	}

	// ��ù�������
	IEntityFactoryManager* CEntityManager::GetEntityFactoryManager(void)
	{
		return (&m_entityFactoryManager);
	}

	// ͨ������������ѯ��Ӧ��ʵ��
	IEntityBase* CEntityManager::CreateEntity(const VRString& strName, const uint64_t ID)
	{
		// �жϴ����ļ�ʵ���Ƿ�ɹ�
		IEntityBase* pEntity = CEntityFileManager::GetInstance().CreateEntity(strName, ID);
		if (NULL == pEntity)
		{
			pEntity = CreateEntityByFactory(strName, ID);
		}

		return (pEntity);
	}

	// ��ʼ��
	void CEntityManager::Init( void )
	{
		IEntityBaseFactory* pIEntityBaseFactory = new CEntityBaseBuilderFactory;
		m_entityFactoryManager.RegisterFactory(pIEntityBaseFactory);
	}

	// �Ƴ�����
	void CEntityManager::RemoveFactory( IEntityBaseFactory* pIEntityBaseFactory )
	{
		ListFactoryEntities::iterator itor = m_listFactoryEntities.find(pIEntityBaseFactory);
		if (m_listFactoryEntities.end() == itor)
		{
			return;
		}

		VectEntityIDs& vecEntities = itor->second;
		for (VectEntityIDs::iterator vecItor = vecEntities.begin(); vecEntities.end() != vecItor; ++vecItor)
		{
			// �Ƴ�ʵ��
			RemoveEntity(*vecItor);
		}

		m_listFactoryEntities.erase(itor);
	}

	// ��ӹ۲���
	void CEntityManager::Attach( IEntityManagerUI* pIEntityManagerUI )
	{
		ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.find(pIEntityManagerUI);
		if (m_listEntityManagerUI.end() == cstItor)
		{
			m_listEntityManagerUI.insert(pIEntityManagerUI);
			pIEntityManagerUI->Init(this);
		}
	}

	void CEntityManager::Detach( IEntityManagerUI* pIEntityManagerUI )
	{
		ListEntityManagerUI::iterator itor = m_listEntityManagerUI.find(pIEntityManagerUI);
		if (m_listEntityManagerUI.end() != itor)
		{
			m_listEntityManagerUI.erase(itor);
		}
	}

	// ͨ����������ϵͳʵ����ļ�ʵ��
	IEntityBase* CEntityManager::CreateEntityByFactory( const VRString& strName, const uint64_t ID )
	{
		// ��ù���
		IEntityBaseFactory* pIEntityBaseFactory  = m_entityFactoryManager.GetEntityFactory(strName);
		if (NULL == pIEntityBaseFactory)
		{
			IComManager::GetInstance().WriteLogMsg("��������Ϊ��", ERROR_MALLOC);
			return (NULL);
		}

		IEntityBulider* pIEntityBulider = pIEntityBaseFactory->CreateEntityBuilder();
		if (NULL == pIEntityBulider)
		{
			IComManager::GetInstance().WriteLogMsg("���󴴽�ʧ��", ERROR_MALLOC);
			return (NULL);
		}

		CEntityDirctor entityDirctor(pIEntityBulider);
		IEntityBase* pIEntityObj = entityDirctor.Construct();
		if (NULL == pIEntityObj)
		{
			IComManager::GetInstance().WriteLogMsg("���󴴽�ʧ��", ERROR_MALLOC);
			return (NULL);
		}

		// ����UID
		pIEntityObj->SetID(ID);

		// ����״̬��
		IStateMachine* pIStateMachince = new CStateMachine(pIEntityObj);
		pIEntityObj->SetStateMachine(pIStateMachince);
		pIEntityObj->InitStateMachine(pIStateMachince);

		// ����״̬
		IState* pIState = pIStateMachince->GetCurrentState();
		if (NULL != pIState)
		{
			pIState->Enter(pIEntityObj);
		}

		// ��ӵ�ʵ����
		AddEntity(pIEntityObj);

		// ģ�ͳ�ʼ��
		pIEntityObj->Init();

		ListFactoryEntities::iterator itor = m_listFactoryEntities.find(pIEntityBaseFactory);
		if (m_listFactoryEntities.end() == itor)
		{
			VectEntityIDs vecEntities;
			vecEntities.push_back(pIEntityObj->GetID());
			m_listFactoryEntities.insert(ListFactoryEntities::value_type(pIEntityBaseFactory, vecEntities));
		}
		else
		{
			VectEntityIDs& vecEntities = itor->second;
			vecEntities.push_back(pIEntityObj->GetID());
		}

		// ��ӵ�
		// ���������ʵ�����Կ�
		//		CEntitySystem::GetInstance().UpdateUI();

		IComManager::GetInstance().WriteLogMsg("�ɹ���������");
		return (pIEntityObj);	
	}

	// �޸�ʵ������
	void CEntityManager::ChangeEntityName( IEntityBase* pIEntity, const VRString& strOld, const VRString& strNew ) const
	{
		// ����ʵ��
		for (ListEntityManagerUI::const_iterator cstItor = m_listEntityManagerUI.begin();
			m_listEntityManagerUI.end() != cstItor; ++cstItor)
		{
			(*cstItor)->UpdateItem(pIEntity, strOld, strNew);
		}
	}

	// ��������Ӽ�
	std::vector<IEntityBase*> CEntityManager::GetEntities( const VRString& strType ) const
	{
		std::vector<IEntityBase*> listEntityBases;
		for (VectEntities::const_iterator cstItor = m_vecEntities.begin(); \
			m_vecEntities.end() != cstItor; ++cstItor)
		{
			IEntityBase* pIEntityBase = *cstItor;
			//const VRString strType = pIEntityBase->GetEntityType();
			IEntityBaseAttribute* pIEntityBaseAttribute = pIEntityBase->GetBaseAttribute();
			const VRString strEntityType = pIEntityBaseAttribute->GetEntityType();
			if (0 == strEntityType.compare(strType))
			{
				listEntityBases.push_back(pIEntityBase);
			}
		}

		return (listEntityBases);
	}

	// �Ƴ����еĹ���
	void CEntityManager::RemoveAllFactroy( void )
	{
		for (ListFactoryEntities::iterator itor = m_listFactoryEntities.begin(); m_listFactoryEntities.end() != itor; ++itor)
		{
			VectEntityIDs& vecEntities = itor->second;
			for (VectEntityIDs::iterator vecItor = vecEntities.begin(); vecEntities.end() != vecItor; ++vecItor)
			{
				// �Ƴ�ʵ��
				RemoveEntity(*vecItor);
			}

//			VRSOFT_DELETE(itor->first);
		}

		m_listFactoryEntities.clear();

	}

}