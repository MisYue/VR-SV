/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  公共配置类接口		                                        */
/* 时间： 2015-05-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _ICONFIGFILE_H_
#define _ICONFIGFILE_H_

namespace VR_Soft
{
	class VRSOFT_DLL IConfigFile
	{
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
		// 读取文件
		virtual void ReadConfig(void) = 0;
	};

	// 创建配置对象
	EXTERN_CPP VRSOFT_TOOLCLASS_DLL IConfigFile* CreateConfigFileInstance(const VRString& strConfigFile);
}

#endif // _ICONFIGFILE_H_