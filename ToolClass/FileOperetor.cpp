#define VRSOFT_TOOLCLASS_EXPORT
#include <io.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#endif 

#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	CFileOperetor::CFileOperetor(void)
	{
	}


	CFileOperetor::~CFileOperetor(void)
	{
	}

	// 获得一个文件夹下所有的文件 不包括目录下的文件夹
	void CFileOperetor::GetFilesInPath(const VRString& strPath,const VRString& strEx, Files& files)
	{
		_chdir(strPath.c_str());

		long handle;
		struct _finddata_t fileInfo;

		handle = _findfirst(strEx.c_str(), &fileInfo);

		// 判断是否有当前文件夹
		if (-1 == handle)
		{
			IComManager::GetInstance().WriteLogMsg(strPath + "无法找到\""+strEx+"\"", ERROR_NOT_FIND);
			return;
		}

		// 查找
		do 
		{
			const VRString strPluginName = fileInfo.name;
			if ((0 == strPluginName.compare(".") || (0 == strPluginName.compare(".."))))
			{
				break;
			}

			// 添加到列表中
			files.push_back(strPluginName);

		}while(!(_findnext(handle, &fileInfo)));
	}

}

