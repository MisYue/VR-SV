/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����������ʵ����                                            */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���һ���ļ��������е��ļ� ������Ŀ¼�µ��ļ���
		static void GetFilesInPath(const VRString& strPath, const VRString& strEx, Files& files);
	};
}


#endif //  _PUBLIC_FILEOPERETOR_H_