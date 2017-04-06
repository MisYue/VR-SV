/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  配置类接口			                                        */
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ICONFIG_H_
#define _ICONFIG_H_

#pragma once

class IConfigUI;

namespace VR_Soft
{
	class VRSOFT_DLL IConfig
	{
	public:
		// 析构函数
		virtual ~IConfig() {}
		// 设置配置文件
		virtual void SetConfigFile(const VRString& strfile) = 0;
		// 保存文件
		virtual bool SaveConfigFile(void) = 0;
		// 获取界面
		virtual bool GetUI(void) { return (false); }
		// 注册配置UI
		virtual void RegisterUI(IConfigUI* pConfigUI) {m_pIConfigUI = pConfigUI;}
		// 反注册配置UI
		virtual void UnRegisterUI(IConfigUI* pConfigUI) { m_pIConfigUI = NULL; }

	protected:
		// 配置文件UI
		IConfigUI* m_pIConfigUI;
	};
};

#endif // _ICONFIG_H_