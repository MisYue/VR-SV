/************************************************************************
	名称：模块导出dll动态库配置文件
	功能：导出dll
	创建时间：2016-05-17
************************************************************************/



#ifdef BIT_FIREPLANNING_EXPORTS

#define BIT_FIREPLANNING_API __declspec(dllexport)
#else
#define BIT_FIREPLANNING_API __declspec(dllimport)
#endif

