/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth3D对象		                                        */
/* 时间： 2016-06-30                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _OSGEARTH3D_H_
#define _OSGEARTH3D_H_

#pragma once

#include "OsgEarth.h"

#include <osgEarthUtil/MeasureTool>
#include <osgEarthUtil/Controls>
#include <osgEarthUtil/Sky>


namespace VR_Soft
{
	class CSynchroManipulator;

	class COsgEarth3D : public COsgEarth
	{
	public:
		explicit COsgEarth3D();
		~COsgEarth3D(void);

	public:
		// 添加视图
		virtual void Attach(IRenderView* pIRenderView);

	public:
		// 添加实体
		virtual void AddEntity(IEntityBase* pIEntity);
		// 添加几何渲染体
		virtual void AddFeatureGeomtry(const IFeatureGeomtry* pIFeatureGoemtry);
		// 配置地球数据
		virtual osgEarth::MapNode* InitMapNode(osgEarth::MapNode* pNodeMap);

	protected:
		// 初始化地球相关工具
		void InitEarthTool(IRenderView* pIRenderView);

	public:
		// 添加天空盒子
		void AddSkyBox(osgEarth::MapNode* pMapNode );
		// 添加指北针
		void AddNorthArrow(CSynchroManipulator* pSynchroManip, IRenderView* pIView );
		// 量算开关
		void DistanceEnable( bool bEnable );
		// 获得量算功能开关
		bool GetDistanceEnable(void) const;

	private:
		osg::ref_ptr<osgEarth::Util::MeasureToolHandler> m_pMeasureToolHandler;
		osgViewer::View* m_pView;
		osgEarth::Util::Controls::ControlCanvas* m_pCanvas;
		bool m_bDistanceEnable; // 量算开关标志

		osg::ref_ptr<osgEarth::Util::SkyNode> m_pSkyNode; // 天空盒子
	};
}


#endif // !_OSGEARTH2D_H_