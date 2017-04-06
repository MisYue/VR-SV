/************************************************
	名称：战斗部数据库数据结构导出dll动态库配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-2-23
	版本：1.0
*************************************************/

#ifndef WARHEADDATABASE_GLOBAL_H
#define WARHEADDATABASE_GLOBAL_H

#ifdef WARHEADDATABASE_EXPORTS
#define WARHEADDATABASE_API __declspec(dllexport)
#else
#define WARHEADDATABASE_API __declspec(dllimport)
#endif

// 头文件
// 头文件
#include <tchar.h>
#include <string>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif // WARHEADDATABASE_GLOBAL_H
