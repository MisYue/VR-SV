/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  时间配置类													*/
/* 时间： 2015-09-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TIMECONFIG_H_
#define _TIMECONFIG_H_

#pragma once

namespace VR_Soft
{
	class CTimeConfig : public IConfig
	{
	public:
		// 构造函数
		explicit CTimeConfig(void);
		// 析构函数
		virtual ~CTimeConfig(void);

	public:
		// 获得开始时间
		bool GetInitTime(struct tm& t);
		// 获得加速倍数
		float GetMultipeTime(void);
		// 获得加速
		float GetQuicken(void);
		// 获得减速
		float GetModerate(void);

	public:
		// 设置配置文件
		virtual void SetConfigFile(const VRString& strfile) ;
		// 保存文件
		virtual bool SaveConfigFile(void);

	protected:
		// String 转 Int
		int ConvertFrom(const VRString& str);

	private:
		IConfigFile* m_pIConfig; // 配置操作文件
	};
}

#endif // _TIMECONFIG_H_
