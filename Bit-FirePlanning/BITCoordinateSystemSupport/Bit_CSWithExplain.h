/********************************************************************
created:	2015/03/03
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	带说明坐标系定义

*********************************************************************/

#ifndef BITCSWITHEXPLAIN_H__
#define BITCSWITHEXPLAIN_H__

// 动态库导出
#include "BITCoordinateSystemSupport_Global.h"
// 坐标系
#include "CoordinateSystem.h"

class BITCOORDINATESYSTEMSUPPORT_API Bit_CSWithExplain
{
public:
	// 空函数
	Bit_CSWithExplain(void);
	// 构造带说明坐标系
	Bit_CSWithExplain( int CSId , string Name , CoordinateSystem CS , string Explain );
	// 拷贝构造函数
	Bit_CSWithExplain( const Bit_CSWithExplain& cCSExplain);
	// 重载"="号
	Bit_CSWithExplain& operator= (const Bit_CSWithExplain& cCSExplain );
	// 重载"=="号
	bool operator == (const Bit_CSWithExplain& cCSExplain )const;

	//设置四个变量
	inline void Set_Initial( const int& CSId , const string& Name , const CoordinateSystem& CS , const string& Explain );
	//设置坐标系编号
	inline void Set_CSId( const int& CSId );
	//得到坐标系Id
	inline int Get_CSId(void) const;
	//得到坐标系名字
	inline string Get_Name(void) const;
	//得到坐标系
	inline CoordinateSystem Get_CS(void) const;
	//得到说明
	inline string Get_Explain(void) const;


	~Bit_CSWithExplain(void);

private:
	int CSId_;
	string Name_;
	string Explain_;
	CoordinateSystem CS_;
	
};
#endif
