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

	// 赋值操作符号
	CEntityID& CEntityID::operator=( const CEntityID& other )
	{
		m_uID = other.m_uID;
		return (*this);
	}

	// 设置ID
	void CEntityID::SetEntityID( const uint64_t uID )
	{
		// 设置ID时 需要到内存对象中变更 内存对象 保持偏移量 一致，
		// 不至于造成内存浪费
		// 获取内存管理
		IMemoryManager* pIMemManager = CComManagerImp::GetComponent<IMemoryManager>(INSTANCE_NAME_MEMORYSYSTEM);
		if (NULL == pIMemManager)
		{
			m_uID = uID;
			IComManager::GetInstance().WriteLogMsg("系统没有加载内存插件", ERROR_NOT_FIND);
			return;
		}

		// 更新内存
		pIMemManager->UpdateMemTab(m_uID, uID, m_pIEntityBase);
		m_uID = uID;
	}

	// 获得ID
	const uint64_t CEntityID::GetEntityID( void ) const
	{
		return (m_uID);
	}

	// 获得对应实体
	IEntityBase* CEntityID::GetEntity( void ) const
	{
		return (m_pIEntityBase);
	}

	
}

