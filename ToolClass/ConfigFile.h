#pragma once

#include <fstream>

namespace VR_Soft
{
	typedef struct ITEMVALUE_TYP
	{
		VRString strItem; // 项名称
		VRString strValue; // 值

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

		// 打开配置文件
		virtual bool OpenFile(void);
		// 打开配置文件
		virtual bool OpenFile(const VRString& strFile);
		// 关闭文件
		virtual void CloseFile(void);
		// 获取文件名称对应项的值
		virtual VRString GetItemValue(const VRString& strName, const VRString& strItem) const;
		// 读取文件
		virtual void ReadConfig(void);

	protected:
		typedef std::list<ITEMVALUE> LstItemValue;
		typedef std::map<VRString, LstItemValue > MapStrItem;

		// 读取项目名称
		bool ReadItemName(const VRString& strText, VRString& strName);
		// 读取项
		bool ReadItem(const VRString& strText, VRString& strName, VRString& strValue);
		// 添加项
		void AddItem(const VRString& strName, const VRString& strValueName, const VRString& strValue);
		// 去掉所有的空格
		VRString Trim(VRString& strLine) const;
		// 去掉左边的空格
		VRString LeftTrim(VRString& strLine) const;
		// 去掉右边的空格
		VRString RightTrim(VRString& strLine) const;

	private:
		VRString m_strConfigFile; // 配置文件
		std::ifstream m_fileOperator; // 文件操作器

		MapStrItem m_mapStrItem; // 项对应名称
	};

}

