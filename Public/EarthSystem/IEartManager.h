#ifndef _IEARTHMANAGER_H_
#define _IEARTHMANAGER_H_

#pragma once

#include <vector>

namespace VR_Soft
{
	const VRString EARTHSYSTEM_TYPENAME = "EARTHSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_EARTHSYSTEM = "EARTHSYSTEM";
	const VRString EARTHSYSTEM_DISC = "地球系统";

	class ISynchroManIpManager;
	class IEarthLayerManager;
	class IFeatureManager;

	class OSGEARTH_DLL IEarthManager : public CSingleton<IEarthManager>, public IComManagerFace
	{
	public:
		enum EARTH_TYPE
		{
			EARTH_2D = 1 << 0, 
			EARTH_3D = 1 << 1,
			EARTH_2D_3D = 1 << 2
		};
	public:
		// 析构函数
		virtual ~IEarthManager() {}
		// 获得地球
		virtual IEarth* GetEarth(EARTH_TYPE et) = 0;
		// 初始化场景
		virtual void RenderEarth(const EARTH_TYPE earthType, IRenderView* pIRendView) = 0;
		// 添加模型
		virtual void AddEntity(const IEntityBase* pIEntity) = 0;
		// 添加显示线
		virtual void AddFeatureGeometry(const IFeatureGeomtry* pIFeatureGeomtry) = 0;
		// 获得同步操作器
		virtual ISynchroManIpManager* GetSynchroManIpManager(void) const = 0;
		// 获得通过位置经纬高度
		virtual osg::Vec3d GetLongLatHightByPoint(float x, float y, double& lat, double& lon, double& height,\
			const VRString& strViewName = "mainView") = 0;
		// 获得图层管理
		virtual IEarthLayerManager* GetEarthLayerManager(void) const = 0;
		// 获得矢量管理
		virtual IFeatureManager* GetEarthFeatureManager(void) const = 0;
		// 设置网格线开关
		virtual void SetGraticuleState(bool bShow) = 0;
		// 获得网格线开关
		virtual bool GetGraticuleState(void) const = 0;
		// 量算
		virtual double Distance(const std::vector<osg::Vec3d>& listPoints) const = 0;
		// 量算开关
		virtual void DistanceEnable(bool bEnable) = 0;
		// 获得量算功能开关
		virtual bool GetDistanceEnable(void) const = 0;
		
	public:
		typedef std::vector<VRString> ViewNames;
	};
}

#endif 