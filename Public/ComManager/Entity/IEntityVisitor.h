/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体访问基类			                                        */
/* 时间： 2016-06-06                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IENTITYVISITOR_H_
#define _IENTITYVISITOR_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IEntityVisitor
	{
	public:
		// 析构函数
		virtual ~IEntityVisitor() { }
		// 访问接口 
		virtual void Visit(IEntityBase* pIEntityBase) = 0;
	};
}

#endif // _IENTITYVISITOR_H_