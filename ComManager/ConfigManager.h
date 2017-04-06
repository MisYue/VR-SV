/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  配置管理类			                                        */
/* 时间： 2015-05-20                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _CONFIGMANAGER_H_
#define _CONFIGMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CConfigManager : public IConfigManager
	{
	public:
		explicit CConfigManager(void);
		virtual ~CConfigManager(void);

	public:
		// 添加配置
		virtual void AddConfig(IConfig* pIConfig);
		// 移除配置
		virtual void RemoveConfig(IConfig* pIConfig);

	protected:
		typedef std::list<IConfig*> LstConfig;

	private:
		LstConfig m_lstConfig; // 配置表
		VR_AUTO_MUTEX
	};
}

#endif // _CONFIGMANAGER_H_
