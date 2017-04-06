#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "TrajectLineEntity.h"
#include "TrajectLine.h"
#include "TrajectLineDrawable.h"
#include "TrajectLineAttribute.h"

namespace VR_Soft
{
/*	CTrajectLineEntity::CTrajectLineEntity(void)
		:m_pTrajectLineAttribute(NULL)
	{
	}


	CTrajectLineEntity::~CTrajectLineEntity(void)
	{
		
	}

	// 初始化
	void CTrajectLineEntity::Init(void)
	{
		// 设置类型
		GetBaseAttribute()->SetEntityType("轨迹");
	}

	// 初始化状态机
	void CTrajectLineEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

	// 获得类型
	const VRString CTrajectLineEntity::GetEntityType(void) const
	{
		return ("轨迹");
	}

	// 模型更新（每一更新帧调用)
	void CTrajectLineEntity::EntityUpdate(const CDateTime& dt)
	{
		
		// 获得仿真状态
		ISimManager::SimCmd simCmd = ISimManager::GetInstance().GetSimCmd();
		if (ISimManager::Pause !=  simCmd && ISimManager::Stop != simCmd )
		{
			SimRun(dt);
			return;
		}
		else
		{
			CEntityBaseImp<ITrajectoryLineEntity>::EntityUpdate(dt);
		}
		
		bool bEdit = m_pTrajectLineAttribute->GetEnableEdit();
		// 判断是否按下鼠标右键
		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && bEdit)
		{
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// 获得点
			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
			if (NULL == pIEarthManager)
			{
				return;
			}

			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
			const osg::Vec3d vWorld = pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);

			dHeight += 10000;
			
			TrajectoryInfo trajectoryInfo;
			trajectoryInfo.dt = 0.0;
			trajectoryInfo.vGeoPos = osg::Vec3d(dLat, dLon, dHeight);
			trajectoryInfo.vEcfPos = vWorld;
			m_pTrajectLine->AddAirLinePoint(trajectoryInfo);

			m_pTrajectLineAttribute->Update();
		}
		else if (IEvent::GetInstance().GetMouseButton(MS_MIDDILE))
		{
			m_pTrajectLineAttribute->SetEnableEdit(false);
		}
		
	}

	// 设置渲染属性
	void CTrajectLineEntity::SetTrajectLineAttribute( CTrajectLineAttribute* pTrajectLineAttribute )
	{
		m_pTrajectLineAttribute = pTrajectLineAttribute;
//		AddAttributes(pTrajectLineAttribute);
	}

	void CTrajectLineEntity::AddEntityBase( IEntityBase* pIEntityBase )
	{
		// 查询是否存在当前的实体
		ListEntityBase::const_iterator cstItor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() != cstItor)
		{
			return;
		}

		// 设置开始点的位置
		IEntityBaseAttribute* pIBaseAttribute = pIEntityBase->GetBaseAttribute();

		if (NULL == m_pTrajectLineAttribute)
		{
			return;
		}

		osg::Vec3d vPos = m_pTrajectLineAttribute->GetPathPoint(0);
		// 转换成经纬高坐标
		osg::Vec3d vGeoPos;
		CConvert::WordToLatLongHeight(vPos, vGeoPos);

		pIBaseAttribute->SetPosition(vGeoPos);

		// 更新模型
		pIEntityBase->NeedUpdate();
		m_listEntityBasees.push_back(pIEntityBase->GetID());
	}

	// 移除实体
	void CTrajectLineEntity::RemoveEntityBase( IEntityBase* pIEntityBase )
	{
		// 查询是否存在当前的实体
		ListEntityBase::iterator itor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() == itor)
		{
			return;
		}

		m_listEntityBasees.erase(itor);
	}

	void CTrajectLineEntity::SimRun( const CDateTime& dt )
	{
		// 查询是否存在当前的实体
		ListEntityBase::iterator itor = m_listEntityBasees.begin();
		for (; m_listEntityBasees.end() != itor; ++itor)
		{
			IEntityBase* pIEntitBase = IEntityManager::GetInstance().GetEntity(*itor);
			if (NULL == pIEntitBase)
			{
				continue;
			}

			IEntityMoveAttribute* pIEntityMoveAttribute = dynamic_cast<IEntityMoveAttribute*>(pIEntitBase->GetAttribute("运动属性"));
			if (NULL == pIEntityMoveAttribute)
			{
				continue;
			}

			// 获得运动当前的点的索引
			int index = pIEntityMoveAttribute->GetIndex();
			osg::Vec3d vTragetPos = m_pTrajectLineAttribute->GetKeyPoint(index);
			
			pIEntityMoveAttribute->SetTragetPosition(vTragetPos);
		}
	}

	// 获得所有实体
	std::vector<IEntityBase* > CTrajectLineEntity::GetAllEntity( void ) const
	{
		std::vector<IEntityBase*> listEntities;
		// 遍历所有的实体
		for (ListEntityBase::const_iterator cstItor = m_listEntityBasees.begin(); m_listEntityBasees.end() != cstItor; ++cstItor)
		{
			IEntityBase* pIEntity = IEntityManager::GetInstance().GetEntity(*cstItor);
			if (NULL != pIEntity)
			{
				listEntities.push_back(pIEntity);
			}
		}

		return (listEntities);
	}
*/
}