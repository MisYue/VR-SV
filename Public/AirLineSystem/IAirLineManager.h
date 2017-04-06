/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线系统入口接口												*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IAIRLINEMANAGER_H_
#define _IAIRLINEMANAGER_H_

#pragma once

#if defined(OSGEARTH) 

#include <osgEarthSymbology/Geometry>

#define OsgEarthGeomtry osgEarth::Symbology::Geometry

#else

#define OsgEarthGeomtry void

#endif

namespace VR_Soft
{
	class ITrajectoryEntity;
	class ITrajectory;
	class IFeatureGeomtryFactory;

	const VRString AIRLINESYSTEM_TYPENAME = "AIRLINESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_AIRLINESYSTEM = "AIRLINESYSTEM";
	const VRString AIRLINESYSTEM_DISC = "航线系统";

	class VRSOFT_PLUGIN_DLL IAirLineManager : public CSingleton<IAirLineManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IAirLineManager() { }

		// 创建弹道
		virtual ITrajectoryEntity* CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) = 0;
		// 创建轨迹算法
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) = 0;
		// 创建地球显示几何图形
		virtual IFeatureGeomtry* CreateFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry) = 0;
		// 几何图形抽象工厂
		virtual IFeatureGeomtryFactory* GetFeatureGeomtryFactory(void) const = 0;

		//// 注册编辑界面
		//virtual void RegisterUI(IAirLineUI* pIAirLineUI) = 0;
		//// 反注册编辑界面
		//virtual void UnReginsterUI(void) = 0;
		//// 获得可编辑的航线
		//virtual IAirLine* GetEidtAirLine(void) const = 0;
		//// 编辑完毕
		//virtual void EndEidtAirLine(void) = 0;
		//// 获得绑定航线
		//virtual IAirLineBind* GetAirLineBind(void) const = 0;
	};
}


#endif //  _IAIRLINEMANAGER_H_