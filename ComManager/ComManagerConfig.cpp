
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include "../../Public/VRSoft.h"
#include "ComManagerConfig.h"

namespace VR_Soft
{
	CComManagerConfig::CComManagerConfig(const VRString& strPath):m_strPath(strPath), m_strCurPath("")
	{
	}


	CComManagerConfig::~CComManagerConfig(void)
	{
		Sava();
	}

	// ��ӵ�ǰ����ӵ�ģ��
	void CComManagerConfig::AddComName(const VRString& strComName )
	{
		VR_MUTEX_AUTO;

		m_lstLoadedCom.push_back(strComName);

		// ����
		Sava();
	}

	// �Ƴ���ǰ����ӵ����
	void CComManagerConfig::RemoveComName(const VRString& strComName)
	{
		VR_MUTEX_AUTO;

		LstLoadedCom::iterator itor = std::find(m_lstLoadedCom.begin(), m_lstLoadedCom.end(), strComName);
		if (m_lstLoadedCom.end() == itor)
		{
			return;
		}

		// �Ƴ�
		m_lstLoadedCom.erase(itor);

		// ����
		Sava();
	}

	// ���浱ǰ�Ѿ���ӵ�����
	void CComManagerConfig::Sava(void)
	{
		const VRString str = GetCurPath()  + "/Config/ComManager/commanager.cfg";

		// �������ļ�
		// �������ļ�
		FILE* pFile = NULL;
		pFile = fopen(str.c_str(), "w");
		if (NULL == pFile)
		{
			ILogManager::GetInstance().SetLogMessage("�������ļ�ʧ��", ERROR_NOT_FIND);
			return;
		}

		// д���ļ�
		LstLoadedCom::const_iterator cstItor = m_lstLoadedCom.begin();
		for (; m_lstLoadedCom.end() != cstItor; ++cstItor)
		{
			//out<<*cstItor<<std::endl;
			fwrite((*cstItor).c_str(), 1, (*cstItor).size(), pFile);
			fwrite("\n", 1, strlen("\n"), pFile);
		}

		fclose(pFile);

		// ��ȡ���
		ILogManager::GetInstance().SetLogMessage("��������ļ���ȡ���");
	/*	std::ofstream out(str);
		if (!out.is_open())
		{
			return;
		}

		LstLoadedCom::const_iterator cstItor = m_lstLoadedCom.begin();
		for (; m_lstLoadedCom.end() != cstItor; ++cstItor)
		{
			out<<*cstItor<<std::endl;
		}

		out.close();
	*/
	}

	// ��ȡ����ӵĲ������
	void CComManagerConfig::ReadCom(void)
	{
		const VRString str = GetCurPath()  + "/Config/ComManager/commanager.cfg";

		// �������ļ�
		FILE* pFile = NULL;
		pFile = fopen(str.c_str(), "r");
		if (NULL == pFile)
		{
			ILogManager::GetInstance().SetLogMessage("�������ļ�ʧ��", ERROR_NOT_FIND);
			return;
		}

		while (!feof(pFile))
		{
			// ��ȡ��
			char szLine[256] = {0};
			fgets(szLine, sizeof(szLine) - 1, pFile); // ������\n  
			if (1 >= strlen(szLine))
			{
				continue;
			}
			Replace(szLine); // ȥ��\n
			IComManager::GetInstance().GetComManagerUI()->InstallPlugin(szLine);
		}

		// �ر��ļ�
		fclose(pFile);
		// ��ȡ���
		ILogManager::GetInstance().SetLogMessage("��������ļ���ȡ���");		
	}

	// ��ʼ������ϵͳ
	void CComManagerConfig::Init() 
	{
		VR_MUTEX_AUTO;

		ReadCom();
	}

	// ���ִ��·��
	VRString CComManagerConfig::GetCurPath(void) const 
	{
		if (0 == m_strCurPath.compare(""))
		{
			GetExePath();
		}

		return (m_strCurPath);
	}

	// ���ȫ��·��
	VRString CComManagerConfig::GetExePath(void) const
	{
		if (m_strPath.empty())
		{
			IComManager::GetInstance().WriteLogMsg("��ǰ·����ȡʧ��");
			return (m_strPath);
		}

		// �������һ�� ��/��
		const int nPos = m_strPath.find_last_of('\\');
		if (-1 == nPos)
		{
			return VRString("");
		}

		// ���·��
		VRString str = m_strPath.substr(0, nPos);

		// ��ǰ·��
		IComManager::GetInstance().WriteLogMsg("��ǰ·��Ϊ:"+str);
		m_strCurPath = str;
		return (str);
	}

	void CComManagerConfig::Replace(char* szLine)
	{
		// �����滻'\n'
		char* pLine = szLine;
		while ('\n' != *pLine)
		{
			++pLine;
		}

		*pLine = '\0';
	}

}

