/************************************************************************
名称：撞击与爆炸分析模块导出dll动态库配置文件 HitAndExplsionPointAnalysis_Glod
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-1-26
	版本：1.0
************************************************************************/



#ifndef HITANDEXPLSIONPOINTANALYSIS_GLOBAL_H
#define HITANDEXPLSIONPOINTANALYSIS_GLOBAL_H

#define HITANDEXPLSIONPOINTANALYSIS_EXPORTS
#ifdef HITANDEXPLSIONPOINTANALYSIS_EXPORTS

#define HITANDEXPLSIONPOINTANALYSIS_API __declspec(dllexport)
#else
#define HITANDEXPLSIONPOINTANALYSIS_API __declspec(dllimport)
#endif

// 头文件
#include <string>

#endif

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

 