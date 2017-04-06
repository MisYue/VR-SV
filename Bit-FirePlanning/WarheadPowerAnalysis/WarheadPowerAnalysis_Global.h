/************************************************
	名称：战斗部威力分析模块导出dll动态库配置文件
	功能：导出dll
	创建人：尹鹏
	创建时间：2015-1-26
	版本：1.0
*************************************************/

#ifndef WARHEADPOWERANALYSIS_GLOBAL_H
#define WARHEADPOWERANALYSIS_GLOBAL_H

#ifdef WARHEADPOWERANALYSIS_EXPORTS
#define WARHEADPOWERANALYSIS_API __declspec(dllexport)
#else
#define WARHEADPOWERANALYSIS_API __declspec(dllimport)
#endif

// 头文件


#endif // WARHEADPOWERANALYSIS_GLOBAL_H
