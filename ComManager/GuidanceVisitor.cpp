
#include "../../Public/VRSoft.h"
#include "GuidanceVisitor.h"

namespace VR_Soft
{
	// ���캯��
	CGuidanceVisitor::CGuidanceVisitor(void)
	{
	}

	// ��������
	CGuidanceVisitor::~CGuidanceVisitor(void)
	{
	}

	// ������
	void CGuidanceVisitor::Visit( IEntityBase* pIEntityBase )
	{
		m_pIEntityBaseAttribute = pIEntityBase->GetBaseAttribute();

		// ���ÿ�ʼλ��
		const ITrajectory::ListTrajectoryInfo& listTrajectoryInfo = m_pITrajectory->GetTrajectoryPoint();
		osg::Vec3d vGeo = listTrajectoryInfo[0].vGeoPos;
//		m_pIEntityBaseAttribute->SetPosition(vGeo);
	}

	// ���õ�����
	void CGuidanceVisitor::SetTrajectory( ITrajectory* pITrajctory )
	{
		m_pITrajectory = pITrajctory;
	}

}
