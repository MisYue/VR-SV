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

	// 初始化
	void CSatelliteEntity::Init(void)
	{
	}

	// 初始化状态机
	void CSatelliteEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{
		
	}

	// 获得类型
	const VRString CSatelliteEntity::GetEntityType(void) const
	{
		return ("卫星");
	}

	// 模型更新（每一更新帧调用)
	void CSatelliteEntity::EntityUpdate(const CDateTime& dt)
	{
		if (NULL == m_pITrajecoty)
		{
			return;
		}

		CSatelliteTrajectory* pSatelliteTrajectory = (CSatelliteTrajectory*)m_pITrajecoty;
		
		osg::Vec3d vPt = pSatelliteTrajectory->GetCurPos(m_pTrajectoryDrawAttribute, dt);
		// 设置位置
		GetBaseAttribute()->SetPosition(vPt);

		// 更新
		NeedUpdate();
	}

	// 设置算法策略
	void CSatelliteEntity::SetTrajectory(ITrajectory* pITrajectory)
	{
		m_pITrajecoty = pITrajectory;
	}

	// 获得算法策略
	ITrajectory* CSatelliteEntity::GetTrajectory(void)
	{
		return (m_pITrajecoty);
	}

	// 生成轨道
	void CSatelliteEntity::GenerateTrajectory(void)
	{
		if (NULL == m_pITrajecoty)
		{
			return;
		}
		m_pITrajecoty->AlgorithmTrajectoryPoint();


		// 获得渲染组件
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

		// 设置第一个在第一个点上
		GetBaseAttribute()->SetPosition(listTrajectoryInfo[0].vGeoPos);
	}

	// 设置两行根数
	void CSatelliteEntity::SetTle(ITle* pITle)
	{
		m_pITile = pITle;
	}

	// 获得两行根数
	ITle* CSatelliteEntity::GetTle(void) const
	{
		return (m_pITile);
	}

}
