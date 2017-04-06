#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "BallMissileTrajectEntity.h"
#include "BallMissileAttribute.h"

namespace VR_Soft
{
	/*CBallMissileTrajectEntity::CBallMissileTrajectEntity(void)
		:m_pITrajectory(NULL),m_bAlgorithm(false)
	{
	}


	CBallMissileTrajectEntity::~CBallMissileTrajectEntity(void)
	{
	}

	// 初始化
	void CBallMissileTrajectEntity::Init(void)
	{
		// 设置类型
		GetBaseAttribute()->SetEntityType("轨迹");
	}

	// 初始化状态机
	void CBallMissileTrajectEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

	// 获得类型
	const VRString CBallMissileTrajectEntity::GetEntityType(void) const
	{
		return ("弹道导弹轨迹");
	}

	// 模型更新（每一更新帧调用)
	void CBallMissileTrajectEntity::EntityUpdate(const CDateTime& dt)
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
		// 获得仿真状态
		if (ISimManager::Start == ISimManager::GetInstance().GetSimCmd())
		{
			return;
		}

		bool bEdit = m_pBallMissileAttribute->GetEnableEdit();
		// 判断是否按下鼠标右键
		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && bEdit)
		{
			m_bAlgorithm = true;
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// 获得点
			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
			if (NULL == pIEarthManager)
			{
				return;
			}

			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
			m_pBallMissileAttribute->SetEndPoint(osg::Vec3d(dLat, dLon, dHeight));
		}
		else if (IEvent::GetInstance().GetMouseButton(MS_LEFT)  && bEdit)
		{
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// 获得点
			IEarthManager*  pIEarthManager = CComManagerImp::GetComponent<IEarthManager>(INSTANCE_NAME_EARTHSYSTEM);
			if (NULL == pIEarthManager)
			{
				return;
			}

			double dLat = 0.0, dLon = 0.0, dHeight = 0.0;
			pIEarthManager->GetEarth()->GetLongLatHightByPoint(v.x(), v.y(), dLat, dLon, dHeight);
			m_pBallMissileAttribute->SetStartPoint(osg::Vec3d(dLat, dLon, dHeight));

		}
		else if (IEvent::GetInstance().GetMouseButton(MS_MIDDILE))
		{
			m_pBallMissileAttribute->SetEnableEdit(false);
		}
		
	}

	// 设置属性
	void CBallMissileTrajectEntity::SetBallMissileAttribute(CBallMissileAttribute* BallMissileAttribute)
	{
		m_pBallMissileAttribute = BallMissileAttribute;
		AddAttributes(m_pBallMissileAttribute);
	}

	// 获得属性
	VR_Soft::CBallMissileAttribute* CBallMissileTrajectEntity::GetBallMissileAttribute(void) const
	{
		return (m_pBallMissileAttribute);
	}

	// 是否开始计算
	bool CBallMissileTrajectEntity::IsAlgorithm(void) const
	{
		return (m_bAlgorithm);
	}

	// 是否启用更新
	void CBallMissileTrajectEntity::SetAlgorithm(void)
	{
		m_bAlgorithm = false;
	}

	// 获得渲染获得点数据
	ITrajectory* CBallMissileTrajectEntity::GetTrajectory( void ) const
	{
		return (m_pITrajectory);
	}

	// 设置渲染数据点对象
	void CBallMissileTrajectEntity::SetTrajectory( ITrajectory* pITrajectory )
	{
		m_pITrajectory = pITrajectory;
	}


	void CBallMissileTrajectEntity::AddEntityBase( IEntityBase* pIEntityBase )
	{
		// 查询是否存在当前的实体
		ListEntityBase::const_iterator cstItor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() != cstItor)
		{
			return;
		}

		// 设置开始点的位置
		IEntityBaseAttribute* pIBaseAttribute = pIEntityBase->GetBaseAttribute();

		osg::Vec3d vPos = m_pBallMissileAttribute->GetPathPoint(0);
		// 转换成经纬高坐标
		osg::Vec3d vGeoPos;
		CConvert::WordToLatLongHeight(vPos, vGeoPos);

		pIBaseAttribute->SetPosition(vGeoPos);

		// 更新模型
		pIEntityBase->NeedUpdate();
		m_listEntityBasees.push_back(pIEntityBase->GetID());
		//m_listEntityBasees.push_back()
	}

	// 移除实体
	void CBallMissileTrajectEntity::RemoveEntityBase( IEntityBase* pIEntityBase )
	{
		// 查询是否存在当前的实体
		ListEntityBase::iterator itor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() == itor)
		{
			return;
		}

		m_listEntityBasees.erase(itor);
	}

	void CBallMissileTrajectEntity::SimRun( const CDateTime& dt )
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
			osg::Vec3d vTragetPos = m_pBallMissileAttribute->GetKeyPoint(index);
			// 判断当前点是否超过最大值
			/*osg::Vec3d vTragetPos = listTrajectoryInfor[index >= listTrajectoryInfor.size() ? \
			listTrajectoryInfor.size() - 1 : index].vGeoPos;
			// 设置目标位置
			pIEntityMoveAttribute->SetTragetPosition(vTragetPos);
		}
	}

	// 获得所有实体
	std::vector<IEntityBase* > CBallMissileTrajectEntity::GetAllEntity( void ) const
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