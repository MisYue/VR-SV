#include "../../Public/VRSoft.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SatelliteTrajectoryDraw.h"
#include "SatelliteEntity.h"

#include <osg/Geometry>

namespace VR_Soft
{
	const double kPI = 3.14159265358979323846264338327950288419716939937510582;
	const double kTWOPI = 2.0 * kPI;

	CSatalliteTrajectoryDraw::CSatalliteTrajectoryDraw()
		: m_pGeode(new osg::Geode)\
		,m_bUpdate(true),m_pITrajectory(NULL)
	{
		m_pGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		m_pMt = new osg::MatrixTransform;
		m_pMt->addChild(m_pGeode);
	}


	CSatalliteTrajectoryDraw::~CSatalliteTrajectoryDraw(void)
	{
	}

	// 更新
	void CSatalliteTrajectoryDraw::Update(void)
	{
		if (!m_bUpdate)
		{
			m_bUpdate = false;
			return;
		}

		InitDrawabel();
		
	}

	DrawObj* CSatalliteTrajectoryDraw::GetDrawObj(void)
	{
		// 获得仿真时间
		double dt = ISimManager::GetInstance().GetStartTime().ToJulian();
		UpdateMatrix(dt);
		return (m_pMt);
	}

	void CSatalliteTrajectoryDraw::SetTrajectory(ITrajectory* pITrajectory)
	{
		m_pITrajectory = pITrajectory;
	}

	// 更新旋转矩阵
	void CSatalliteTrajectoryDraw::UpdateMatrix(double dt)
	{
		const double t = (dt - 2451545.0) / 36525.0;

		// Rotation angle in arcseconds
		double theta = 67310.54841
			+ (876600.0 * 3600.0 + 8640184.812866) * t
			+ 0.093104 * t * t
			- 0.0000062 * t * t * t;

		double dTheta = osg::DegreesToRadians(theta / 240.0);

		double dRot = dTheta - kTWOPI * floor(dTheta / kTWOPI);

		m_pMt->setMatrix(osg::Matrix::rotate(dRot, -osg::Z_AXIS));
	}

	// 初始化渲染体
	bool CSatalliteTrajectoryDraw::InitDrawabel(void)
	{
		assert (NULL != m_pITrajectory);

		m_pGeode->removeDrawables(0, m_pGeode->getNumChildren());
		
		// 获得
		osg::Vec3Array* pVertexArray = GetVertexArrays(m_pITrajectory);
		if (NULL == pVertexArray)
		{
			ILogManager::GetInstance().SetLogMessage("获得弹道实体失败", ERROR_EXCEPT);
			return (false);
		}

		osg::Geometry* pGometry = new osg::Geometry;
		pGometry->setVertexArray(pVertexArray);

		osg::Vec4dArray* pColor = new osg::Vec4dArray;
		pColor->push_back(osg::Vec4(1.0f, 0.3f, 0.9f, 1.0));
		pGometry->setColorArray(pColor);
		pGometry->setColorBinding(osg::Geometry::BIND_OVERALL);
		pGometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, pVertexArray->size()));

		m_pGeode->addDrawable(pGometry);

		return (true);
	}

	// 获得顶点
	osg::Vec3Array* CSatalliteTrajectoryDraw::GetVertexArrays(ITrajectory* pITrajectory) const
	{
		const ITrajectory::ListTrajectoryInfo& listTrajectoryInfo = pITrajectory->GetTrajectoryPoint();
		if (listTrajectoryInfo.empty())
		{
			return (NULL);
		}

		size_t siCount = listTrajectoryInfo.size();
		osg::Vec3Array* pVertexArray = new osg::Vec3Array(siCount);

		int nSize = (int)siCount;
		for (int index = 0; index < nSize; ++index)
		{
			// 转换成世界坐标
			osg::Vec3d vWorld = listTrajectoryInfo[index].vEciPos;
		//	CConvert::LatLongHeightToWord(listTrajectoryInfo[index].vGeoPos, vWorld);
			(*pVertexArray)[index] = vWorld;
		}

		return (pVertexArray);
	}

}
