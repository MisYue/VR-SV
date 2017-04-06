#include "../../Public/EarthSystem/EarthSystem.h"
#include "EarthLayerManager.h"

#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgDB/FileUtils>
#include <osgDB/FileNameUtils>

#include <boost/foreach.hpp>

namespace VR_Soft
{
	// 构造函数
	CEarthLayer::CEarthLayer( osgEarth::Layer* pLayer, LayerType lt )
		:m_pLayer(pLayer), m_lt(lt), m_strName("")
	{
		if (IMAGET_TYPE == m_lt)
		{
			m_strName = (((osgEarth::ImageLayer*)m_pLayer)->getName());
		}
		else if (ELEVATION_TYPE == m_lt)
		{
			m_strName = (((osgEarth::ElevationLayer*)m_pLayer)->getName());
		}
		else
		{
			m_strName = (((osgEarth::ModelLayer*)m_pLayer)->getName());
		}

	}

	// 析构函数
	CEarthLayer::~CEarthLayer( void )
	{

	}

	// 设置图层名称
	void CEarthLayer::SetLayerName( const VRString& strLayerName )
	{
		if (IMAGET_TYPE == m_lt)
		{
			((osgEarth::ImageLayer*)m_pLayer)->setName(strLayerName);
		}
		else if (ELEVATION_TYPE == m_lt)
		{
			((osgEarth::ElevationLayer*)m_pLayer)->setName(strLayerName);
		}
		
		m_strName = strLayerName;
	}

	// 获得图层名称
	VRString CEarthLayer::GetLayerName( void ) const
	{
		return (m_strName);
	}

	// 获得图层路径
	VRString CEarthLayer::GetLayerPath( void ) const
	{
		return ("");
	}

	// 设置图层透明度
	void CEarthLayer::SetOpacity( float fOpacity )
	{

	}

	// 获得透明度
	float CEarthLayer::GetOpacity( void ) const
	{
		return (1.0f);
	}

	// 设置显示状态
	void CEarthLayer::SetVisible( bool bValue )
	{
		if (IMAGET_TYPE == m_lt)
		{
			((osgEarth::ImageLayer*)m_pLayer)->setVisible(bValue);
		}
		else if (ELEVATION_TYPE == m_lt)
		{
			((osgEarth::ElevationLayer*)m_pLayer)->setVisible(bValue);
		}
		else if (FEARTRUE_TYPE == m_lt)
		{
			((osgEarth::ModelLayer*)m_pLayer)->setVisible(bValue);
		}
	}

	// 获得显示状态
	bool CEarthLayer::GetVisible( void ) const
	{
		return (true);
	}

	// 获得图层类型
	LayerType CEarthLayer::GetLayerType( void ) const
	{
		return (m_lt);
	}

	
	//////////////////////////////////////////////////////////////////////////

	// 构造函数
	CEarthLayerManager::CEarthLayerManager(void)
		:m_pEarthMap2D(NULL),m_pEarthMap3D(NULL)
	{
	}

	// 析构函数
	CEarthLayerManager::~CEarthLayerManager(void)
	{
	}

	// 设置三维地图
	void CEarthLayerManager::SetEarthMap3D( osgEarth::MapNode* pMapNode )
	{
		m_pEarthMap3D = pMapNode->getMap();

		// 获得所有图层
		int nCount = m_pEarthMap3D->getNumImageLayers();
		for (int index = 0; index < nCount; ++index)
		{
			osgEarth::ImageLayer* pImageLayer = m_pEarthMap3D->getImageLayerAt(index);
			CEarthLayer* pLayer = new CEarthLayer(pImageLayer, IMAGET_TYPE);
			AddEarthLayer(pImageLayer->getUID(), pLayer);
	
		}

		nCount = m_pEarthMap3D->getNumElevationLayers();
		for (int index = 0; index < nCount; ++index)
		{
			osgEarth::ElevationLayer* pElevationLayer = m_pEarthMap3D->getElevationLayerAt(index);
			CEarthLayer* pLayer = new CEarthLayer(pElevationLayer, ELEVATION_TYPE);
			AddEarthLayer(pElevationLayer->getUID(), pLayer);
		}

		nCount = m_pEarthMap3D->getNumModelLayers();
		for (int index = 0; index < nCount; ++index)
		{
			osgEarth::ModelLayer* pModelLayer = m_pEarthMap3D->getModelLayerAt(index);
			CEarthLayer* pLayer = new CEarthLayer(pModelLayer, FEARTRUE_TYPE);
			AddEarthLayer(pModelLayer->getUID(), pLayer);
		}



	}

	// 添加影像图层
	void CEarthLayerManager::AddImageLayer( osgEarth::ImageLayer* pImageLayer )
	{

		if (NULL != m_pEarthMap3D)
		{
			AddImageLayer(m_pEarthMap3D, pImageLayer );
		}

		if (NULL != m_pEarthMap2D)
		{
			AddImageLayer(m_pEarthMap2D, pImageLayer );
		}
	}

	// 添加影像图层
	void CEarthLayerManager::AddImageLayer( osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer )
	{
		pMap->beginUpdate();
		pMap->addImageLayer(pImageLayer);
		pMap->endUpdate();
	}

	// 移除影像图层
	void CEarthLayerManager::RemoveImagerLayer( osgEarth::ImageLayer* imageLayer )
	{
		if (NULL != m_pEarthMap3D)
		{
			RemoveImagerLayer(m_pEarthMap3D, imageLayer);
		}

		if (NULL != m_pEarthMap2D)
		{
			RemoveImagerLayer(m_pEarthMap2D, imageLayer);
		}
	}

	// 移除影像图层
	void CEarthLayerManager::RemoveImagerLayer( osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer )
	{
		pMap->removeImageLayer(pImageLayer);
	}

	// 添加高程图层
	void CEarthLayerManager::AddElevationLayer( osgEarth::ElevationLayer* pElevationLayer )
	{
		if (NULL != m_pEarthMap3D)
		{
			AddElevationLayer(m_pEarthMap3D, pElevationLayer);
		}

	/*	if (NULL != m_pEarthMap2D)
		{
			AddElevationLayer(m_pEarthMap2D, pElevationLayer);
		}*/
	}


	// 添加高程图层
	void CEarthLayerManager::AddElevationLayer( osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer )
	{
		pMap->addElevationLayer(pElevationLayer);
	}

	// 移除高程图层
	void CEarthLayerManager::RemoveElevationLayer( osgEarth::ElevationLayer* pElevationLayer )
	{
		if (NULL != m_pEarthMap3D)
		{
			RemoveElevationLayer(m_pEarthMap3D, pElevationLayer);
		}
	}

	// 移除高程图层
	void CEarthLayerManager::RemoveElevationLayer( osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer )
	{
		pMap->removeElevationLayer(pElevationLayer);
	}

	// 创建图层
	IEarthLayer* CEarthLayerManager::CreateEarthLayer( const VRString& strLayerPath, LayerType lt )
	{
		osgEarth::Layer* pLayer = NULL;
		if (IMAGET_TYPE == lt)
		{
			osgEarth::Drivers::GDALOptions gdalOption;
			gdalOption.url() = strLayerPath;
			gdalOption.tileSize() = 15;
			gdalOption.maxDataLevel() = 5;

			VRString fileName = osgDB::getSimpleFileName(strLayerPath);
			pLayer = new osgEarth::ImageLayer(osgEarth::ImageLayerOptions(fileName, gdalOption));
			AddImageLayer((osgEarth::ImageLayer*)pLayer);
			
		}
		else if (ELEVATION_TYPE == lt)
		{
			osgEarth::Drivers::GDALOptions gdalOption;
			gdalOption.url() = strLayerPath;
			gdalOption.tileSize() = 15;

			VRString fileName = osgDB::getSimpleFileName(strLayerPath);
			pLayer = new osgEarth::ElevationLayer(osgEarth::ElevationLayerOptions(fileName, gdalOption));
			AddElevationLayer((osgEarth::ElevationLayer*)pLayer);
		}
		else 
		{
			osgEarth::Drivers::OGRFeatureOptions featureOptions;
			featureOptions.url() = strLayerPath;
			osgEarth::Symbology::Style style;

			osgEarth::Symbology::LineSymbol* ls = style.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>();
			ls->stroke()->color() = osgEarth::Symbology::Color::Yellow;
			ls->stroke()->width() = 2.0f;
			
			
			osgEarth::Symbology::AltitudeSymbol* alt = style.getOrCreateSymbol<osgEarth::Symbology::AltitudeSymbol>();
			/*	alt->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
			alt->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_GPU;*/
			 style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->verticalOffset() = osgEarth::Symbology::NumericExpression( 1000.0 );

			 style.getOrCreate<osgEarth::Symbology::RenderSymbol>()->lighting() = false; // osgEarth::as<bool>(c.value(), *defaults.lighting());

			osgEarth::Drivers::FeatureGeomModelOptions geomOptions;
			geomOptions.featureOptions() = featureOptions;
			geomOptions.styles() = new osgEarth::StyleSheet();
			geomOptions.styles()->addStyle( style );
			geomOptions.enableLighting() = false;

			osgEarth::ModelLayerOptions layerOptions(strLayerPath, geomOptions );
			pLayer =  new osgEarth::ModelLayer(layerOptions);
			AddModelLayer((osgEarth::ModelLayer*)pLayer);
		}

		CEarthLayer* pEarthLayer = new CEarthLayer(pLayer, lt);
		
		// 添加图层进入
		AddEarthLayer(pLayer->getUID(), pEarthLayer);

		return (pEarthLayer);
	}

	// 添加图层进入
	void CEarthLayerManager::AddEarthLayer(const int ID, CEarthLayer* pEarthLayer )
	{
		ListIDEarthLayers::const_iterator cstItor = m_listIDEarthLayers.find(ID);
		if (m_listIDEarthLayers.end() != cstItor)
		{
			return;
		}

		m_listIDEarthLayers.insert(ListIDEarthLayers::value_type(ID, pEarthLayer));
	}

	// 获得所有的图层
	IEarthLayerManager::ListEarthLayers CEarthLayerManager::GetAllLayer( void )
	{
		ListEarthLayers listEarthLayer;

		typedef ListIDEarthLayers::value_type ValueType;
		BOOST_FOREACH(ValueType v, m_listIDEarthLayers)
		{
			listEarthLayer.push_back(v.second);
		}


		return (listEarthLayer);
	}

	// 查找图层
	IEarthLayerManager::ListEarthLayers CEarthLayerManager::FindEarthLayer( const VRString& strEarthLayerName ) const
	{
		ListEarthLayers listEartyLayers;

		typedef ListIDEarthLayers::value_type ValueType;
		BOOST_FOREACH(ValueType v, m_listIDEarthLayers)
		{
			if (0 == strEarthLayerName.compare(v.second->GetLayerName()))
			{
				listEartyLayers.push_back(v.second);
			}
		}

		return (listEartyLayers);
	}

	// 查找图层
	IEarthLayer* CEarthLayerManager::FindEarthLayer( const int ID ) const
	{
		ListIDEarthLayers::const_iterator cstItor = m_listIDEarthLayers.find(ID);
		if (m_listIDEarthLayers.end() == cstItor)
		{
			return (NULL);
		}

		return (cstItor->second);
	}

	// 删除图层
	void CEarthLayerManager::RemoveEarthLayer( const int ID )
	{
		ListIDEarthLayers::iterator itor = m_listIDEarthLayers.find(ID);
		if (m_listIDEarthLayers.end() == itor)
		{
			return ;
		}

		CEarthLayer* pEarthLayer = (CEarthLayer*)itor->second;

		if (pEarthLayer->GetLayerType() == IMAGET_TYPE)
		{
			RemoveImagerLayer((osgEarth::ImageLayer*)pEarthLayer->GetLayer());
		}
		else if (pEarthLayer->GetLayerType() == ELEVATION_TYPE)
		{
			RemoveElevationLayer((osgEarth::ElevationLayer*)pEarthLayer->GetLayer());
		}
		else
		{
			RemoveModelLayer((osgEarth::ModelLayer*)pEarthLayer->GetLayer());
		}

		VRSOFT_DELETE(pEarthLayer);
		m_listIDEarthLayers.erase(itor);
	}

	// 删除图层
	void CEarthLayerManager::RemoveEarthLayer( IEarthLayer* pIEarthLayer )
	{
		RemoveEarthLayer(((CEarthLayer*)pIEarthLayer)->GetLayer()->getUID());
	}

	void CEarthLayerManager::RemoveModelLayer( osgEarth::ModelLayer* pModelLayer )
	{
		if (NULL != m_pEarthMap3D)
		{
			m_pEarthMap3D->removeModelLayer(pModelLayer);
		}
		if (NULL != m_pEarthMap2D)
		{
			m_pEarthMap2D->removeModelLayer(pModelLayer);
		}
	}

	// 添加模型图层
	void CEarthLayerManager::AddModelLayer( osgEarth::ModelLayer* pModelLayer )
	{
		if (NULL != m_pEarthMap3D)
		{
			m_pEarthMap3D->addModelLayer(pModelLayer);
		}

		if (NULL != m_pEarthMap2D)
		{
			m_pEarthMap2D->addModelLayer(pModelLayer);
		}
	}

	// 设置三维地图
	void CEarthLayerManager::SetEarthMap2D( osgEarth::MapNode* pMapNode )
	{
		m_pEarthMap2D = pMapNode->getMap();
	}


}
