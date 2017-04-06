/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  仿真系统整个系统进行仿真时间和对模型调度                      */
/* 时间： 2015-10-21                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _SIMSYSTEM_H_
#define _SIMSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CSimSingleThreadEngine;
	class CSimTime;

	class CSimSystem : public ISimManager
	{
	public:
		// 构造函数
		explicit CSimSystem(const VRString& strName);
		// 析构函数
		virtual ~CSimSystem(void);

	public:
		// 设置是否为服务器
		virtual void SetServer(const bool bServer);
		// 返回是否为服务器
		virtual bool IsServer(void) const { return (m_bServer); }
		// 设置引擎命令
		virtual void SetCmd(const SimCmd simCmd);
		// 单独作为一个进程运行直接进入循环
		virtual void Run(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 初始化系统
		virtual void Init(void);
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	public:
		// 获得线程对象
		CSimSingleThreadEngine* GetSimThreadEngine(void) const { return (m_pSimThreadEngine); }

	protected:

	private:
		VRString m_strName;
		bool m_bServer; // 是否为服务器
		CSimTime* m_pSimTime;
		CSimSingleThreadEngine* m_pSimThreadEngine; // 线程引擎
	};

	// 注册工厂
	REGISTER_COMFACTORY(CSimSystem, SimManager, SIMSYSTEM_TYPENAME, INSTANCE_NAME_SIMSYSTEM, SIMSYSTEM_DISC );

}

#endif // _SIMSYSTEM_H_
