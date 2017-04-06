/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类工厂基类		                                        */
/* 时间： 2015-05-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _RADARFACTORY_H_
#define _RADARFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CRadarFactory : public IEntityBaseFactory
	{
	public:
		explicit CRadarFactory(void);
		virtual ~CRadarFactory(void);

		// 获取类型
		virtual VRString GetEntiryBaseType(void) const;
		// 创建类型
		virtual IEntityBase* CreateEntityInstance(void);
		// 获得类型名称
		virtual VRString GetEntityBaseName(void);
	};
}

#endif // _RADARFACTORY_H_