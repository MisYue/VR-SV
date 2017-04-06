/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备系统入口接口												*/
/* 时间： 2015-11-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IEQUIPMANAGER_H_
#define _PUBLICE_IEQUIPMANAGER_H_

#pragma once

namespace VR_Soft
{
	const VRString EQUIPSYSTEM_TYPENAME = "EQUIPSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_EQUIPSYSTEM = "EQUIPSYSTEM";
	const VRString EQUIPSYSTEM_DISC = "装备系统";

	class VRSOFT_PLUGIN_DLL IEquipManager : public CSingleton<IEquipManager>, public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IEquipManager() { }
		// 获得默认状态
		virtual IState* GetDefultState(void) = 0;
		// 创建雷达
		//	virtual IRadar* CreateEntity(IEntityBaseFactory* pEntityFactory, const VRString& strName) = 0;
	};
}


#endif //  !_PUBLICE_IEQUIPMANAGER_H_