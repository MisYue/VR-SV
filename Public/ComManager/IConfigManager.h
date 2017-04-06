/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  配置管理接口			                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ICONFIGMANAGER_H_
#define _ICONFIGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class VRSOFT_DLL IConfigManager : public CSingleton<IConfigManager>
	{
	public:
		// 析构函数
		virtual ~IConfigManager() { }
		// 添加配置
		virtual void AddConfig(IConfig* pIConfig) = 0;
		// 移除配置
		virtual void RemoveConfig(IConfig* pIConfig) = 0;
	};
}

#endif // _ICONFIGMANAGER_H_