/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  雷达接触属性类												*/
/* 时间： 2015-06-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _BASEELECATTRIBUTE_H_
#define _BASEELECATTRIBUTE_H_

#pragma once

namespace VR_Soft
{
	class CBaseElecAttribute : public CAttributeImp<IBaseElecAttribute>
	{
	public:
		// 构造函数
		explicit CBaseElecAttribute(void);
		// 析构函数
		virtual ~CBaseElecAttribute(void);

	public:
		// 设置半径
		virtual void SetRadius(float fRaius) = 0;
		// 获得半径
		virtual float GetRadius(void) const = 0;
		// 设置扫描速度
		virtual void SetScanSpeed(float fSpeed) = 0;
		// 获得扫描速度
		virtual float GetScanSpeed(void) const = 0;
		// 设置渲染模式
		virtual void SetDrawMode(const DrawMode dm) = 0;
		// 获得渲染模式
		virtual DrawMode GetDrawMode(void) const = 0;
		// 设置网格数
		virtual void SetWireframeCount(int nCount) = 0;
		// 设置网格数
		virtual int GetWireframeCount(void) const = 0;
		// 设置扫描开关
		virtual void SetScanState(bool bOpen) = 0;
		// 获得扫描开关
		virtual bool GetScanState(void) const = 0;

	private:
		double m_dRadius; // 半径
		float m_fSpeed; // 扫描速度
		DrawMode m_dm; // 渲染模式
		int m_nFrameCount; // 细分个数
		bool m_bOpen; // 扫描开关
	};

}

#endif // !_BASEELECATTRIBUTE_H_