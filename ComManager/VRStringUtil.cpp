#include "../../Public/VRSoft.h"
#include <boost/algorithm/string.hpp>

#if (WIN32)
#include <Windows.h>
#endif

namespace VR_Soft
{
	// 构造函数
	CVRStringUtil::CVRStringUtil( void )
	{

	}

	// 析构函数
	CVRStringUtil::~CVRStringUtil()
	{

	}

	// 抓换大写
	VRString CVRStringUtil::ToUpper(VRString& strText )
	{
		boost::algorithm::to_upper(strText);
		return (strText);
	}

	// 转换小写
	VR_Soft::VRString CVRStringUtil::ToLower( VRString& strText )
	{
		boost::algorithm::to_lower(strText);
		return (strText);
	}

	// Unicode转换UTF8编码
	std::string CVRStringUtil::UnicodeToUTF8( const std::wstring &src )
	{
		std::string strResult;
#if (WIN32)
		int n = WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, 0, 0, 0, 0 );
		strResult.resize(n);
		::WideCharToMultiByte( CP_UTF8, 0, src.c_str(), -1, (char*)strResult.c_str(), strResult.length(), 0, 0 );
#endif

		return (strResult);
	}

	std::wstring CVRStringUtil::GB2312ToUnicode( const std::string& src )
	{
		std::wstring wstrResult;
#if (WIN32)
		int n = MultiByteToWideChar( CP_ACP, 0, src.c_str(), -1, NULL, 0 );
		wstrResult.resize(n);
		::MultiByteToWideChar( CP_ACP, 0, src.c_str(), -1, (LPWSTR)wstrResult.c_str(), wstrResult.length());
#endif

		return (wstrResult);
	}

	// GB2312转换UTF8
	std::string CVRStringUtil::GB2312ToUTF8( const std::string& src )
	{
		std::wstring strWideChar = GB2312ToUnicode(src);
		return (UnicodeToUTF8(strWideChar));
	}

}