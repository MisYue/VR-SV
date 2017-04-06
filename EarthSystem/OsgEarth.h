/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth对象		                                            */
/* 时间： 2016-07-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _OSGEARTH_H_
#define _OSGEARTH_H_

#pragma once

#include <boost/regex.hpp>
#include <osgEarth/MapNode>
#include <osgEarthUtil/GraticuleNode>
#include <osgEarthUtil/AutoClipPlaneHandler>

namespace VR_Soft
{
	class IRenderView;

	class COsgEarth : public IEarth
	{
	public:
		explicit COsgEarth(void);
		virtual ~COsgEarth(void);

	public:
		// 添加视图
		virtual void Attach(IRenderView* pIRenderView);
		// 获得对应的地球节点
		virtual EarthMap* GetEarthMap(void) const;
		// 显示网格线
		void SetGraticuleState(bool bShow);
		// 获得网格线是否显示
		bool GetGraticuleState(void) const;
		

	public:
		// 添加实体到数字地球场景中
		virtual void AddEntity(IEntityBase* pIEntity) = 0;
		// 添加几何渲染体
		virtual void AddFeatureGeomtry(const IFeatureGeomtry* pIFeatureGoemtry) = 0;

	public:
		// 获得视图
		IRenderView* GetRenderView(void) const;
		// 获得视图名称
		inline const VRString& GetRenderName(void) const { return (m_strViewName); }
		// 配置地球数据
		virtual osgEarth::MapNode* InitMapNode(osgEarth::MapNode* pNodeMap);

	protected:
		// 获得根节点
		virtual osg::Group* GetRoot(void) const ;
		

	protected:
		osgEarth::MapNode* m_pMapNode;
		osgEarth::Util::GraticuleNode* m_pGraticuleNode;
		osg::Group* m_pRoot;
		VRString m_strViewName;
		osg::Camera* m_pCamera;
	};

/////////////////////////////创建地球/////////////////////////////////////////////
	class COsgEarth2D;
	class COsgEarth3D;

	class CEarthFactory
	{
	public: 
		// 创建2D地图
		static COsgEarth* CreateEarth2D(osgEarth::MapNode* pMapNode);
		// 创建3D地图
		static COsgEarth* CreateEarth3D(osgEarth::MapNode* pMapNode);
	};
}


#endif // !_OSGEARTH_H_