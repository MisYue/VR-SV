#pragma once

#include <fstream>

namespace VR_Soft
{
	typedef struct ITEMVALUE_TYP
	{
		VRString strItem; // ������
		VRString strValue; // ֵ

		ITEMVALUE_TYP(VRString item, VRString value):strItem(item),strValue(value)
		{

		}

		bool operator== (const VRString item)
		{
			return (strItem.compare(item) == 0);
		}

		bool operator== (const VRString item) const
		{
			return (strItem.compare(item) == 0);
		}
	}ITEMVALUE, *PTR_ITEMVALUE;

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
		// ��ȡ�ļ�
		virtual void ReadConfig(void);

	protected:
		typedef std::list<ITEMVALUE> LstItemValue;
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

	private:
		VRString m_strConfigFile; // �����ļ�
		std::ifstream m_fileOperator; // �ļ�������

		MapStrItem m_mapStrItem; // ���Ӧ����
	};

}

