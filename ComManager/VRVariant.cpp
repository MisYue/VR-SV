#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	CVRVariant::CVRVariant(void)
		:m_pValue(NULL)  
	{
	}

	CVRVariant::CVRVariant(CVRVariant& ma)  
		:m_pValue(ma.IsEmpty()?NULL:ma.m_pValue->Clone())  
	{  

	}  

	

	// ��������
	CVRVariant& CVRVariant::Swap( CVRVariant& ma )
	{
		//������������ĵ�ַ�����������������ͷ��ڴ棬���Ч��  
		std::swap( ma.m_pValue, m_pValue);  
		return *this; 
	}

	// �Ƿ�Ϊ��
	bool CVRVariant::IsEmpty()
	{
		return !m_pValue;
	}
}

