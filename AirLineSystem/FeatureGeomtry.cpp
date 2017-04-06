#include "../../Public/VRSoft.h"
#include "../../Public/AirLineSystem/AirLineSystem.h"
#include "FeatureGeomtry.h"

#include <osgEarthSymbology/AltitudeSymbol>
#include <osgEarthSymbology/LineSymbol>


using namespace osgEarth;
using namespace osgEarth::Symbology;
using namespace osgEarth::Features;
using namespace osgEarth::Annotation;

namespace VR_Soft
{
	// 构造函数
	CFeatureGeomtry::CFeatureGeomtry( OsgEarthGeomtry* pOsgEarthGeomtry )
		:m_pGeomety(pOsgEarthGeomtry),m_pFeatureNode2D(NULL), m_pFeatureNode3D(NULL)
	{
		m_vColor.set(Color::Red.r(), Color::Red.g(), Color::Red.b(), Color::Red.a());

		m_style.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
		m_style.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
		m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

		m_style2D.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
		m_style2D.getOrCreate<LineSymbol>()->stroke()->width() = 3.0f;
		m_style2D.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	}

	// 析构函数
	CFeatureGeomtry::~CFeatureGeomtry( void )
	{
		m_pGeomety->clear();
		if (NULL != m_pFeatureNode2D)
		{
			osg::Node::ParentList& listParent2D = m_pFeatureNode2D->getParents();
			for (int index = 0; index < (int)listParent2D.size(); ++index)
			{
				listParent2D[index]->removeChild(m_pFeatureNode2D);
			}
		}
		
		if (NULL != m_pFeatureNode3D)
		{
			osg::Node::ParentList& listParent3D = m_pFeatureNode3D->getParents();
			for (int index = 0; index < (int)listParent3D.size(); ++index)
			{
				listParent3D[index]->removeChild(m_pFeatureNode3D);
			}
		}
		

		
		//VRSOFT_DELETE(m_pGeomety);

		if (NULL != m_pFeatureNode3D)
		{
			typedef osg::Node::ParentList ParentList;
			ParentList& listParent = m_pFeatureNode3D->getParents();
			int nCount = (int)listParent.size();
			for (int index = 0; index < nCount; ++index)
			{
				listParent[index]->removeChild(m_pFeatureNode3D);
			}
		}

		if (NULL != m_pFeatureNode2D)
		{
			typedef osg::Node::ParentList ParentList;
			ParentList& listParent = m_pFeatureNode2D->getParents();
			int nCount = (int)listParent.size();
			for (int index = 0; index < nCount; ++index)
			{
				listParent[index]->removeChild(m_pFeatureNode2D);
			}
		}

	}

	// 设置颜色
	void CFeatureGeomtry::SetColor( const osg::Vec4& vColor )
	{
		m_vColor = vColor;
		m_style.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
		m_style2D.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
	}

	// 获得颜色
	osg::Vec4 CFeatureGeomtry::GetColor( void ) const
	{
		return (m_vColor);
	}

	// 设置线宽
	void CFeatureGeomtry::SetWidth( const float fWidth )
	{
		m_fWidth = fWidth;
		m_style.getOrCreate<LineSymbol>()->stroke()->width() = m_fWidth;
		m_style2D.getOrCreate<LineSymbol>()->stroke()->width() = m_fWidth;
	}

	// 获得线宽
	float CFeatureGeomtry::GetWidth( void ) const
	{
		return (m_fWidth);
	}

	// 设置贴地技术
	void CFeatureGeomtry::SetTechnique( const IFeatureGeomtry::Technique technique )
	{
		m_tchnique = technique;

		switch (m_tchnique)
		{
		case IFeatureGeomtry::TECHNIQUE_DRAPE:
			{
				m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_DRAPE;
				m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_DRAPE;
			}
			break;

		case IFeatureGeomtry::TECHNIQUE_GPU:
			{
				m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
				m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
			}
			break;
		case IFeatureGeomtry::TECHNIQUE_SCENE:
			{
				m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_SCENE;
				m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_SCENE;
			}
			break;
		case IFeatureGeomtry::TECHNIQUE_MAP:
			{
				m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_MAP;
				m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_MAP;
			}
			break;

		default:
			break;
		}
	}

	// 获得贴地技术
	IFeatureGeomtry::Technique CFeatureGeomtry::GetTechnique( void ) const
	{
		return (m_tchnique);
	}

	// 设置高程
	void CFeatureGeomtry::SetClamping( const IFeatureGeomtry::Clamping clamping )
	{
		m_clamping = clamping;

		switch (m_clamping)
		{
		case IFeatureGeomtry::CLAMP_NONE:
			{
				m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_NONE;
			}
			break;

		case IFeatureGeomtry::CLAMP_TO_TERRAIN:
			{
				m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
			}
			break;
		case IFeatureGeomtry::CLAMP_RELATIVE_TO_TERRAIN:
			{
				m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
			}
			break;
		case IFeatureGeomtry::CLAMP_ABSOLUTE:
			{
				m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_ABSOLUTE;
			}
			break;

		default:
			break;
		}
	}

	// 获得模型嵌入
	IFeatureGeomtry::Clamping CFeatureGeomtry::GetClamping( void ) const
	{
		return (m_clamping);
	}


	// 获得所有点
	std::vector<osg::Vec3d>  CFeatureGeomtry::GetAllPoints(void) const
	{
		std::vector<osg::Vec3d> listPoints;
		if (NULL == m_pGeomety)
		{
			return (listPoints);
		}

		Geometry::const_iterator cstItor = m_pGeomety->begin();
		for (; m_pGeomety->end() != cstItor; ++cstItor)
		{
			listPoints.push_back(*cstItor);
		}

		return (listPoints);
	}

	// 获得索引点
	osg::Vec3d CFeatureGeomtry::GetPoint( const int index )
	{
		int nCount = m_pGeomety->size();
		if (0 > index || index > nCount )
		{
			return (osg::Vec3d(0, 0, 0));
		}

		return ((*m_pGeomety)[index]);
	}

	// 设置点
	void CFeatureGeomtry::SetPoint( const int index, const osg::Vec3d& vPoint )
	{
		int nCount = m_pGeomety->size();
		if (0 > index )
		{
			return ;
		}
		else if (index >= nCount)
		{
			m_pGeomety->push_back(vPoint);
		}
		else
		{
			(*m_pGeomety)[index] = vPoint;
		}
		UpdateDrawable();
		
	}

	// 移除点
	void CFeatureGeomtry::Remove( const int index )
	{
		Geometry::iterator itor = m_pGeomety->begin();
		for (int n = 0;  m_pGeomety->end() != itor; ++n, ++itor)
		{
			if (n == index)
			{
				m_pGeomety->erase(itor);
				break;
			}
		}

		UpdateDrawable();
	}

	// 移除所有的点
	void CFeatureGeomtry::RemoveAll( void )
	{
		m_pGeomety->clear();
		UpdateDrawable();
	}

	// 设置2D地图
	void CFeatureGeomtry::SetMapNode2D( EarthMap* pEarthMap )
	{
		if (NULL == m_pFeatureNode2D)
		{
			m_pFeatureNode2D = new FeatureNode(pEarthMap, new Feature(m_pGeomety, pEarthMap->getMapSRS()->getGeographicSRS()), m_style2D);
			return;
		}

		m_pFeatureNode2D->setMapNode(pEarthMap);
	}

	// 设置3D地图
	void CFeatureGeomtry::SetMapNode3D( EarthMap* pEarthMap )
	{
		if (NULL == m_pFeatureNode3D)
		{
			m_pFeatureNode3D = new FeatureNode(pEarthMap, new Feature(m_pGeomety, pEarthMap->getMapSRS()->getGeographicSRS()), m_style);
			return;
		}

		m_pFeatureNode3D->setMapNode(pEarthMap);
	}

	// 获得渲染节点
	DrawObj* CFeatureGeomtry::GetDrawObj2D( void ) const
	{
		return (m_pFeatureNode2D);
	}

	// 获得渲染节点
	DrawObj* CFeatureGeomtry::GetDrawObj3D( void ) const
	{
		return (m_pFeatureNode3D);
	}

	// 设置渲染体
	void CFeatureGeomtry::SetGeomtry( osgEarth::Symbology::Geometry* pGeomtry )
	{
		m_pGeomety = pGeomtry;
	}

	// 设置所有点
	void CFeatureGeomtry::SetAllPoints( const std::vector<osg::Vec3d>& listPoints )
	{
		RemoveAll();

		typedef std::vector<osg::Vec3d> ListPoints;
		for (ListPoints::const_iterator cstItor = listPoints.begin(); listPoints.end() != cstItor; ++cstItor)
		{
			m_pGeomety->push_back(*cstItor);
		}

		// 更新集合体
		UpdateDrawable();
	}

	// 更新集合体
	void CFeatureGeomtry::UpdateDrawable()
	{
		if (NULL != m_pFeatureNode2D)
		{
			m_pFeatureNode2D->init();
		}
		
		if (NULL != m_pFeatureNode3D)
		{
			m_pFeatureNode3D->init();
		}
	}

}
