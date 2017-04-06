
#include "../../Public/VRSoft.h"
#include "EntityBaseAttribute.h"
#include "MoveAttribute.h"
#include "EntityDirctor.h"

namespace VR_Soft
{
	// 构造函数
	CEntityDirctor::CEntityDirctor(IEntityBulider* pIEntityBulider)
		:m_pIEntityBulider(pIEntityBulider)
	{

	}

	// 析构函数
	CEntityDirctor::~CEntityDirctor(void)
	{
		VRSOFT_DELETE(m_pIEntityBulider);
	}

	// 生成
	IEntityBase* CEntityDirctor::Construct()
	{
		if (NULL == m_pIEntityBulider)
		{
			return (NULL);
		}

		// 创建实体
		IEntityBase* pIEntityBase = m_pIEntityBulider->GetEntity();
		pIEntityBase->SetBaseAttribute(new CEntityBaseAttribute(pIEntityBase));

		// 设置名称
		pIEntityBase->SetName(m_pIEntityBulider->CreateEntityName());

		// 创建渲染管理
		m_pIEntityBulider->CreateDrawManager();
		// 创建其它属性
		m_pIEntityBulider->CreateAttribute();
		// 创建其它渲染属性
		m_pIEntityBulider->CreateDrawAttribute();
// 
// 		// 判断是否创建运动属性
// 		if (m_pIEntityBulider->IsCreateMoveAttribute())
// 		{
// 			pIEntityBase->AddAttributes(new CMoveAttribute(pIEntityBase));
// 		}
// 
		// 返回实体
		return (m_pIEntityBulider->GetEntity());
	}
}