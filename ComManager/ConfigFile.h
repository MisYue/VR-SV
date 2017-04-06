#pragma once

#include <fstream>

namespace VR_Soft
{

	class CConfigFile : public IConfigFile
	{
	public:
		explicit CConfigFile(const VRString& strFile);
		explicit CConfigFile(void);
		virtual ~CConfigFile(void);

		// �������ļ�
		virtual bool OpenFile(void);
		// �������ļ�
		virtual bool OpenFile(const VRString& strFile);
		// �ر��ļ�
		virtual void CloseFile(void);
		// ��ȡ�ļ����ƶ�Ӧ���ֵ
		virtual VRString GetItemValue(const VRString& strName, const VRString& strItem) const;
		// ���һ�����µ�������Ŀ
		virtual const LstItemValue& GetItemValus(const VRString& strName) const ;
		// ��ȡ�ļ�
		virtual void ReadConfig(void);

	protected:
		typedef std::map<VRString, LstItemValue > MapStrItem;

		// ��ȡ��Ŀ����
		bool ReadItemName(const VRString& strText, VRString& strName);
		// ��ȡ��
		bool ReadItem(const VRString& strText, VRString& strName, VRString& strValue);
		// �����
		void AddItem(const VRString& strName, const VRString& strValueName, const VRString& strValue);
		// ȥ�����еĿո�
		VRString Trim(VRString& strLine) const;
		// ȥ����ߵĿո�
		VRString LeftTrim(VRString& strLine) const;
		// ȥ���ұߵĿո�
		VRString RightTrim(VRString& strLine) const;
		void Replace(char* szLine);
	private:
		VRString m_strConfigFile; // �����ļ�
		// std::ifstream m_fileOperator; // �ļ�������
		FILE* m_pFile; // �ļ����

		MapStrItem m_mapStrItem; // ���Ӧ����
	};

}

