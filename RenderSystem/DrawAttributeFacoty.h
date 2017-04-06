/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图插件的头文件集合	                                        */
/* 时间： 2016-03-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _DRAWATTRIBUTEFACTORY_H_
#define _DRAWATTRIBUTEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CDrawAttributeFactory : public IDrawAttributeFactory
	{
	public:
		virtual ~CDrawAttributeFactory();
		// 实体渲染管理类
		virtual IEntityDrawManager* CreateEntityDrawManagerInstance(IEntityBase* pIEntityBase);
		// 实体渲染
		virtual IMeshDrawAttribute* CreateMeshInstance(IEntityBase* pIEntityBase, const VRString& strDrawName);
		// 轨迹线
		virtual IDrawAttribute* CreateTrackLine(IEntityBase* pIEntityBase);
	};
}


#endif