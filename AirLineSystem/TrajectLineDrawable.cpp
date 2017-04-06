#include "../../Public/VRSoft.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "TrajectLineDrawable.h"

#include <osg/Geometry>

namespace VR_Soft
{
	CTrajectLineDrawable::CTrajectLineDrawable(void)
		: CAttributeImp<IDrawAttribute>(NULL, "ad"),m_pGeode(new osg::Geode)\
		,m_bUpdate(true),m_pITrajectory(NULL)
	{
	}


	CTrajectLineDrawable::~CTrajectLineDrawable(void)
	{
	}

	// ����
	void CTrajectLineDrawable::Update(void)
	{
		InitDrawabel();
	}

	// �����Ⱦ��
	DrawObj* CTrajectLineDrawable::GetDrawObj(void)
	{
		return (m_pGeode);
	}

	// �����㷨����
	void CTrajectLineDrawable::SetTrajectory(ITrajectory* pITrajectory)
	{
		m_pITrajectory = pITrajectory;
	}

	// ��ʼ����Ⱦ��
	bool CTrajectLineDrawable::InitDrawabel(void)
	{
		assert (NULL != m_pITrajectory);

		m_pGeode->removeDrawables(0, m_pGeode->getNumChildren());

		// ���
		osg::Vec3Array* pVertexArray = GetVertexArrays(m_pITrajectory);
		if (NULL == pVertexArray)
		{
			ILogManager::GetInstance().SetLogMessage("���ߴ���ʧ��", ERROR_EXCEPT);
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

	// ��ö���
	osg::Vec3Array* CTrajectLineDrawable::GetVertexArrays(ITrajectory* pITrajectory) const
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
			// ת������������
			osg::Vec3d vWorld ; //= listTrajectoryInfo[index].vEciPos;
			CConvert::LatLongHeightToWord(listTrajectoryInfo[index].vGeoPos, vWorld);
			(*pVertexArray)[index] = vWorld;
		}

		return (pVertexArray);
	}

}
