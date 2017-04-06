#include "../../Public/VRSoft.h"
#include "../../Public/SatelliteSystem/SatelliteSystem.h"
#include "SVTle.h"

namespace VR_Soft
{
	CSVTle::CSVTle(const VRString& strName, const VRString& strLine1, const VRString& strLine2)
		:m_strName(strName), m_strLine1(strLine1), m_strLine2(strLine2)
	{
	}


	CSVTle::~CSVTle(void)
	{
	}

	// �������
	VRString & CSVTle::GetName(void)
	{
		return (m_strName);
	}

	// ��õ�һ����
	VRString& CSVTle::GetLine1(void)
	{
		return (m_strLine1);
	}

	// ��ȡ�ڶ�����
	VRString& CSVTle::GetLine2(void)
	{
		return (m_strLine2);
	}

}