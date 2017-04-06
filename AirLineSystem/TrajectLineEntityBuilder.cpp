#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "TrajectLineEntity.h"
#include "TrajectLineEntityBuilder.h"
#include "TrajectLineAttribute.h"


namespace VR_Soft
{
/*	unsigned int CTrajectLineEntityBuilder::m_index = 0;
	CTrajectLineEntityBuilder::CTrajectLineEntityBuilder(void)
	{
		m_pTrajectLineEntity = new CTrajectLineEntity;
	}


	CTrajectLineEntityBuilder::~CTrajectLineEntityBuilder(void)
	{
	}

	// 创建渲染管理属性
	void CTrajectLineEntityBuilder::CreateDrawManager(void)
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
	void CTrajectLineEntityBuilder::CreateDrawAttribute(void)
	{
//		CTrajectLineAttribute* pTrajectLineAttribute = new CTrajectLineAttribute(m_pTrajectLineEntity);
//		m_pTrajectLineEntity->SetTrajectLineAttribute(pTrajectLineAttribute);
	}

	// 创建其它的属性
	void CTrajectLineEntityBuilder::CreateAttribute(void)
	{
		//CTrajectLineAttribute* pAttribute = new CTrajectLineAttribute(m_pTrajectLineEntity);
		//m_pTrajectLineEntity->AddAttributes(pAttribute);
	}

	// 获得名称
	VR_Soft::VRString CTrajectLineEntityBuilder::CreateEntityName(void) const
	{
		VRString str = m_pTrajectLineEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// 获得产品
	IEntityBase* CTrajectLineEntityBuilder::GetEntity(void)
	{
		return (m_pTrajectLineEntity);
	}

	// 是否创建运动属性 返回true 则创建
	bool CTrajectLineEntityBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}
	*/
}

