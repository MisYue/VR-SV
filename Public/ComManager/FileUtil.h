/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  模型管理组件	                                                */
/* 时间： 2016-03-25                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_FILEUTIL_H_
#define _PUBLIC_FILEUTIL_H_

#pragma once

#include <cstdio>

namespace VR_Soft
{
	class VRSOFT_DLL CFileUtil
	{
	public:
		// 构造函数
		CFileUtil(void);
		CFileUtil(const VRString& strFile);
		CFileUtil(const CFileUtil& other);
		~CFileUtil(void);

	public:
		// 打开
		void Open(const VRString& strFile);
		// 打开
		void Open(void);
		// 关闭
		void Close(void);
		// 获得行
		VRString GetLine();
		// 是否结束
		bool Eof(void);

	protected:
		// 移除行尾的 “\n"
		void RemoveN(char* pszLine);
		// 设置文件名
		void CopyFileName(const VRString& strFile);


	private:
		FILE* m_pFile;
		char* m_szFile;
	};

}

#endif // !_PUBLIC_FILEUTIL_H_