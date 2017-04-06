/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth对象		                                            */
/* 时间： 2016-06-30                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _OSGEARTH2D_H_
#define _OSGEARTH2D_H_

#pragma once

#include "OsgEarth.h"

namespace VR_Soft
{
	class COsgEarth2D : public COsgEarth
	{
	public:
		explicit COsgEarth2D();
		~COsgEarth2D(void);

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
		
	};
}


#endif // !_OSGEARTH2D_H_