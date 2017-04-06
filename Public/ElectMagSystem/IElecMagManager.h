/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  电磁系统入口接口												*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IELECMAGMANAGER_H_
#define _IELECMAGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class IRadar;
	class IState;

	const VRString ELECMAGSYSTEM_TYPENAME = "ELECMAGSYSTEM_TYPENAME";
	const VRString INSTANCE_NAME_ELECMAGSYSTEM = "ELECMAGSYSTEM";
	const VRString ELECMAGSYSTEM_DISC = "电磁系统";

	class ELECTMAG_DLL IElecMagManager : public IComManagerFace
	{
	public:
		// 析构函数
		virtual ~IElecMagManager() { }
		// 获得默认状态
		virtual IState* GetDefultState(void) = 0;
		// 创建电磁特效基本属性
		virtual 
		// 创建雷达
	//	virtual IRadar* CreateEntity(IEntityBaseFactory* pEntityFactory, const VRString& strName) = 0;
	};
}


#endif //  _IELECMAGMANAGER_H_