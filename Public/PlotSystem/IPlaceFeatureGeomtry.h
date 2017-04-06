/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地标标绘的接口		                                        */
/* 时间： 2016-09-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPLACEFEATUREGEOMTRY_H_
#define _PUBLIC_IPLACEFEATUREGEOMTRY_H_

namespace VR_Soft
{
	class OSGRPLOT_DLL IPlaceFeatureGeomtry : public IFeatureGeomtry
	{
	public:
		// 析构函数
		virtual ~IPlaceFeatureGeomtry(void) { }
		// 设置文字
		virtual void SetText(const VRString& strText) = 0;
		// 设置图标
		virtual void SetIcon(const VRString& strIcon) = 0;
	};
}

#endif // !_PUBLIC_IPLACEFEATUREGEOMTRY_H_