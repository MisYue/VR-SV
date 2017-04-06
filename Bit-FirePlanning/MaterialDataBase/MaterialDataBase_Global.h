/************************************************
	名称：材料数据库数据结构导出dll动态库配置文件
	功能：导出dll
	创建人：尹鹏
	创建时间：2015-4-11
	版本：1.0
*************************************************/

#ifndef MATERIALDATABASE_GLOBAL_H
#define MATERIALDATABASE_GLOBAL_H


#ifdef MATERIALDATABASE_EXPORTS

#define MATERIALDATABASE_API __declspec(dllexport)
#else
#define MATERIALDATABASE_API __declspec(dllimport)
#endif

//头文件
#include <string>
#include <math.h>

using namespace std;
template class __declspec(dllexport) std::allocator<char>;
template class __declspec(dllexport) std::basic_string<char>;

#endif // MATERIALATTRIBUTE_GLOBAL_H