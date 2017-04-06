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

	// 创建渲染管理属性
	void CBallMissileTrajectBuilder::CreateDrawManager(void)
	{
		// 获得渲染组件
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pTrajectLineEntity);
	}

	// 创建渲染属性
	void CBallMissileTrajectBuilder::CreateDrawAttribute(void)
	{
// 		CBallMissileTrajectDrawable* pBallMissileDrawalbe = new CBallMissileAttribute(m_pTrajectLineEntity);
// 		m_pTrajectLineEntity->AddAttributes(pBallMissileDrawalbe);
	}

	// 创建其它的属性
	void CBallMissileTrajectBuilder::CreateAttribute(void)
	{
	//	CBallMissileAttribute* pAttribute = new CBallMissileAttribute(m_pTrajectLineEntity);
//		m_pTrajectLineEntity->SetBallMissileAttribute(pAttribute);
	}

	// 获得名称
	VR_Soft::VRString CBallMissileTrajectBuilder::CreateEntityName(void) const
	{
		VRString str = m_pTrajectLineEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// 获得产品
	IEntityBase* CBallMissileTrajectBuilder::GetEntity(void)
	{
		return (m_pTrajectLineEntity);
	}

	// 是否创建运动属性 返回true 则创建
	bool CBallMissileTrajectBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}
	*/
}