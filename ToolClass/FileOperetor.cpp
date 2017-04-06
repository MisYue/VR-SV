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

	// ���һ���ļ��������е��ļ� ������Ŀ¼�µ��ļ���
	void CFileOperetor::GetFilesInPath(const VRString& strPath,const VRString& strEx, Files& files)
	{
		_chdir(strPath.c_str());

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
	}

}

