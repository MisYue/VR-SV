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

	// ��ʼ��
	void CBallMissileTrajectEntity::Init(void)
	{
		// ��������
		GetBaseAttribute()->SetEntityType("�켣");
	}

	// ��ʼ��״̬��
	void CBallMissileTrajectEntity::InitStateMachine(IStateMachine* pIStateMachine)
	{

	}

	// �������
	const VRString CBallMissileTrajectEntity::GetEntityType(void) const
	{
		return ("���������켣");
	}

	// ģ�͸��£�ÿһ����֡����)
	void CBallMissileTrajectEntity::EntityUpdate(const CDateTime& dt)
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
		// ��÷���״̬
		if (ISimManager::Start == ISimManager::GetInstance().GetSimCmd())
		{
			return;
		}

		bool bEdit = m_pBallMissileAttribute->GetEnableEdit();
		// �ж��Ƿ�������Ҽ�
		if (IEvent::GetInstance().GetMouseButton(MS_RIGHT) && bEdit)
		{
			m_bAlgorithm = true;
			osg::Vec2d v = IEvent::GetInstance().GetMousePosition2D();
			// ��õ�
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
			// ��õ�
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

	// ��������
	void CBallMissileTrajectEntity::SetBallMissileAttribute(CBallMissileAttribute* BallMissileAttribute)
	{
		m_pBallMissileAttribute = BallMissileAttribute;
		AddAttributes(m_pBallMissileAttribute);
	}

	// �������
	VR_Soft::CBallMissileAttribute* CBallMissileTrajectEntity::GetBallMissileAttribute(void) const
	{
		return (m_pBallMissileAttribute);
	}

	// �Ƿ�ʼ����
	bool CBallMissileTrajectEntity::IsAlgorithm(void) const
	{
		return (m_bAlgorithm);
	}

	// �Ƿ����ø���
	void CBallMissileTrajectEntity::SetAlgorithm(void)
	{
		m_bAlgorithm = false;
	}

	// �����Ⱦ��õ�����
	ITrajectory* CBallMissileTrajectEntity::GetTrajectory( void ) const
	{
		return (m_pITrajectory);
	}

	// ������Ⱦ���ݵ����
	void CBallMissileTrajectEntity::SetTrajectory( ITrajectory* pITrajectory )
	{
		m_pITrajectory = pITrajectory;
	}


	void CBallMissileTrajectEntity::AddEntityBase( IEntityBase* pIEntityBase )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��ʵ��
		ListEntityBase::const_iterator cstItor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() != cstItor)
		{
			return;
		}

		// ���ÿ�ʼ���λ��
		IEntityBaseAttribute* pIBaseAttribute = pIEntityBase->GetBaseAttribute();

		osg::Vec3d vPos = m_pBallMissileAttribute->GetPathPoint(0);
		// ת���ɾ�γ������
		osg::Vec3d vGeoPos;
		CConvert::WordToLatLongHeight(vPos, vGeoPos);

		pIBaseAttribute->SetPosition(vGeoPos);

		// ����ģ��
		pIEntityBase->NeedUpdate();
		m_listEntityBasees.push_back(pIEntityBase->GetID());
		//m_listEntityBasees.push_back()
	}

	// �Ƴ�ʵ��
	void CBallMissileTrajectEntity::RemoveEntityBase( IEntityBase* pIEntityBase )
	{
		// ��ѯ�Ƿ���ڵ�ǰ��ʵ��
		ListEntityBase::iterator itor = std::find(m_listEntityBasees.begin(), m_listEntityBasees.end(), pIEntityBase->GetID());
		if (m_listEntityBasees.end() == itor)
		{
			return;
		}

		m_listEntityBasees.erase(itor);
	}

	void CBallMissileTrajectEntity::SimRun( const CDateTime& dt )
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
			osg::Vec3d vTragetPos = m_pBallMissileAttribute->GetKeyPoint(index);
			// �жϵ�ǰ���Ƿ񳬹����ֵ
			/*osg::Vec3d vTragetPos = listTrajectoryInfor[index >= listTrajectoryInfor.size() ? \
			listTrajectoryInfor.size() - 1 : index].vGeoPos;
			// ����Ŀ��λ��
			pIEntityMoveAttribute->SetTragetPosition(vTragetPos);
		}
	}

	// �������ʵ��
	std::vector<IEntityBase* > CBallMissileTrajectEntity::GetAllEntity( void ) const
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