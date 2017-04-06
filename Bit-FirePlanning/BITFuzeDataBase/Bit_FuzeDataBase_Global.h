/************************************************************************
	名称：弹药用引信息导出配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-8-21
	版本：1.0
************************************************************************/

#ifndef BITFUZEDATABASE_GLOBAL_H
#define BITFUZEDATABASE_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITFUZEDATABASE_EXPORTS

#define BITFUZEDATABASE_API __declspec(dllexport)
#else
#define BITFUZEDATABASE_API __declspec(dllimport)
#endif

// 头文件
//#include "math.h"
#include <string>

#endif 