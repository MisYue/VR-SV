#ifndef _ISOLARCONFIG_H_
#define _ISOLARCONFIG_H_

namespace VR_Soft
{
	typedef struct PLANETINFO_TYPE
	{
		double dRadius; // 半径
		VRString strName; // 名称
		VRString strTextrue; // 纹理
	}Planet, *PTR_Planet;


	class OSGEARTH_DLL ISolarConfig : public CSingleton<ISolarConfig>
	{
	public:
		// 获得行星信息
		virtual PTR_Planet GetSolarInfo(const VRString& strPlanetName) = 0;
	};
};

#endif _ISOLARCONFIG_H_