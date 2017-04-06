#include "../../Public/VRSoft.h"
#include "../../Public/MemoreySystem/MemorySystem.h"
#include "../../Public/Plugin/PluginDepined.h"
#include "EntityID.h"

namespace VR_Soft
{
	CEntityID::CEntityID(IEntityBase* pIEntityBase, const uint64_t ID)
		:m_pIEntityBase(pIEntityBase), m_uID(ID)
	{
		SetEntityID(ID);
	}

	CEntityID::~CEntityID(void)
	{
	}

	// ��ֵ��������
	CEntityID& CEntityID::operator=( const CEntityID& other )
	{
		m_uID = other.m_uID;
		return (*this);
	}

	// ����ID
	void CEntityID::SetEntityID( const uint64_t uID )
	{
		// ����IDʱ ��Ҫ���ڴ�����б�� �ڴ���� ����ƫ���� һ�£�
		// ����������ڴ��˷�
		// ��ȡ�ڴ����
		IMemoryManager* pIMemManager = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManager)
		{
			m_uID = uID;
			IComManager::GetInstance().WriteLogMsg("ϵͳû�м����ڴ���", ERROR_NOT_FIND);
			return;
		}

		// �����ڴ�
		pIMemManager->UpdateMemTab(m_uID, uID, m_pIEntityBase);
		m_uID = uID;
	}

	// ���ID
	const uint64_t CEntityID::GetEntityID( void ) const
	{
		return (m_uID);
	}

	// ��ö�Ӧʵ��
	IEntityBase* CEntityID::GetEntity( void ) const
	{
		return (m_pIEntityBase);
	}

	
}

