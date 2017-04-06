#define VRSOFT_PLUGIN_EXPORT
#include <stdlib.h>
#include "../../Public/VRSoft.h"
#include "TimeConfig.h"

namespace VR_Soft
{
	// ���캯��
	CTimeConfig::CTimeConfig(void):m_pIConfig(NULL)
	{
		// ע��������
		//IConfigManager::GetInstance().AddConfig(this);
	}

	// ��������
	CTimeConfig::~CTimeConfig(void)
	{
		VRSOFT_DELETE(m_pIConfig);
	}

	// ��ÿ�ʼʱ��
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

		// ��ʼ��ֵ
		t.tm_year = ConvertFrom(strYear) - 1900;
		t.tm_mon = ConvertFrom(strMonth);
		t.tm_mday = ConvertFrom(strDay);
		t.tm_hour = ConvertFrom(strHour);
		t.tm_min = ConvertFrom(strMinute);
		t.tm_sec = ConvertFrom(strSeconde);

		return (true);
	}

	// ��ü��ٱ���
	float CTimeConfig::GetMultipeTime(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "multiple");
		return (atof(strMulti.c_str()));
	}

	// ��ü���
	float CTimeConfig::GetQuicken(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "Quicken");
		return (atof(strMulti.c_str()));
	}

	// ��ü���
	float CTimeConfig::GetModerate(void)
	{
		VRString strMulti = m_pIConfig->GetItemValue("multipleTime", "Moderate");
		return (atof(strMulti.c_str()));
	}

	// ���������ļ�
	void CTimeConfig::SetConfigFile(const VRString& strfile)
	{
		// ����ָ��
		m_pIConfig = CreateConfigFileInstance(strfile);
		// ��ȡ�����ļ�
		m_pIConfig->ReadConfig();
		
	}

	// �����ļ�
	bool CTimeConfig::SaveConfigFile(void)
	{
		return (true);
	}

	// String ת Int
	int CTimeConfig::ConvertFrom(const VRString& str)
	{
		return atoi(str.c_str());
	}

}

