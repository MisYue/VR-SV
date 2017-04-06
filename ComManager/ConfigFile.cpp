
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <cstdio>
#include "../../Public/VRSoft.h"

#include "ConfigFile.h"

namespace VR_Soft
{

	const VRString g_strSpace = " ";// /f/n/t/r/v";

	CConfigFile::CConfigFile(const VRString& strFile):m_strConfigFile(strFile),m_pFile(NULL)
	{
	}

	CConfigFile::CConfigFile(void):m_strConfigFile(""),m_pFile(NULL)
	{

	}

	CConfigFile::~CConfigFile(void)
	{
		CloseFile();
	}

	// �������ļ�
	bool CConfigFile::OpenFile(const VRString& strFile)
	{
		m_strConfigFile = strFile;
		return (OpenFile());
	}

	// �������ļ�
	bool CConfigFile::OpenFile(void)
	{
		// �ж��Ƿ��ļ�
		if (m_strConfigFile.empty())
		{
			return (false);
		}

		if (NULL != m_pFile)
		{
			return (true);
		}

		// �ж��ļ��Ǳ���
		m_pFile = fopen(m_strConfigFile.c_str(), "r");
		if (NULL != m_pFile)
		{
			ILogManager::GetInstance().SetLogMessage("�������ļ���" + m_strConfigFile);
			return (true);
		}
		else
		{
			ILogManager::GetInstance().SetLogMessage("�������ļ�ʧ�ܣ�" + m_strConfigFile);
			return (false);
		}
		
		/*
		// �ж��Ƿ��Ѿ���
		if (!m_fileOperator.is_open())
		{
			m_fileOperator.open(m_strConfigFile);

			// д����־
			ILogManager* pLog = IComManager::GetInstance().GetLogManager();
			if (NULL != pLog)
			{
				pLog->SetLogMessage("�������ļ���" + m_strConfigFile);
			}
		}

		return m_fileOperator.is_open();*/
		return (0);
	}

	// �ر��ļ�
	void CConfigFile::CloseFile(void)
	{
		// �ж��Ƿ��
		if (NULL == m_pFile)
		{
			return;
		}

		fclose(m_pFile);
	/*	if (m_fileOperator.is_open())
		{
			// д����־
			IComManager::GetInstance().WriteLogMsg("�ر������ļ���" + m_strConfigFile);
			m_fileOperator.close();
		}
		*/
	}

	// ��ȡ�ļ����ƶ�Ӧ���ֵ
	VRString CConfigFile::GetItemValue(const VRString& strName, const VRString& strItem) const
	{
		VRString strItemName = strName;
		Trim(strItemName);

		VRString strItemValue = strItem;
		Trim(strItemValue);
		// ͨ�����Ʋ�ѯ��
		MapStrItem::const_iterator cstItor = m_mapStrItem.find(strItemName);
		if (m_mapStrItem.end() == cstItor)
		{
			return ("");
		}

		// ת����Ŀ
		const LstItemValue& itemValue = cstItor->second;
		// ��ѯֵ
		LstItemValue::const_iterator cstItorValue = std::find(itemValue.begin(), itemValue.end(), strItemValue);
		if (itemValue.end() == cstItorValue)
		{
			return ("");
		}

		// ����ֵ
		return (cstItorValue->strValue);
		//return "";
	}

	// ���һ�����µ�������Ŀ
	const IConfigFile::LstItemValue& CConfigFile::GetItemValus(const VRString& strName) const
	{
		// ��ѯ�Ƿ���ڵ�ǰ����Ŀ����
		MapStrItem::const_iterator itor = m_mapStrItem.find(strName);
		return itor->second;
	}

	// ��ȡ�ļ�
	void CConfigFile::ReadConfig(void)
	{
		// ���ļ�
		if(!OpenFile())
		{
			return;
		}

		// д����־
		IComManager::GetInstance().WriteLogMsg("��ȡ�����ļ���" + m_strConfigFile);

		VRString strItemName;
		// ��ȡ�ļ�
		//while (!m_fileOperator.eof())
		while (!feof(m_pFile))
		{
			char szLine[256] = {0};
			//fread(szLine, sizeof(char), sizeof(char) * 256, m_pFile);
			fgets(szLine, sizeof(szLine) - 1, m_pFile);
			if (1 >= strlen(szLine))
			{
				continue;
			}
			Replace(szLine); // ȥ��\n
			//m_fileOperator.getline(szLine, sizeof(char) * 256);

			VRString strLeftNoSpace = Trim(VRString(szLine));
			// �ж��Ƿ�Ϊ����
			if (strLeftNoSpace.empty())
			{
				continue;
			}

			// �ж��Ƿ�Ϊע���� #
			if (strLeftNoSpace[0] == '#')
			{
				continue;
			}

			// ��ȡ����
			if (ReadItemName(strLeftNoSpace, strItemName))
			{
				continue;
			}

			VRString strName, strValues;
			if (!ReadItem(strLeftNoSpace, strName, strValues))
			{
				continue;
			}

			// ��ӵ�����
			AddItem(strItemName, strName, strValues);
		}

		// д����־
		IComManager::GetInstance().WriteLogMsg("��ȡ�����ļ���" + m_strConfigFile + " ���");
	}

	// ��ȡ��Ŀ����
	bool CConfigFile::ReadItemName(const VRString& strText, VRString& strName)
	{
		// �ж��Ƿ���'[ ]'
		int nBeginPos = strText.find_first_of('[');
		int nEndPos = strText.find_last_of(']');

		if ((-1 == nBeginPos) && (-1 == nEndPos) && (nBeginPos <= nEndPos))
		{
			return (false);
		}

		// ��ȡ����
		strName = strText.substr(nBeginPos + 1, nEndPos - 1);

		return (true);
	}

	// ��ȡ��
	bool CConfigFile::ReadItem(const VRString& strText, VRString& strName, VRString& strValue)
	{
		// ��ѯ�Ƿ��С�=��
		int nPos = strText.find('=');
		if (-1 == nPos)
		{
			return (false);
		}

		// ��ȡ�ַ�������
		int nLength = strText.length();
		// ��ȡ����
		strName = strText.substr(0, nPos);
		strValue = strText.substr(nPos + 1,nLength - nPos);

		// �������ո�
		strName = Trim(strName);
		strValue = Trim(strValue);
		return (true);
	}

	// �����
	void CConfigFile::AddItem(const VRString& strName, const VRString& strValueName, const VRString& strValue)
	{
		ITEMVALUE value(strValueName,strValue);
		// ��ѯ�Ƿ���ڵ�ǰ����Ŀ����
		MapStrItem::iterator itor = m_mapStrItem.find(strName);
		if (m_mapStrItem.end() != itor)
		{
			LstItemValue& itemValue = itor->second;
			itemValue.push_back(value);
		}
		else
		{
			// ������ֵ
			LstItemValue itemValue;
			itemValue.push_back(value);
			m_mapStrItem[strName] = itemValue;
		}
	}

	// ȥ�����еĿո�
	VRString CConfigFile::Trim(VRString& strLine) const
	{
		int nPos = strLine.find_last_not_of(g_strSpace);
		VRString str = strLine.erase(strLine.find_last_not_of(g_strSpace) + 1);
		return (str.erase(0, str.find_first_not_of(g_strSpace)));
	}

	// ȥ����ߵĿո�
	VR_Soft::VRString CConfigFile::LeftTrim(VRString& strLine) const
	{
		return (strLine.erase(strLine.find_first_not_of(g_strSpace)));
	}

	// ȥ���ұߵĿո�
	VR_Soft::VRString CConfigFile::RightTrim(VRString& strLine) const
	{
		return (strLine.erase(strLine.find_last_not_of(g_strSpace) + 1));
	}

	void CConfigFile::Replace(char* szLine)
	{
		// �����滻'\n'
		// �����Ƿ����\n
		int nCount = (int)strlen(szLine) - 1;
		char* pLine = szLine + nCount;
		if ('\n' == *pLine)
		{
			*pLine = '\0';
		}	
	}

	// ������ͼ����
	IConfigFile* CreateConfigFileInstance(const VRString& strConfigFile)
	{
		return new CConfigFile(strConfigFile);
	}
}

