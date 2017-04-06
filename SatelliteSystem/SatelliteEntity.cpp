#define VRSOFT_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteEntity.h"
#include "SatelliteTrajectoryDraw.h"
#include "SatelliteTrajectory.h"

namespace VR_Soft
{
	CSatelliteEntity::CSatelliteEntity(void)
	{
	}


	CSatelliteEntity::~CSatelliteEntity(void)
	{
	}

	// ��ʼ��
	void CSatelliteEntity::Init(void)
	{
	}

	// ��ʼ��״̬��
	void CSatelliteEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{
		
	}

	// �������
	const VRString CSatelliteEntity::GetEntityType(void) const
	{
		return ("����");
	}

	// ģ�͸��£�ÿһ����֡����)
	void CSatelliteEntity::EntityUpdate(const CDateTime& dt)
	{
		if (NULL == m_pITrajecoty)
		{
			return;
		}

		CSatelliteTrajectory* pSatelliteTrajectory = (CSatelliteTrajectory*)m_pITrajecoty;
		
		osg::Vec3d vPt = pSatelliteTrajectory->GetCurPos(m_pTrajectoryDrawAttribute, dt);
		// ����λ��
		GetBaseAttribute()->SetPosition(vPt);

		// ����
		NeedUpdate();
	}

	// �����㷨����
	void CSatelliteEntity::SetTrajectory(ITrajectory* pITrajectory)
	{
		m_pITrajecoty = pITrajectory;
	}

	// ����㷨����
	ITrajectory* CSatelliteEntity::GetTrajectory(void)
	{
		return (m_pITrajecoty);
	}

	// ���ɹ��
	void CSatelliteEntity::GenerateTrajectory(void)
	{
		if (NULL == m_pITrajecoty)
		{
			return;
		}
		m_pITrajecoty->AlgorithmTrajectoryPoint();


		// �����Ⱦ���
		IRenderManager* pIRenderManager = CComManagerImp::GetComponent<IRenderManager>(INSTANCE_NAME_RENDERSYSTEM);
		if (NULL == pIRenderManager)
		{
			return;
		}

		m_pTrajectoryDrawAttribute = new CSatalliteTrajectoryDraw();

		m_pTrajectoryDrawAttribute->SetTrajectory(m_pITrajecoty);
		pIRenderManager->GetTrajectoryManager()->AddTrajectory(m_pTrajectoryDrawAttribute);

		m_pTrajectoryDrawAttribute->Update();

		const ITrajectory::ListTrajectoryInfo listTrajectoryInfo = m_pITrajecoty->GetTrajectoryPoint();
		if (listTrajectoryInfo.empty())
		{
			return;
		}

		// ���õ�һ���ڵ�һ������
		GetBaseAttribute()->SetPosition(listTrajectoryInfo[0].vGeoPos);
	}

	// �������и���
	void CSatelliteEntity::SetTle(ITle* pITle)
	{
		m_pITile = pITle;
	}

	// ������и���
	ITle* CSatelliteEntity::GetTle(void) const
	{
		return (m_pITile);
	}

}
