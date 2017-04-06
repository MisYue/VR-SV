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

	// ��ӹ켣
	void CDrawTrajectoryManager::AddTrajectory(IDrawTrajectory* pIDrawTrajectory)
	{
		// ��ӵ���������
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

	// �Ƴ��켣
	void CDrawTrajectoryManager::RemoveTrajectory(IDrawTrajectory* pIDrawTrajectory)
	{
		// ��ӵ���������
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

	// ��Ҫ���»���
	void CDrawTrajectoryManager::Update(void)
	{

	}

	// �����Ⱦ��
	DrawObj* CDrawTrajectoryManager::GetDrawObj(void)
	{
		return (m_pRoot);
	}

	// ���
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

