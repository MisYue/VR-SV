/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体基类工厂基类		                                        */
/* 时间： 2015-05-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _IENTITYBASEFACTORY_H_
#define _IENTITYBASEFACTORY_H_

#pragma once

namespace VR_Soft
{
	class IEntityBulider;

	class IEntityBaseFactory
	{
	public:
		// 析构函数
		virtual ~IEntityBaseFactory() { }
		// 获取类型
		virtual VRString GetEntiryBaseType(void) const = 0;
		// 创建类型
		virtual IEntityBulider* CreateEntityBuilder(void) = 0;


	public:
		static int m_nCount;
	};

	// 创建工厂对象宏
#define CREATE_ENTITYBASE_FACTORY(functionname) EXTERN_CPP VRSOFT_DLL IEntityBaseFactory* functionname(void);

}

#endif // _IENTITYBASEFACTORY_H_