/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地球配置类													*/
/* 时间： 2015-05-12                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _EARTHCONFIG_H_
#define _EARTHCONFIG_H_

#pragma once

namespace VR_Soft
{
	class CEarthConfig : public IConfig
	{
	public:
		// 构造函数
		explicit CEarthConfig(const VRString& strFile);
		// 析构函数
		virtual ~CEarthConfig(void);

	public:
		// 设置配置文件
		virtual void SetConfigFile(const VRString& strfile) ;
		// 保存文件
		virtual bool SaveConfigFile(void) ;

	private:
		IConfigFile* m_pIConfig; // 配置操作文件
	};
}


#endif //  _EARTHCONFIG_H_