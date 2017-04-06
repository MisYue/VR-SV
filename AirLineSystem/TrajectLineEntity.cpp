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

	// ��ʼ��
	void CTrajectLineEntity::Init(void)
	{
		// ��������
		GetBaseAttribute()->SetEntityType("�켣");
	}

	// ��ʼ��״̬��
	void CTrajectLineEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

	// �������
	const VRString CTrajectLineEntity::GetEntityType(void) const
	{
		return ("�켣");
	}

	// ģ�͸��£�ÿһ����֡����)
	void CTrajectLineEntity::EntityUpdate(const CDateTime& dt)
	{
		
		// ��÷���״̬
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
		// �ж��Ƿ�������Ҽ�
		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && bEdit)
		{
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// ��õ�
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

	// ������Ⱦ����
	void CTrajectLineEntity::SetTrajectLineAttribute( CTrajectLineAttribute* pTrajectLineAttribute )
	{
		m_pTrajectLineAttribute = pTrajectLineAttribute;
//		AddAttributes(pTrajectLineAttribute);
	}

	void CTrajectLineEntity::AddEntityBase( IEntityBase* pIEntityBase )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��ʵ��
		ListEntityBase::const_iterator cstItor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() != cstItor)
		{
			return;
		}

		// ���ÿ�ʼ���λ��
		IEntityBaseAttribute* pIBaseAttribute = pIEntityBase->GetBaseAttribute();

		if (NULL == m_pTrajectLineAttribute)
		{
			return;
		}

		osg::Vec3d vPos = m_pTrajectLineAttribute->GetPathPoint(0);
		// ת���ɾ�γ������
		osg::Vec3d vGeoPos;
		CConvert::WordToLatLongHeight(vPos, vGeoPos);

		pIBaseAttribute->SetPosition(vGeoPos);

		// ����ģ��
		pIEntityBase->NeedUpdate();
		m_listEntityBasees.push_back(pIEntityBase->GetID());
	}

	// �Ƴ�ʵ��
	void CTrajectLineEntity::RemoveEntityBase( IEntityBase* pIEntityBase )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��ʵ��
		ListEntityBase::iterator itor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() == itor)
		{
			return;
		}

		m_listEntityBasees.erase(itor);
	}

	void CTrajectLineEntity::SimRun( const CDateTime& dt )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��ʵ��
		ListEntityBase::iterator itor = m_listEntityBasees.begin();
		for (; m_listEntityBasees.end() != itor; ++itor)
		{
			IEntityBase* pIEntitBase = IEntityManager::GetInstance().GetEntity(*itor);
			if (NULL == pIEntitBase)
			{
				continue;
			}

			IEntityMoveAttribute* pIEntityMoveAttribute = dynamic_cast<IEntityMoveAttribute*>(pIEntitBase->GetAttribute("�˶�����"));
			if (NULL == pIEntityMoveAttribute)
			{
				continue;
			}

			// ����˶���ǰ�ĵ������
			int index = pIEntityMoveAttribute->GetIndex();
			osg::Vec3d vTragetPos = m_pTrajectLineAttribute->GetKeyPoint(index);
			
			pIEntityMoveAttribute->SetTragetPosition(vTragetPos);
		}
	}

	// �������ʵ��
	std::vector<IEntityBase* > CTrajectLineEntity::GetAllEntity( void ) const
	{
		std::vector<IEntityBase*> listEntities;
		// �������е�ʵ��
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