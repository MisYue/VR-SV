#define VRSOFT_PLUGIN_EXPORT
#include <stdlib.h>
#include "../../Public/VRSoft.h"
#include "TimeConfig.h"

namespace VR_Soft
{
	// 构造函数
	CTimeConfig::CTimeConfig(void):m_pIConfig(NULL)
	{
		// 注册进入管理
		//IConfigManager::GetInstance().AddConfig(this);
	}

	// 析构函数
	CTimeConfig::~CTimeConfig(void)
	{
		VRSOFT_DELETE(m_pIConfig);
	}

	// 获得开始时间
	bool CTimeConfig::GetInitTime(struct tm& t)
	{
		if (NULL == m_pIConfig)
		{
			return (false);
		}
		VRString strInitTime = "initTime";
		VRString strYear = m_pIConfig->GetItemValue(strInitTime, "year");
		VRString strMonth = m_pIConfig->GetItemValue(strInitTime, "month");
		VRString strDay = m_pIConfig->GetItemValue(strInitTime, "day");
		VRString strHour = m_pIConfig->GetItemValue(strInitTime, "hour");
		VRString strMinute = m_pIConfig->GetItemValue(strInitTime, "minute");
		VRString strSeconde = m_pIConfig->GetItemValue(strInitTime, "seconds");

		// 初始化值
		t.tm_year = ConvertFrom(strYear) - 1900;
		t.tm_mon = ConvertFrom(strMonth);
		t.tm_mday = ConvertFrom(strDay);
		t.tm_hour = ConvertFrom(strHour);
		t.tm_min = ConvertFrom(strMinute);
		t.tm_sec = ConvertFrom(strSeconde);

		return (true);
	}

	// 获得加速倍数
	float CTimeConfig::GetMultipeTime(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "multiple");
		return (atof(strMulti.c_str()));
	}

	// 获得加速
	float CTimeConfig::GetQuicken(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "Quicken");
		return (atof(strMulti.c_str()));
	}

	// 获得减速
	float CTimeConfig::GetModerate(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "Moderate");
		return (atof(strMulti.c_str()));
	}

	// 设置配置文件
	void CTimeConfig::SetConfigFile(const VRString& strfile)
	{
		// 创建指针
		m_pIConfig = CreateConfigFileInstance(strfile);
		// 读取配置文件
		m_pIConfig->ReadConfig();
		
	}

	// 保存文件
	bool CTimeConfig::SaveConfigFile(void)
	{
		return (true);
	}

	// String 转 Int
	int CTimeConfig::ConvertFrom(const VRString& str)
	{
		return atoi(str.c_str());
	}

}

