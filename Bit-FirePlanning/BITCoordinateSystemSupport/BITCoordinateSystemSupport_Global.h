/************************************************************************
	名称：坐标系支持模块导出dll动态库配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-3-20
	版本：1.0
************************************************************************/

#ifndef BITCOORDINATESYSTEMSUPPORT_GLOBAL_H
#define BITCOORDINATESYSTEMSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITCOORDINATESYSTEMSUPPORT_EXPORTS

#define BITCOORDINATESYSTEMSUPPORT_API __declspec(dllexport)
#else
#define BITCOORDINATESYSTEMSUPPORT_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>
#include <string>
#include <math.h>


#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926
//// 定义宽字符等
//#ifdef UNICODE
//typedef wchar_t BITSimChar;
//typedef std::wstring BITSimStr;
//#define BITSimStrlen wcslen  // 取得宽字节字符串中字符长度，不包含 '/0'
//#define BITMemcpy wmemcpy    // 宽字节的拷贝
//#define _T(x) L##x         // 把字符串连起来
//#else
//	
//#endif

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H