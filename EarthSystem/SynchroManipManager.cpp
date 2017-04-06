#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroManipManager.h"

#include <algorithm>

namespace VR_Soft
{
	CSynchroManipManager::CSynchroManipManager(void)
	{
	}


	CSynchroManipManager::~CSynchroManipManager(void)
	{
	}

	// ��Ӳ�����
	void CSynchroManipManager::Add( CSynchroManipulator* pSynchorManipulator )
	{
		// �����Ƿ���ڵ�ǰ�Ĳ�����
		ListSynchroManipulators::const_iterator cstItor = std::find(m_listSynchroManipulators.begin(), m_listSynchroManipulators.end(), pSynchorManipulator);
		if (m_listSynchroManipulators.end() == cstItor)
		{
			m_listSynchroManipulators.push_back(pSynchorManipulator);
		}

	}

	// �Ƴ�������
	void CSynchroManipManager::Remove( CSynchroManipulator* pSynchorManipulator )
	{
		// �����Ƿ���ڵ�ǰ�Ĳ�����
		ListSynchroManipulators::iterator itor = std::find(m_listSynchroManipulators.begin(), m_listSynchroManipulators.end(), pSynchorManipulator);
		if (m_listSynchroManipulators.end() == itor)
		{
			return;
		}

		VRSOFT_DELETE(*itor);
		m_listSynchroManipulators.erase(itor);
	}

	// �Ƴ����в�����
	void CSynchroManipManager::RemoveAll( void )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			VRSOFT_DELETE(*itor);
		}

		m_listSynchroManipulators.clear();
	}

	// �����ӵ�
	void CSynchroManipManager::SetViewPoint( const osgEarth::Viewpoint& vp, double duration_s /*=0.0 */ )
	{
		SetViewPoint(NULL, vp, duration_s);
	}

	// �����ӵ�
	void CSynchroManipManager::SetViewPoint( const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s /*=0.0 */ )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			if (pSynchroManip == pManip)
			{
				continue;
			}
			pManip->SetViewPoint(vp, duration_s);
		}
	}

	// ����ԭʼ�ӵ�
	void CSynchroManipManager::SetHomeViewPoint(const CSynchroManipulator* pSynchroManip, const osgEarth::Viewpoint& vp, double duration_s)
	{
		const osgEarth::Viewpoint& viewPoint = pSynchroManip->getViewpoint();
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			if (pSynchroManip == pManip)
			{
				continue;
			}
			
			pManip->home(duration_s);
		//	pManip->setViewpoint(viewPoint, duration_s);
		}
	}

	// ���þ���
	void CSynchroManipManager::SetDistance( const CSynchroManipulator* pSynchroManip, const double dDistance )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			if (pSynchroManip == pManip)
			{
				continue;
			}
			pManip->setDistance(dDistance);
		}
	}

	// ����ʵ��ģ��
	void CSynchroManipManager::SetTrackEntity( const uint64_t uID )
	{
		// ���ʵ��
		IEntityBase* pIEntity = IEntityManager::GetInstance().GetEntity(uID);
		if (NULL == pIEntity)
		{
			IComManager::GetInstance().WriteLogMsg("ʵ�岻���ڣ�SetTrackEntity", ERROR_NOT_FIND);
			return;
		}

		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			pManip->SetTrackEntity(pIEntity);
		}
	}

	// �Ͽ�����ģ��
	void CSynchroManipManager::BreakTrackEntity( void )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			pManip->breakTether();
		}
	}

	// ����ӵ�
	osgEarth::Viewpoint CSynchroManipManager::GetViewPoint( void ) const
	{
		if (m_listSynchroManipulators.empty())
		{
			return (osgEarth::Util::Viewpoint());
		}

		return (m_listSynchroManipulators[0]->getViewpoint());
	}

}
