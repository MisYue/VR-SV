/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  卫星系统入口接口												*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_ISATELLITEMANAGER_H_
#define _PUBLICE_ISATELLITEMANAGER_H_

namespace VR_Soft
{
	const VRString SATELLITESYSTEM_TYPENAME = "SATELLITESYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_SATELLITESYSTEM = "SATELLITESYSTEM";
	const VRString SATELLITESYSTEM_DISC = "卫星系统";

	class ITle;

	class VRSOFT_PLUGIN_DLL ISatelliteManager : public CSingleton<ISatelliteManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~ISatelliteManager(void) { }
		// 获得默认状态
		virtual IState* GetDefultState(void) = 0;
		// 创建两行根数
		virtual ITle* CreateTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2) = 0;
		// 创建弹道
		virtual IEntityBase* CreateSatelliteEntity(const VRString& strName, const VRString& strTrajectory, const uint64_t ID) = 0;
		// 创建轨迹算法
		virtual ITrajectory* CreateTrajectory(const VRString& strTrajectory) = 0;
	};
}

#endif