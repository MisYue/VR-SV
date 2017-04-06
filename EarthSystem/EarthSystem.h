/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth系统管理系统                                          */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _EARTHSYSTEM_H_
#define _EARTHSYSTEM_H_

#pragma once

namespace osg
{
	class Group;
}

namespace osgEarth
{
	namespace Util
	{
		class EarthManipulator;
	}
};

#include <osgEarth/Viewpoint>



namespace VR_Soft
{

	class IEarth;
	class COsgEarth;
	class CSynchroManipManager;
	class CEarthLayerManager;
	class CFeatureManager;

	class CEarthSystem : public IEarthManager
	{
	public:
		// 构造函数
		explicit CEarthSystem(const VRString& strName);
		// 析构函数
		virtual ~CEarthSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const ;
		// 对组件进行初始化
		virtual void Init(void) ;
		// 获得地球
		virtual IEarth* GetEarth(EARTH_TYPE et) ;
		// 初始化场景
		virtual void RenderEarth(const EARTH_TYPE earthType, IRenderView* pIRendView);
		// 添加模型
		virtual void AddEntity(const IEntityBase* pIEntity);
		// 添加显示线
		virtual void AddFeatureGeometry(const IFeatureGeomtry* pIFeatureGeomtry);
		// 获得同步操作器
		virtual ISynchroManIpManager* GetSynchroManIpManager(void) const;
		// 获得通过位置经纬高度
		virtual osg::Vec3d GetLongLatHightByPoint(float x, float y, double& lat, double& lon, double& height,\
			const VRString& strViewName = "mainView");
		// 获得图层管理
		virtual IEarthLayerManager* GetEarthLayerManager(void) const ;
		// 获得矢量管理
		virtual IFeatureManager* GetEarthFeatureManager(void) const;
		// 设置网格线开关
		virtual void SetGraticuleState(bool bShow);
		// 获得网格线开关
		virtual bool GetGraticuleState(void) const ;
		// 量算
		virtual double Distance(const std::vector<osg::Vec3d>& listPoints) const;
		// 量算开关
		virtual void DistanceEnable(bool bEnable);
		// 获得量算功能开关
		virtual bool GetDistanceEnable(void) const;

		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		// 设置渲染对应的视图
		void SetNodeToView(const VRString& strViewName);
		// 初始化2、3维场景
		void Init2D3D(void);

	protected:
		
		// 初始化视点
		void InitViewpoint(IConfigFile *pIConfigFile, osgEarth::Util::EarthManipulator* pMp);

	private:
		IEarth* m_pEarth; // 地球模型
		VRString m_strName; // 组件名称
		ViewNames m_viewNames; // 视图名称集合
		VRString m_strFilePath;
		
		COsgEarth* m_pOsgEarth2D;
		COsgEarth* m_pOsgEarth3D; // 
		CSynchroManipManager* m_pSynchroManipManager; // 管理工具

		osgEarth::Viewpoint m_viewPoint;
		CEarthLayerManager* m_pEarthLayerManager; // 图层管理
		CFeatureManager* m_pFeatureManager; // 矢量数据管理
	};

	// 注册工厂
	REGISTER_COMFACTORY(CEarthSystem, EarthManager, EARTHSYSTEM_TYPENAME, INSTANCE_NAME_EARTHSYSTEM, EARTHSYSTEM_DISC);
}


#endif // _EARTHSYSTEM_H_