#ifndef _ICOMMANAGERFACE_H_
#define _ICOMMANAGERFACE_H_

#pragma once

#include "IComManagerFaceImp.h"

namespace VR_Soft
{
	class VRSOFT_DLL IComManagerFace //: public IComManagerFaceImp<IComManagerFace>
	{
	public:
		// 析构函数
		virtual ~IComManagerFace(void) { }
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const = 0;
		// 对组件进行初始化
		virtual void Init(void) = 0;
	public:
		// 设置获取属性
		SET_GET_PROPERTY_INTERFACE(Name, VRString);
		// static const VRString COM_TYPE_NAME;
	};
}
#endif