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
		// ���������Ϣ
		virtual PTR_Planet GetSolarInfo(const VRString& strPlanetName);
		// ����

	protected:
		
		
	private:
		typedef std::map<VRString, Planet> MapStrPlanetInfo;
		MapStrPlanetInfo m_mapStrPlanet; // �����б�
		IConfigFile *m_pIConfig; // �����ļ�
	};
}

#endif // _COLARCONFIG_H_