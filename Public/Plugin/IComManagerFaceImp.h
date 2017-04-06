/************************************************************************/
/* 作者： LJ		                                                    */
/* 用途:  组件接口模板			                                        */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ICOMMANAGERFACEIMP_H_
#define _ICOMMANAGERFACEIMP_H_

#pragma once

#include "../VRConfig.h"

namespace VR_Soft
{
	template <typename T>
	class IComManagerFaceImp
	{
	public:
		// 析构函数
		virtual ~IComManagerFaceImp() {}
		// 设置获取属性
		SET_GET_PROPERTY(Name, VRString, str);
		
	private:
		VRString m_strName; // 组件接口名称
	};
}

#endif