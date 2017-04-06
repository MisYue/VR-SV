#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteEntityBuilder.h"
#include "SatelliteEntity.h"
#include "SatelliteTrajectoryDraw.h"
namespace VR_Soft
{
	unsigned int CSatelliteEntityBuilder::m_index = 0;
	CSatelliteEntityBuilder::CSatelliteEntityBuilder(void)
	{
		m_pSatelliteEntity = new CSatelliteEntity;
	}


	CSatelliteEntityBuilder::~CSatelliteEntityBuilder(void)
	{
	}

	void CSatelliteEntityBuilder::CreateDrawManager(void)
	{
		// 获得渲染组件
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pSatelliteEntity);
	}

	// 创建渲染属性
	void CSatelliteEntityBuilder::CreateDrawAttribute(void)
	{
		// 添加渲染属性

		// 获得渲染组件
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		IDrawAttribute* pISatelliteDrawAttribute= pIDrawAttributeFactory->CreateMeshInstance(m_pSatelliteEntity, "DFH4");
		m_pSatelliteEntity->AddDrawAttribute(pISatelliteDrawAttribute);

		// 创建算法
		

		// 设置渲染属性
	//	pISatelliteDrawAttribute->GetItem("三维实体")->SetValue((VRString)"DFH4");
	}

	// 创建其它的属性
	void CSatelliteEntityBuilder::CreateAttribute(void)
	{
		/*CTrajectoryAttribute* pTrajectoryAttribute = new CTrajectoryAttribute(m_pTrajectoryEntity);
		m_pTrajectoryEntity->AddAttributes(pTrajectoryAttribute);*/

		
	}

	// 获得名称
	VR_Soft::VRString CSatelliteEntityBuilder::CreateEntityName(void) const
	{
		VRString str = m_pSatelliteEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// 获得产品
	IEntityBase* CSatelliteEntityBuilder::GetEntity(void)
	{
		return (m_pSatelliteEntity);
	}

	// 是否创建运动属性 返回true 则创建
	bool CSatelliteEntityBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}

	// 注册工厂
//	REGISTER_BASEENTITY_FACTORY(CSatelliteEntityBuilder, "卫星");

}
