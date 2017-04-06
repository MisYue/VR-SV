#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "BallMissileTrajectDrawable.h"
#include "BallMissileTrajectEntity.h"

#include <osg/Geometry>

namespace VR_Soft
{
/*	CBallMissileTrajectDrawable::CBallMissileTrajectDrawable(IEntityBase* pIEntityBase)
		:CAttributeImp<IDrawAttribute>(pIEntityBase, "弹道导弹弹道渲染属性")
	{
		m_pGeode = new osg::Geode;

		// 设置名称
		//m_BallMissilTraject.SetTrajectoryEntity(pIEntityBase);
		m_pBallMissileTrajectEntity = dynamic_cast<CBallMissileTrajectEntity*>(pIEntityBase);
	}


	CBallMissileTrajectDrawable::~CBallMissileTrajectDrawable(void)
	{
	}

	// 更新
	void CBallMissileTrajectDrawable::Update(void)
	{
		if (!m_pBallMissileTrajectEntity->IsAlgorithm())
		{
			return ;
		}
	//	m_BallMissilTraject.AlgorithmTrajectoryPoint();

		// 获得更新顶点
	//	const ITrajectory::ListTrajectoryInfo& listTrajectoryInfo = m_BallMissilTraject.GetTrajectoryPoint();
		UpdateDrawable();

		m_pBallMissileTrajectEntity->SetAlgorithm();
	}

	// 获得渲染体
	DrawObj* CBallMissileTrajectDrawable::GetDrawObj(void)
	{
		return (m_pGeode);
	}

	// 是否随着移动
	bool CBallMissileTrajectDrawable::IsMove(void) const
	{
		return (false);
	}

	// 初始化
	void CBallMissileTrajectDrawable::Init(void)
	{
		// 渲染体
		osg::Geometry* pGeomerty = new osg::Geometry;
		m_pGeode->addDrawable(pGeomerty);


		osg::Vec4Array* pColorArray = new osg::Vec4Array;
		pColorArray->push_back(osg::Vec4(1, 0, 0, 1));

		pGeomerty->setColorArray(pColorArray);

		pGeomerty->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP));
	}

	// 初始化绘制体
	void CBallMissileTrajectDrawable::InitDrawable( void )
	{
		m_pGeode = new osg::Geode;

		m_pLineGeometry = new osg::Geometry;
		m_pGeode->addDrawable(m_pLineGeometry);

		osg::Vec4Array* pColorArray = new osg::Vec4Array;
		pColorArray->push_back(osg::Vec4(1, 0, 0, 1));

		m_pLineGeometry->setColorArray(pColorArray);

		m_pLineGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP));
	}

	// 更新渲染体
	void CBallMissileTrajectDrawable::UpdateDrawable(void)
	{
		osg::Vec3Array* pVertexArray = new osg::Vec3Array;
		int nCount = 0;// (int)m_listDrawPoints.size();
		for (int index = 0; index < nCount; ++index)
		{
//			pVertexArray->push_back(m_listDrawPoints[index]);
		}

		osg::Geometry* pGeomerty = m_pLineGeometry;
		pGeomerty->setVertexArray(pVertexArray);

		osg::Vec4Array* pColorArray = (osg::Vec4Array*)pGeomerty->getColorArray();
		pGeomerty->setColorArray(pColorArray);
		pGeomerty->setColorBinding(osg::Geometry::BIND_OVERALL);

		osg::DrawArrays* pDrawArrays = (osg::DrawArrays*)pGeomerty->getPrimitiveSet(0);
		pDrawArrays->set(GL_LINE_STRIP, 0, pVertexArray->size());
	}
	*/
}
