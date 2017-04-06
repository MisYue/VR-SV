#include "../../Public/PlotSystem/PlotSystem.h"
#include "PlotPlaceGeomtry.h"

#include <osgEarthSymbology/AltitudeSymbol>
#include <osgEarthSymbology/LineSymbol>
#include <osgEarthSymbology/TextSymbol>
#include <osgEarthSymbology/IconSymbol>


using namespace osgEarth;
using namespace osgEarth::Symbology;
using namespace osgEarth::Annotation;

namespace VR_Soft
{
	// 构造函数
	CPlotPlaceGeomtry::CPlotPlaceGeomtry(void)
		:m_pPlaceNode2D(NULL), m_pPlaceNode3D(NULL)
	{
		m_vColor.set(Color::Red.r(), Color::Red.g(), Color::Red.b(), Color::Red.a());

		m_style.getOrCreate<TextSymbol>()->fill()->color() = m_vColor.asRGBA();
		m_style.getOrCreate<TextSymbol>()->size() = 12.0f;
		m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
		m_style.getOrCreate<TextSymbol>()->encoding() = TextSymbol::ENCODING_UTF8;

		m_style2D.getOrCreate<TextSymbol>()->fill()->color() = m_vColor.asRGBA();
		m_style2D.getOrCreate<TextSymbol>()->size() = 12.0f;
		m_style2D.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
		m_style2D.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
		m_style2D.getOrCreate<TextSymbol>()->encoding() = TextSymbol::ENCODING_UTF8;
	}

	// 析构函数
	CPlotPlaceGeomtry::~CPlotPlaceGeomtry( void )
	{
		osg::Node::ParentList& listParent2D = m_pPlaceNode2D->getParents();
		for (int index = 0; index < (int)listParent2D.size(); ++index)
		{
			listParent2D[index]->removeChild(m_pPlaceNode2D);
		}

		osg::Node::ParentList& listParent3D = m_pPlaceNode3D->getParents();
		for (int index = 0; index < (int)listParent3D.size(); ++index)
		{
			listParent3D[index]->removeChild(m_pPlaceNode3D);
		}

		//VRSOFT_DELETE(m_pGeomety);

		if (NULL != m_pPlaceNode3D)
		{
			typedef osg::Node::ParentList ParentList;
			ParentList& listParent = m_pPlaceNode3D->getParents();
			int nCount = (int)listParent.size();
			for (int index = 0; index < nCount; ++index)
			{
				listParent[index]->removeChild(m_pPlaceNode3D);
			}
		}

		if (NULL != m_pPlaceNode2D)
		{
			typedef osg::Node::ParentList ParentList;
			ParentList& listParent = m_pPlaceNode2D->getParents();
			int nCount = (int)listParent.size();
			for (int index = 0; index < nCount; ++index)
			{
				listParent[index]->removeChild(m_pPlaceNode2D);
			}
		}

	}

	// 设置颜色
	void CPlotPlaceGeomtry::SetColor( const osg::Vec4& vColor )
	{
		m_vColor = vColor;
		m_style.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
		m_style2D.getOrCreate<LineSymbol>()->stroke()->color() = m_vColor.asRGBA();
	}

	// 获得颜色
	osg::Vec4 CPlotPlaceGeomtry::GetColor( void ) const
	{
		return (m_vColor);
	}

	// 设置线宽
	void CPlotPlaceGeomtry::SetWidth( const float fWidth )
	{
		m_fWidth = fWidth;
		m_style.getOrCreate<LineSymbol>()->stroke()->width() = m_fWidth;
		m_style2D.getOrCreate<LineSymbol>()->stroke()->width() = m_fWidth;
	}

	// 获得线宽
	float CPlotPlaceGeomtry::GetWidth( void ) const
	{
		return (m_fWidth);
	}

	// 设置贴地技术
	void CPlotPlaceGeomtry::SetTechnique( const IFeatureGeomtry::Technique technique )
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
	IFeatureGeomtry::Technique CPlotPlaceGeomtry::GetTechnique( void ) const
	{
		return (m_tchnique);
	}

	// 设置高程
	void CPlotPlaceGeomtry::SetClamping( const IFeatureGeomtry::Clamping clamping )
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
	IFeatureGeomtry::Clamping CPlotPlaceGeomtry::GetClamping( void ) const
	{
		return (m_clamping);
	}


	// 获得所有点
	std::vector<osg::Vec3d>  CPlotPlaceGeomtry::GetAllPoints(void) const
	{
		std::vector<osg::Vec3d> listPoints;
		return (listPoints);
	}

	// 获得索引点
	osg::Vec3d CPlotPlaceGeomtry::GetPoint( const int index )
	{
		if (NULL != m_pPlaceNode3D)
		{
			osgEarth::GeoPoint gp = m_pPlaceNode3D->getPosition();
			return (osg::Vec3d(gp.x(), gp.y(), gp.z()));
		}
		else if (NULL != m_pPlaceNode2D)
		{
			osgEarth::GeoPoint gp = m_pPlaceNode2D->getPosition();
			return (osg::Vec3d(gp.x(), gp.y(), gp.z()));
		}

		return (osg::Vec3d(0, 0, 0));
	}

	// 设置点
	void CPlotPlaceGeomtry::SetPoint( const int index, const osg::Vec3d& vPoint )
	{
		if (NULL != m_pPlaceNode2D)
		{
			m_pPlaceNode2D->setPosition(GeoPoint(m_pPlaceNode2D->getMapNode()->getMapSRS()->getGeodeticSRS() , vPoint.x(), vPoint.y()));
		}
		if (NULL != m_pPlaceNode3D)
		{
				m_pPlaceNode3D->setPosition(GeoPoint(m_pPlaceNode3D->getMapNode()->getMapSRS()->getGeodeticSRS() , vPoint.x(), vPoint.y(), vPoint.z()));
		}
		
	//	UpdateDrawable();

	}

	// 移除点
	void CPlotPlaceGeomtry::Remove( const int index )
	{
		return;
	}

	// 移除所有的点
	void CPlotPlaceGeomtry::RemoveAll( void )
	{
		
		UpdateDrawable();
	}

	// 设置2D地图
	void CPlotPlaceGeomtry::SetMapNode2D( EarthMap* pEarthMap )
	{
		if (NULL == m_pPlaceNode2D)
		{
			m_pPlaceNode2D = new PlaceNode(pEarthMap, GeoPoint(),m_style2D, NULL);
			return;
		}

		m_pPlaceNode2D->setMapNode(pEarthMap);
	}

	// 设置3D地图
	void CPlotPlaceGeomtry::SetMapNode3D( EarthMap* pEarthMap )
	{
		if (NULL == m_pPlaceNode3D)
		{
			m_pPlaceNode3D = new PlaceNode(pEarthMap, GeoPoint( ),m_style, NULL);
			return;
		}

		m_pPlaceNode3D->setMapNode(pEarthMap);
	}

	// 获得渲染节点
	DrawObj* CPlotPlaceGeomtry::GetDrawObj2D( void ) const
	{
		return (m_pPlaceNode2D);
	}

	// 获得渲染节点
	DrawObj* CPlotPlaceGeomtry::GetDrawObj3D( void ) const
	{
		return (m_pPlaceNode3D);
	}

	// 设置文字
	void CPlotPlaceGeomtry::SetText(const VRString& strText)
	{
		if (NULL != m_pPlaceNode3D)
		{
			m_pPlaceNode3D->setText(CVRStringUtil::GB2312ToUTF8(strText));
		}
		if (NULL != m_pPlaceNode2D)
		{
			m_pPlaceNode2D->setText(CVRStringUtil::GB2312ToUTF8(strText));
		}
	}

	// 设置图标
	void CPlotPlaceGeomtry::SetIcon(const VRString& strIcon)
	{
		if (NULL != m_pPlaceNode3D)
		{
			osg::Image* pImage = osgDB::readImageFile(strIcon);
			m_style.getOrCreate<IconSymbol>()->setImage(pImage);
			m_pPlaceNode3D->setStyle(m_style);
		}
		if (NULL != m_pPlaceNode2D)
		{
			m_style2D.getOrCreate<IconSymbol>()->url()->setLiteral(strIcon);
			m_pPlaceNode2D->setStyle(m_style);
		}
	}

	// 设置渲染体
	void CPlotPlaceGeomtry::SetGeomtry( osgEarth::Symbology::Geometry* pGeomtry )
	{
		//m_pGeomety = pGeomtry;
	}

	// 设置所有点
	void CPlotPlaceGeomtry::SetAllPoints( const std::vector<osg::Vec3d>& listPoints )
	{
		RemoveAll();

		/*typedef std::vector<osg::Vec3d> ListPoints;
		for (ListPoints::const_iterator cstItor = listPoints.begin(); listPoints.end() != cstItor; ++cstItor)
		{
			m_pGeomety->push_back(*cstItor);
		}
*/
		// 更新集合体
		UpdateDrawable();
	}

	// 更新集合体
	void CPlotPlaceGeomtry::UpdateDrawable()
	{
		/*if (NULL != m_pPlaceNode2D)
		{
			m_pPlaceNode2D->init();
		}

		if (NULL != m_pPlaceNode3D)
		{
			m_pPlaceNode3D->init();
		}*/
	}

	// 获得3D地图
	/*EarthMap* CPlotPlaceGeomtry::GetMap3D( void )
	{
	if (NULL == m_pPlaceNode3D)
	{
	return (NULL);
	}

	return (m_pPlaceNode3D->getMapNode());
	}*/


}
