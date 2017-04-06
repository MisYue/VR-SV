//#pragma once

/********************************************************************
created:	2016/06/02
 
file base:	BIT_DAMAGESIMULATION_API
file ext:	h
author:		Xuyuxin

purpose:	为金属材料数据库提供数据结构

*********************************************************************/

#ifndef BITMETALDATA_H__
#define BITMETALDATA_H__

// 动态库
#include "MaterialDataBase_Global.h"
// 单位制
#include "BITUnitsSupport/Bit_UnitSystem.h"
// 硬度
#include "Bit_Hardness.h"

class MATERIALDATABASE_API Bit_MetalData
{
public:
	// 空函数
	Bit_MetalData(void);
	// 构造初始化函数
	Bit_MetalData( Bit_UnitSystem US , string MMId , string MMaterialName
		, string MMaterialClass , double MMaterialDensity ,double CompressYieldStrength[2] 
		, double DrawYieldStrength[2] , double CompressLimitationStrength[2] 
		, double DrawLimitationStrength[2] , Bit_Hardness MHard , double DrawElongation[2] 
		, double DrawSectionShrinkage[2] , double YoungModulus[2] , double YawTangestModulus[2] 
		, double CompressionModulus[2] , double CompressionTangestModulus[2] , double PoissonRatio );
	// 拷贝构造函数
	Bit_MetalData( const Bit_MetalData& cMD );
	// 重载“=”
	Bit_MetalData& operator= (const Bit_MetalData& cMD );
	// 重载“==”
	bool operator == (const Bit_MetalData& cMD )const;

	// 初始化函数
	~Bit_MetalData(void);

	//初始化设置
	void Set_Initial( const Bit_UnitSystem& US , const string& MMId 
		, const string& MMaterialName , const string& MMaterialClass 
		, const double& MMaterialDensity , const double CompressYieldStrength[2] 
		, const double DrawYieldStrength[2] , const double CompressLimitationStrength[2] 
		, const double DrawLimitationStrength[2] , const Bit_Hardness& MHard 
		, const double DrawElongation[2] , const double DrawSectionShrinkage[2] 
		, const double YoungModulus[2] , const double YawTangestModulus[2] 
		, const double CompressionModulus[2] , const double CompressionTangestModulus[2]
		, const double PoissonRatio );

	//得到是否定义
	inline bool Get_IfDefinition(void)const;
	// 得到单位系
	inline Bit_UnitSystem Get_US(void)const;
	// 得到材料编号
	inline string Get_MMId(void)const;
	// 得到材料名称
	inline string Get_Name(void)const;
	// 得到材料大类
	inline string Get_Class(void)const;
	// 得到材料密度（当前单位制）
	inline double Get_Density(void)const;
	// 得到材料密度(mm-g-us)
	inline double Get_DensityForC(void)const;
	// 得到压缩强度的应变率（当前单位制）
	inline double Get_CompressYieldStrength_SR(void)const;
	// 得到压缩强度（当前单位制）
	inline double Get_CompressYieldStrength_St(void)const;
	// 得到压缩强度及应变率（当前单位制）
	void Get_CompressYieldStrength( double *SR , double *St )const;

	// 得到拉伸极限强度的应变率（当前单位制）
	inline double Get_DrawLimitationStrength_SR(void)const;
	// 得到拉伸极限强度（当前单位制）
	inline double Get_DrawLimitationStrength_St(void)const;

	//得到硬度
	inline Bit_Hardness Get_MHard(void)const;

	//得到拉伸延伸率的应变率（当前单位制）
	inline double Get_DrawElongation_SR(void)const;
	//得到拉伸延伸率
	inline double Get_DrawElongation_Value(void)const;

	//得到拉伸断面收缩率应变率（当前单位制）
	inline double Get_DrawSectionShrinkage_SR(void)const;
	//得到拉伸断面收缩率
	inline double Get_DrawSectionShrinkage_Value(void)const;

	//得到杨氏模量应变率（当前单位制）
	inline double Get_YoungModulus_SR(void)const;
	//得到杨氏模量
	inline double Get_YoungModulus_Value(void)const;

	//得到拉伸切线模量应变率（当前单位制）
	inline double Get_YawTangestModulus_SR(void)const;
	//得到拉伸切线模量
	inline double Get_YawTangestModulus_Value(void)const;

	//得到压缩模量应变率（当前单位制）
	inline double Get_CompressionModulus_SR(void)const;
	//得到压缩模量
	inline double Get_CompressionModulus_Value(void)const;

	//压缩切线模量应变率（当前单位制）
	inline double Get_CompressionTangestModulus_SR(void)const;
	//得到压缩模量
	inline double Get_CompressionTangestModulus_Value(void)const;

	//得到泊松比
	inline double Get_PoissonRatio(void)const;

	// 所有数据转换到新的单位制中


	//计算得到拉伸屈强比

	// double
private:
	// 单位系
	Bit_UnitSystem US_;
	//(金属材料号，对材料库)
	string MMId_;
	//材料名称
	string MMaterialName_;
	//材料大类
	string MMaterialClass_;
	//材料密度
	double MMaterialDensity_;
	//压缩屈服强度(带应变率)
	double CompressYieldStrength_[2];
	//拉伸屈服强度(带应变率)
	double DrawYieldStrength_[2];
	//压缩极限强度(带应变率)
	double CompressLimitationStrength_[2];
	//拉伸极限强度(带应变率)
	double DrawLimitationStrength_[2];
	//硬度
	Bit_Hardness MHard_;
	//拉伸延伸率
	double DrawElongation_[2];
	//拉伸断面收缩率
	double DrawSectionShrinkage_[2];
	//杨氏模量
	double YoungModulus_[2];
	//拉伸切线(tangent modulus)模量
	double YawTangestModulus_[2];
	//压缩模量
	double CompressionModulus_[2];
	//压缩切线模量
	double CompressionTangestModulus_[2];
	//泊松比
	double PoissonRatio_;
	//是否定义
	bool IfDefinition_;
};
#endif
