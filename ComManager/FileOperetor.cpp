
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

	// ���һ���ļ��������е��ļ� ������Ŀ¼�µ��ļ���
	void CFileOperetor::GetFilesInPath(const VRString& strPath,const VRString& strEx, Files& files)
	{
		// _chdir(strPath.c_str());
		boost::filesystem::path dir(strPath);
		// �ж�·���Ƿ����
		if (!boost::filesystem::exists(dir))
		{
			ILogManager::GetInstance().SetLogMessage(strPath + "�� ·��������", ERROR_NOT_FIND);
			return;
		}

		// �ж��Ƿ�Ϊһ��Ŀ¼
		if (!boost::filesystem::is_directory(dir))
		{
			ILogManager::GetInstance().SetLogMessage(strPath + " ������һ��Ŀ¼", ERROR_NOT_FIND);
			return;
		}

		// ������ǰĿ¼�����к�׺�ļ�
		namespace FileSystem = boost::filesystem;
		FileSystem::directory_iterator endItor;
		for (FileSystem::directory_iterator itor(dir); itor != endItor; ++itor)
		{
			const FileSystem::path& filePath = itor->path();
			if (FileSystem::is_regular_file(itor->status())
				&& 0 == filePath.extension().string().compare(strEx))  
			{  
				// ����ļ�
				files.push_back(filePath.filename().string());
			} 
		}

		/*
		long handle;
		struct _finddata_t fileInfo;

		handle = _findfirst(strEx.c_str(), &fileInfo);

		// �ж��Ƿ��е�ǰ�ļ���
		if (-1 == handle)
		{
			IComManager::GetInstance().WriteLogMsg(strPath + "�޷��ҵ�\""+strEx+"\"", ERROR_NOT_FIND);
			return;
		}

		// ����
		do 
		{
			const VRString strPluginName = fileInfo.name;
			if ((0 == strPluginName.compare(".") || (0 == strPluginName.compare(".."))))
			{
				break;
			}

			// ��ӵ��б���
			files.push_back(strPluginName);

		}while(!(_findnext(handle, &fileInfo)));
		*/
	}

}

