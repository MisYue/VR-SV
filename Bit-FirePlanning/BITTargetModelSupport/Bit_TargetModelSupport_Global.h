/************************************************************************
	名称：目标模型工程模块导出dll动态库配置文件BITTargetModelSupport
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-4-22
	版本：1.0
************************************************************************/

#ifndef BITTARGETMODELSUPPORT_GLOBAL_H
#define BITTARGETMODELSUPPORT_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITTARGETMODELSUPPORT_EXPORTS

#define BITTARGETMODELSUPPORT_API __declspec(dllexport)
#else
#define BITTARGETMODELSUPPORT_API __declspec(dllimport)
#endif

// 头文件
// #include <tchar.h>


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