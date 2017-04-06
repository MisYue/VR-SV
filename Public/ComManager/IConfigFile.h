/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  公共配置类接口		                                        */
/* 时间： 2015-05-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ICONFIGFILE_H_
#define _ICONFIGFILE_H_

#include <list>

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

	class VRSOFT_DLL IConfigFile
	{
	public:
		typedef std::list<ITEMVALUE> LstItemValue;
	public:
		// 析构函数
		virtual ~IConfigFile() { }
		// 打开配置文件
		virtual bool OpenFile(void) = 0;
		// 打开配置文件
		virtual bool OpenFile(const VRString& strFile) = 0;
		// 关闭文件
		virtual void CloseFile(void) = 0;
		// 获取文件名称对应项的值
		virtual VRString GetItemValue(const VRString& strName, const VRString& strItem) const = 0;
		// 获得一个项下的所有项目
		virtual const LstItemValue& GetItemValus(const VRString& strName) const = 0;
		// 读取文件
		virtual void ReadConfig(void) = 0;
	};

	// 创建配置对象
	EXTERN_CPP VRSOFT_DLL IConfigFile* CreateConfigFileInstance(const VRString& strConfigFile);
}

#endif // _ICONFIGFILE_H_