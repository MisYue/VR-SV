/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地球图层管理 负责23D图层同步管理								*/
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _EARTHLAYERMANAGER_H_
#define _EARTHLAYERMANAGER_H_

#pragma once

#include <osgEarth/Map>
#include <osgEarthUtil/GraticuleNode>
#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	// 地球图层
	class CEarthLayer : public IEarthLayer
	{
	public: 
		// 构造函数
		CEarthLayer(osgEarth::Layer* pLayer, LayerType lt);
		// 析构函数
		virtual ~CEarthLayer(void);

	public:
		// 设置图层名称
		virtual void SetLayerName(const VRString& strLayerName);
		// 获得图层名称
		virtual VRString GetLayerName(void) const ;
		// 获得图层路径
		virtual VRString GetLayerPath(void) const ;
		// 设置图层透明度
		virtual void SetOpacity(float fOpacity) ;
		// 获得透明度
		virtual float GetOpacity(void) const;
		// 设置显示状态
		virtual void SetVisible(bool bValue) ;
		// 获得显示状态
		virtual bool GetVisible(void) const ;
		// 获得图层类型
		virtual LayerType GetLayerType(void) const ;

	public:
		osgEarth::Layer* GetLayer(void) { return (m_pLayer); }

	private:
		osgEarth::Layer* m_pLayer; // 图层指针
		LayerType m_lt; // 类型
		VRString m_strName; // 图层名称
	};


	//////////////////////////////////////////////////////////////////////////
	class CEarthLayerManager : public IEarthLayerManager
	{
	public:
		// 构造函数
		CEarthLayerManager(void);
		// 析构函数
		virtual ~CEarthLayerManager(void);

	public: 
		// 创建图层
		virtual IEarthLayer* CreateEarthLayer(const VRString& strLayerPath, LayerType lt);
		// 查找图层
		virtual ListEarthLayers FindEarthLayer(const VRString& strEarthLayerName) const ;
		// 查找图层
		virtual IEarthLayer* FindEarthLayer(const int ID) const ;
		// 删除图层
		virtual void RemoveEarthLayer(const int ID) ;
		// 删除图层
		virtual void RemoveEarthLayer(IEarthLayer* pIEarthLayer) ;
		// 获得所有的图层
		virtual ListEarthLayers GetAllLayer(void) ;

	public:
		// 设置三维地图
		void SetEarthMap2D(osgEarth::MapNode* pMapNode);
		// 设置三维地图
		void SetEarthMap3D(osgEarth::MapNode* pMapNode);
		// 添加影像图层
		void AddImageLayer(osgEarth::ImageLayer* pImageLayer);
		// 移除影像图层
		void RemoveImagerLayer(osgEarth::ImageLayer* imageLayer);
		// 添加高程图层
		void AddElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
		// 移除高程图层
		void RemoveElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
		// 添加模型图层
		void AddModelLayer(osgEarth::ModelLayer* pModelLayer);
		// 移除模型图层
		void RemoveModelLayer( osgEarth::ModelLayer* pModelLayer );

	protected:
		// 添加影像图层
		void AddImageLayer(osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer);
		// 移除影像图层
		void RemoveImagerLayer(osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer);
		// 添加高程图层
		void AddElevationLayer(osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer);
		// 移除高程图层
		void RemoveElevationLayer(osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer);
		// 添加图层进入
		void AddEarthLayer( const int ID, CEarthLayer* pEarthLayer );
		
	private:
		osgEarth::Map* m_pEarthMap2D;
		osgEarth::Map* m_pEarthMap3D;
		//osgEarth::Util::GraticuleNode* m_pGraticuleNode;
		typedef boost::unordered_map<int, IEarthLayer*> ListIDEarthLayers;
		ListIDEarthLayers m_listIDEarthLayers;
	};

}

#endif // !_EARTHLAYERMANAGER_H_