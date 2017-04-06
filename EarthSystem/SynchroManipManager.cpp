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

	// 添加操作器
	void CSynchroManipManager::Add( CSynchroManipulator* pSynchorManipulator )
	{
		// 查找是否存在当前的操作器
		ListSynchroManipulators::const_iterator cstItor = std::find(m_listSynchroManipulators.begin(), m_listSynchroManipulators.end(), pSynchorManipulator);
		if (m_listSynchroManipulators.end() == cstItor)
		{
			m_listSynchroManipulators.push_back(pSynchorManipulator);
		}

	}

	// 移除操作器
	void CSynchroManipManager::Remove( CSynchroManipulator* pSynchorManipulator )
	{
		// 查找是否存在当前的操作器
		ListSynchroManipulators::iterator itor = std::find(m_listSynchroManipulators.begin(), m_listSynchroManipulators.end(), pSynchorManipulator);
		if (m_listSynchroManipulators.end() == itor)
		{
			return;
		}

		VRSOFT_DELETE(*itor);
		m_listSynchroManipulators.erase(itor);
	}

	// 移除所有操作器
	void CSynchroManipManager::RemoveAll( void )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			VRSOFT_DELETE(*itor);
		}

		m_listSynchroManipulators.clear();
	}

	// 设置视点
	void CSynchroManipManager::SetViewPoint( const osgEarth::Viewpoint& vp, double duration_s /*=0.0 */ )
	{
		SetViewPoint(NULL, vp, duration_s);
	}

	// 设置视点
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

	// 设置原始视点
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

	// 设置距离
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

	// 跟踪实体模型
	void CSynchroManipManager::SetTrackEntity( const uint64_t uID )
	{
		// 获得实体
		IEntityBase* pIEntity = IEntityManager::GetInstance().GetEntity(uID);
		if (NULL == pIEntity)
		{
			IComManager::GetInstance().WriteLogMsg("实体不存在，SetTrackEntity", ERROR_NOT_FIND);
			return;
		}

		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			pManip->SetTrackEntity(pIEntity);
		}
	}

	// 断开跟踪模型
	void CSynchroManipManager::BreakTrackEntity( void )
	{
		for (ListSynchroManipulators::iterator itor = m_listSynchroManipulators.begin(); m_listSynchroManipulators.end() != itor; ++itor)
		{
			CSynchroManipulator* pManip = *itor;
			pManip->breakTether();
		}
	}

	// 获得视点
	osgEarth::Viewpoint CSynchroManipManager::GetViewPoint( void ) const
	{
		if (m_listSynchroManipulators.empty())
		{
			return (osgEarth::Util::Viewpoint());
		}

		return (m_listSynchroManipulators[0]->getViewpoint());
	}

}
