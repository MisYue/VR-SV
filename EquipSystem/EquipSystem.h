/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  装备系统入口接口												*/
/* 时间： 2015-11-11                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IEQUIPMANAGER_H_
#define _IEQUIPMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CEquipManager;

	class CEquipSystem : public IEquipManager
	{
	public:
		explicit CEquipSystem(const VRString& strName);
		virtual ~CEquipSystem(void);

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
		// 获得装备插件
		CEquipManager* GetEquipManager(void) const;

	private:
		VRString m_strName; // 名称
		CEquipManager* m_pEquitManager; // 装备插件集合
	};

	// 注册工厂
	REGISTER_COMFACTORY(CEquipSystem, EquipManager, EQUIPSYSTEM_TYPENAME, INSTANCE_NAME_EQUIPSYSTEM, EQUIPSYSTEM_DISC);
}


#endif //  !_IEQUIPMANAGER_H_



