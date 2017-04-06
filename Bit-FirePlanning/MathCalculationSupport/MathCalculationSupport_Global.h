/************************************************************************
	名称：数学计算模块导出dll动态库配置文件 MathcalculationSupport_global
	功能：导出dll
	创建人：徐豫新、尹鹏
	创建时间：2015-1-26
	版本：1.0
************************************************************************/

#ifndef MATHCALCULATIONSUPPORT_GLOBAL_H
#define MATHCALCULATIONSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef MATHCALCULATIONSUPPORT_EXPORTS

#define MATHCALCULATIONSUPPORT_API __declspec(dllexport)
#else
#define MATHCALCULATIONSUPPORT_API __declspec(dllimport)
#endif

// 头文件
#include <tchar.h>
#include <string>
#include <math.h>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

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


#define pi 3.14159265358979323846			//定义Pi值 = 3.1415926
#define radius_earthaverage 6371.004        //定义地球平均半径 = 6371.004，单位：km
#define LongAix_Gobe 6378.137               //定义地球长轴=6378.137，单位：km
#define ShortAix_Gobe 6356.752314           //定义地球短轴=6356.752314，单位：km
//#define MaxNodeInSS 100000                  //定义单个面上的最大节点数
//#define GA 9.80665                          //定义重力加速度 

#endif // MATHCALCULATIONSUPPORT_GLOBAL_H