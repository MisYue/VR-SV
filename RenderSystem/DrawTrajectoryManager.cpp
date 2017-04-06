#include "../../Public/VRSoft.h"
#include "DrawTrajectoryManager.h"

#include <algorithm>

namespace VR_Soft
{
	CDrawTrajectoryManager::CDrawTrajectoryManager(void)
	{
		m_pRoot = new osg::Group;
	}


	CDrawTrajectoryManager::~CDrawTrajectoryManager(void)
	{
	}

	// 添加轨迹
	void CDrawTrajectoryManager::AddTrajectory(IDrawTrajectory* pIDrawTrajectory)
	{
		// 添加到管理类中
		ListDrawTrajectorys::const_iterator cstItor = std::find(m_listDrawTrajectorys.begin(), m_listDrawTrajectorys.end(), pIDrawTrajectory);
		if (m_listDrawTrajectorys.end() != cstItor)
		{
			pIDrawTrajectory->Update();
			return;
		}

		m_listDrawTrajectorys.push_back(pIDrawTrajectory);

		osg::Node* pNode = pIDrawTrajectory->GetDrawObj();
		m_pRoot->addChild(pNode);
	}

	// 移除轨迹
	void CDrawTrajectoryManager::RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory)
	{
		// 添加到管理类中
		ListDrawTrajectorys::iterator itor = std::find(m_listDrawTrajectorys.begin(), m_listDrawTrajectorys.end(), pIDrawTrajectory);
		if (m_listDrawTrajectorys.end() == itor)
		{
			return;
		}

		osg::Node* pNode = pIDrawTrajectory->GetDrawObj();
		m_pRoot->removeChild(pNode);

		m_listDrawTrajectorys.erase(itor);
		VRSOFT_DELETE(pIDrawTrajectory);
	}

	// 需要重新绘制
	void CDrawTrajectoryManager::Update(void)
	{

	}

	// 获得渲染体
	DrawObj* CDrawTrajectoryManager::GetDrawObj(void)
	{
		return (m_pRoot);
	}

	// 清空
	void CDrawTrajectoryManager::Clear(void)
	{
		ListDrawTrajectorys::iterator itor = m_listDrawTrajectorys.begin();
		for (; m_listDrawTrajectorys.end() != itor; ++itor)
		{
			VRSOFT_DELETE(*itor);
		}

		m_listDrawTrajectorys.clear();
	}

}

