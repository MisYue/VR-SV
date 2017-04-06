
#include <io.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#endif 

#include "../../Public/VRSoft.h"

#include <boost/filesystem.hpp>

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
		// _chdir(strPath.c_str());
		boost::filesystem::path dir(strPath);
		// 判断路径是否存在
		if (!boost::filesystem::exists(dir))
		{
			ILogManager::GetInstance().SetLogMessage(strPath + "： 路径不存在", ERROR_NOT_FIND);
			return;
		}

		// 判断是否为一个目录
		if (!boost::filesystem::is_directory(dir))
		{
			ILogManager::GetInstance().SetLogMessage(strPath + " ：不是一个目录", ERROR_NOT_FIND);
			return;
		}

		// 遍历当前目录下所有后缀文件
		namespace FileSystem = boost::filesystem;
		FileSystem::directory_iterator endItor;
		for (FileSystem::directory_iterator itor(dir); itor != endItor; ++itor)
		{
			const FileSystem::path& filePath = itor->path();
			if (FileSystem::is_regular_file(itor->status())
				&& 0 == filePath.extension().string().compare(strEx))  
			{  
				// 获得文件
				files.push_back(filePath.filename().string());
			} 
		}

		/*
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
		*/
	}

}

