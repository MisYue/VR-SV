/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航线系统入口													*/
/* 时间： 2015-08-03                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _AIRLINESYSTEM_H_
#define _AIRLINESYSTEM_H_

// #include "airlinesystem_global.h"

#pragma once

namespace VR_Soft
{
	class CAirLineManager;
	class CFeatureGeomtryFactory;

	class CAirLineSystem : public IAirLineManager
	{
	public:
		explicit CAirLineSystem(const VRString& strName);
		virtual ~CAirLineSystem(void);

	public:
		// 创建弹道
		virtual ITrajectoryEntity* CreateTrajectroryEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) ;
		//// 创建卫星轨道
		//virtual ITrajectoryEntity* CreateSatelliteTrajectory(const VRString& strName, const uint64_t ID);
		// 创建轨迹算法
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) ;
		// 创建地球显示几何图形
		virtual IFeatureGeomtry* CreateFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry) ;
		// 几何图形抽象工厂
		virtual IFeatureGeomtryFactory* GetFeatureGeomtryFactory(void) const ;
		//// 注册编辑界面
		//virtual void RegisterUI(IAirLineUI* pIAirLineUI);
		//// 反注册编辑界面
		//virtual void UnReginsterUI(void);
		//// 获得可编辑的航线
		//virtual IAirLine* GetEidtAirLine(void) const;
		//// 编辑完毕
		//virtual void EndEidtAirLine(void) ;
		//// 获得绑定航线
		//IAirLineBind* GetAirLineBind(void) const;

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 对组件进行初始化
		virtual void Init(void) ;
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	public:
	

	protected:
		void InitSystem(void);

	private:
		VRString m_strName; // 名称
		CAirLineManager* m_pAirLineManager; // 装备插件集合
		CFeatureGeomtryFactory* m_featureGeomtryFactory;
	};

	// 注册工厂
	REGISTER_COMFACTORY(CAirLineSystem, AirLineManager, AIRLINESYSTEM_TYPENAME, INSTANCE_NAME_AIRLINESYSTEM, AIRLINESYSTEM_DISC);
}

#endif // _AIRLINESYSTEM_H_
