#ifndef _ISOLARCONFIG_H_
#define _ISOLARCONFIG_H_

namespace VR_Soft
{
	typedef struct PLANETINFO_TYPE
	{
		double dRadius; // �뾶
		VRString strName; // ����
		VRString strTextrue; // ����
	}Planet, *PTR_Planet;


	class OSGEARTH_DLL ISolarConfig : public CSingleton<ISolarConfig>
	{
	public:
		// ���������Ϣ
		virtual PTR_Planet GetSolarInfo(const VRString& strPlanetName) = 0;
	};
};

#endif _ISOLARCONFIG_H_