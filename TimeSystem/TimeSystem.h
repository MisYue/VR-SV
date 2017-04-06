/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间系统管理插件实现类                                        */
/* 时间： 2015-09-15                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _TIMESYSTEM_H_
#define _TIMESYSTEM_H

#pragma once

#include "Timer.h"
#include "TimeConfig.h"

namespace VR_Soft
{
	class CTimerThread;

	class CTimeSystem : public ITimeManager
	{
	public:
		explicit CTimeSystem(const VRString& strName);
		virtual ~CTimeSystem(void);

	public:
		// 获得时间返回字符串
		virtual ITimer* GetTime(void) ;
		// 加速
		virtual void Quicken(void);
		// 减速
		virtual void Moderate(void);
		// 暂停
		virtual void Suspend(void);
		// 恢复
		virtual void Recover(void);
		// 停止（复位）
		virtual void Stop(void) ;
		// 开始
		virtual void Start(void) ;
		// 跳转
		virtual void Jump(struct tm& t);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName;
		CTimer m_timer; // 时间
		CTimerThread* m_pTimeThread; // 线程
		CTimeConfig m_timeConfig; // 配置文件
	};

	// 注册工厂
	REGISTER_COMFACTORY(CTimeSystem, TimeManager, TIMESYSTEM_TYPENAME, INSTANCE_NAME_TIMESYSTEM, TIMESYSTEM_DISC );
}


#endif // _TIMESYSTEM_H_