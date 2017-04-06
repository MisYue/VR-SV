

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

	// 打开
	void CFileUtil::Open(const VRString& strFile)
	{
		if (NULL != m_pFile)
		{
			Close();
		}

		// 打开文件
		m_pFile = fopen(m_szFile, "r");
		
	}

	// 打开
	void CFileUtil::Open(void)
	{
		Open(m_szFile);
	}

	// 关闭
	void CFileUtil::Close(void)
	{
		fclose(m_pFile);
	}

	// 获得行
	VRString CFileUtil::GetLine()
	{
		if (NULL == m_pFile)
		{
			IComManager::GetInstance().WriteLogMsg("文件没有打开", ERROR_NOT_FIND);
			return ("");
		}

		// 读取行
		char szLine[NMAXLINECOUNT] = {0};
		fgets(szLine, NMAXLINECOUNT, m_pFile);
		RemoveN(szLine);
		return (szLine);
	}

	// 是否结束
	bool CFileUtil::Eof(void)
	{
		return (feof(m_pFile) > 0 ? true : false);
	}

	// 移除行尾的 “\n"
	void CFileUtil::RemoveN(char* pszLine)
	{
		// 查找是否存在\n
		int nCount = (int)strlen(pszLine) - 1;
		char* pLine = pszLine + nCount;
		if ('\n' == *pLine)
		{
			*pLine = '\0';
		}	
	}

	// 设置文件名
	void CFileUtil::CopyFileName(const VRString& strFile)
	{
		VRSOFT_DELETE_ARRAY(m_szFile);

		size_t nSize = strFile.size() + 1;
		m_szFile = new char[nSize];
		memset(m_szFile, 0, nSize);
		strcpy(m_szFile, strFile.c_str());
	}

}
