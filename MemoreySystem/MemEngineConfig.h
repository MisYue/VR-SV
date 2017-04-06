/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  内存引擎配置类												*/
/* 时间： 2015-11-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef  _MEMENGINECONFIGE_H_
#define  _MEMENGINECONFIGE_H_

#pragma once

namespace VR_Soft
{
	class CMemEngineConfig : public IConfig
	{
	public:
		explicit CMemEngineConfig(void);
		virtual ~CMemEngineConfig(void);

	public:
		// 设置配置文件
		virtual void SetConfigFile(const VRString& strfile);
		// 保存文件
		virtual bool SaveConfigFile(void);

	public:
		// 获得需要分配的空间大小
		int GetMenCount(void) const;
		// 获得起始地址
		int GetStartAddr(void) const;
		// 获得数据标识大小
		int GetStructCount(void) const;

	protected:
		// 初始化
		void Init(void);


	private:
		IConfigFile* m_pIConfig; // 配置操作文件
		int m_nCount; // 整个内存大小
		int m_nStructCount; // 格式区大小
		int m_nStartAddr; // 起始地址
	};
}

#endif // !_MEMENGINECONFIGE_H_