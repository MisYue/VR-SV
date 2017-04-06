/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  环境系统入口类												*/
/* 时间： 2015-11-19                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ENVIRONMENTSYSTEM_H_
#define _ENVIRONMENTSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class CEnvironmentManager;

	class CEnvironmentSystem : public IEnvironmentManager
	{
	public:
		// 构造函数
		explicit CEnvironmentSystem(const VRString& strName);
		// 析构函数
		virtual ~CEnvironmentSystem(void);

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 对组件进行初始化
		virtual void Init(void) ;
		// 获得默认状态
		virtual IState* GetDefultState(void) ;
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	private:
		VRString m_strName; // 名称
		CEnvironmentManager* m_pEnvironmentManager;
	};

	// 注册工厂
	REGISTER_COMFACTORY(CEnvironmentSystem, EnvironmentManager, ENVIRONEMNTSYSTEM_TYPENAME, INSTANCE_NAME_ENVIRONEMNTSYSTEM, ENVIRONEMNTSYSTEM_DISC);
}


#endif // !_ENVIRONMENTSYSTEM_H_