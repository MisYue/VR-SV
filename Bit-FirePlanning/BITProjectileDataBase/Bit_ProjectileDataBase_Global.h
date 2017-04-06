/************************************************************************
	名称：弹药信息导出配置文件
	功能：导出dll
	创建人：徐豫新
	创建时间：2016-8-21
	版本：1.0
************************************************************************/

#ifndef BITPROJECTILEDATABASE_GLOBAL_H
#define BITPROJECTILEDATABASE_GLOBAL_H

//#define MATHCALCULATIONSUPPORT_EXPORTS
#ifdef BITPROJECTILEDATABASE_EXPORTS

#define BITPROJECTILEDATABASE_API __declspec(dllexport)
#else
#define BITPROJECTILEDATABASE_API __declspec(dllimport)
#endif

// 头文件
//#include "math.h"
#include <string>

#endif 