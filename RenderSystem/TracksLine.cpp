#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "TracksLine.h"

#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	CTracksLine::CTracksLine(IEntityBase* pIEntityBase)
		:CAttributeImp<IDrawAttribute>(pIEntityBase, "��������Ⱦ����"),m_pGeode(new osg::Geode) \
		,m_nMaxCount(50), m_bShow(true),n_nCurrent(0),m_pLineWidth(new osg::LineWidth(2)),m_bOpenLight(false)
	{
	}


	CTracksLine::~CTracksLine(void)
	{
	}

	void CTracksLine::Init()
	{
		osg::Vec3Array* pVertexArray = new osg::Vec3Array(m_nMaxCount);

		m_pGeomerty = new osg::Geometry;
		m_pGeode->addDrawable(m_pGeomerty);
		m_pGeomerty->setVertexArray(pVertexArray);
		m_pGeomerty->setDataVariance(osg::Object::DYNAMIC);

		osg::Vec4Array* pColorArray = new osg::Vec4Array;
		pColorArray->push_back(osg::Vec4(1, 0, 0, 1));
		m_pGeomerty->setColorArray(pColorArray);
		m_pGeomerty->setColorBinding(osg::Geometry::BIND_OVERALL);
		m_pGeomerty->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, pVertexArray->size()));

		// �����߶δ�С
		m_pGeomerty->getOrCreateStateSet()->setAttribute(m_pLineWidth);
		m_pGeomerty->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		// ��ʾ����
		DEFINITION_PROPERTY(Show, &CTracksLine::SetShow, &CTracksLine::GetShow,"����", "true", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Show, "TRUE", true);
		ADDENUM_PROPERTY(Show, "FALSE", false);

		// ����
		DEFINITION_PROPERTY(Light, &CTracksLine::SetLightOn, &CTracksLine::IsOpenLight,"����", "true", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Light, "TRUE", true);
		ADDENUM_PROPERTY(Light, "FALSE", false);

		// �߿�
		DEFINITION_PROPERTY(LineWidth, &CTracksLine::SetLineWidth, &CTracksLine::GetLineWidth,"�߿�", "", "", CTRL_EDIT);
	}

	// ����
	void CTracksLine::Update(void)
	{
		// ��û��������е�λ������
		IEntityDrawAttribute* pIEntityDrawAttribute = GetEntity()->GetEntityDrawAttribute();
		if (NULL == pIEntityDrawAttribute)
		{
			return;
		}
		osg::Vec3d vGeo = pIEntityDrawAttribute->GetPosition();

		// ת������������
		osg::Vec3d vWorld;
		CConvert::LatLongHeightToWord(vGeo, vWorld);

		// ��ӵ���Ⱦ����
		AddPoint(vWorld);

		// ������Ⱦ��
		UpdateGeomerty();
	}

	// �����Ⱦ��
	DrawObj* CTracksLine::GetDrawObj(void)
	{
		return (m_pGeode);
	}

	// �Ƿ������ƶ�
	bool CTracksLine::IsMove(void) const
	{
		return (false);
	}

	// �����Ƿ�����
	void CTracksLine::SetShow(bool bShow)
	{
		m_bShow = bShow;
		if (!m_bShow)
		{
			m_pGeode->setNodeMask(0x00);
		}
		else
		{
			m_pGeode->setNodeMask(0x01);
		}
	}

	// ����Ƿ�����
	bool CTracksLine::GetShow(void) const
	{
		return (m_bShow);
	}

	// �����߿�
	void CTracksLine::SetLineWidth(int nWidth)
	{
		m_pLineWidth->setWidth(nWidth);
	}

	// ����߿�
	int CTracksLine::GetLineWidth(void) const
	{
		return ((int)m_pLineWidth->getWidth());
	}

	// �Ƿ�򿪹���
	void CTracksLine::SetLightOn(bool bOn)
	{
		m_bOpenLight = bOn;
		if (m_bOpenLight)
		{
			m_pGeomerty->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		}
		else
		{
			m_pGeomerty->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		}
	}

	// ��ù���״̬
	bool CTracksLine::IsOpenLight(void) const
	{
		return (m_bOpenLight); 
	}

	// ��ӵ�������Ⱦ����
	void CTracksLine::AddPoint(const osg::Vec3f& vWorld)
	{
		// �����Ⱦ���ж���ĸ���
		osg::Vec3Array* pVertexArray = (osg::Vec3Array*)m_pGeomerty->getVertexArray();
		//int nCurrentCount = (int)pVertexArray->size();
		if (n_nCurrent >( m_nMaxCount - 1))
		{
			for (int index = 0; index < n_nCurrent - 1; ++index)
			{
				(*pVertexArray)[index] = (*pVertexArray)[index + 1];
			}

			--n_nCurrent;
		}

		// ����ֵ
		(*pVertexArray)[n_nCurrent++] = vWorld;

		m_pGeomerty->setVertexArray(pVertexArray);
	}

	// ������Ⱦ��
	void CTracksLine::UpdateGeomerty(void)
	{
		// �����Ⱦ���ж���ĸ���
		osg::Vec3Array* pVertexArray = (osg::Vec3Array*)m_pGeomerty->getVertexArray();
		int nCurrentCount = (int)pVertexArray->size();

		// ������Ⱦ��
		osg::DrawArrays* pDrawArray = (osg::DrawArrays*)m_pGeomerty->getPrimitiveSet(0);
		pDrawArray->set(GL_LINE_STRIP, 0, n_nCurrent);
		/*	pDrawArray->setCount(n_nCurrent);
		pDrawArray->setFirst(0);*/
		pDrawArray->dirty();
		//m_pGeode->dirtyBound();
	}

}
