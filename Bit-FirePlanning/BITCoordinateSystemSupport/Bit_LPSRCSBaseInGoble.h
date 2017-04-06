/********************************************************************
created:	2016/03/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	在地球坐标系中的区域平面空间直角坐标系(LocalPlaneSpaceRectangularCoordinates)

*********************************************************************/

// 动态库导出
#include "BITCoordinateSystemSupport_Global.h"

//数学函数坐标
//#include "MathCalculationSupport/CoordinatesPosition.h"
//坐标系描述
#include "Bit_CSWithExpAndUS.h"

#ifndef BITLPSRCSBASEINGOBLE_H__
#define BITLPSRCSBASEINGOBLE_H__

class BITCOORDINATESYSTEMSUPPORT_API Bit_LPSRCSBaseInGoble
{
public:
	//空函数
	Bit_LPSRCSBaseInGoble(void);
	//构造初始化
	Bit_LPSRCSBaseInGoble( Bit_CSWithExpAndUS RCS );
	// 拷贝构造函数
	Bit_LPSRCSBaseInGoble( const Bit_LPSRCSBaseInGoble& cLPSRCS);
	// 重载"="号函数
	Bit_LPSRCSBaseInGoble& operator= (const Bit_LPSRCSBaseInGoble& cLPSRCS );

	~Bit_LPSRCSBaseInGoble(void);

	//通过设置进行坐标系的初始化
	inline void Set_LPSRCSBaseInGoble( const Bit_CSWithExpAndUS& RCS );
	//得到带单位制和坐标描述的坐标系
	inline Bit_CSWithExpAndUS Get_RCSExplainAndUS(void)const;
	//得到带描述直角坐标系
	inline Bit_CSWithExplain Get_RCSExplain(void) const;
	//得到单位制度
	inline Bit_UnitSystem Get_RCSUS(void) const;
	//得到长度单位
	inline double Get_RCSLengthUnit(void)const;
	//得到是否定义了单位
	inline bool Get_IfUS(void)const;
	//根据输入的经度、纬度和高度得到相应的空间坐标(输入坐标长度)
	CoordinatesPosition ComputeRCSOnB_L_H( const double& B , const double& L, const double&H , const double& H_LengthUnit)const;
	//根据输入的经度、纬度和高度得到相应的空间坐标(在该定义坐标系的单位制中)
	CoordinatesPosition ComputeRCSOnB_L_HInUS( const double& B , const double& L, const double&H)const;

private:
	//带描述的直角坐标系
	Bit_CSWithExpAndUS RCS_;
	//判断是否设置了单位系统
	bool IfUS_;
};
#endif
