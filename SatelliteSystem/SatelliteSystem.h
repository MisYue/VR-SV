/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星系统入口类												*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _SATELLITESYSTEM_H_
#define _SATELLITESYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteManager;

	class CSatelliteSystem : public ISatelliteManager
	{
	public:
		// 构造函数
		explicit CSatelliteSystem(const VRString& strName);
		// 析构函数
		virtual ~CSatelliteSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 对组件进行初始化
		virtual void Init(void) ;
		// 获得默认状态
		virtual IState* GetDefultState(void) ;
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// 创建两行根数
		virtual ITle* CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2) ;
		// 创建弹道
		virtual IEntityBase* CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) ;
		// 创建轨迹算法
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) ;

	private:
		VRString m_strName; // 名称
		CSatelliteManager* m_pSatelliteManager; // 卫星插件管理系统
	};

	// 注册工厂
	REGISTER_COMFACTORY(CSatelliteSystem, SatelliteManager, SATELLITESYSTEM_TYPENAME, INSTANCE_NAME_SATELLITESYSTEM, SATELLITESYSTEM_DISC);
}


#endif // !_SATELLITESYSTEM_H_