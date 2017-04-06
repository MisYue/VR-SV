/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  组件管理界面实现类                                            */
/* 时间： 2015-05-13                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_FILEOPERETOR_H_
#define _PUBLIC_FILEOPERETOR_H_

#pragma once

#include <vector>

namespace VR_Soft
{
	class VRSOFT_DLL CFileOperetor
	{
	public:
		typedef std::vector<VRString> Files;
	public:
		CFileOperetor(void);
		~CFileOperetor(void);

	public:
		// 获得一个文件夹下所有的文件 不包括目录下的文件夹
		static void GetFilesInPath(const VRString& strPath, const VRString& strEx, Files& files);
	};
}


#endif //  _PUBLIC_FILEOPERETOR_H_