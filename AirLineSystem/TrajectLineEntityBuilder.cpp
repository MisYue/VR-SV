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

	// ������Ⱦ��������
	void CTrajectLineEntityBuilder::CreateDrawManager(void)
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
	void CTrajectLineEntityBuilder::CreateDrawAttribute(void)
	{
//		CTrajectLineAttribute* pTrajectLineAttribute = new CTrajectLineAttribute(m_pTrajectLineEntity);
//		m_pTrajectLineEntity->SetTrajectLineAttribute(pTrajectLineAttribute);
	}

	// ��������������
	void CTrajectLineEntityBuilder::CreateAttribute(void)
	{
		//CTrajectLineAttribute* pAttribute = new CTrajectLineAttribute(m_pTrajectLineEntity);
		//m_pTrajectLineEntity->AddAttributes(pAttribute);
	}

	// �������
	VR_Soft::VRString CTrajectLineEntityBuilder::CreateEntityName(void) const
	{
		VRString str = m_pTrajectLineEntity->GetEntityType();
		char szName[3] = {0};
		str += itoa(m_index++, szName, 10);
		return (str);
	}

	// ��ò�Ʒ
	IEntityBase* CTrajectLineEntityBuilder::GetEntity(void)
	{
		return (m_pTrajectLineEntity);
	}

	// �Ƿ񴴽��˶����� ����true �򴴽�
	bool CTrajectLineEntityBuilder::IsCreateMoveAttribute( void )
	{
		return (false);
	}
	*/
}

