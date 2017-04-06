/********************************************************************
created:	2016/08/20
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	地面人员区域定义

*********************************************************************/

#include "BITTargetModelSupport/Bit_TargetModelSupport_Global.h"

// 单位制度
#include "BITUnitsSupport/Bit_UnitSystem.h"

#ifndef BITGROUNDAREA_H__
#define BITGROUNDAREA_H__

class BITTARGETMODELSUPPORT_API Bit_GroundArea
{
public:
	// 空
	Bit_GroundArea(void);
	// 初始化结构
	Bit_GroundArea( Bit_UnitSystem US , double AreaLength , double AreaWidth
		, double LengthDivideV , double WidthDivideV );
	// 拷贝构造函数
	Bit_GroundArea( const Bit_GroundArea& cGA );
	// 重载等号
	Bit_GroundArea& operator= (const Bit_GroundArea& cGA );
	// 重载“==”等号
	bool operator == (const Bit_GroundArea& cGA )const;
	// 重载“!=”等号
	bool operator != (const Bit_GroundArea& cGA )const;

	~Bit_GroundArea(void);

	// 设置初始化
	void Set_Initial( const Bit_UnitSystem& US , const double& AreaLength 
		, const double& AreaWidth , const double& LengthDivideV , const double & WidthDivideV );
	// 转换单位
	// 三个单位均转换但是不输出
	inline void TransitionUS( const Bit_UnitSystem& NewUS );

	//得到是否定义
	inline bool Get_USDefinition(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;
	// 得到目标区域长度
	inline double Get_AreaLength(void)const;
	// 得到目标区域宽度
	inline double Get_AreaWidth(void)const;
	// 得到长度方向划分值
	inline double Get_LengthDivideV(void)const;
	// 宽度方向划分值
	inline double Get_WidthDivideV(void)const;
private:
	// 单位制
	Bit_UnitSystem US_;
	// 目标区域长度
	double AreaLength_;
	// 目标区域宽度
	double AreaWidth_;
	// 长度方向划分值
	double LengthDivideV_;
	// 宽度方向划分值
	double WidthDivideV_;
	//单位制定义
	bool USDefinition_;
};
#endif
