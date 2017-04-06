/********************************************************************
created:	2015/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	带说明和单位制的直角坐标系定义

*********************************************************************/

#ifndef BITCSWITHEXPANDUS_H__
#define BITCSWITHEXPANDUS_H__

// 动态库导出
#include "BITCoordinateSystemSupport_Global.h"
// 坐标系
#include "BITUnitsSupport\Bit_UnitSystem.h"
// 坐标系描述
#include "Bit_CSWithExplain.h"


class BITCOORDINATESYSTEMSUPPORT_API Bit_CSWithExpAndUS
{
public:
	// 空
	Bit_CSWithExpAndUS(void);
	// 初始化方法1
	Bit_CSWithExpAndUS( Bit_CSWithExplain RCSExplain , Bit_UnitSystem US );
	// 构造初始化方法2
	Bit_CSWithExpAndUS( int CSId , string Name , CoordinateSystem CS , string Explain , Bit_UnitSystem US );

	// 拷贝构造函数
	Bit_CSWithExpAndUS( const Bit_CSWithExpAndUS& cCSExplainUS);
	// 重载"="号
	Bit_CSWithExpAndUS& operator= (const Bit_CSWithExpAndUS& cCSExplainUS );
	// 重载"=="号
	bool operator == (const Bit_CSWithExpAndUS& cCSExplainUS )const;


	~Bit_CSWithExpAndUS(void);

	//设置初始参数
	void Set_Initial( const int& CSId , const string& Name , const CoordinateSystem& CS , 
		const string& Explain , const Bit_UnitSystem& US );
	//设置单位制度
	inline void Set_US(const Bit_UnitSystem& US );
	//设置坐标系编号
	inline void Set_CSId( const int& CSId );

	//得到带描述的直角坐标系
	inline Bit_CSWithExplain Get_RCSExplain(void) const;
	//得到坐标系编号
	inline int Get_CSId(void) const;
	//得到坐标系名字
	inline string Get_Name(void) const;
	//得到坐标系说明
	inline string Get_Explain(void) const;
	//得到单位制
	inline Bit_UnitSystem Get_US(void) const;
	//得到长度单位
	inline double Get_LengthUnit(void) const; 
	
private:
	//带描述的直角坐标系
	Bit_CSWithExplain RCSExplain_;
	//坐标系
	Bit_UnitSystem US_;
};
#endif
