
#include "../../Public/VRSoft.h"
#include "GuidanceVisitor.h"

namespace VR_Soft
{
	// 构造函数
	CGuidanceVisitor::CGuidanceVisitor(void)
	{
	}

	// 析构函数
	CGuidanceVisitor::~CGuidanceVisitor(void)
	{
	}

	// 访问器
	void CGuidanceVisitor::Visit( IEntityBase* pIEntityBase )
	{
		m_pIEntityBaseAttribute = pIEntityBase->GetBaseAttribute();

		// 设置开始位置
		const ITrajectory::ListTrajectoryInfo& listTrajectoryInfo = m_pITrajectory->GetTrajectoryPoint();
		osg::Vec3d vGeo = listTrajectoryInfo[0].vGeoPos;
//		m_pIEntityBaseAttribute->SetPosition(vGeo);
	}

	// 设置点数据
	void CGuidanceVisitor::SetTrajectory( ITrajectory* pITrajctory )
	{
		m_pITrajectory = pITrajctory;
	}

}
