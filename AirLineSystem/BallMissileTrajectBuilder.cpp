#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "BallMissileTrajectBuilder.h"
#include "BallMissileTrajectEntity.h"
#include "BallMissileAttribute.h"
#include "BallMissileTrajectDrawable.h"

namespace VR_Soft
{
/*	unsigned int CBallMissileTrajectBuilder::m_index = 0;
	CBallMissileTrajectBuilder::CBallMissileTrajectBuilder(void)
	{
		m_pTrajectLineEntity = new CBallMissileTrajectEntity;
	}


	CBallMissileTrajectBuilder::~CBallMissileTrajectBuilder(void)
	{
	}

	// ������Ⱦ��������
	void CBallMissileTrajectBuilder::CreateDrawManager(void)
	{
		// �����Ⱦ���
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pTrajectLineEntity);
	}

	// ������Ⱦ����
	void CBallMissileTrajectBuilder::CreateDrawAttribute(void)
	{
// 		CBallMissileTrajectDrawable* pBallMissileDrawalbe = new CBallMissileAttribute(m_pTrajectLineEntity);
// 		m_pTrajectLineEntity->AddAttributes(pBallMissileDrawalbe);
	}

	// ��������������
	void CBallMissileTrajectBuilder::CreateAttribute(void)
	{
	//	CBallMissileAttribute* pAttribute = new CBallMissileAttribute(m_pTrajectLineEntity);
//		m_pTrajectLineEntity->SetBallMissileAttribute(pAttribute);
	}

	// �������
	VR_Soft::VRString CBallMissileTrajectBuilder::CreateEntityName(void) const
	{
		VRString str = m_pTrajectLineEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// ��ò�Ʒ
	IEntityBase* CBallMissileTrajectBuilder::GetEntity(void)
	{
		return (m_pTrajectLineEntity);
	}

	// �Ƿ񴴽��˶����� ����true �򴴽�
	bool CBallMissileTrajectBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}
	*/
}