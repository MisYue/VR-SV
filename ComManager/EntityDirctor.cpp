
#include "../../Public/VRSoft.h"
#include "EntityBaseAttribute.h"
#include "MoveAttribute.h"
#include "EntityDirctor.h"

namespace VR_Soft
{
	// ���캯��
	CEntityDirctor::CEntityDirctor(IEntityBulider* pIEntityBulider)
		:m_pIEntityBulider(pIEntityBulider)
	{

	}

	// ��������
	CEntityDirctor::~CEntityDirctor(void)
	{
		VRSOFT_DELETE(m_pIEntityBulider);
	}

	// ����
	IEntityBase* CEntityDirctor::Construct()
	{
		if (NULL == m_pIEntityBulider)
		{
			return (NULL);
		}

		// ����ʵ��
		IEntityBase* pIEntityBase = m_pIEntityBulider->GetEntity();
		pIEntityBase->SetBaseAttribute(new CEntityBaseAttribute(pIEntityBase));

		// ��������
		pIEntityBase->SetName(m_pIEntityBulider->CreateEntityName());

		// ������Ⱦ����
		m_pIEntityBulider->CreateDrawManager();
		// ������������
		m_pIEntityBulider->CreateAttribute();
		// ����������Ⱦ����
		m_pIEntityBulider->CreateDrawAttribute();
// 
// 		// �ж��Ƿ񴴽��˶�����
// 		if (m_pIEntityBulider->IsCreateMoveAttribute())
// 		{
// 			pIEntityBase->AddAttributes(new CMoveAttribute(pIEntityBase));
// 		}
// 
		// ����ʵ��
		return (m_pIEntityBulider->GetEntity());
	}
}