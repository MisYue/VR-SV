/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  电磁系统入口													*/
/* 时间： 2015-05-22                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ELECTMAGSYSTEM_H_
#define _ELECTMAGSYSTEM_H_

#pragma once

namespace VR_Soft
{
	class IRadar;
	class CElectPluginManager;

	class CElectMagSystem : public IElecMagManager
	{
	public:
		explicit CElectMagSystem(const VRString& strName);
		virtual ~CElectMagSystem();

	public:
		// 获取类型名称
		virtual const VRString& GetTypeName(void) const;
		// 对组件进行初始化
		virtual void Init(void) ;
		// 获得默认状态
		virtual IState* GetDefultState(void);
		//设置属性
		SET_GET_PROPERTY(Name, VRString, str);

	protected:
		// 初始化
		void InitSystem(void);

	private:
		VRString m_strName; // 名称
		CElectPluginManager* m_pElectPluginManager;
	};

	// 注册工厂
	REGISTER_COMFACTORY(CElectMagSystem, ElecMagManager, ELECMAGSYSTEM_TYPENAME, INSTANCE_NAME_ELECMAGSYSTEM, ELECMAGSYSTEM_DISC);
}

#endif // ELECTMAGSYSTEM_H
