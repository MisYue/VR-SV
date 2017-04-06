/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  字符串操作单元		                                        */
/* 时间： 2016-07-09                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_VRSTRINGUTIL_H_
#define _PUBLIC_VRSTRINGUTIL_H_

#include <boost/lexical_cast.hpp>

namespace VR_Soft
{
	class VRSOFT_DLL CVRStringUtil
	{
	public: 
		// 构造函数
		explicit CVRStringUtil(void);
		// 析构函数
		virtual ~CVRStringUtil();
		// 字符串转换成数字
		template <typename T>
		static T StringToNumber(const VRString& str)
		{
			try
			{
				T value =  boost::lexical_cast<T>(str.c_str());
				return (value);
			}
			catch (...)
			{
				const VRString strTypeName(typeid(T).name());
				IComManager::GetInstance().WriteLogMsg("字符串数据类型转换" + strTypeName + "失败;StringToNumber", ERROR_CONVER_FAILD);

			}	

			return (T());
		}
		// 抓换大写
		static VRString ToUpper( VRString& strText );
		// 转换小写
		static VRString ToLower( VRString& strText );
		// Unicode转换UTF8编码
		static std::string UnicodeToUTF8(const std::wstring &src);
		// GB2312转换Unicode编码
		static std::wstring GB2312ToUnicode(const std::string& src);
		// GB2312转换UTF8
		static std::string GB2312ToUTF8(const std::string& src);
	};
}

#endif // !_PUBLIC_VRSTRINGUTIL_H_