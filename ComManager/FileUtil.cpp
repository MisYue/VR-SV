

#include "../../Public/VRSoft.h"

const int NMAXLINECOUNT = 1024;

namespace VR_Soft
{
	CFileUtil::CFileUtil(void):m_pFile(NULL),m_szFile(NULL)
	{
	}


	CFileUtil::CFileUtil(const VRString& strFile)
		:m_pFile(NULL),m_szFile(NULL)
	{
		CopyFileName(strFile);
		Open();
	}

	CFileUtil::CFileUtil(const CFileUtil& other)
		:m_pFile(other.m_pFile)
	{
		CopyFileName(other.m_szFile);
	}

	CFileUtil::~CFileUtil(void)
	{
		VRSOFT_DELETE_ARRAY(m_szFile);
		Close();
	}

	// ��
	void CFileUtil::Open(const VRString& strFile)
	{
		if (NULL != m_pFile)
		{
			Close();
		}

		// ���ļ�
		m_pFile = fopen(m_szFile, "r");
		
	}

	// ��
	void CFileUtil::Open(void)
	{
		Open(m_szFile);
	}

	// �ر�
	void CFileUtil::Close(void)
	{
		fclose(m_pFile);
	}

	// �����
	VRString CFileUtil::GetLine()
	{
		if (NULL == m_pFile)
		{
			IComManager::GetInstance().WriteLogMsg("�ļ�û�д�", ERROR_NOT_FIND);
			return ("");
		}

		// ��ȡ��
		char szLine[NMAXLINECOUNT] = {0};
		fgets(szLine, NMAXLINECOUNT, m_pFile);
		RemoveN(szLine);
		return (szLine);
	}

	// �Ƿ����
	bool CFileUtil::Eof(void)
	{
		return (feof(m_pFile) > 0 ? true : false);
	}

	// �Ƴ���β�� ��\n"
	void CFileUtil::RemoveN(char* pszLine)
	{
		// �����Ƿ����\n
		int nCount = (int)strlen(pszLine) - 1;
		char* pLine = pszLine + nCount;
		if ('\n' == *pLine)
		{
			*pLine = '\0';
		}	
	}

	// �����ļ���
	void CFileUtil::CopyFileName(const VRString& strFile)
	{
		VRSOFT_DELETE_ARRAY(m_szFile);

		size_t nSize = strFile.size() + 1;
		m_szFile = new char[nSize];
		memset(m_szFile, 0, nSize);
		strcpy(m_szFile, strFile.c_str());
	}

}
