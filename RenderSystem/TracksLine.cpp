#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "TracksLine.h"

#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	CTracksLine::CTracksLine(IEntityBase* pIEntityBase)
		:CAttributeImp<IDrawAttribute>(pIEntityBase, "航迹线渲染属性"),m_pGeode(new osg::Geode) \
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

		// 设置线段大小
		m_pGeomerty->getOrCreateStateSet()->setAttribute(m_pLineWidth);
		m_pGeomerty->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		// 显示隐藏
		DEFINITION_PROPERTY(Show, &CTracksLine::SetShow, &CTracksLine::GetShow,"显隐", "true", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Show, "TRUE", true);
		ADDENUM_PROPERTY(Show, "FALSE", false);

		// 光照
		DEFINITION_PROPERTY(Light, &CTracksLine::SetLightOn, &CTracksLine::IsOpenLight,"光照", "true", "", CTRL_COMBOX);
		ADDENUM_PROPERTY(Light, "TRUE", true);
		ADDENUM_PROPERTY(Light, "FALSE", false);

		// 线宽
		DEFINITION_PROPERTY(LineWidth, &CTracksLine::SetLineWidth, &CTracksLine::GetLineWidth,"线宽", "", "", CTRL_EDIT);
	}

	// 更新
	void CTracksLine::Update(void)
	{
		// 获得基础属性中的位置属性
		IEntityDrawAttribute* pIEntityDrawAttribute = GetEntity()->GetEntityDrawAttribute();
		if (NULL == pIEntityDrawAttribute)
		{
			return;
		}
		osg::Vec3d vGeo = pIEntityDrawAttribute->GetPosition();

		// 转换成世界坐标
		osg::Vec3d vWorld;
		CConvert::LatLongHeightToWord(vGeo, vWorld);

		// 添加到渲染体中
		AddPoint(vWorld);

		// 更新渲染体
		UpdateGeomerty();
	}

	// 获得渲染体
	DrawObj* CTracksLine::GetDrawObj(void)
	{
		return (m_pGeode);
	}

	// 是否随着移动
	bool CTracksLine::IsMove(void) const
	{
		return (false);
	}

	// 设置是否隐藏
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

	// 获得是否隐藏
	bool CTracksLine::GetShow(void) const
	{
		return (m_bShow);
	}

	// 设置线宽
	void CTracksLine::SetLineWidth(int nWidth)
	{
		m_pLineWidth->setWidth(nWidth);
	}

	// 获得线宽
	int CTracksLine::GetLineWidth(void) const
	{
		return ((int)m_pLineWidth->getWidth());
	}

	// 是否打开光照
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

	// 获得光照状态
	bool CTracksLine::IsOpenLight(void) const
	{
		return (m_bOpenLight); 
	}

	// 添加点数到渲染体中
	void CTracksLine::AddPoint(const osg::Vec3f& vWorld)
	{
		// 获得渲染体中顶点的个数
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

		// 设置值
		(*pVertexArray)[n_nCurrent++] = vWorld;

		m_pGeomerty->setVertexArray(pVertexArray);
	}

	// 更新渲染体
	void CTracksLine::UpdateGeomerty(void)
	{
		// 获得渲染体中顶点的个数
		osg::Vec3Array* pVertexArray = (osg::Vec3Array*)m_pGeomerty->getVertexArray();
		int nCurrentCount = (int)pVertexArray->size();

		// 更新渲染体
		osg::DrawArrays* pDrawArray = (osg::DrawArrays*)m_pGeomerty->getPrimitiveSet(0);
		pDrawArray->set(GL_LINE_STRIP, 0, n_nCurrent);
		/*	pDrawArray->setCount(n_nCurrent);
		pDrawArray->setFirst(0);*/
		pDrawArray->dirty();
		//m_pGeode->dirtyBound();
	}

}
