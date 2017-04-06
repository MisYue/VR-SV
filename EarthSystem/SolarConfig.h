#ifndef _COLARCONFIG_H_
#define _COLARCONFIG_H_

#pragma once

namespace VR_Soft
{
	class CSolarConfig : public ISolarConfig
	{
	public:
		explicit CSolarConfig(const VRString& strConfig);
		~CSolarConfig(void);

	public:
		// 获得行星信息
		virtual PTR_Planet GetSolarInfo(const VRString& strPlanetName);
		// 设置

	protected:
		
		
	private:
		typedef std::map<VRString, Planet> MapStrPlanetInfo;
		MapStrPlanetInfo m_mapStrPlanet; // 行星列表
		IConfigFile *m_pIConfig; // 配置文件
	};
}

#endif // _COLARCONFIG_H_