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
		// �����Ⱦ���
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		pIDrawAttributeFactory->CreateEntityDrawManagerInstance(m_pSatelliteEntity);
	}

	// ������Ⱦ����
	void CSatelliteEntityBuilder::CreateDrawAttribute(void)
	{
		// �����Ⱦ����

		// �����Ⱦ���
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		IDrawAttributeFactory* pIDrawAttributeFactory =  pIRenderManager->GetDrawAttributeFactory();
		IDrawAttribute* pISatelliteDrawAttribute= pIDrawAttributeFactory->CreateMeshInstance(m_pSatelliteEntity, "DFH4");
		m_pSatelliteEntity->AddDrawAttribute(pISatelliteDrawAttribute);

		// �����㷨
		

		// ������Ⱦ����
	//	pISatelliteDrawAttribute->GetItem("��άʵ��")->SetValue((VRString)"DFH4");
	}

	// ��������������
	void CSatelliteEntityBuilder::CreateAttribute(void)
	{
		/*CTrajectoryAttribute* pTrajectoryAttribute = new CTrajectoryAttribute(m_pTrajectoryEntity);
		m_pTrajectoryEntity->AddAttributes(pTrajectoryAttribute);*/

		
	}

	// �������
	VR_Soft::VRString CSatelliteEntityBuilder::CreateEntityName(void) const
	{
		VRString str = m_pSatelliteEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// ��ò�Ʒ
	IEntityBase* CSatelliteEntityBuilder::GetEntity(void)
	{
		return (m_pSatelliteEntity);
	}

	// �Ƿ񴴽��˶����� ����true �򴴽�
	bool CSatelliteEntityBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}

	// ע�Ṥ��
//	REGISTER_BASEENTITY_FACTORY(CSatelliteEntityBuilder, "����");

}
