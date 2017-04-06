/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  雷达接触属性接口												*/
/* 时间： 2015-06-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IBASEELECTATTRIBUTE_H_
#define _PUBLIC_IBASEELECTATTRIBUTE_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IBaseElecAttribute : public  IAttribute
	{
	public: 
		// 析构函数
		virtual ~IBaseElecAttribute(void) { }
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
	};
}

#endif // !_PUBLIC_IBASEELECTATTRIBUTE_H_