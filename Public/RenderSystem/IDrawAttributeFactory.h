/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  视图插件的头文件集合	                                        */
/* 时间： 2016-03-23                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLICE_IDRAWATTRIBUTEFACTORY_H_
#define _PUBLICE_IDRAWATTRIBUTEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class OSGRENDER_DLL IDrawAttributeFactory
	{
	public:
		virtual ~IDrawAttributeFactory() { }
		// 实体渲染管理类
		virtual IEntityDrawManager* CreateEntityDrawManagerInstance(IEntityBase* pIEntityBase) = 0;
		// 实体渲染
		virtual IMeshDrawAttribute* CreateMeshInstance(IEntityBase* pIEntityBase, const VRString& strDrawName) = 0;
		// 轨迹线
		virtual IDrawAttribute* CreateTrackLine(IEntityBase* pIEntityBase) = 0;
	};
}


#endif