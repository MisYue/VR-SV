/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ģ�͹������	                                                */
/* ʱ�䣺 2016-03-25                                                    */
/* �޸�ʱ��:                                                            */
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
		// ���캯��
		CFileUtil(void);
		CFileUtil(const VRString& strFile);
		CFileUtil(const CFileUtil& other);
		~CFileUtil(void);

	public:
		// ��
		void Open(const VRString& strFile);
		// ��
		void Open(void);
		// �ر�
		void Close(void);
		// �����
		VRString GetLine();
		// �Ƿ����
		bool Eof(void);

	protected:
		// �Ƴ���β�� ��\n"
		void RemoveN(char* pszLine);
		// �����ļ���
		void CopyFileName(const VRString& strFile);


	private:
		FILE* m_pFile;
		char* m_szFile;
	};

}

#endif // !_PUBLIC_FILEUTIL_H_